#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
// TODO: included only for serialization of array
#include "johnson_trotter.h"
#include "lookup_table.h"
#include "map.h"
#include "pretty_print.h"
#include "utils.h"
#include "args.h"

// TODO: move to lookup_table_t
#define TYPE(F) \
    F(OUTCOME), \
    F(NEIGHBOUR), \
    F(FREQUENCY), \
    F(ROTATE)

#define RENDER(F) \
    F(PRETTY), \
    F(DEC), \
    F(HEX), \
    F(BIN)

ENUM(TYPE)
ENUM(RENDER)

void usage(char **argv, int status)
{
    printf("usage: %s TYPE SIZE MAPPING RENDER ALIGN THREADS\n", argv[0]);
    printf("\tTYPE\tlookup table type: OUTCOME|NEIGHBOUR|FREQUENCY|ROTATE\n");
    printf("\t\toutcome\t\tlife b3s23 outcomes in array\n");
    printf("\t\tneighbour\tarray of arrays of neighbourhoods leading to particular outcomes\n");
    printf("\t\tfrequency\tarray of neighbourhoods sorted by appearance frequency\n");
    printf("\t\trotate\t\tsmall lookup table for matrix rotation and flipping\n");
    printf("\tSIZE\tnumber 'N' or pair 'WxH' for square or rectangle correspondingly\n");
    printf("\tMAPPING\tenumeration of cells in matrix in form '0,1,2,3,...,n-1' in arbitrary order or 'DEFAULT' for sequential\n");
    printf("\tRENDER\trender type: PRETTY|DEC|HEX|BIN\n");
    printf("\tALIGN\tnumber 'N', alignment in bits for table chunk, ignored if render type is pretty\n");
    printf("\tTHREADS\tnumber of parallel threads\n");
    exit(status);
}

int main(int argc, char **argv)
{
    ARGS_INIT(argc, argv, 6)
    PARSE_ENUM(TYPE, type)
    PARSE_PAIR(width, height)
    PARSE_ARRAY(mapping, width * height)
    PARSE_ENUM(RENDER, render)
    PARSE_UINT(align)
    PARSE_UINT(threads)

    map_t m;
    m.width = width;
    m.height = height;
    m.value = mapping;

    permutation_t *p = permutation_init(width * height);
    free(p->value);
    p->value = mapping;
    char *mapping_str = permutation_serialize(p);
    free(p);

    printf("attempt to print table of type %d of size %dx%d with mapping (%s), render %d and align %d in %d threads\n",
        type, width, height, mapping_str, render, align, threads);

    lookup_table_t *table;
    bool was_generated = false;
    if (type == OUTCOME)
    {
        table = generate_table(&m, threads);
        was_generated = true;
    }
    else
        usage(argv, 11);

    if (render == PRETTY)
    {
        pretty_print_table(table);
        // TODO: BUG: something overflows for 6x6 chunks with default mapping
        printf("monotonous outcome intervals: %zu\n", count_monotone(table, INT_MAX));
    }
    else
        usage(argv, 12);

    if (was_generated)
        free_lookup_table(table);

    return 0;
}
