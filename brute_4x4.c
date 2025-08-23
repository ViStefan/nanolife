#include <stdio.h>

#include "johnson_trotter.h"
#include "gentab.h"

int main(int argc, char **argv) {
	permutation *p = init(WIDTH * HEIGHT);
    int c = count_monotone(p->value);
    printf("%d : ", c);
    print(p);
    
    for (int i = 0; i < factorial(WIDTH * HEIGHT) - 1; ++i)
    {
        next(p);
        c = count_monotone(p->value);
        printf("%d : ", c);
        print(p);
    }

    return 0;
}
