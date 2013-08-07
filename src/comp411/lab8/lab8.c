#include <stdio.h>

int a[] = {30, 40, 50, 10, 20};

int compare(int a, int b){
	return a < b;
}

int min(int array[], int size){
	int i;
	int minIndex = 0;
	int minValue = array[0];
	
	for (i = 1; i < size; i++)
		if (compare(array[i], minValue)) {
			minValue = array[i];
			minIndex = i; 
		}
	return minIndex;
}

void selectionSort(int array[], int N){
	int i, j, t;
	int *p = array;
	
	for (i = 0; i < N-1; i++) {
		j = min(p,N-i);
		t = array[i];
		array[i] = array[i+j];
		array[i+j] = t;
		p += 1;
	}
}

int main(){
	int i;

	for (i = 0; i < 5; i++)
		 printf("%d: %d\n", i, a[i]);
	printf("\n");

	selectionSort(a, 5);

	for (i = 0; i < 5; i++)
		printf("%d: %d\n", i, a[i]);
	printf("\n");
}