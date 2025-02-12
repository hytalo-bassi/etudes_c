#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define MAX_SIZE 10

typedef struct _heap {
  size_t size;
  int* arr;
} Heap;

void swap(int* a, int* b);

void maxheapify(Heap* heap, int i);

Heap* build_max_heap(int* arr, size_t n);

int parent(int i);

int left(int i);

int right(int i);

void prepopulate(int *arr, size_t s);

void print(Heap heap);

int main() {
  int* arr = malloc(sizeof(int) * MAX_SIZE);
  prepopulate(arr, MAX_SIZE);
  
  Heap *heap = build_max_heap(arr, MAX_SIZE);
  
  print(*heap);
  return EXIT_SUCCESS;
}

void swap(int *a, int* b) {
  int tmp = *a;
  
  *a = *b;
  *b = tmp;
}

void maxheapify(Heap *heap, int i) {
  int l = left(i + 1) - 1;
  int r = right(i + 1) - 1;
  int largest;
  
  // Acessar alem da posição floor(n/2) vai levar para um no sem filhos
  if (i > heap->size / 2)
    return;

  if (heap->arr[l] > heap->arr[i])
    largest = l;
  else
    largest = i;

  if (r <= heap->size - 1 && heap->arr[r] > heap->arr[largest])
    largest = r;
  
  if (largest != i) {
    swap(heap->arr + largest, heap->arr + i);
    maxheapify(heap, largest);
  }
}

Heap* build_max_heap(int *arr, size_t n) {
  Heap* heap = malloc(sizeof(Heap));
  heap->size = n;
  heap->arr = arr;

  for (int i = (n / (int) 2) - 1; i >= 0; i--)
    maxheapify(heap, i);

  return heap;
}

int parent(int i) {
  return i / 2; 
}

int left(int i) {
  return 2*i;
}

int right(int i) {
  return 2*i + 1;
}

void print(Heap heap) {
  int i = 0;
  int h = 0;

  while (i < heap.size) {
    printf("%d ", heap.arr[i]);
    // se o cursor está em cima do limite de números da altura h
    if (i == pow(2, h + 1) - 2) {
      puts("\n");
      h++;
    }
    i++;
  }

  puts("");
}

// void print(Heap heap) {
//   printf("[");
//   
//   for (size_t i = 0; i < heap.size - 1; i++) {
//     printf("%d, ", heap.arr[i]);
//   }
// 
//   printf("%d]\n", heap.arr[heap.size - 1]);
// }

void prepopulate(int* arr, size_t n) {
  arr[0] = 1;
  for (size_t i = 1; i < n; i++)
    arr[i] = 11 - i;
}
