#ifndef MAP_H
#define MAP_H

struct map
{
	int *value;
	int width;
	int height;
} typedef map;

int getbit(int bits, int x, int y, map *m);

#endif
