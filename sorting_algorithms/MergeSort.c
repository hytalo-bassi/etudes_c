#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Array {
    int *data;
    size_t len;
} Array;

int min(int a, int b) {
  if (a <= b) {
    return a;
  }

  return b;
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

Array merge(Array *left, Array *right) {
  Array res = init(left->len + right->len);
  size_t left_i = 0;
  size_t right_i = 0;
  size_t i = 0;

  while (i < res.len) {
    while (left_i < left->len && (left->data[left_i] <= right->data[min(right_i, right->len)] || right_i == right->len)) {
      res.data[i++] = left->data[left_i++];
    }

    while (right_i < right->len && (right->data[right_i] < left->data[left_i] || left_i == left->len)) {
      res.data[i++] = right->data[right_i++];
    }
  }

  return res;
}

Array mergesort(Array *arr) {
  if (arr->len < 2) return *arr;
  
  Array left = init(arr->len / 2);
  Array right = init(arr->len - left.len);

  memcpy(left.data, arr->data, sizeof(int) * left.len);
  memcpy(right.data, arr->data + left.len, sizeof(int) * right.len);
  
  Array l1 = mergesort(&left);
  Array l2 = mergesort(&right);
  return merge(&l1, &l2);
}

int main(int argc, char *argv[argc + 1]) {
  const int len = atoi(argv[1]);
  Array arr = init(len);

  prepopulate(arr, 2147483646);
  // print(arr);
  
  // print(mergesort(&arr));
  return EXIT_SUCCESS;
}
