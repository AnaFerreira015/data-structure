#include <stdlib.h>
#include <stdio.h>

void printing_array(int array[], int size, int i);

void reading_array(int array[], int size, int i);

int square(int number);

int factorial(int number);

void map(int (*function)(int n), int array[], int size, int i);

int main()
{
    int size;

    printf("Size: \n");
    scanf("%d", &size);

    int numbers[size];

    reading_array(numbers, size, 0);

    printf("\nSquare: \n");
    map(factorial, numbers, size, 0);

    printing_array(numbers, size, 0);
    return 0;
}

void printing_array(int array[], int size, int i)
{
    if (i < size)
    {
        printf("[%d] = %d\n", i, array[i]);
        printing_array(array, size, ++i);
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

int square(int number)
{
    return number * number;
}

int factorial(int number)
{
    if (number <= 1)
    {
        return 1;
    }
    else
    {
        return number * factorial(number - 1);
    }
}

void map(int (*function)(int n), int array[], int size, int i)
{
    if (i < size)
    {
        array[i] = (*function)(array[i]);
        map(function, array, size, ++i);
    }
}