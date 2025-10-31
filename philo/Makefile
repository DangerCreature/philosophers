NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC += helpers1.c
SRC += main.c
SRC += init.c
SRC += cleanup.c
SRC += forks.c
SRC += rutine.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
