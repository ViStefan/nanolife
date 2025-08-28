#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "johnson_trotter.h"
#include "lookup_table.h"

// TODO: parametrize
#define THREADS 8
#define WIDTH 3
#define HEIGHT 3

typedef struct {
    map *m;
    permutation *p;
    int start;
    int stop;
} thread_data;

void *brute_thread(void *t)
{
    thread_data *td = ((thread_data *)t);

    for (int i = td->start; i <= td->stop; ++i)
    {
        td->m->value = td->p->value;
        int c = count_monotone(td->m);
        char *s = serialize(td->p);
        printf("%d : %s\n", c, s);
        free(s);

        int status;
        for (int j = 0; j < THREADS; ++j)
            status = next(td->p);

        if (status == PERMUTATION_OVERFLOW)
            break;
    }

    free_permutation(td->p);

    return NULL;
}

int main(int argc, char **argv) {
    int aligned_size = factorial(WIDTH * HEIGHT) + THREADS;
    const int chunk_size = aligned_size / THREADS;

    pthread_t pthreads[THREADS];
    thread_data td[THREADS];
    map m[THREADS];
    permutation *p[THREADS];

	for (int i = 0; i < THREADS; ++i)
    {
        m[i].height = WIDTH;
        m[i].width = HEIGHT;
        p[i] = init(m[i].width * m[i].height);
        for (int j = 0; j < i; ++j)
            next(p[i]);
        td[i].m = &m[i];
        td[i].p = p[i];
        td[i].start = i * chunk_size;
        td[i].stop = (i == THREADS - 1) ? aligned_size - 1 : ((i + 1) * chunk_size - 1);
        pthread_create(&pthreads[i], NULL, brute_thread, &td[i]);
    }

	for (int i = 0; i < THREADS; ++i)
        pthread_join(pthreads[i], NULL);

    return 0;
}
