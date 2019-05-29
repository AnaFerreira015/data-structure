#include <stdlib.h>
#include <stdio.h>

void reading_array(int array[], int size, int i);

void even(int number);

void odd(int number);

void filter(void (*function)(int n), int array[], int size, int i);

int main()
{
    int size;

    printf("Size: \n");
    scanf("%d", &size);

    int numbers[size];

    reading_array(numbers, size, 0);

    printf("Even:\n");
    filter(even, numbers, size, 0);

    printf("Odd:\n");
    filter(odd, numbers, size, 0);
    return 0;
}

void filter(void (*function)(int n), int array[], int size, int i)
{
    if (i < size)
    {
        (*function)(array[i]);
        filter(function, array, size, ++i);
    }
}

void even(int number)
{
    if ((number % 2) == 0)
    {
        printf("%d\n", number);
    }
}

void odd(int number)
{
    if (!((number % 2) == 0))
    {
        printf("%d\n", number);
    }
}

void reading_array(int array[], int size, int i)
{
    if (i < size)
    {
        printf("[%d] = ", i);
        scanf("%d", &array[i]);
        reading_array(array, size, ++i);
    }
}
