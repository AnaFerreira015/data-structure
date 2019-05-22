#include <stdlib.h>
#include <stdio.h>

void merge(int vector[], int left, int right, int size)
{
    int *vector_aux = (int *)malloc(size * sizeof(int));
    int i = left, mid = ((left + right) / 2);
    int walk1, walk2;

    walk1 = left;
    walk2 = mid + 1;

    while ((walk1 < mid + 1) && (walk2 < right + 1))
    {
        if (vector[walk1] <= vector[walk2])
        {
            vector_aux[i++] = vector[walk1];
            walk1++;
        }
        else
        {
            vector_aux[i++] = vector[walk2];
            walk2++;
        }
    };

    if (walk2 == right + 1)
    {
        while ((walk1 < mid + 1))
        {
            vector_aux[i++] = vector[walk1];
            walk1++;
        };
    }
    else
    {
        while ((walk2 < right + 1))
        {
            vector_aux[i++] = vector[walk2];
            walk2++;
        };
    }

    for (i = left; i < right - left + 1; i++)
        vector[i] = vector_aux[i];
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void mergesort(int vector[], int size, int left, int right)
{
    int mid = (left + right) / 2;
    if (right - left == 1)
    {
        if (vector[left] > vector[right])
            swap(&vector[left], &vector[right]);
    }
    else
    {
        mergesort(vector, size, left, mid);
        mergesort(vector, size, mid + 1, right);
        merge(vector, left, right, size);
    }
}

void read_array(int vector[], int size, int i)
{
    if (i < size)
    {
        printf("[%d] = ", i);
        scanf("%d", &vector[i]);
        read_array(vector, size, ++i);
    }
}

void print_array(int vector[], int size, int i)
{
    if (i < size)
    {
        printf("[%d] = %d\n", i, vector[i]);
        print_array(vector, size, ++i);
    }
}

int main()
{
    int size;

    printf("Size of the array: \n");
    scanf("%d", &size);

    int vector[] = {};

    read_array(vector, size, 0);

    printf("Before ordenation:\n");
    print_array(vector, size, 0);

    mergesort(vector, 4, 0, 4 - 1);

    printf("After ordenation:\n");
    print_array(vector, size, 0);

    return 0;
}