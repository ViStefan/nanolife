#include <stdio.h>
#include "pretty_print.h"
#include "life.h"

void putsquare(int color)
{
    if (color)
        printf("\u2b1b");
    else
        printf("\u2b1c");
}

void pretty_print_chunk(int in, int out, map *m)
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

void pretty_print_table(map *m)
{
	long int size = 1 << (m->width * m->height);
    int result[size];
	for (int i = 0; i < size; ++i)
	{
		printf("\n%d:\n", i);
        result[i] = life_chunk(i, m);
        pretty_print_chunk(i, result[i], m);
	}

    int prev = result[0];
    int n = 1;
    printf("0");
    for (int i = 1; i < size; ++i)
    {
        if (result[i] != prev)
        {
            printf(", %d", i);
            prev = result[i];
            ++n;
        }
    }
    printf("\n--%d--", n);
}


