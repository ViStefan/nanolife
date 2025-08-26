#include <pthread.h>
// TODO: temporary!
#include <stdio.h>
#include "map.h"
#include "life.h"

struct thread_data
{
    int bits;
    int width;
    int height;
    map *m;
    int *result;
} typedef thread_data;

void *life_thread(void *t)
{
    thread_data *td = ((thread_data*) t);
    *(td->result) = life(td->bits, td->width, td->height, td->m);
    return NULL;
}

int life(int bits, int w, int h, map *m)
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

int life_chunk(int bits, map *m)
{	
    int size = (m->width - 2) * (m->height - 2);
    pthread_t pthreads[size];
    int result[size];
    thread_data td[size];

    int i = 0;

    for (int h = 1; h < m->height - 1; ++h)
    {
        for (int w = 1; w < m->width - 1; ++w)
        {
            td[i].bits = bits;
            td[i].width = w;
            td[i].height = h;
            td[i].m = m;
            td[i].result = &result[i];
            pthread_create(&pthreads[i], NULL, life_thread, &td[i]);
            ++i;
        }
    }

    for (i = 0; i < size; ++i)
        pthread_join(pthreads[i], NULL);

    int out = 0;
    for (i = 0; i < size; ++i)
    {
        out = (out << 1) | result[i];
    }
    return out;
}


