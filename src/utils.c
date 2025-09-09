#include <stdlib.h>
#include <stdio.h>

unsigned long long factorial(int n)
{
    int r = 1;
    do
    {
        r *= n;
    } while (--n);
    return r;
}

// how many chars you need to store "1, 2, 3, ..., n"?
int sequence_string_length(int n)
{
    if (n < 10)
        return n * 3 * sizeof(char);
    return 30 + (4 * (n - 10)) * sizeof(char);
}

char *serialize_sequence(int *sequence, int size)
{
    char *buffer = malloc(sequence_string_length(size));
    char *c = buffer;

    c += sprintf(c, "%d", sequence[0]);
    for (int i = 1; i < size; ++i)
        c += sprintf(c, ", %d", sequence[i]);
    return buffer;
} 
