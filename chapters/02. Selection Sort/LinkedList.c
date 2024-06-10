#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct LinkedNode {
  int val;
  struct LinkedNode *next;
};

struct LinkedNode* insert(struct LinkedNode *last_node, int val) {
  struct LinkedNode *current_node = (struct LinkedNode*) malloc(sizeof (struct LinkedNode));
  current_node->val = val;
  current_node->next = NULL;

  if (last_node != NULL) {
    last_node->next = current_node;
  }

  return current_node;
}

void print(struct LinkedNode *node) {
  if (node == NULL) {
    return;
  }

  char end[6] = "\n";

  if (node->next != NULL) {
    strcpy(end, " -> \n");
  }

  printf(ANSI_COLOR_YELLOW "%p" ANSI_COLOR_CYAN " (val: %d)" ANSI_COLOR_RESET "%s", node, node->val, end);
  if (node->next != NULL) {
    print(node->next);
  }
}

int main() {
  struct LinkedNode first_node;
  struct LinkedNode *last_node;
  int i = 0;

  while (1) {
    char input[255];
    puts("Inform a value and press Enter (write s to stop): ");
    scanf("%s", &input);
    
    if (!strcmp(input, "s")) {
      break;
    }
    
    int val = atoi(input);
      
    if (i == 0) {
      first_node = *insert(NULL, val);
      last_node = &first_node;
    } else {
      last_node = insert(last_node, val);
    }

    i++;
  }
  print(&first_node);

  return EXIT_SUCCESS;
}
