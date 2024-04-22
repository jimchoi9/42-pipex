NAME = pipex
LIBFT_DIR = ./libft_src/
LIBFT_NAME = libft.a
CC = cc
CFLAGS = 
# -Wall -Wextra -Werror

SRC_M = pipex_main.c pipex_parsing.c pipex_utils.c
SRC_B = bonus_pipex_main.c bonus_pipex_parsing.c bonus_pipex_utils.c 
SRCS = $(if $(filter bonus, $(MAKECMDGOALS)), $(SRC_B), $(SRC_M))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(LIBFT_DIR)$(LIBFT_NAME):
	make -C $(LIBFT_DIR)

$(OBJS)	:	$(SRCS)
	$(CC) $(CFLAGS) -c $^

clean:
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

bonus :

.PHONY: bonus all clean fclean re