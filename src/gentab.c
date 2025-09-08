#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
// TODO: included only for serialization of array
#include "johnson_trotter.h"
#include "lookup_table.h"
#include "map.h"
#include "pretty_print.h"
#include "utils.h"

#define THREADS 4

// TODO: move to lookup_table_t
enum TYPE
{
    OUTCOME,
    NEIGHBOUR,
    FREQUENCY,
    ROTATE
};

enum RENDER
{
    PRETTY,
    DEC,
    HEX,
    BIN
};

void usage(char **argv, int status)
{
    printf("usage: %s TYPE SIZE MAPPING RENDER ALIGN\n", argv[0]);
    printf("\tTYPE\tlookup table type: outcome|neighbour|frequency|rotate\n");
    printf("\t\toutcome\t\tlife b3s23 outcomes in array\n");
    printf("\t\tneighbour\tarray of arrays of neighbourhoods leading to particular outcomes\n");
    printf("\t\tfrequency\tarray of neighbourhoods sorted by appearance frequency\n");
    printf("\t\trotate\t\tsmall lookup table for matrix rotation and flipping\n");
    printf("\tSIZE\tnumber 'N' or pair 'WxH' for square or rectangle correspondingly\n");
    printf("\tMAPPING\tenumeration of cells in matrix in form '0,1,2,3,...,n-1' in arbitrary order or 'default' for sequential\n");
    printf("\tRENDER\trender type: pretty|dec|hex|bin\n");
    printf("\tALIGN\tnumber 'N', alignment in bits for table chunk, ignored if render type is pretty\n");
    exit(status);
}

int main(int argc, char **argv)
{
    if (argc < 6)
        usage(argv, 1);

    enum TYPE type;
    if (!strcmp(argv[1], "outcome"))
        type = OUTCOME;
    else if (!strcmp(argv[1], "neighbour"))
        type = NEIGHBOUR;
    else if (!strcmp(argv[1], "frequency"))
        type = FREQUENCY;
    else if (!strcmp(argv[1], "rotate"))
        type = ROTATE;
    else 
        usage(argv, 2);

    size_t width, height;
    char *end;
    width = height = (size_t)strtoul(argv[2], &end, 10);
    if (errno == ERANGE)
        usage(argv, 3);
    if (*end == 'x')
    {
        height = (size_t)strtoul(end + 1, &end, 10);
        if (errno == ERANGE || *end != '\0')
            usage(argv, 4);
    }
    else if (*end != '\0')
        usage(argv, 5);

    int mapping[width * height];
    if (!strcmp(argv[3], "default"))
        for (size_t i = 0; i < width * height; ++i)
            mapping[i] = i;
    else
    {
        end = argv[3];
        int i = 0;
        while (*end != '\0')
        {
            if ((size_t)i >= width * height)
                usage(argv, 6);

            mapping[i++] = (size_t)strtoul(end, &end, 10);
            if (errno == ERANGE || (*end != ',' && *end != '\0'))
                usage(argv, 7);
            if (*end == ',')
                ++end;
        }
        if ((size_t)i < width * height)
            usage(argv, 8);
    }

    enum RENDER render = PRETTY;
    if (!strcmp(argv[4], "pretty"))
        render = PRETTY;
    else if (!strcmp(argv[4], "dec"))
        render = DEC;
    else if (!strcmp(argv[4], "hex"))
        render = HEX;
    else if (!strcmp(argv[4], "bin"))
        render = BIN;
    else
        usage(argv, 9);

    size_t align = strtoul(argv[5], &end, 10);
    if (errno == ERANGE || *end != '\0')
        usage(argv, 10);

    map_t m;
    m.width = width;
    m.height = height;
    m.value = mapping;

    permutation_t *p = permutation_init(width * height);
    free(p->value);
    p->value = mapping;
    char *mapping_str = permutation_serialize(p);
    free(p);

    printf("attempt to print table of type %d of size %zux%zu with mapping (%s), render %d and align %zu\n",
        type, width, height, mapping_str, render, align);

    lookup_table_t *table;
    bool was_generated = false;
    if (type == OUTCOME)
    {
        table = generate_table(&m, THREADS);
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
