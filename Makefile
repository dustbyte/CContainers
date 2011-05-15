CC		=	gcc
RM		=	rm -f

CFLAGS		+=	-W -Wall -ansi -pedantic
CFLAGS		+=	-gdwarf-2 -g3

INCDIR		=	include
SRCDIR		=	unit_test

UT_LIST		=	ut_list
LIST_SRC	=	$(SRCDIR)/ut_list.c
LIST_OBJ	=	$(LIST_SRC:.c=.o)

all:			$(UT_LIST)

$(UT_LIST):		$(LIST_OBJ)
			$(CC) $(LIST_OBJ) $(LDFLAGS) -o $(UT_LIST)

clean:
			$(RM) $(LIST_OBJ)

distclean:		clean
			$(RM) $(UT_LIST)

re:			distclean all

.c.o:
			$(CC) -I$(INCDIR) $(CFLAGS) -c $< -o $@
