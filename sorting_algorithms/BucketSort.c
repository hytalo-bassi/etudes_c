#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct iNode {
  struct iNode *next;
  struct iNode *prev;
  int val;
} Node;

typedef struct iList {
  size_t len;
  Node *head;
} List;

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

List init_l() {
  List res = { .len = 0, .head = NULL };
  return res;
}

void sortedInsert(List *l, int val) {
  Node *ptr = l->head;
  l->len = l->len + 1;

  Node *n = malloc(sizeof(Node));
  n->val = val;
  
  if (ptr == NULL || ptr->val >= val) {
    n->next = ptr;
    l->head = n;
    return;
  }

  while (ptr->next != NULL && (ptr->next->val < val))
    ptr = ptr->next;
  
  n->next = ptr->next;
  n->prev = ptr;
  ptr->next = n;
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

void print_l(List l) {
  Node *ptr = l.head;
  while (ptr != NULL) {
    if (ptr->next != NULL)
      printf("[%d]<->", ptr->val);
    else
      printf("[%d]\n", ptr->val);
    ptr = ptr->next;
  }
}

void prepopulate(Array arr, int range) {
  srand(time(NULL));
  for (size_t i = 0; i < arr.len; i++) {
    arr.data[i] = rand() % (range + 1);
  }
}

void bucket_sort(Array *arr, int m) {
  List buckets[arr->len];
  m++;
  
  size_t i = 0;
  for (; i < arr->len; i++){
    buckets[i] = init_l();
  }

  for (i = 0; i < arr->len; i++)
    sortedInsert(buckets + (arr->len * arr->data[i]) / m, arr->data[i]);
  
  size_t n = 0;
  for (i = 0; i < arr->len; i++) {
    Node *ptr = buckets[i].head;
    while (ptr != NULL) {
      arr->data[n] = ptr->val;
      ptr = ptr->next;
      n++;
    }
  }
}

int main(int argc, char *argv[argc + 1]) {
  if (argc == 1) {
    puts("./a.out <length of array>");
    return EXIT_SUCCESS;
  }

  const int len = atoi(argv[1]);
  Array arr = init(len);

  prepopulate(arr, len);
  print(arr);

  bucket_sort(&arr, len);

  print(arr);
  return EXIT_SUCCESS;
}
