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

shimon *swap(shimon *head, shimon *element)
{
    shimon *exchange;

    if (!element->direction ||
        (element->direction == -1 && element->prev == NULL) ||
        (element->direction == 1 && element->next == NULL))
        return head;

    if (element->direction == -1)
    {
        shimon *exchange = element->prev;
        shimon *next = element->next;
        shimon *prev = exchange->prev;
        element->prev = prev;
        element->next = exchange;
        exchange->prev = element;
        exchange->next = next;
    }
    else
    {
        shimon *exchange = element->next;
        shimon *next = exchange->next;
        shimon *prev = element->prev;
        element->prev = exchange;
        element->next = next;
        exchange->prev = prev;
        exchange->next = element;
    }

    if (element->prev == NULL)
        return element;
    if (exchange->prev == NULL)
        return exchange;

    return head;
}

shimon *next(shimon *head)
{
    shimon *max = head;
    do {
        if (head->direction != 0 && max->value < head->value)
            max = head;
        head = head->next;
    } while (head != NULL);

    swap(head, max);
    return max;
}

int main()
{
    permutation = fill(LENGTH);
    print(permutation);
    printf("\n");
    shimon *max = next(permutation);
    print(permutation);
    printf("\n");
    printf("%d", max->value);
    free(permutation);
    return 0;
}
