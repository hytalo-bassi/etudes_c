#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Array {
    int *data;
    size_t len;
} Array;

void swap(int *a, int *b) {
  const int tmp = *a;
  *a = *b;
  *b = tmp;
}

Array init(size_t len) {
  Array res = { .len = len, .data = malloc(len * sizeof(int)) };
  return res;
}

void print(Array arr) {
    printf("[ ");
    for (size_t i = 0; i < arr.len; i++) {
        if (i == arr.len - 1) {
            printf("%d ]\n", arr.data[i]);
            return;
        }
        printf("%d, ", arr.data[i]);
    }
}

void prepopulate(Array arr, int range) {
  srand(time(NULL));
  for (size_t i = 0; i < arr.len; i++) {
    arr.data[i] = rand() % (range + 1);
  }
}

size_t partition(Array *arr, size_t start, size_t end) {
  int pivot = arr->data[end];
  size_t i = start;

  for (size_t j = start; j <= end - 1; j++) {
    if (arr->data[j] <= pivot) {
      swap(arr->data + i, arr->data + j);
      i++;
    }
  }

  swap(arr->data + i, arr->data + end);
  return i;
}

void _quicksort(Array *arr, size_t start, size_t end) {
  if (end - start + 1 < 2 || start > end || end < 0) return;
  
  size_t p = partition(arr, start, end);

  _quicksort(arr, start, p - 1);
  _quicksort(arr, p + 1, end);
}

void quicksort(Array *arr) {
  _quicksort(arr, 0, arr->len - 1);
}

int main(int argc, char *argv[argc + 1]) {
  const int len = atoi(argv[1]);
  Array arr = init(len);

  prepopulate(arr, 1000);
  print(arr);
  quicksort(&arr);
  print(arr);
  return EXIT_SUCCESS;
}
