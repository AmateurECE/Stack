/******************************************************************************
 * NAME:	    stack.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Contains source code for an implementation of a stack.
 *		    Follows the typedefs and macros in stack.h. Also contains
 *		    test code for which can be compiled with 'make debug.'
 *
 * CREATED:	    05/05/2017
 *
 * LAST EDITED:	    03/14/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    stack_create
 *
 * DESCRIPTION:	    Initializes a stack with the given information and returns
 *		    a pointer to it.
 *
 * ARGUMENTS:	    size: int -- the size of the stack.
 *		    destroy: (void (*)(void *)) -- pointer to a user-defined
 *			     function that frees memory held within the stack.
 *
 * RETURN:	    stack * -- or NULL, if unsuccessful.
 *
 * NOTES:	    O(1)
 ***/
stack * stack_create(int size, void (*destroy)(void *))
{
  if (size == 0)
    return NULL;

  stack * _stack = malloc(sizeof(stack));
  if (_stack == NULL)
    return NULL;

  *_stack = (stack){
    .destroy = destroy,
    .size = 0,
    .capacity = size,
    .head = 0,
    .stack = calloc(size, sizeof(void *))
  };

  if (_stack->stack == NULL)
    return NULL;

  return _stack;
}

/******************************************************************************
 * FUNCTION:	    stack_peek
 *
 * DESCRIPTION:	    Returns without removing the top of the stack.
 *
 * ARGUMENTS:	    stack: (stack *) -- the stack to be operated on.
 *		    pData: (void **) -- destination to place the top element.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int stack_peek(stack * stack, void ** pData)
{
  if (stack == NULL || pData == NULL || stack_isempty(stack))
    return -1;

  *pData = stack->stack[stack->head - 1];
  return 0;
}

/******************************************************************************
 * FUNCTION:	    stack_push
 *
 * DESCRIPTION:	    Pushes data onto the top of the stack.
 *
 * ARGUMENTS:	    stack: (stack *) -- the stack to be operated on.
 *		    data: (void *) -- data to place on the stack.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int stack_push(stack * stack, void * data)
{
  if (stack == NULL || data == NULL || stack_isfull(stack))
    return -1;

  stack->stack[stack->head] = (void *)data;
  stack->head++;
  stack->size++;
  return 0;
}

/******************************************************************************
 * FUNCTION:	    stack_pop
 *
 * DESCRIPTION:	    Pops data from the top of the stack.
 *
 * ARGUMENTS:	    stack: (stack *) -- the stack to be operated on.
 *		    data: (void **) -- destination for the top of the stack.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int stack_pop(stack * stack, void ** data)
{
  if (stack == NULL || data == NULL || stack_isempty(stack))
    return -1;

  stack->head--;
  *data = stack->stack[stack->head];
  stack->size--;
  return 0;
}

/******************************************************************************
 * FUNCTION:	    stack_destroy
 *
 * DESCRIPTION:	    Removes all data in the stack, and sets all bytes of memory
 *		    to 0. If destroy is set to NULL, does not free the memory
 *		    held within the stack.
 *
 * ARGUMENTS:	    st: (stack *) -- the stack to be operated on.
 *
 * RETURN:	    void.
 *
 * NOTES:	    O(n)
 ***/
void stack_destroy(stack ** st)
{
  if (st == NULL || *st == NULL)
    return;

  void * data;
  while (!stack_isempty(*st)) {
    stack_pop(*st, &data);
    if ((*st)->destroy)
      (*st)->destroy(data);
  }

  free((*st)->stack);
  free(*st);
  *st = NULL;
}

/******************************************************************************
 * FUNCTION:	    stack_traverse
 *
 * DESCRIPTION:	    Traverse the stack in `st' and invoke the callback function
 *		    `func' on each entry in the stack.
 *
 * ARGUMENTS:	    st: (stack *) -- the stack to traverse.
 *		    func: (void (*)(void *)) -- the callback function.
 *
 * RETURN:	    void.
 *
 * NOTES:	    none.
 ***/
void stack_traverse(stack * st, void (*func)(void *))
{
  if (stack_size(st) == 0 || func == NULL)
    return;
  int i = 0;
  for (void * e = st->stack[i++]; e != NULL; e = st->stack[i++])
    func(e);
}

/*****************************************************************************/
