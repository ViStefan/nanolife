#include <stdio.h>

#define WIDTH 3
#define HEIGHT 4

#include "johnson_trotter.h"
#include "gentab.c"

int permutation[LENGTH];
int direction[LENGTH];

int main(int argc, char **argv) {
    fill(permutation, direction);
    int c = count_monotone(permutation);
    printf("%d : ", c);
    print(permutation);
    
    for (int i = 0; i < factorial(LENGTH) - 1; ++i)
    {
        next(permutation, direction);
        c = count_monotone(permutation);
        printf("%d : ", c);
        print(permutation);
    }

    return 0;
}
