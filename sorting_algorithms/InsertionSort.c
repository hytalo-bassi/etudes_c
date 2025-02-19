#include <stdio.h>
#include <stdlib.h>
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

void insertion_sort(Array *arr) {
  int k = 0;
  for (size_t i = 1; i < arr->len; i++) {
    size_t j = i;
    while (j > 0 && arr->data[j - 1] > arr->data[j]) {
      swap(arr->data + j - 1, arr->data + j);
      k++;
      j--;
    }
  }
  printf("swaps: %d\n", k);
}

int main(int argc, char *argv[argc + 1]) {
  if (argc == 1) {
    puts("./a.out <length of array>");
    return EXIT_SUCCESS;
  }

  const int len = atoi(argv[1]);
  Array arr = init(len);

  prepopulate(arr, 1000);
  print(arr);

  insertion_sort(&arr);
  print(arr);
  return EXIT_SUCCESS;
}
