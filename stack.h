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
 * LAST EDITED:	    06/07/17
 ***/

#ifndef __ET_STACK_H__
#define __ET_STACK_H__

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct _Stack_{

  void (*destroy)(void *);
  int size;
  int capacity;
  int head;
  void ** stack;

} Stack;

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define stack_size(stack) ((stack)->size)
#define stack_isfull(stack) ((stack)->size == (stack)->capacity ? 1 : 0)
#define stack_isempty(stack) ((stack)->size == 0 ? 1 : 0)

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern void stack_init(Stack *, void (*)(void *), int);
extern int stack_peek(Stack *, void **);
extern int stack_push(Stack *, void *);
extern int stack_pop(Stack *, void **);
extern void stack_dest(Stack *);

#endif /* __ET_STACK_H__ */

/******************************************************************************/
