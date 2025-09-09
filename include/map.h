#ifndef MAP_H
#define MAP_H

typedef struct
{
    int *value;
    int width;
    int height;
    int size;
    int blocks;
    int *block_start;
    int *block_size;
} map_t;

void map_init_blocks(map_t *m);
void map_free_blocks(map_t *m);
int getbit(int bits, int x, int y, map_t *m);
int normalize_bits(int bits, map_t *m);

#endif
