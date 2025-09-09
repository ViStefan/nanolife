#include "map.h"
#include <stdlib.h>

inline int getbit(int bits, int x, int y, map_t *m)
{
    if (x < 0 || x > m->width - 1 || y < 0 || y > m->height - 1) return 0;
    return (bits >> m->value[x + m->width * y]) & 1;
}

int normalize_bits(int bits, map_t *m)
{
    int result = 0;
    for (int i = 0; i < m->blocks; ++i)
        result |= ((bits >> m->value[m->block_start[i]]) &
            ~((unsigned)~0 << m->block_size[i])) << m->block_start[i];
    return result;
}

void map_init_blocks(map_t *m)
{
    int size = m->width * m->height;
    int *block_start = malloc(sizeof(int) * size);
    int *block_size = malloc(sizeof(int) * size);

    int blocks = 0;
    for (int i = 0; i < size; ++i)
    {
        int start = i;
        block_start[blocks] = start;
        while (i < size && m->value[i] == m->value[i + 1] - 1) i++;
        block_size[blocks++] = i - start + 1;
    }
    
    m->block_start = block_start;
    m->block_size = block_size;
    m->blocks = blocks;
}

void map_free_blocks(map_t *m)
{
    free(m->block_start);
    free(m->block_size);
}
