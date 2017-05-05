/*
 * NAME: stack.h -- custom implementation of a stack. Woot.
 * AUTHOR: Ethan D. Twardy
 * CREATED: 04/14/17
 * LAST EDITED: 04/14/17
 */

#ifndef __ET_STACK__
#define __ET_STACK__

#include <string.h>

/************* TYPE DEFINITIONS *************/
/********************************************/

typedef struct _Stack_{

  void (*destroy)(void *);
  int size;
  int capacity;
  int head;
  void ** stack;

} Stack;

/************* MACRO DEFINITIONS ************/
/********************************************/

#define stack_size(stack) ((stack)->size)
#define stack_isfull(stack) ((stack)->size == (stack)->capacity ? 1 : 0)
#define stack_isempty(stack) ((stack)->size == 0 ? 1 : 0)

/************* PUBLIC INTERFACE ************/
/*******************************************/

// FUNCTION: init O(1) -- initializes the stack to the size specified in size.
// PARAMETERS: stack: (Stack *) -- the stack to be operated on.
//             destroy: void (*)(void *) -- user defined function to free data.
//             size: int -- the capacity of the stack.
// RETURN: void
void stack_init(Stack * stack, void (*destroy)(void * data), int size)
{
  stack->destroy = destroy;
  stack->size = 0;
  stack->capacity = size;
  stack->head = 0;
  stack->stack = (void *)calloc(size, sizeof(void *));
}

// FUNCTION: peek O(1) -- returns, but does not remove, the head of the stack.
// PARAMETERS: stack (Stack *) -- the stack to be operated on.
// RETURN: void * -- head of the stack
int stack_peek(Stack * stack, void ** pData)
{
  if (stack_isempty(stack))
    return -1;

  *pData = stack->stack[stack->head - 1];
}

// FUNCTION: push O(1) -- pushes data onto the top of the stack.
// PARAMETERS: stack: (Stack *) -- the stack to be operated on.
//             data: (void *) -- the data to be pushed onto the stack.
// RETURN: int -- -1 on failure, 0 on success.
int stack_push(Stack * stack, void * data)
{
  if (stack_isfull(stack))
    return -1;

  stack->stack[stack->head] = (void *)data;
  stack->head++;
  stack->size++;
}

// FUNCTION: pop O(1) -- pops the data off of the top of the stack and places
//           it in data.
// PARAMETERS: stack: (Stack *) -- the stack to be operated on.
//             data: (void **) -- the data is placed here after being popped.
// RETURN: int -- -1 on failure, 0 on success.
int stack_pop(Stack * stack, void ** data)
{
  if (stack_isempty(stack))
    return -1;

  stack->head--;
  *data = stack->stack[stack->head];
  stack->size--;
}

// FUNCTION: dest O(n) -- sets all memory in the stack to 0.
// PARAMETERS: stack: (Stack *) -- the stack to be destroyed.
// RETURN: void
void stack_dest(Stack * stack)
{
  void * data;
  while (!stack_isempty(stack)) {
    stack_pop(stack, &data);
    stack->destroy(data);
  }

  free(stack->stack);
  memset(stack, 0, sizeof(Stack));
}

#endif // __ET_STACK__
