NAME = philo
CC = @cc
RM = rm -f
CFLAGS = -Werror -Wextra -Wall
# -fsanitize=thread -g3
OBJ = philo.o utils.o utils1.o

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)


fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME)
	$(RM) $(B_NAME)

re: fclean all
