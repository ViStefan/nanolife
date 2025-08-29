#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include "johnson_trotter.h"

#define THREADS 8

typedef struct
{
    permutation *perm;
    int threads;
    void (*callback)(permutation *p);
} thread_data;


void *permutate_thread(void *t)
{
    thread_data *td = ((thread_data*) t);
    permutation *p = td->perm;

    while (p->step <= p->size)
    {
        td->callback(p);
        for (int i = 0; i < td->threads; ++i)
            next(p);

    } 

    return NULL;
}

void permutate(int number, int threads, void (*callback)(permutation *p))
{
    thread_data td[threads];
    pthread_t pthreads[threads];

    for (int i = 0; i < threads; ++i)
    {
        td[i].callback = callback;
        td[i].threads = threads;
        td[i].perm = init(number);
        for (int j = 0; j < i; ++j)
            next(td[i].perm);
        pthread_create(&pthreads[i], NULL, permutate_thread, &td[i]);
    }

    for (int i = 0; i < threads; ++i) {
        pthread_join(pthreads[i], NULL);
        free_permutation(td[i].perm);
    }
}

void usage(char **argv)
{
    printf("%s NUM\n", argv[0]);
    printf("\tNUM - sane number of elements to permutate\n");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        usage(argv);
        return 1;
    }

    char *end;
    unsigned long num = strtoul(argv[1], &end, 10);

    if (*end != '\0' || errno == ERANGE)
    {
        usage(argv);
        return 2;
    }

    permutate(num, THREADS, &print);

    return 0;
}
