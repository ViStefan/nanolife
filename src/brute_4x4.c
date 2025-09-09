#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "johnson_trotter.h"
#include "lookup_table.h"
#include "utils.h"

#define SLEEP 10

enum AGGREGATION
{
    MIN,
    ALL
};

void usage(char **argv, int status)
{
    printf("usage: %s SIZE THREADS\n", argv[0]);
    printf("\tSIZE\tnumber 'N' or pair 'WxH' for square or rectangle correspondingly\n");
    printf("\tTHREADS\tnumber of parallel threads\n");
    printf("\tAGGREGATION\tsupject to print, one of min|all\n");
    exit(status);
}

typedef struct {
    map_t *m;
    permutation_t *p;
    unsigned long long start;
    unsigned long long stop;
    int *minimum;
    pthread_mutex_t *minimum_mutex;
    int threads;
    enum AGGREGATION aggr;
    unsigned long long *progress;
    unsigned long long max_progress;
} thread_data;

void *progress_thread(void *t)
{
    int time = 0;
    thread_data *td = ((thread_data *)t);

    while (*td->progress < td->max_progress)
    {
        sleep(SLEEP);
        ++time;
        int percent = *td->progress * 100 / td->max_progress;
        int speed = *td->progress / (time * SLEEP);
        int approx = (td->max_progress - *td->progress) / speed;
        int sec = approx % 60;
        int min = (approx / 60) % 60;
        int hour = (approx / 3600);
        fprintf(stderr, "%d%%, %dh %dmin %ds left\n", percent, hour, min, sec);
    }

    return NULL;
}

void *brute_thread(void *t)
{
    thread_data *td = ((thread_data *)t);

    for (unsigned long long i = td->start; i < td->stop; ++i)
    {
        bool should_print = false;
        td->m->value = td->p->value;
        lookup_table_t *table = generate_table(td->m, 1);
        int c = count_monotone(table, (size_t)td->minimum);
        if (td->aggr == MIN)
        {
            pthread_mutex_lock(td->minimum_mutex);
            if (c < *td->minimum)
            {
                *td->minimum = c;
                should_print = true;
            }
            pthread_mutex_unlock(td->minimum_mutex);
        }
        if (should_print || td->aggr == ALL)
        {
            char *s = permutation_serialize(td->p);
            printf("%d : %s\n", c, s);
            free(s);
        }
        free_lookup_table(table);
        *td->progress += 1;

        int status = permutation_next(td->p, td->threads);

        if (status == PERMUTATION_OVERFLOW)
            break;
    }

    free_permutation(td->p);

    return NULL;
}

int bruteforce(int width, int height, int threads, enum AGGREGATION aggr) {
    int result = INT_MAX;
    unsigned long long progress = 0;

    const unsigned long long aligned_size = factorial(width * height) + threads;
    printf("aligned size: %llu\n", aligned_size);
    const unsigned long long chunk_size = aligned_size / threads;

    pthread_t pthreads[threads];
    thread_data td[threads];
    map_t m[threads];
    permutation_t *p[threads];

    pthread_mutex_t minimum;
    pthread_mutex_init(&minimum, NULL);

    for (int i = 0; i < threads; ++i)
    {
        m[i].height = width;
        m[i].width = height;
        p[i] = permutation_init(m[i].width * m[i].height);
        permutation_next(p[i], i);
        td[i].m = &m[i];
        td[i].p = p[i];
        td[i].threads = threads;
        td[i].aggr = aggr;
        td[i].start = i * chunk_size;
        td[i].stop = (i == threads - 1) ? aligned_size : ((i + 1) * chunk_size);
        td[i].minimum = &result;
        td[i].minimum_mutex = &minimum;
        td[i].max_progress = aligned_size;
        td[i].progress = &progress;
        pthread_create(&pthreads[i], NULL, brute_thread, &td[i]);
    }
    
    pthread_t progress_pt;
    pthread_create(&progress_pt, NULL, progress_thread, &td[0]);
    pthread_detach(progress_pt);

    for (int i = 0; i < threads; ++i)
        pthread_join(pthreads[i], NULL);

    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 4)
        usage(argv, 1);

    int width, height;
    char *end;
    width = height = (size_t)strtoul(argv[1], &end, 10);
    if (errno == ERANGE)
        usage(argv, 2);
    if (*end == 'x')
    {
        height = (size_t)strtoul(end + 1, &end, 10);
        if (errno == ERANGE || *end != '\0')
            usage(argv, 3);
    }
    else if (*end != '\0')
        usage(argv, 4);

    int threads = strtoul(argv[2], &end, 10);
    if (errno == ERANGE || *end != '\0')
        usage(argv, 5);

    enum AGGREGATION aggr = MIN;
    if (!strcmp(argv[3], "all"))
        aggr = ALL;
    else if (!strcmp(argv[3], "min"))
        aggr = MIN;
    else
        usage(argv, 6);

    bruteforce(width, height, threads, aggr);
}
