#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include <stddef.h>
#include "map.h"

typedef struct {
    size_t size;
    size_t outcome_size;
    map_t *map;
    int *table;
} lookup_table_t;

size_t count_monotone(lookup_table_t *t, size_t border);
size_t count_monotone_on_the_fly(map_t *m, size_t border, lookup_table_t *normal);
lookup_table_t *generate_table(map_t *m, int threads, lookup_table_t *normal);
void free_lookup_table(lookup_table_t *t);

#endif
