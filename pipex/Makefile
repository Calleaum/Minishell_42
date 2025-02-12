SRC =	pipex.c
NAME = pipex
OBJ = $(SRC:.c=.o)

SRC_B =	pipex_bonus.c	utils_bonus.c	utils_bonus2.c
NAME_B = pipex_bonus
OBJ_B = $(SRC_B:.c=.o)

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

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) -o $(NAME_B)

.PHONY = all clean fclean re bonus