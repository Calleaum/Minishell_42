SRC =	ft_atoi.c		ft_bzero.c		ft_calloc.c		ft_isalnum.c		\
		ft_isalpha.c	ft_isascii.c	ft_isdigit.c	ft_isprint.c		\
		ft_itoa.c		ft_memchr.c		ft_memcmp.c		ft_memcpy.c			\
		ft_memmove.c	ft_memset.c		ft_putchar_fd.c	ft_putendl_fd.c		\
		ft_putnbr_fd.c	ft_putstr_fd.c	ft_split.c		ft_strchr.c			\
		ft_strdup.c		ft_striteri.c	ft_strjoin.c	ft_strlcat.c		\
		ft_strlcpy.c	ft_strlen.c		ft_strmapi.c	ft_strncmp.c		\
		ft_strnstr.c	ft_strrchr.c	ft_strtrim.c	ft_substr.c			\
		ft_tolower.c	ft_toupper.c	ft_printf.c		ft_print_char.c		\
		ft_print_hex.c	ft_print_int.c	ft_print_str.c	ft_uitoa.c			\
		ft_putstr.c		ft_print_unsigned.c	ft_print_pointer.c	ft_atol.c	\
		get_next_line.c ft_strcpy.c ft_strcmp.c fd_print_char.c fd_print_str.c \
		fd_printf.c fd_print_hex.c fd_print_int.c fd_print_pointer.c fd_print_unsigned.c

NAME = libft.a
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re