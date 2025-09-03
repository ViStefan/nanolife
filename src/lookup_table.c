#include <stdlib.h>
#include "lookup_table.h"
#include "map.h"
#include "life.h"

lookup_table_t *generate_table(map_t *m)
{
    lookup_table_t *table = malloc(sizeof(lookup_table_t));
    table->map = m;
    table->size = 1 << (m->width * m->height);
    table->table = malloc(sizeof(int) * table->size);

    for (size_t i = 0; i < table->size; ++i)
        table->table[i] = life_chunk(i, m);

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
