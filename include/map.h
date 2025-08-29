#ifndef MAP_H
#define MAP_H

typedef struct
{
	int *value;
	int width;
	int height;
} map;

int getbit(int bits, int x, int y, map *m);

#endif
