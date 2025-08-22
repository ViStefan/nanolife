#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "johnson_trotter.h"

void permutate(int number)
{
    permutation *p = init(number);
    printf("%d: ", p->step);
    print(p);
    for (int i = 0; i < factorial(p->size) - 1; ++i)
    {
        next(p);
        printf("%d: ", p->step);
        print(p);
    }
    free_permutation(p);
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
