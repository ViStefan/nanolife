#include <stdio.h>
#include "pretty_print.h"
#include "life.h"
#include "lookup_table.h"
#include <stdbool.h>

void putsquare(int color)
{
    if (color)
        printf("\u2b1b");
    else
        printf("\u2b1c");
}

void pretty_print_chunk(int in, map_t *m, bool outcome, int out, int outcome_size)
{
    int out_width = m->width - 2;
    outcome_size -= 1;

    for (int h = 0; h < m->height; ++h)
    {
        for (int w = 0; w < m->width; ++w)
            putsquare(getbit(in, w, h, m));

        if (outcome)
        {
            if (h > 0 && h < m->height - 1)
            {
                if (h == (m->height - 1) / 2)
                    printf(" → ");
                else
                    printf("   ");
                
                for (int w = 0; w < m->width - 2; ++w)
                    putsquare((out >> (outcome_size - (w + (h - 1) * out_width))) & 1);
            }
        }
        printf("\n");
    }
}

// pp with outcome, from map
void pretty_print_chunk_out_m(int in, int out, map_t *m)
{
    pretty_print_chunk(in, m, true, out, (m->width - 2) * (m->height - 2));
}

// pp with no outcome, from map
void pretty_print_chunk_m(int in, map_t *m)
{
    pretty_print_chunk(in, m, false, 0, 0);
}

// pp with outcome, from lookup table 
void pretty_print_chunk_out_l(int in, int out, lookup_table_t *lt)
{
    pretty_print_chunk(in, lt->map, true, out, lt->outcome_size);
}

// pp with no outcome, from lookup table 
void pretty_print_chunk_l(int in, lookup_table_t *lt)
{
    pretty_print_chunk(in, lt->map, false, 0, 0);
}

void pretty_print_table(lookup_table_t *table)
{
    for (size_t i = 0; i < table->size; ++i)
    {
        printf("\n%zu:\n", i);
        pretty_print_chunk(i, table->map, true, table->table[i], table->outcome_size);
    }
}
