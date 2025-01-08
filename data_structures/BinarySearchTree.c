#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT_SIZE 256

typedef struct _data {
  int val;
  const char *key;
} Data;

typedef struct _node {
  struct _node *p;
  struct _node *left;
  struct _node *right;
  Data d;
} Node;

typedef struct _tree {
  Node* root;
} Tree;

Node *create_node(int val, const char *key) {
  Data z = { val, key };

  Node *n = malloc(sizeof(Node));
  *n = (Node) { NULL, NULL, NULL, z };
  
  return n;
}

char* read_string(char *str) {
  fgets(str, INPUT_SIZE, stdin);
  str[strcspn(str, "\n")] = '\0';

  return str;
}

// Inserts Data to a BST. If the root node T
// is null, then creates a root node.
// Arguments:
//  Tree* T: the tree.
//  int val: the value to be inserted.
//  const char* key: satellite data.
// Returns: nothing.
void insert(Tree* T, int val, const char* key);

// Prints the values of the tree already sorted (Inorder Tree Walk)
// Arguments:
//  Node *T: the root node of the tree(T->p == NULL)
//  Node *max: pointer to the rightmost node of the tree.
// Returns: nothing
void inwalk(Node *T, Node* max);


// Searches in a BST for some value.
// Arguments:
//  Node *T: the root node of the tree(T->p == NULL);
//  int val: the value to be searched.
// Returns: the found Node of NULL.
Node *search(Node *T, int val);


// Returns the maximum value in a BST.
// Arguments:
//  Tree T: the tree.
// Returns: the maximum value node.
Node* max(Tree T);

// Returns the minimum value in a BST.
// Arguments:
//  Tree T: the tree.
// Returns: the minimum value node.
Node* min(Tree T);

// Free a entire Tree. Deallocates the left node,
// then the right node and n node.
// Arguments:
//  Node *n: pointer to the parent node.
// Returns: void.
void free_node(Node* n);


int main() {
  Tree T = { NULL };
  
  char val_buffer[INPUT_SIZE], key_buffer[INPUT_SIZE];

  while (strcmp("stop", read_string(val_buffer)) != 0) {
    read_string(key_buffer);

    insert(&T, strtol(val_buffer, NULL, 10), strdup(key_buffer));
  }
  
  puts("Search:");
  read_string(val_buffer);
  printf("%s\n", search(T.root, strtol(val_buffer, NULL, 10))->d.key);

  inwalk(T.root, max(T));
  free_node(T.root);

  return EXIT_SUCCESS;
}

// Inserts y to x. Helper function
void _insert(Node *x, Node *y) {
  if (y == NULL)
    return;

  if (y->d.val < x->d.val) {
    if (x->left != NULL)
      return _insert(x->left, y);

    x->left = y;
  } else {
    if (x->right != NULL)
      return _insert(x->right, y);

    x->right = y;
  }
  
  y->p = x;
}

void insert(Tree *T, int val, const char* key) {
  Node *n = create_node(val, key);
  if (T->root == NULL)
    T->root = n;
  else
    _insert(T->root, n);
}

void inwalk(Node *T, Node *max) {
  if (T == NULL)
    return;

  if (T->p == NULL)
    printf("{ ");
  if (T == max) {
    printf("%s: %d }\n", T->d.key, T->d.val);
    return;
  }
  
  inwalk(T->left, max);
  printf("%s: %d, ", T->d.key, T->d.val);
  inwalk(T->right, max);
}

Node *search(Node *T, int val) {
  if (T == NULL)
    return NULL;

  if (val < T->d.val)
    return search(T->left, val);
  else if (val == T->d.val)
    return T;

  return search(T->right, val);
}

Node *max(Tree T) {
  Node *n = T.root;
  while (n->right != NULL)
    n = n->right;

  return n;
}

Node *min(Tree T) {
  Node *n = T.root;
  while (n->left != NULL)
    n = n->left;

  return n;
}

void free_node(Node *n) {
  if (n == NULL)
    return;

  free_node(n->left);
  free_node(n->right);
  free(n);
}
