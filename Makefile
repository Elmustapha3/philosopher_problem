NAME = philo
CC = cc
RM = rm -rf
CFLAGS =  -Werror -Wextra -Wall  #-fsanitize=thread -g3
OBJ = philo.o utils.o utils1.o parsing.o

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
