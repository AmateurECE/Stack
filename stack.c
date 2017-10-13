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
 * FUNCTION:	    stack_init
 *
 * DESCRIPTION:	    Initializes the stack to the size specified in 'size.'
 *
 * ARGUMENTS:	    stack: (Stack *) -- the stack to be operated on.
 *		    destroy: (void (*)(void *)) -- pointer to a user-defined
 *			     function that frees memory held within the stack.
 *		    size: int -- the size of the stack.
 *
 * RETURN:	    void.
 *
 * NOTES:	    O(1)
 ***/
void stack_init(Stack * stack, void (*destroy)(void * data), int size)
{
  stack->destroy = destroy;
  stack->size = 0;
  stack->capacity = size;
  stack->head = 0;
  stack->stack = (void *)calloc(size, sizeof(void *));
}

/*******************************************************************************
 * FUNCTION:	    stack_peek
 *
 * DESCRIPTION:	    Returns without removing the top of the stack.
 *
 * ARGUMENTS:	    stack: (Stack *) -- the stack to be operated on.
 *		    pData: (void **) -- destination to place the top element.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int stack_peek(Stack * stack, void ** pData)
{
  if (stack_isempty(stack))
    return -1;

  *pData = stack->stack[stack->head - 1];
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    stack_push
 *
 * DESCRIPTION:	    Pushes data onto the top of the stack.
 *
 * ARGUMENTS:	    stack: (Stack *) -- the stack to be operated on.
 *		    data: (void *) -- data to place on the stack.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int stack_push(Stack * stack, void * data)
{
  if (stack_isfull(stack))
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
 * ARGUMENTS:	    stack: (Stack *) -- the stack to be operated on.
 *		    data: (void **) -- destination for the top of the stack.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(1)
 ***/
int stack_pop(Stack * stack, void ** data)
{
  if (stack_isempty(stack))
    return -1;

  stack->head--;
  *data = stack->stack[stack->head];
  stack->size--;
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    stack_dest
 *
 * DESCRIPTION:	    Removes all data in the stack, and sets all bytes of memory
 *		    to 0. If destroy is set to NULL, does not free the memory
 *		    held within the stack.
 *
 * ARGUMENTS:	    stack: (Stack *) -- the stack to be operated on.
 *
 * RETURN:	    void.
 *
 * NOTES:	    O(n)
 ***/
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

/******************************************************************************/
