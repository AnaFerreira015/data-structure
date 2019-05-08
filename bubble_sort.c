
#include <stdlib.h>
#include <stdio.h>

void bubble_sort(int array[], int i, int j, int aux, int tamanho) {
	if (i != tamanho - 1)
	{
		if (j < tamanho)
		{
			if (array[i] > array[j])
			{
				aux = array[i];
				array[i] = array[j];
				array[j] = aux;
			}
			bubble_sort(array, i, ++j, aux, tamanho);
		}
		bubble_sort(array, ++i, j, aux, tamanho);
	}
}

void print_array(int array[], int i, int tamanho){
	if (i < tamanho) {
		printf("array [%d] = %d\n", i, array[i]);
		print_array(array, ++i, tamanho);
	}
	else {
		return;
	}
}

int main() {
	int numeros[5] = {4, 2, 5, 3, 1};
	bubble_sort(numeros, 0, 0, 0, 5);
	print_array(numeros, 0, 5);
	return 0;
}