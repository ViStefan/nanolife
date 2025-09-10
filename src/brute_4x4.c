#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#include "johnson_trotter.h"
#include "lookup_table.h"
#include "utils.h"
#include "args.h"

#define AGGREGATION(F) \
    F(MIN), \
    F(ALL)

ENUM(AGGREGATION)

void usage(char *name)
{
    printf("usage: %s SIZE THREADS AGGREGATION\n", name);
    printf("\tSIZE\tnumber 'N' or pair 'WxH' for square or rectangle correspondingly\n");
    printf("\tTHREADS\tnumber of parallel threads\n");
    printf("\tAGGREGATION\tsupject to print, one of MIN|ALL\n");
}

typedef struct {
    map_t *m;
    permutation_t *p;
    lookup_table_t *normal;
    unsigned long long start;
    unsigned long long stop;
    int *minimum;
    pthread_mutex_t *minimum_mutex;
    int threads;
    enum AGGREGATION aggr;
    unsigned long long *progress;
} thread_data;

typedef struct {
    int sleep;
    unsigned long long *progress;
    unsigned long long max_progress;
} progress_data;

void *progress_thread(void *t)
{
    int time = 0;
    progress_data *pd = ((progress_data*)t);

    while (*pd->progress < pd->max_progress)
    {
        sleep(pd->sleep);
        ++time;
        int percent = *pd->progress * 100 / pd->max_progress;
        int speed = *pd->progress / (time * pd->sleep);
        int approx = (pd->max_progress - *pd->progress) / speed;
        int sec = approx % 60;
        int min = (approx /= 60) % 60;
        int hour = (approx /= 60);
        if (hour != 0)
            fprintf(stderr, "%d%%, %dh %dmin %ds left\n", percent, hour, min, sec);
        else if (min != 0)
            fprintf(stderr, "%d%%, %dmin %ds left\n", percent, min, sec);
        else
            fprintf(stderr, "%d%%, %ds left\n", percent, sec);
    }

    return NULL;
}

void *brute_thread(void *t)
{
    thread_data *td = ((thread_data *)t);

    for (unsigned long long i = td->start; i < td->stop; ++i)
    {
        bool should_print = false;
        // TODO: is it necessary?
        // TODO: should move default initialization to map?
        // TODO: how to continue permutation if broke? store step number?
        td->m->value = td->p->value;
        map_init_blocks(td->m);
        lookup_table_t *table = generate_table(td->m, 1, td->normal);
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
        map_free_blocks(td->m);
        *td->progress += 1;

        int status = permutation_next(td->p, td->threads);

        if (status == PERMUTATION_OVERFLOW)
            break;
    }

    free_permutation(td->p);

    return NULL;
}

int bruteforce(int width, int height, int threads, enum AGGREGATION aggr) {
    int minimum = INT_MAX;
    unsigned long long progress = 0;

    const unsigned long long aligned_size = factorial(width * height) + threads;
    const unsigned long long chunk_size = aligned_size / threads;

    pthread_t pthreads[threads];
    thread_data td[threads];
    map_t m[threads];
    permutation_t *p[threads];

    pthread_mutex_t minimum_mutex;
    pthread_mutex_init(&minimum_mutex, NULL);

    map_t normal_map;
    normal_map.width = width;
    normal_map.height = height;
    permutation_t *normal_permutation = permutation_init(normal_map.width * normal_map.height);
    normal_map.value = normal_permutation->value;

    lookup_table_t *normal = generate_table(&normal_map, threads, NULL);

    for (int i = 0; i < threads; ++i)
    {
        m[i].height = width;
        m[i].width = height;
        td[i].m = &m[i];

        p[i] = permutation_init(m[i].width * m[i].height);
        permutation_next(p[i], i);
        td[i].p = p[i];

        td[i].normal = normal;

        td[i].threads = threads;
        td[i].start = i * chunk_size;
        td[i].stop = (i == threads - 1) ? aligned_size : ((i + 1) * chunk_size);

        td[i].aggr = aggr;
        td[i].minimum = &minimum;
        td[i].minimum_mutex = &minimum_mutex;

        td[i].progress = &progress;

        pthread_create(&pthreads[i], NULL, brute_thread, &td[i]);
    }
    
    pthread_t progress_pt;
    progress_data pd;
    pd.max_progress = aligned_size;
    pd.progress = &progress;
    pd.sleep = (aligned_size < 1000000) ? 1 : 10;

    pthread_create(&progress_pt, NULL, progress_thread, &pd);
    pthread_detach(progress_pt);

    for (int i = 0; i < threads; ++i)
    {
        pthread_join(pthreads[i], NULL);
        free_permutation(p[i]);
    }

    free_lookup_table(normal);

    return 0;
}

int main(int argc, char **argv)
{
    ARGS_INIT(argc, argv, 3)
    PARSE_PAIR(width, height)
    PARSE_UINT(threads)
    PARSE_ENUM(AGGREGATION, aggr)

    bruteforce(width, height, threads, aggr);
}
