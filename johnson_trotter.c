#include <stdio.h>
#include <stdlib.h>

#define LENGTH 3

struct shimon
{
    int value;
    int direction;
    struct shimon *next;
    struct shimon *prev;
} typedef shimon;

shimon *permutation;

shimon *fill(int size)
{
    shimon *array = malloc(sizeof(shimon) * size);
    for (int i = 0; i < size; ++i)
    {
        array[i].value = i;
        array[i].direction = -1;
        array[i].next = &array[i + 1];
        array[i].prev = &array[i - 1];
    }

    array[0].direction = 0;
    array[0].prev = NULL;
    array[size - 1].next = NULL;

    return array;
}

void print(shimon *head)
{
    do {
        printf("%d (%d) -> ", head->value, head->direction);
        head = head->next;
    } while (head != NULL);
}

shimon *next(shimon *head)
{
    shimon *max = head;
    do {
        if (head->direction != 0 && max->value < head->value)
            max = head;
        head = head->next;
    } while (head != NULL);

    return max;
    
}

int main()
{
    permutation = fill(LENGTH);
    print(permutation);
    printf("\n");
    shimon *max = next(permutation);
    printf("%d", max->value);
    free(permutation);
    return 0;
}
