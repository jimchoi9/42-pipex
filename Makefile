NAME = pipex
NAME_B = pipex
LIBFT_DIR = ./libft_src/
LIBFT_NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I.

SRC_MAIN = pipex_main.c pipex_parsing.c pipex_utils.c
SRC_BONUS = bonus_pipex_main.c bonus_pipex_parsing.c bonus_pipex_utils.c
SRCS = $(SRC_MAIN)
OBJS = $(SRCS:.c=.o)

SRCS_BONUS = $(SRC_BONUS)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME):  $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $^
	rm -rf BONUS

bonus: BONUS

BONUS:  $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS_BONUS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $^
	touch $@

$(LIBFT_DIR)$(LIBFT_NAME):
	make -C $(LIBFT_DIR)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $^

$(OBJS_BONUS): $(SRCS_BONUS)
	$(CC) $(CFLAGS) -c $^

clean:
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJS) $(OBJS_BONUS)
	rm -rf BONUS

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME)_bonus

re: fclean all

.PHONY: all bonus clean fclean re
