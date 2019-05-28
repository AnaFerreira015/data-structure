#include <stdlib.h>
#include <stdio.h>

void print_array(int array[], int size);

void reading_array(int array[], int size);

int square (int number);

int factorial(int number);

void map(int(*function)(int n), int array[], int size);

int main () {
    int size;

    printf("Size: \n");
    scanf("%d", &size);

    int numbers[size];

    reading_array(numbers, size);

    printf("\nSquare: \n");
    map(square, numbers, size);
    return 0;
}

void printing_array(int array[], int size) {
    int i;

    for(i = 0; i < size; i++) {
        printf("[%d] = %d\n", i, array[i]);
    }
}

void reading_array(int array[], int size) {
    int i;

    for(i = 0; i < size; i++) {
        printf("[%d] = ", i);
        scanf("%d", &array[i]);
    }
}

int square (int number) {
    return number*number;
}

int factorial(int number) {
    if(number <= 1) {
        return 1;
    }
    else {
        return number*factorial(number-1);
    }
}

void map(int(*function)(int n), int array[], int size) {
    int i;

    for(i = 0; i < size; i++) {
        array[i] = (*function)(array[i]);
    }
    printing_array(array, size);
}