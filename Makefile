SRC =	minishell.c \
		utils/utils2.c \
		utils/utils.c \
		ft_split_all.c \
		builtin/ft_echo.c \
		parsing/env.c \
		parsing/env2.c \
		builtin/ft_cd.c\
		builtin/ft_exit.c

NAME = minishell
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
LIBFT_DIR = ./libftFINAL
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(OBJ_B)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_B)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY = all clean fclean re