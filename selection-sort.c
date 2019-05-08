#include <stdlib.h>
#include <stdio.h>

void print_array(int *array, int i, int size)
{
    if (i < size)
    {
        printf("[%d] = %d\n", i, array[i]);
        print_array(array, ++i, size);
    }
}

void read_array(int *array, int i, int tamanho)
{
    if (i < tamanho)
    {
        printf("array [%d] = ", i);
        scanf("%d", &array[i]);
        read_array(array, ++i, tamanho);
    }
    else
    {
        return;
    }
}

void selection_sort(int *v, int i, int j, int size)
{
    int aux;
    if (i < size)
    {
        if (j < size)
        {
            if (v[i] >= v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
            selection_sort(v, i, ++j, size);
        }
        else
        {
            selection_sort(v, ++i, i + 1, size);
        }
    }
}

int main()
{
    int size_of_array;

    printf("Enter the size of the array: \n");
    scanf("%d", &size_of_array);

    int array[size_of_array];

    read_array(array, 0, size_of_array);

    printf("\n");
    printf("Array without selection sort:\n");
    print_array(array, 0, size_of_array);

    printf("\n");
    printf("Array with selection sort:\n");
    selection_sort(array, 0, 1, size_of_array);
    print_array(array, 0, size_of_array);
    return 0;
}