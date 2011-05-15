NAME	=	unit_test

CC	=	gcc
RM	=	rm -f

CFLAGS	+=	-W -Wall -ansi -pedantic
CFLAGS	+=	-gdwarf-2 -g3

SRCDIR	=	src
INCDIR	=	include

SRC	=	$(SRCDIR)/main.c

OBJ	=	$(SRC:.c=.o)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

distclean:	clean
		$(RM) $(NAME)

re:		distclean all

.c.o:
		$(CC) -I$(INCDIR) $(CFLAGS) -c $< -o $@
