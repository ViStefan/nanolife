#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

int parse_pair(char *arg, unsigned int *left, unsigned int *right)
{
    char *end;
    *left = *right = strtoul(arg, &end, 10);
    if (errno == ERANGE)
        return 1;
    if (*end == 'x')
    {
        *right = (size_t)strtoul(end + 1, &end, 10);
        if (errno == ERANGE || *end != '\0')
            return 1;
    }
    else if (*end != '\0')
        return 1;

    return 0;
}

int parse_uint(char *arg, unsigned int *n)
{
    char *end;
    *n = strtoul(arg, &end, 10);
    if (errno == ERANGE || *end != '\0')
        return 1;
    return 0;
}

int parse_enum(char* arg, int *value, ...)
{
    va_list args;
    int i = 0;
    va_start(args, value);
    char *en;
    do
    {
        en = va_arg(args, char *);
        *value = i++;
        if (en == NULL)
            goto not_found;
    } while (strcmp(arg, en));
    return 0;

not_found:
    return 1;
}

int parse_array(char *arg, int size, int *value)
{
    char *end;
    if (!strcmp(arg, "DEFAULT"))
        for (int i = 0; i < size; ++i)
            value[i] = i;
    else
    {
        end = arg;
        int i = 0;
        while (*end != '\0')
        {
            if (i == size)
                return 1;

            value[i++] = strtoul(end, &end, 10);
            if (errno == ERANGE || (*end != ',' && *end != '\0'))
                return 1;
            if (*end == ',')
                ++end;
        }
        if (i < size)
            return 1;
    }

    return 0;

}
