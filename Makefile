SRC =	minishell.c \
		builtin/ft_cd.c\
		builtin/ft_ctrl.c \
		builtin/ft_echo.c \
		builtin/ft_env.c \
		builtin/ft_exit.c \
		builtin/ft_export.c \
		builtin/ft_pwd.c \
		builtin/ft_unset.c \
		parsing/list_utils.c \
		parsing/list_utils2.c \
		parsing/list_utils3.c \
		parsing/list.c \
		env/dollar.c \
		env/env_export.c \
		env/env_export2.c \
		env/env.c \
		env/expand_env.c \
		env/update_env.c \
		utils/utils.c \
		utils/utils2.c \
		utils/utils_unset.c \
		utils/utils_export.c \
		free.c \
		exec/test.c

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