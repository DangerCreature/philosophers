# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 11:36:57 by gwolfrum          #+#    #+#              #
#    Updated: 2025/11/03 11:37:02 by gwolfrum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC += main.c
SRC += helpers.c
SRC += tabel_set.c
SRC += tabel_clear.c
SRC += sem_trywait.c
SRC += handel_chiald.c
SRC += rutine.c
SRC += forks.c

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
