#include "lookup_table.h"
#include "map.h"
#include "johnson_trotter.h"
#include "pretty_print.h"

int main(int argc, char **argv)
{
    map m;
    // TODO: parametrize
    m.width = 3;
    m.height = 4;

    permutation *p = init(m.width * m.height);
    m.value = p->value;

    pretty_print_table(&m);

    return 0;
}
