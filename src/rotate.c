#include <string.h>
#include "pretty_print.h"
#include "johnson_trotter.h"
#include "map.h"

int chunk[4] = {
    1, 2, 4, 8
};

int lookup_table[16] = {
    0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
};

void print_chunk(int *chunk, map_t *map)
{
    int in = 0;
    for (int i = 0; i < 4; ++i)
        in = (in << 4) | chunk[i];

    pretty_print_chunk(in, 0, map);

   
}

int main(void)
{
    permutation_t *p = init(16);
    map_t map;
    map.width = 4;
    map.height = 4;
    map.value = p->value;
    
    int c2[4];

    memcpy(c2, chunk, sizeof(int) * 4);

    for (int i = 0; i < 4; ++i)
        c2[i] = lookup_table[c2[i]];

    print_chunk(chunk, &map);
    print_chunk(c2, &map);

    free_permutation(p);
    return 0;
}
