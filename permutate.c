#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include "johnson_trotter.h"

#define THREADS 12

void *permutate_thread(void *t)
{

    permutation *p = ((permutation *) t);

    int size = factorial(p->size);
    do
    {
        print(p);
        for (int i = 0; i < THREADS; ++i)
        {
            next(p);
        }

    } while (p->step <= size);

    return NULL;
}

void permutate(int number)
{
    permutation *p[THREADS];

    for (int i = 0; i < THREADS; ++i)
    {
        p[i] = init(number);
        for (int j = 0; j < i; ++j)
            next(p[i]);
    }

    pthread_t threads[THREADS];

    for (int i = 0; i < THREADS; ++i)
        pthread_create(&threads[i], NULL, permutate_thread, p[i]);

    for (int i = 0; i < THREADS; ++i)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < THREADS; ++i)
        free_permutation(p[i]);
}

void usage(char **argv)
{
    printf("%s NUM\n", argv[0]);
    printf("\tNUM - sane number of elements to permutate\n");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        usage(argv);
        return 1;
    }

    char *end;
    unsigned long num = strtoul(argv[1], &end, 10);

    if (*end != '\0' || errno == ERANGE)
    {
        usage(argv);
        return 2;
    }

    permutate(num);

    return 0;
}
