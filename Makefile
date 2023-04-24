NAME = pipex
HEADER = pipex.h
LIBFT = libft/libft.a
CFLAGS = -Wall -Wextra -Werror -g
CC = gcc
FILES = main.o\
		utils.o\
		err_handler.o\

HEADERS = libft/libft.h\
			push_swap.h\

all: $(NAME)

$(NAME): $(FILES) $(LIBFT)
	$(CC) -o $(NAME) $(CFLAGS) $(FILES) $(LIBFT)

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIBFT):
	make -C libft

clean:
	rm -f $(FILES)
	make fclean -C libft

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re