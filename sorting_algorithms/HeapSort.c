#include "../data_structures/Heap.h"
#include <stdlib.h>
#include <stdio.h>

int* read_input(int *n) {
  printf("N: ");
  scanf("%d", n);

  int* arr = malloc(*n * sizeof(int));
  if (arr == NULL) {
      printf("Memory allocation failed!\n");
      exit(EXIT_FAILURE);
  }

  printf("Enter %d integers: ", *n);
  for (int i = 0; i < *n; i++)
      scanf("%d", arr + i);

  return arr;
}

void heapsort(int *heap, size_t size) {
  if (size < 2)
    return;

  swap(heap, heap + size - 1);
  maxheapify(heap, size - 1, 0);
  
  heapsort(heap, size - 1);
}

int main() {
  int n;
  int *arr = read_input(&n);

  build_max_heap(arr, n);
  heapsort(arr, n);

  for (size_t i = 0; i < n; i++)
    printf("%d ", arr[i]);
  puts("");
  return EXIT_SUCCESS;
}
