#include <stdio.h>
#include "pretty_print.h"
#include "life.h"
#include "lookup_table.h"

void putsquare(int color)
{
    if (color)
        printf("\u2b1b");
    else
        printf("\u2b1c");
}

void pretty_print_chunk(int in, int out, map_t *m)
{
    int out_width = m->width - 2;
    int out_size = (m->height - 2) * out_width - 1;

    for (int h = 0; h < m->height; ++h)
    {
        for (int w = 0; w < m->width; ++w)
        {
            putsquare(getbit(in, w, h, m));
        }

        if (h > 0 && h < m->height - 1)
        {
            if (h == (m->height - 1) / 2)
                printf(" → ");
            else
                printf("   ");
            
            for (int w = 0; w < m->width - 2; ++w)
            {
                putsquare((out >> (out_size - (w + (h - 1) * out_width))) & 1);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void pretty_print_table(map_t *m)
{
    lookup_table_t *table = generate_table(m);
	for (size_t i = 0; i < table->size; ++i)
	{
		printf("\n%zu:\n", i);
        pretty_print_chunk(i, table->table[i], table->map);
	}

    free_lookup_table(table);
}


