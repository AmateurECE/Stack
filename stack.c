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

#ifdef CONFIG_DEBUG_STACK
#include <time.h>
#include <assert.h>
#endif /* CONFIG_DEBUG_STACK */

#include "stack.h"

/*******************************************************************************
 * LOCAL PROTOTYPES
 ***/

#ifdef CONFIG_DEBUG_STACK
static inline void error_exit(char *);
#endif /* CONFIG_DEBUG_STACK */

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

/*******************************************************************************
 * MAIN
 ***/

#ifdef CONFIG_DEBUG_STACK
int main(int argc, char * argv[])
{
  int * pNum;
  Stack * stack = malloc(sizeof(Stack));

  if (stack == NULL)
    error_exit("Could not allocate memory for stack!");

  srand((unsigned)time(NULL));

  /* Initialize the stack with size 10 and destroy = stdlib::free() */
  stack_init(stack, free, 10);

  /* Fill the stack */
  printf("==== Inserting ====\n");
  for (int i = 0; i < 10; i++) {
    if ((pNum = malloc(sizeof(int))) == NULL)
      error_exit("Could not allocate memory for pNum!");
    *pNum = rand() % 10;
    printf("int %d @ %p\n", *pNum, pNum);
    stack_push(stack, (void *)pNum);
  }

  /* Do not allow insertion into a full stack */
  if (stack_isfull(stack)) {
    pNum = malloc(sizeof(int));
    *pNum = rand() % 10;
    assert(stack_push(stack, pNum) == -1);
    free(pNum);
  }

  /* Peek at the top of the stack */
  printf("==== Peek ====\n");
  stack_peek(stack, (void **)&pNum);
  printf("int %d @ %p\n", *pNum, pNum);
  printf("==============\n");

  /* Empty the stack */
  printf("==== Removing =====\n");
  while (!stack_isempty(stack)) {
    stack_pop(stack, (void **)&pNum);
    printf("int %d @ %p\n", *pNum, pNum);
    free(pNum);
  }

  /* Do not allow removal from an empty stack */
  if (stack_isempty(stack))
    assert(stack_pop(stack, (void **)&pNum) == -1);

  stack_dest(stack);
  free(stack);

  return 0;
}
#endif /* CONFIG_DEBUG_STACK */

/*******************************************************************************
 * LOCAL FUNCTIONS
 ***/

#ifdef CONFIG_DEBUG_STACK
static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}
#endif /* CONFIG_DEBUG_STACK */

/******************************************************************************/
