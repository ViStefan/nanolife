#include "map.h"

int getbit(int bits, int x, int y, map_t *m)
{
    if (x < 0 || x > m->width - 1 || y < 0 || y > m->height - 1) return 0;
    return (bits >> m->value[x + m->width * y]) & 1;
}
