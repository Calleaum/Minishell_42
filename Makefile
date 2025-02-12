SRC =	minishell.c	get_next_line.c
NAME = minishell
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libftFINAL
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ) $(OBJ_B)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_B)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY = all clean fclean re