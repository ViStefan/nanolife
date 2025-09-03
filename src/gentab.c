#include <stdio.h>
#include "lookup_table.h"
#include "map.h"
#include "pretty_print.h"

int main(void)
{
    map_t m;
    // TODO: parametrize
    m.width = 3;
    m.height = 3;
    int map[] = {
        1, 2, 3,
        4, 0, 5,
        6, 7, 8
    };
    m.value = map;

    lookup_table_t *table = generate_table(&m);
    pretty_print_table(table);
    printf("monotonous outcome intervals: %zu\n", count_monotone(table));

    free_lookup_table(table);

    return 0;
}
