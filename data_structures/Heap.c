#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int parent(int i) {
  return i / 2; 
}

int left(int i) {
  return 2*i;
}

int right(int i) {
  return 2*i + 1;
}

void swap(int *a, int* b) {
  int tmp = *a;
  
  *a = *b;
  *b = tmp;
}

void maxheapify(int *arr, size_t size, int i) {
  int l = left(i + 1) - 1;
  int r = right(i + 1) - 1;
  int largest;
  
  if (l < size && arr[l] > arr[i])
    largest = l;
  else
    largest = i;

  if (r < size && arr[r] > arr[largest])
    largest = r;
  
  if (largest != i) {
    swap(arr + largest, arr + i);
    maxheapify(arr, size, largest);
  }
}

void build_max_heap(int *arr, size_t n) {
  for (int i = (n / (int) 2) - 1; i >= 0; i--)
    maxheapify(arr, n, i);
}

void print(int* heap, size_t size) {
  int i = 0;
  int h = 0;

  while (i < size) {
    printf("%d ", heap[i]);
    // se o cursor está em cima do limite de números da altura h
    if (i == pow(2, h + 1) - 2) {
      puts("\n");
      h++;
    }
    i++;
  }

  puts("");
}

void prepopulate(int* arr, size_t n) {
  arr[0] = 1;
  for (size_t i = 1; i < n; i++)
    arr[i] = 11 - i;
}


