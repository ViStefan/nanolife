#include <stdbool.h>
#include "lookup_table.h"
#include "map.h"

void pretty_print_chunk(int in, map_t *m, bool outcome, int out, int outcome_size);
void pretty_print_table(lookup_table_t *t);

// pp versions w/ or w/o outcome, from map or lookup table
void pretty_print_chunk_out_m(int in, int out, map_t *m);
void pretty_print_chunk_m(int in, map_t *m);
void pretty_print_chunk_out_l(int in, int out, lookup_table_t *lt);
void pretty_print_chunk_l(int in, lookup_table_t *lt);
void print_as_code(lookup_table_t *lt);
