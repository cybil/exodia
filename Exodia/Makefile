
SRCDIR	=	./sources/

HDERDIR	=	./headers/

CXXFLAGS	+=	-Wall -Wextra -I$(HDERDIR)

CC	=	g++

RM	=	rm -f

NAME	=	exodia

SRC	=	$(SRCDIR)main.cpp \
		$(SRCDIR)Player.cpp \
		$(SRCDIR)Animation.cpp \
		$(SRCDIR)Map.cpp

OBJ	=	$(SRC:.cpp=.o)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) -lsfml-graphics -lsfml-system -lsfml-window

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all