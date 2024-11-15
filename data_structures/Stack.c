#include <stdlib.h>
#include <stdio.h>
#define MAX_SIZE 1000

typedef struct {
     int arr[MAX_SIZE];
     int top;
} Stack;

void init(Stack *stack) {
  stack->top = -1;
}

short isEmpty(Stack *stack) {
  return stack->top < 0;
}

short isFull(Stack *stack) {
  return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, int v) {
  if (isFull(stack)) {
    puts("Stack is full");
    return;
  }

  stack->arr[++stack->top] = v;
}

int pop(Stack *stack) {
  if (isEmpty(stack)) {
    puts("Stack is empty");
    return -1;
  }
  int v = stack->arr[stack->top];
  --stack->top;
  return v;
}


int peek(Stack *stack) {
  if (isEmpty(stack)) {
    puts("Stack is empty");
    return -1;
  }

  return stack->arr[stack->top];
}

void adds_to_stack(Stack *stack) {
  int val;
  printf("Value to add: ");
  scanf("%d", &val);
  push(stack, val);
}

void print_stack(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack is empty\n");
    return;
  }

  size_t j = stack->top;
  for (; j > 0; j--) 
    printf("%d, ", stack->arr[j]);
  printf("%d\n", stack->arr[j]);
}

int main() {
  Stack stack;
  init(&stack);

  char help_message[] = "Type one of the following to do something:\n"
        "i: Inserts to the stack\n"
        "p: Pops from the stack\n"
        "r: Reads stack\n"
        "h: Prints this screen\n"
        "s: Stops program\n";

  char opt;
  puts(help_message);
  printf("Option: ");
  scanf(" %c", &opt);
  
  while (opt != 's') {
    switch (opt) {
      case 'h':
        puts(help_message);
        break;
      case 'r':
        print_stack(&stack);
        break;
      case 'p':
        printf("The element popped was %d\n", pop(&stack));
        break;
      case 'i':
        adds_to_stack(&stack);
        break;
      default:
        break;
    }

    printf("Option: ");
    scanf(" %c", &opt);
  }

  return EXIT_SUCCESS;
}
