###############################################################################
# NAME:		    makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the 'stack' debugging program.
#
# CREATED:	    10/13/2017
#
# LAST EDITED:	    03/16/2018
###

TOP:=$(PWD)
CFLAGS = -g -O0 -Wall
CC=gcc

SRCS += stack.c
SRCS += test.c

OBJS = $(patsubst %.c,%.o,$(SRCS))

.PHONY: debug clean force

all: force $(OBJS) stack
	dsymutil stack

$(OBJS): force

stack: force
	$(CC) $(CFLAGS) -o stack $(OBJS)

clean: force
	rm -f $(TOP)/*.c~
	rm -f $(TOP)/*.h~
	rm -f $(TOP)/*.o
	rm -f $(TOP)/Makefile~

force:

###############################################################################
