#include "lookup_table.h"
#include "map.h"
#include "life.h"

int count_monotone(map_t *m)
{
	long int size = 1 << (m->width * m->height);
    int result[size];
	for (int i = 0; i < size; ++i)
        result[i] = life_chunk(i, m);

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
