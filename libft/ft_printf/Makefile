NAME = libftprintf.a

SRC += ft_putnbr_base.c
SRC += ft_printf_core.c
SRC += ft_putstr.c
SRC += ft_putadress.c
SRC += ft_putnbr.c
SRC += ft_strlen.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
	ar rcs $(NAME) $(OBJ)

%o:			%c
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re NAME SRC OBJ
