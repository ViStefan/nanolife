#include "map.h"
#include "life.h"

int life(int bits, int x, int y, map_t *m)
{
    int neighbours = 0;

    for (int j = y - 1; j <= y + 1; ++j)
        for (int i = x - 1; i <= x + 1; ++i)
            neighbours += getbit(bits, i, j, m);

    int self = getbit(bits, x, y, m);
    neighbours -= self;

    return(neighbours == 3 || (self && neighbours == 2));
}

int life_chunk(int bits, map_t *m)
{
    int out = 0;

    for (int h = 1; h < m->height - 1; ++h)
        for (int w = 1; w < m->width - 1; ++w)
            out = (out << 1) | life(bits, w, h, m);

    return out;
}


