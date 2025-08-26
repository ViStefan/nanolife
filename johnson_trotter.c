#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "johnson_trotter.h"

void *permutate_thread(void *t)
{

    permutation_threaded *pt = ((permutation_threaded*) t);
    permutation *p = pt->perm;

    // should store permutations number in struct?
    int size = factorial(p->size);
    do
    {
        pt->callback(p);
        for (int i = 0; i < pt->threads; ++i)
            next(p);

    } while (p->step <= size);

    return NULL;
}

void permutate(int number, int threads, void (*callback)(permutation *p))
{
    permutation_threaded pt[threads];
    pthread_t pthreads[threads];

    for (int i = 0; i < threads; ++i)
    {
        pt[i].callback = callback;
        pt[i].threads = threads;
        pt[i].perm = init(number);
        for (int j = 0; j < i; ++j)
            next(pt[i].perm);
        pthread_create(&pthreads[i], NULL, permutate_thread, &pt[i]);
    }

    for (int i = 0; i < threads; ++i) {
        pthread_join(pthreads[i], NULL);
        free_permutation(pt[i].perm);
    }
}

permutation *init(int size)
{
    permutation *p = malloc(sizeof(permutation));

    p->size = size;
    p->step = 1;
    p->value = malloc(sizeof(int) * size);
    p->direction = malloc(sizeof(int) * size);

    for (int i = 0; i < p->size; ++i)
    {
        p->value[i] = i;
        p->direction[i] = -1;
    }
    p->direction[0] = 0;
    
    return p;
}

void free_permutation(permutation *p)
{
    free(p->value);
    free(p->direction);
    free(p);
}

void print(permutation *p)
{
    // TODO: line length?
    char buffer[p->size * 4];
    char *c = buffer;

    c += sprintf(c, "%d", p->value[0]);
    for (int i = 1; i < p->size; ++i)
        c += sprintf(c, ", %d", p->value[i]);
    printf("%s\n", buffer);
}

void swap(permutation *p, int n)
{
    if (!p->direction[n] ||
        (p->direction[n] == -1 && n == 0) ||
        (p->direction[n]  == 1 && n == p->size - 1))
        return;

    int d = p->direction[n];
    int is_outermost = (d == -1) ? (n == 1) : (n == p->size - 2);

    int t = p->value[n];
    p->value[n] = p->value[n + d];
    p->value[n + d] = t;

    t = p->direction[n];
    p->direction[n] = p->direction[n + d];
    p->direction[n + d] = t;

    if (is_outermost)
        p->direction[n + d] = 0;
    else if (p->value[n + (2 * d)] > p->value[n + d])
        p->direction[n + d] = 0;
}

void next(permutation *p)
{
    int max = -1;
    int maxindex = -1;
    for (int i = 0; i < p->size; ++i)
        if (p->direction[i] != 0 && (max == -1 || max < p->value[i]))
        {
            max = p->value[i];
            maxindex = i;
        }

    // TODO: here if max == -1, last permutation reached

    int border = maxindex + p->direction[maxindex];

    swap(p, maxindex);

    for (int i = 0; i < maxindex; ++i)
        if (p->value[i] > max)
            p->direction[i] = 1;

    for (int i = maxindex + 1; i < p->size; ++i)
        if (p->value[i] > max)
            p->direction[i] = -1;

    p->step++;
}

int factorial(int n)
{
    int r = 1;
    do
    {
        r *= n;
    } while (--n);
    return r;
}

