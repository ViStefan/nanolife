#include <stdio.h>

#include "johnson_trotter.h"
#include "lookup_table.h"

int main(int argc, char **argv) {
    struct map m;
    m.width = 3;
    m.height = 4;
    
    permutation *p = init(m.width * m.height);
    m.value = p->value;
    int c = count_monotone(&m);
    printf("%d : ", c);
    print(p);
    
    int size = factorial(m.width * m.height) - 1;
    
    for (int i = 0; i < size; ++i)
    {
        next(p);
        m.value = p->value;
        c = count_monotone(&m);
        printf("%d : ", c);
        print(p);
    }

    free_permutation(p);

    return 0;
}
