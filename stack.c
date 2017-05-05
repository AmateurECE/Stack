/*
 * NAME: stack_new.c -- a different test file for the stack.
 * AUTHOR: Ethan D. Twardy
 * CREATED: 05/05/17
 * LAST EDITED: 05/05/17
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "stack.h"

static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

int main(int argc, char * argv[])
{
  int * pNum;
  Stack * stack = malloc(sizeof(Stack));

  if (stack == NULL)
    error_exit("Could not allocate memory for stack!");

  srand((unsigned)time(NULL));

  // Initialize the stack with size 10 and destroy = stdlib::free()
  stack_init(stack, free, 10);

  // Fill the stack
  printf("==== Inserting ====\n");
  for (int i = 0; i < 10; i++) {
    if ((pNum = malloc(sizeof(int))) == NULL)
      error_exit("Could not allocate memory for pNum!");
    *pNum = rand() % 10;
    printf("int %d @ %p\n", *pNum, pNum);
    stack_push(stack, (void *)pNum);
  }

  // Do not allow insertion into a full stack
  if (stack_isfull(stack)) {
    pNum = malloc(sizeof(int));
    *pNum = rand() % 10;
    assert(stack_push(stack, pNum) == -1);
    free(pNum);
  }

  // Peek at the top of the stack
  printf("==== Peek ====\n");
  stack_peek(stack, (void **)&pNum);
  printf("int %d @ %p\n", *pNum, pNum);
  printf("==============\n");

  // Empty the stack
  printf("==== Removing =====\n");
  while (!stack_isempty(stack)) {
    stack_pop(stack, (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    free(pNum);
  }

  // Do not allow removal from an empty stack
  if (stack_isempty(stack))
    assert(stack_pop(stack, (void **)&pNum) == -1);

  stack_dest(stack);
  free(stack);

  return 0;
}
