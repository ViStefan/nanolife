#include <stdio.h>
#include <stdlib.h>
#include "johnson_trotter.h"
#include "utils.h"

permutation *init(int n)
{
    permutation *p = malloc(sizeof(permutation));

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

void free_permutation(permutation *p)
{
    free(p->value);
    free(p->direction);
    free(p);
}

void print(permutation *p)
{
    char *buffer = serialize(p);
    printf("%s\n", buffer);
    free(buffer);
}

char *serialize(permutation *p)
{
    char *buffer = malloc(sequence_string_length(p->n));
    char *c = buffer;

    c += sprintf(c, "%d", p->value[0]);
    for (int i = 1; i < p->n; ++i)
        c += sprintf(c, ", %d", p->value[i]);
    return buffer;
}

void swap(permutation *p, int n)
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

int next(permutation *p)
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
