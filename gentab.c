#include "lookup_table.h"
#include "map.h"
#include "johnson_trotter.h"
#include "pretty_print.h"

int main(int argc, char **argv)
{
    map m;
    // TODO: parametrize
    m.width = 3;
    m.height = 3;

    //permutation *p = init(m.width * m.height);
    int map[] = {1, 2, 3, 4, 0, 5, 6, 7, 8};
    m.value = map;

    pretty_print_table(&m);

    return 0;
}
