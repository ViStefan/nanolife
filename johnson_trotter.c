#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

int permutation[LENGTH];
int direction[LENGTH];

void fill(int *p, int *d)
{
    for (int i = 0; i < LENGTH; ++i)
    {
        p[i] = i;
        d[i] = -1;
    }

    d[0] = 0;
}

void print(int *p, int *d)
{
    printf("%d", p[0]);
    for (int i = 1; i < LENGTH; ++i)
        printf(", %d", p[i]);
    printf("\n");
}

void swap(int *p, int *d, int n)
{
    if (!d[n] ||
        (d[n] == -1 && n == 0) ||
        (d[n]  == 1 && n == LENGTH - 1))
        return;

    // TODO: extract method for general swapping of two elements
    // TODO: or maybe just use two arrays and no pointer arithmetics?
    if (d[n] == -1)
    {
        int t = p[n];
        p[n] = p[n - 1];
        p[n - 1] = t;

        t = d[n];
        d[n] = d[n - 1];
        d[n - 1] = t;

        if (n > 1 && p[n - 2] > p[n - 1])
            d[n - 1] = 0;

        if (n == 1)
            d[n - 1] = 0;

    }
    else
    {
        int t = p[n];
        p[n] = p[n + 1];
        p[n + 1] = t;

        t = d[n];
        d[n] = d[n + 1];
        d[n + 1] = t;

        if (n < LENGTH - 2 && p[n + 2] > p[n + 1])
                d[n + 1] = 0;

        if (n == LENGTH - 2)
            d[n + 1]  = 0;
    }
}

void next(int *p, int *d)
{
    int max = -1;
    int maxindex = -1;
    for (int i = 0; i < LENGTH; ++i)
        if (d[i] != 0 && (max == -1 || max < p[i]))
        {
            max = p[i];
            maxindex = i;
        }

    // TODO: here if max == -1, last permutation reached

    int border = maxindex + d[maxindex];

    swap(p, d, maxindex);

    for (int i = 0; i < maxindex; ++i)
        if (p[i] > max)
            d[i] = 1;

    for (int i = maxindex + 1; i < LENGTH; ++i)
        if (p[i] > max)
            d[i] = -1;
}

int factorial(int n)
{
    int r = 1;
    do
    {
        r *= n;
    } while (--n);
    return r;
}

int main()
{
    fill(permutation, direction);
    print(permutation, direction);
    for (int i = 0; i < factorial(LENGTH) - 1; ++i)
    {
        next(permutation, direction);
        print(permutation, direction);
    }
    return 0;
}
