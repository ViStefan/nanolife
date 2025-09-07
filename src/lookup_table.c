#include <stdlib.h>
#include <pthread.h>
#include "lookup_table.h"
#include "map.h"
#include "life.h"

#define THREADS 4

typedef struct
{
    lookup_table_t *table;
    unsigned long long start;
    unsigned long long stop;
} thread_data;

void *generate_table_thread(void *t)
{
    thread_data *td = ((thread_data *)t);

    for (unsigned long long i = td->start; i <= td->stop; ++i)
        td->table->table[i] = life_chunk(i, td->table->map);

    return NULL;
}

lookup_table_t *generate_table(map_t *m)
{
    lookup_table_t *table = malloc(sizeof(lookup_table_t));
    table->map = m;
    table->size = 1 << (m->width * m->height);
    table->outcome_size = (m->width - 2) * (m->height - 2);
    table->table = malloc(sizeof(int) * table->size);

    int chunk_size = table->size / THREADS;

    pthread_t pthreads[THREADS];
    thread_data td[THREADS];

    for (int i = 0; i < THREADS; ++i)
    {
        td[i].table = table;
        td[i].start = i * chunk_size;
        td[i].stop = (i + 1) * chunk_size;
    }

    td[THREADS - 1].stop = table->size;

    for (int i = 0; i < THREADS; ++i)
        pthread_create(&pthreads[i], NULL, generate_table_thread, &td[i]);

    for (int i = 0; i < THREADS; ++i)
        pthread_join(pthreads[i], NULL);

    return table;
}

void free_lookup_table(lookup_table_t *t)
{
    free(t->table);
    free(t);
}

size_t count_monotone(lookup_table_t *table)
{
    int prev = table->table[0];
    size_t n = 1;
    for (size_t i = 1; i < table->size; ++i)
        if (table->table[i] != prev)
        {
            prev = table->table[i];
            ++n;
        }

    return n;
}
