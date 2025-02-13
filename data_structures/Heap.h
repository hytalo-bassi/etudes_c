// Como este arquivo define uma estrutura comum para um algoritmo de Ordenação,
// o HeapSort, ele será convertido para um header file. Header Files são arquivos
// que podem ser utilizados por outros programas em C.

#ifndef HEAP_DSA_GUARD
#define HEAP_DSA_GUARD

#include <stdlib.h>

void swap(int* a, int* b);

void maxheapify(int* arr, size_t size, int i);

void build_max_heap(int* arr, size_t n);

int parent(int i);

int left(int i);

int right(int i);

void prepopulate(int *arr, size_t s);

void print(int* heap, size_t size);

#endif
