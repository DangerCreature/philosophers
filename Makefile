NAME = philo
LIB = libft/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC += paths.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: libft $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

libft:
	cd libft && $(MAKE)

clean:
	cd libft && $(MAKE) clean
	rm -f $(OBJ)

fclean: clean
	cd libft && $(MAKE) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: libft clean fclean re
