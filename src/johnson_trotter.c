#include <stdio.h>
#include <stdlib.h>
#include "johnson_trotter.h"
#include "utils.h"

permutation_t *permutation_init(int n)
{
    permutation_t *p = malloc(sizeof(permutation_t));

    p->n = n;
    p->size = factorial(n);
    p->step = 1;
    p->value = malloc(sizeof(int) * n);
    p->direction = malloc(sizeof(int) * n);

    for (int i = 0; i < p->n; ++i)
    {
        p->value[i] = i;
        p->direction[i] = -1;
    }
    p->direction[0] = 0;
    
    return p;
}

void free_permutation(permutation_t *p)
{
    free(p->value);
    free(p->direction);
    free(p);
}

void permutation_print(permutation_t *p)
{
    char *buffer = permutation_serialize(p);
    printf("%s\n", buffer);
    free(buffer);
}

char *permutation_serialize(permutation_t *p)
{
    return serialize_sequence(p->value, p->n);
}

void swap(permutation_t *p, int n)
{
    if (!p->direction[n] ||
        (p->direction[n] == -1 && n == 0) ||
        (p->direction[n]  == 1 && n == p->n - 1))
        return;

    int d = p->direction[n];
    int is_outermost = (d == -1) ? (n == 1) : (n == p->n - 2);

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

int permutation_next_impl(permutation_t *p)
{
    p->step++;
    if (p->step > p->size)
        return PERMUTATION_OVERFLOW;
        
    int max = -1;
    int maxindex = -1;
    for (int i = 0; i < p->n; ++i)
        if (p->direction[i] != 0 && (max == -1 || max < p->value[i]))
        {
            max = p->value[i];
            maxindex = i;
        }

    swap(p, maxindex);

    for (int i = 0; i < maxindex; ++i)
        if (p->value[i] > max)
            p->direction[i] = 1;

    for (int i = maxindex + 1; i < p->n; ++i)
        if (p->value[i] > max)
            p->direction[i] = -1;

    return 0;
}

int permutation_next(permutation_t *p, int n)
{
    int status = 0;
    for (int i = 0; i < n; ++i)
        status = permutation_next_impl(p);
    return status;
}
