#include <stdlib.h>
#include <stdio.h>

int linear_search(int key, int array[], int size, int i)
{
	if (i < size)
	{
		if (key == array[i])
		{
			return i;
		}
		return linear_search(key, array, size, ++i);
	}
	else
	{
		printf("\nKey %d wasn't found\n", key);
	}
}

void initialize_array(int array[], int size, int i)
{
	if (i < size)
	{
		printf("array[%d]: ", i);
		scanf("%d", &array[i]);
		return initialize_array(array, size, ++i);
	}
	else
	{
		return;
	}
}

int main()
{
	int key, result, size;

	printf("Enter the size of array: \n");
	scanf("%d", &size);

	int array[size];

	initialize_array(array, size, 0);

	printf("Key: ");
	scanf("%d", &key);

	result = linear_search(key, array, size, 0);

	printf("\nKey %d and index %d\n", key, result);
}