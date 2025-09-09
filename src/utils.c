#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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

char *serialize_array(int *array, int size, int chunk_size, int newline, int tabs)
{
    // 20 bytes must be enough for any int or int64 + '\0'
    char *chunk = malloc(20);
    int chunk_buffer_size = sprintf(chunk, "%d", ~(INT_MAX << chunk_size));
    free(chunk);

    int lines = size / newline + (size % newline > 0);
    int buffer_size = (chunk_buffer_size + 2) * size + ((tabs * 4) * lines);
    char *buffer = malloc(buffer_size);
    char *c = buffer;

    int i = 0;
    for (int l = 0; l < lines; ++l)
    {
        for (int t = 0; t < tabs; ++t)
            c += sprintf(c, "    ");
        
        for (int t = 0; t < newline; ++t)
        {
            c += sprintf(c, "%*d, ", chunk_buffer_size, array[i++]);
            if (i == size)
            {
                c -= 2;
                c += sprintf(c, "\n");
                break;
            }
        }

        --c;
        c += sprintf(c, "\n");
    }
    return buffer;
}
