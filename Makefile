NAME = pipex
LIBFT_DIR = ./libft/
LIBFT_NAME = libft.a
CC = cc
CFLAGS = 
# -Wall -Wextra -Werror

SRC = main.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(LIBFT_DIR)$(LIBFT_NAME):
	make bonus -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re