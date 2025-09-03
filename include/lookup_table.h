#include <stddef.h>
#include "map.h"

typedef struct {
    size_t size;
    map_t *map;
    int *table;
} lookup_table_t;

size_t count_monotone(lookup_table_t *t);
lookup_table_t *generate_table(map_t *m);
void free_lookup_table(lookup_table_t *t);

