#include "map.h"
#include "life.h"

int life(int bits, int w, int h, map_t *m)
{
    int neighbours = 0;

    for (int y = h - 1; y <= h + 1; ++y)
    {
        for (int x = w - 1; x <= w + 1; ++x)
        {
            neighbours += getbit(bits, x, y, m);
        }
    }

    int self = getbit(bits, w, h, m);
    neighbours -= self;

    return(neighbours == 3 || (self && neighbours == 2));
}

int life_chunk(int bits, map_t *m)
{	
    int out = 0;

    for (int h = 1; h < m->height - 1; ++h)
    {
        for (int w = 1; w < m->width - 1; ++w)
        {
            out = (out << 1) | life(bits, w, h, m);
        }
    }
    return out;
}


