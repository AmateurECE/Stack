/*******************************************************************************
 * NAME:	    stack.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file for the implementation of a stack. Contains
 *		    API function prototypes and typedefs.
 *
 * CREATED:	    04/14/17
 *
 * LAST EDITED:	    02/12/2018
 ***/

#ifndef __ET_STACK_H__
#define __ET_STACK_H__

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  void (*destroy)(void *);
  int size;
  int capacity;
  int head;
  void ** stack;

} stack;

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define stack_size(stack) ((stack)->size)
#define stack_isfull(stack) ((stack)->size == (stack)->capacity ? 1 : 0)
#define stack_isempty(stack) ((stack)->size == 0 ? 1 : 0)

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern stack * stack_create(int, void (*)(void *));
extern int stack_peek(stack *, void **);
extern int stack_push(stack *, void *);
extern int stack_pop(stack *, void **);
extern void stack_destroy(stack **);

#endif /* __ET_STACK_H__ */

/******************************************************************************/
