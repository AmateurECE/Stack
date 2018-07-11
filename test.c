/******************************************************************************
 * NAME:	    test.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains the debugging code for stack.c
 *
 * CREATED:	    10/13/2017
 *
 * LAST EDITED:	    07/10/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stack.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define error_exit(...) { fprintf(stderr, __VA_ARGS__); exit(1); }

/******************************************************************************
 * LOCAL PROTOTYPES
 ***/

static int test_create(void);
static int test_peek(void);
static int test_push(void);
static int test_pop(void);
static int test_destroy(void);

/******************************************************************************
 * MAIN
 ***/

int main(int argc, char * argv[])
{
  /* Seed the random number generator */
  srand((unsigned)time(NULL));

  printf("Test Create (stack_create): \t%s\n",
	 test_create() ? "Pass" : "Fail");
  printf("Test Peek (stack_peek):\t\t%s\n", test_peek() ? "Pass" : "Fail");
  printf("Test Push (stack_push):\t\t%s\n", test_push() ? "Pass" : "Fail");
  printf("Test Pop (stack_pop):\t\t%s\n", test_pop() ? "Pass" : "Fail");
  printf("Test Destroy (stack_destroy):\t%s\n",
	 test_destroy() ? "Pass" : "Fail");
}

/******************************************************************************
 * LOCAL FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    test_create
 *
 * DESCRIPTION:	    This function tests the function test_create.
 *
 * ARGUMENTS:	    void.
 *
 * RETURN:	    int -- 1 if the tests pass, 0 otherwise.
 *
 * NOTES:	    none.
***/
static int test_create(void)
{
  /* Normal allocation */
  stack * stack = stack_create(10, free);
  if (stack == NULL)
    return 0;
  stack_destroy(&stack);

  /* Size == 0 */
  stack = stack_create(0, free);
  if (stack != NULL)
    return 0;

  /* destroy == NULL */
  stack = stack_create(10, NULL);
  if (stack == NULL)
    return 0;
  stack_destroy(&stack);

  return 1;
}

/******************************************************************************
 * FUNCTION:	    test_peek
 *
 * DESCRIPTION:	    Test the stack_peek function.
 *
 * ARGUMENTS:	    void.
 *
 * RETURN:	    int -- 1 if the tests pass, 0 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_peek(void)
{
  stack * stack = stack_create(2, NULL);
  int num = 1;
  int * pNum = NULL;

  /* Peek on an empty stack */
  if (!stack_peek(stack, (void **)&pNum))
    return 0;

  if (stack_push(stack, &num))
    return 0;

  /* Normal peek */
  if (stack_peek(stack, (void **)&pNum))
    return 0;
  if (pNum == NULL)
    return 0;
  if (*pNum != 1)
    return 0;

  /* Test for NULL inputs */
  if (!stack_peek(NULL, (void **)&pNum))
    return 0;
  if (!stack_peek(stack, NULL))
    return 0;

  stack_destroy(&stack);
  return 1;
}

/******************************************************************************
 * FUNCTION:	    test_push
 *
 * DESCRIPTION:	    Tests the stack_push function
 *
 * ARGUMENTS:	    void.
 *
 * RETURN:	    int -- 1 if the tests pass, 0 otherwise.
 *
 * NOTES:	    none
 ***/
static int test_push(void)
{
  stack * stack = stack_create(10, free);
  int * pNum;

  /* Fill the stack */
  while (!stack_isfull(stack)){
    if ((pNum = malloc(sizeof(int))) == NULL)
      error_exit("Could not allocate memory for pNum!");
    *pNum = rand() % 10;
    if (stack_push(stack, (void *)pNum))
      return 0;
  }

  /* Do not allow insertion into a full stack */
  if (stack_isfull(stack)) {
    pNum = malloc(sizeof(int));
    *pNum = rand() % 10;
    if (stack_push(stack, pNum) != -1)
      return 0;
    free(pNum);
  } else { return 0; } /* The stack really should be full */

  if (stack_pop(stack, (void **)&pNum)) /* Remove one for the next test */
    return 0;
  free(pNum);
  pNum = malloc(sizeof(int));
  *pNum = rand() % 20;

  /* Test for NULL inputs */
  if (!stack_push(NULL, (void **)&pNum))
    return 0;
  if (!stack_push(stack, NULL))
    return 0;
  free(pNum);
  stack_destroy(&stack);

  return 1;
}

/******************************************************************************
 * FUNCTION:	    test_pop
 *
 * DESCRIPTION:	    This function tests the stack_pop function.
 *
 * ARGUMENTS:	    void
 *
 * RETURN:	    int -- 1 if the tests pass, 0 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_pop(void)
{
  stack * stack = stack_create(10, free);
  int * pNum;

  /* Fill the stack */
  while (!stack_isfull(stack)){
    if ((pNum = malloc(sizeof(int))) == NULL)
      error_exit("Could not allocate memory for pNum!");
    *pNum = rand() % 10;
    if (stack_push(stack, (void *)pNum))
      return 0;
  }

  while (!stack_isempty(stack)) {
    if (stack_pop(stack, (void **)&pNum))
      return 0;
    free(pNum);
  }

  if (stack_isempty(stack)) {
    if (!stack_pop(stack, (void **)&pNum))
      return 0;    
  } else { return 0; } /* The stack should really be empty here */

  pNum = malloc(sizeof(int));
  *pNum = rand() % 20;
  if (stack_push(stack, pNum))
    return 0;

  if (!stack_pop(NULL, (void **)&pNum))
    return 0;
  if (!stack_pop(stack, NULL))
    return 0;
  stack_destroy(&stack);

  return 1;
}

/******************************************************************************
 * FUNCTION:	    test_destroy
 *
 * DESCRIPTION:	    This function tests the stack_destroy function.
 *
 * ARGUMENTS:	    void.
 *
 * RETURN:	    int -- 1 if the tests pass, 0 otherwise.
 *
 * NOTES:	    none
 ***/
static int test_destroy(void)
{
  int * pNum;
  stack * stack = stack_create(10, free);
  stack_destroy(&stack);
  if (stack != NULL)
    return 0;

  stack = stack_create(10, free);
  /* Fill the stack */
  while (!stack_isfull(stack)){
    if ((pNum = malloc(sizeof(int))) == NULL)
      error_exit("Could not allocate memory for pNum!");
    *pNum = rand() % 10;
    if (stack_push(stack, (void *)pNum))
      return 0;
  }

  stack_destroy(&stack);
  if (stack != NULL)
    return 0;

  /* Test for NULL inputs--if it doesn't segfault, it passes. */
  stack = NULL;
  stack_destroy(&stack);
  stack_destroy(NULL);

  return 1;
}

/*****************************************************************************/
