#include <stdlib.h>
#include <pthread.h>
#include "lookup_table.h"
#include "map.h"
#include "life.h"

typedef struct
{
    lookup_table_t *table;
    lookup_table_t *normal;
    unsigned long long start;
    unsigned long long stop;
} thread_data;

void *generate_table_thread(void *t)
{
    thread_data *td = ((thread_data *)t);

    if (td->normal == NULL)
        for (unsigned long long i = td->start; i <= td->stop; ++i)
            td->table->table[i] = life_chunk(i, td->table->map);
    else
        for (unsigned long long i = td->start; i < td->stop; ++i)
            td->table->table[i] = td->normal->table[normalize_bits(i, td->table->map)];

    return NULL;
}

lookup_table_t *generate_table(map_t *m, int threads, lookup_table_t *normal)
{
    lookup_table_t *table = malloc(sizeof(lookup_table_t));
    table->map = m;
    table->size = 1 << (m->width * m->height);
    table->outcome_size = (m->width - 2) * (m->height - 2);
    table->table = malloc(sizeof(int) * table->size);

    int chunk_size = table->size / threads;

    pthread_t pthreads[threads];
    thread_data td[threads];

    for (int i = 0; i < threads; ++i)
    {
        td[i].table = table;
        td[i].normal = normal;
        td[i].start = i * chunk_size;
        td[i].stop = (i + 1) * chunk_size;
    }

    td[threads - 1].stop = table->size;

    if (threads > 1)
    {
        for (int i = 0; i < threads; ++i)
            pthread_create(&pthreads[i], NULL, generate_table_thread, &td[i]);

        for (int i = 0; i < threads; ++i)
            pthread_join(pthreads[i], NULL);
    }
    else
        generate_table_thread((void *)&td[0]);

    return table;
}

void free_lookup_table(lookup_table_t *t)
{
    free(t->table);
    free(t);
}

size_t count_monotone(lookup_table_t *table, size_t border)
{
    int prev = table->table[0];
    size_t n = 1;
    for (size_t i = 1; i < table->size; ++i)
        if (table->table[i] != prev)
        {
            prev = table->table[i];
            ++n;
            if (n > border)
                return n;
        }

    return n;
}

size_t count_monotone_on_the_fly(map_t *m, size_t border, lookup_table_t *normal)
{
    size_t size = 1 << (m->width * m->height);
    int current;
    int prev = normal->table[normalize_bits(0, m)];
    size_t n = 1;
    for (size_t i = 1; i < size; ++i)
    {
        current = normal->table[normalize_bits(i, m)];
        if (current != prev)
        {
            prev = current;
            ++n;
            if (n > border)
                return n;
        }
    }

    return n;
}
