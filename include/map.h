#ifndef MAP_H
#define MAP_H

typedef struct
{
	int *value;
	int width;
	int height;
} map_t;

int getbit(int bits, int x, int y, map_t *m);

#endif
