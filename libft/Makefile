NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC += ft_atoi.c
SRC += ft_bzero.c
SRC += ft_calloc.c
SRC += ft_isalnum.c
SRC += ft_isalpha.c
SRC += ft_isascii.c
SRC += ft_isdigit.c
SRC += ft_isprint.c
SRC += ft_itoa.c
SRC += ft_memchr.c
SRC += ft_memcmp.c
SRC += ft_memcpy.c
SRC += ft_memmove.c
SRC += ft_memset.c
SRC += ft_putchar_fd.c
SRC += ft_putendl_fd.c
SRC += ft_putnbr_fd.c
SRC += ft_putstr_fd.c
SRC += ft_split.c
SRC += ft_strchr.c
SRC += ft_strdup.c
SRC += ft_striteri.c
SRC += ft_strjoin.c
SRC += ft_strlcat.c
SRC += ft_strlcpy.c
SRC += ft_strlen.c
SRC += ft_strmapi.c
SRC += ft_strncmp.c
SRC += ft_strnstr.c
SRC += ft_strrchr.c
SRC += ft_strtrim.c
SRC += ft_substr.c
SRC += ft_tolower.c
SRC += ft_toupper.c
SRC += ft_printf/ft_putnbr_base.c
SRC += ft_printf/ft_printf_core.c
SRC += ft_printf/ft_putstr.c
SRC += ft_printf/ft_putadress.c
SRC += ft_printf/ft_putnbr.c
SRC += get_next_line/get_next_line.c
SRC += get_next_line/get_next_line_utils.c


OBJ = $(SRC:.c=.o)

%o: %c
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME)  $(OBJ)
# ar for type archive, r for replace or add, c for creating the archive and s for adding the index.

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
