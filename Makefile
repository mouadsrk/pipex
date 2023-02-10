NAME = pipex

src = pipex.c pipex_utiles.c split.c pipex_utiles2.c cmd.c
OBJ = pipex.o pipex_utiles.o split.o pipex_utiles2.o cmd.o

FLGS = -Wall -Wextra -Werror

RM = rm -fr

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(FLGS) $(OBJ) -o $(NAME)

%.o : %.c pipex.h
	cc $(FLGS) -c $< 

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : clean all

	