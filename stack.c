/*******************************************************************************
 * NAME:	    stack.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Contains source code for an implementation of a stack.
 *		    Follows the typedefs and macros in stack.h. Also contains
 *		    test code for debugging which is compiled with 'make debug.'
 *
 * CREATED:	    05/05/17
 *
 * LAST EDITED:	    06/07/17
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    stack_create
 *
 * DESCRIPTION:	    Initializes a stack_t with the given information and returns
 *		    a pointer to it.
 *
 * ARGUMENTS:	    size: int -- the size of the stack.
 *		    destroy: (void (*)(void *)) -- pointer to a user-defined
 *			     function that frees memory held within the stack.
 *
 * RETURN:	    stack_t * -- or NULL, if unsuccessful.
 *
 * NOTES:	    O(1)
 ***/
stack_t * stack_create(int size, void (*destroy)(void *))
{
  if (size == 0)
    return NULL;

  stack_t * stack = malloc(sizeof(stack_t));
  if (stack == NULL)
    return NULL;

  *stack = (stack_t){
    .destroy = destroy,
    .size = 0,
    .capacity = size,
    .head = 0,
    .stack = calloc(size, sizeof(void *))
  };

  if (stack->stack == NULL)
    return NULL;

  return stack;
}

/*******************************************************************************
 * FUNCTION:	    stack_peek
 *
 * DESCRIPTION:	    Returns without removing the top of the stack.
 *
 * ARGUMENTS:	    stack: (stack_t *) -- the stack to be operated on.
 *		    pData: (void **) -- destination to place the top element.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int stack_peek(stack_t * stack, void ** pData)
{
  if (stack == NULL || pData == NULL || stack_isempty(stack))
    return -1;

  *pData = stack->stack[stack->head - 1];
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    stack_push
 *
 * DESCRIPTION:	    Pushes data onto the top of the stack.
 *
 * ARGUMENTS:	    stack: (stack_t *) -- the stack to be operated on.
 *		    data: (void *) -- data to place on the stack.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int stack_push(stack_t * stack, void * data)
{
  if (stack == NULL || data == NULL || stack_isfull(stack))
    return -1;

  stack->stack[stack->head] = (void *)data;
  stack->head++;
  stack->size++;
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    stack_pop
 *
 * DESCRIPTION:	    Pops data from the top of the stack.
 *
 * ARGUMENTS:	    stack: (stack_t *) -- the stack to be operated on.
 *		    data: (void **) -- destination for the top of the stack.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int stack_pop(stack_t * stack, void ** data)
{
  if (stack == NULL || data == NULL || stack_isempty(stack))
    return -1;

  stack->head--;
  *data = stack->stack[stack->head];
  stack->size--;
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    stack_destroy
 *
 * DESCRIPTION:	    Removes all data in the stack, and sets all bytes of memory
 *		    to 0. If destroy is set to NULL, does not free the memory
 *		    held within the stack.
 *
 * ARGUMENTS:	    stack: (stack_t *) -- the stack to be operated on.
 *
 * RETURN:	    void.
 *
 * NOTES:	    O(n)
 ***/
void stack_destroy(stack_t ** stack)
{
  if (stack == NULL || *stack == NULL)
    return;

  void * data;
  while (!stack_isempty(*stack)) {
    stack_pop(*stack, &data);
    if ((*stack)->destroy)
      (*stack)->destroy(data);
  }

  free((*stack)->stack);
  free(*stack);
  *stack = NULL;
}

/******************************************************************************/
