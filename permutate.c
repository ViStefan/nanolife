#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "johnson_trotter.h"

#define THREADS 12

void usage(char **argv)
{
    printf("%s NUM\n", argv[0]);
    printf("\tNUM - sane number of elements to permutate\n");
}

void print_permutation(permutation *p)
{
    print(p);
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

    permutate(num, THREADS, &print_permutation);

    return 0;
}
