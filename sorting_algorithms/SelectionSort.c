#include <stdio.h>

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print(int vec[], size_t len) {
  printf("[ ");
  for (size_t i = 0; i < len; i++) {
    if (i == len - 1) {
      printf("%d ]\n", vec[i]);
      continue;
    }
    printf("%d, ", vec[i]);
  }
}

void swap(int *a, int *b) {
  const int tmp = *a;
  *a = *b;
  *b = tmp;
}

// Doesn't work with already sorted arrays
void sort(int *arr, size_t len) {
  int *smallest = &arr[0];
  int start = 0;
  while (start < len) {
    for (size_t i = start; i < len; i++) {
        int *elem = &arr[i];
        if (*elem <= *smallest) {
          smallest = elem;
        }
    }
    
    swap(&arr[start], smallest);
    start++;
  }
}

int main() {
  int n;
  printf("How much elements are in the list: ");
  scanf("%d", &n);
  
  int vec[n];
  
  for (size_t i = 0; i < n; i++) {
    int val;
    printf("Inform the %dth number: ", i + 1);
    scanf("%d", &val);
    vec[i] = val;
  }
  
  print(vec, n);

  sort(vec, n);
  print(vec, n);
}
