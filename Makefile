NAME = pipex
LIBFT_DIR = ./libft_src/
LIBFT_NAME = libft.a
CC = cc
CFLAGS = 
# -Wall -Wextra -Werror

SRC = pipex_main.c pipex_parsing.c pipex_utils.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(LIBFT_DIR)$(LIBFT_NAME):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re