#ifndef LIFE_H
#define LIFE_H

#include "map.h"

int life(int bits, int w, int h, map_t *m);
int life_chunk(int bits, map_t *m);

#endif /* LIFE_H */
