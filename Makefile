CC		=	gcc
RM		=	rm -rf

UT_DIR		=	unit_test

CFLAGS		=	-g3 -W -Wall -ansi -Iinclude -I$(UT_DIR)/include

UT_SRC		=	$(UT_DIR)/unit_test.c
UT_OBJ		=	$(UT_SRC:.c=.o)

SLIST_BIN	=	ut_slist
SLIST_SRC	=	$(UT_DIR)/ut_slist.c
SLIST_OBJ	=	$(SLIST_SRC:.c=.o)

STACK_BIN	=	ut_stack
STACK_SRC	=	$(UT_DIR)/ut_stack.c
STACK_OBJ	=	$(STACK_SRC:.c=.o)

LIST_BIN	=	ut_list
LIST_SRC	=	$(UT_DIR)/ut_list.c
LIST_OBJ	=	$(LIST_SRC:.c=.o)

$(LIST_BIN):		$(UT_OBJ) $(LIST_OBJ)
			$(CC) $(UT_OBJ) $(LIST_OBJ) -o $(LIST_BIN)

$(SLIST_BIN):		$(UT_OBJ) $(SLIST_OBJ)
			$(CC) $(UT_OBJ) $(SLIST_OBJ) -o $(SLIST_BIN)

$(STACK_BIN):		$(UT_OBJ) $(STACK_OBJ)
			$(CC) $(UT_OBJ) $(STACK_OBJ) -o $(STACK_BIN)

all:			$(SLIST_BIN) $(STACK_BIN) $(LIST_BIN)

clean:
			$(RM) $(UT_OBJ)
			$(RM) $(SLIST_OBJ)
			$(RM) $(STACK_OBJ)
			$(RM) $(LIST_OBJ)


fclean:			clean
			$(RM) $(SLIST_BIN)
			$(RM) $(STACK_BIN)
			$(RM) $(LIST_BIN)


re:			fclean all

.c.o:
			$(CC) $(CFLAGS) -c $< -o $@
