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

size_t count_monotone(lookup_table_t *t);
lookup_table_t *generate_table(map_t *m);
void free_lookup_table(lookup_table_t *t);

#endif
