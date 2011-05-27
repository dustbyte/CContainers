CC		=	gcc
RM		=	rm -f

CFLAGS		+=	-W -Wall -ansi -pedantic
CFLAGS		+=	-gdwarf-2 -g3

INCDIR		=	include
SRCDIR		=	unit_test

UT_LIST		=	ut_list
LIST_SRC	=	$(SRCDIR)/ut_list.c
LIST_OBJ	=	$(LIST_SRC:.c=.o)

UT_SLIST	=	ut_slist
SLIST_SRC	=	$(SRCDIR)/ut_slist.c
SLIST_OBJ	=	$(SLIST_SRC:.c=.o)

UT_STACK	=	ut_stack
STACK_SRC	=	$(SRCDIR)/ut_stack.c
STACK_OBJ	=	$(STACK_SRC:.c=.o)

UT_QUEUE	=	ut_queue
QUEUE_SRC	=	$(SRCDIR)/ut_queue.c
QUEUE_OBJ	=	$(QUEUE_SRC:.c=.o)

all:			$(UT_LIST)

$(UT_LIST):		$(LIST_OBJ) $(SLIST_OBJ) $(STACK_OBJ) $(QUEUE_OBJ)
			$(CC) $(LIST_OBJ) $(LDFLAGS) -o $(UT_LIST)
			$(CC) $(SLIST_OBJ) $(LDFLAGS) -o $(UT_SLIST)
			$(CC) $(STACK_OBJ) $(LDFLAGS) -o $(UT_STACK)
			$(CC) $(QUEUE_OBJ) $(LDFLAGS) -o $(UT_QUEUE)

clean:
			$(RM) $(LIST_OBJ)
			$(RM) $(SLIST_OBJ)
			$(RM) $(STACK_OBJ)
			$(RM) $(QUEUE_OBJ)

distclean:		clean
			$(RM) $(UT_LIST)
			$(RM) $(UT_SLIST)
			$(RM) $(UT_STACK)
			$(RM) $(UT_QUEUE)

re:			distclean all

.c.o:
			$(CC) -I$(INCDIR) $(CFLAGS) -c $< -o $@
