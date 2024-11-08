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

void swap(int *a, int *b) {
  const int tmp = *a;
  *a = *b;
  *b = tmp;
  // We're going to use this method to swap the values of nodes also.
  // That is not a good idea if you're planning to add more information
  // in a node other than a number 'val', since it will not truly swap
  // the node but the 'val' field.
}

List init() {
  List res = { .len = 0, .head = NULL };
  return res;
}

void insert(List *l, int val) {
  Node *ptr = l->head;
  l->len = l->len + 1;

  Node *n = malloc(sizeof(Node));
  n->val = val;
  n->next = NULL;
  
  if (ptr == NULL) {
    l->head = n;
    return;
  }

  while (ptr->next != NULL)
    ptr = ptr->next;

  n->prev = ptr;
  ptr->next = n;
}

// It first looked reasonable to add this method for
// pushing nodes to any position, but we're not
// going to use push in the insertion sort. Anyway,
// it will stand here just for admiration.
short push(List *l, int val, size_t i) {
  if (i > l->len)
    return 1;
  else if (i < 0)
    return -1;
  else if (i == l->len) {
    // Adding to the end of the list
    insert(l, val);
  }
  else {
    l->len = l->len + 1;
    Node *n = malloc(sizeof(Node));
    n->val = val;
    Node *ptr = l->head;
    
    if (i == 0) {
      // If the node is being pushed to the start of the list
      l->head->prev = n;
      n->next = l->head;
      l->head = n;
    } else {
      // The node is being pushed anywhere between the second and second to last position;
      for (size_t j = 0; j < i; j++)
            ptr = ptr->next;
      n->next = ptr;
      n->prev = ptr->prev;

      ptr->prev->next = n;
      ptr->prev = n;

    }
  }

  return 0;
}

void print(List l) {
  Node *ptr = l.head;
  while (ptr != NULL) {
    if (ptr->next != NULL)
      printf("[%d]<->", ptr->val);
    else
      printf("[%d]\n", ptr->val);
    ptr = ptr->next;
  }
}


int randint(int range) {
  return rand() % (range + 1);
}

void prepopulate(List *l, int n, int range) {
  for (size_t i = 0; i < n; i++)
    insert(l, randint(range));
}


void insertion_sort(List *l) {
  if (l->head == NULL)
    return;
  for (Node *i = l->head->next; i != NULL; i = i->next) {
    Node *j = i;
    while (j->prev != NULL && j->prev->val > j->val) {
      swap(&(j->prev->val), &(j->val));
      j = j->prev;
    }
  }
}

void _freeNode(Node *n) {
  if (n == NULL)
    return;
  _freeNode(n->next);
  free(n);
}

void freel(List *l) {
  _freeNode(l->head);
}

int main(int argc, char *argv[argc + 1]) {
  srand(time(NULL));

  if (argc == 1) {
    puts("./a.out <length of array>");
    return EXIT_FAILURE;
  }

  const int len = atoi(argv[1]);
  List l = init();

  prepopulate(&l, len, len);
  print(l);
  
  const int pos = randint(len);
  const int val = randint(len);

  printf("Adding '%d' to the %dth position.\n", val, pos + 1);

  push(&l, val, pos);

  print(l);
  
  puts("The list after sorting:");
  insertion_sort(&l);
  print(l);
  
  freel(&l);
  return EXIT_SUCCESS;
}
