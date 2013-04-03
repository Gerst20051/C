#include<stdio.h>
#define N 8
#define SWAP(X,Y) {register int t = X; X = Y; Y = t;}

int a[N] = { 6, 5, 8, 4, 2, 7, 1, 3 };

int counter = 0;

void
printA ()
{
  int i;
  printf ("The array: ");
  for (i = 0; i < N; printf (" %d ", a[i]), i++);
  printf ("\n");
}

void
quicksort (int array[], int low, int high)
{
  printA ();
  printf ("low: %d      high: %d\n", low, high);
  printf ("quicksort(array[], %d, %d)\n", low, high);
  int pivot, i, j, k;
  if (low < high)
    {
      k = (low + high) >> 1;
      SWAP (array[low], array[k]);
      pivot = array[low];
      i = low + 1;
      j = high;
      while (i <= j)
        {
          while ((i <= high) && (array[i] <= pivot))
            i++;
          while ((j >= low) && (array[j] > pivot))
            j--;
          if (i < j)
            SWAP (array[i], array[j]);
        }
      SWAP (array[low], array[j]);
      quicksort (array, low, j - 1);
      quicksort (array, j + 1, high);
    }
}

main ()
{
  quicksort (a, 0, N - 1);
}