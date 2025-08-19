#include <stdio.h>

#define WIDTH 3
#define HEIGHT 4 

#include "johnson_trotter.c"

#define CHUNK_SIZE (WIDTH - 2) * (HEIGHT - 2)

int getbit(int bits, int x, int y, int *map)
{
	if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1) return 0;
	return (bits >> map[x + WIDTH * y]) & 1;
}

int life(int bits, int w, int h, int *map)
{
    int neighbours = 0;

    for (int y = h - 1; y <= h + 1; ++y)
    {
        for (int x = w - 1; x <= w + 1; ++x)
        {
            neighbours += getbit(bits, x, y, map);
        }
    }

    int self = getbit(bits, w, h, map);
    neighbours -= self;

    return(neighbours == 3 || (self && neighbours == 2));
}

int life_chunk(int bits, int *map)
{	
    int out = 0;

    for (int h = 1; h < HEIGHT - 1; ++h)
    {
        for (int w = 1; w < WIDTH - 1; ++w)
        {
            out = (out << 1) | life(bits, w, h, map);
        }
    }
    return out;
}

void putsquare(int color)
{
    if (color)
        printf("\u2b1b");
    else
        printf("\u2b1c");
}

void pretty_print_chunk(int in, int out, int *map)
{
    for (int h = 0; h < HEIGHT; ++h)
    {
        for (int w = 0; w < WIDTH; ++w)
        {
            putsquare(getbit(in, w, h, map));
        }

        if (h > 0 && h < HEIGHT - 1)
        {
            if (h == (HEIGHT - 1) / 2)
                printf(" → ");
            else
                printf("   ");
            
            for (int w = 0; w < WIDTH - 2; ++w)
            {
                putsquare((out >> ((CHUNK_SIZE - 1) - (w + (h - 1) * (WIDTH - 2)))) & 1);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int pretty_print_table(int *map)
{
	long int size = 1 << (WIDTH * HEIGHT);
    int result[size];
	for (int i = 0; i < size; ++i)
	{
		printf("\n%d:\n", i);
        result[i] = life_chunk(i, map);
        pretty_print_chunk(i, result[i], map);
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

int count_monotone(int *map)
{
	long int size = 1 << (WIDTH * HEIGHT);
    int result[size];
	for (int i = 0; i < size; ++i)
        result[i] = life_chunk(i, map);

    int prev = result[0];
    int n = 1;
    for (int i = 1; i < size; ++i)
    {
        if (result[i] != prev)
        {
            prev = result[i];
            ++n;
        }
    }
    return n;
}
