NAME = so_long

SRCS =	check_map.c\

LIB = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDES= -I ./includes

VPATH = src

LINK = -ldl -pthread -lm

LIBS = -L /usr/local/lib libmlx.a -lXext -lX11

all: $(NAME)

$(NAME): $(SRCS) $(LIB)
	$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIB) $(LINK) -o $(NAME) -Og

$(LIB):
	$(MAKE) -C libft
	mv libft/$(LIB) .
	$(MAKE) -C libft clean

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME) $(LIB)

re: fclean all

test:
	$(CC) $(CFLAGS) main_test.c $(LIBS) $(LINK) -o $(NAME)

.PHONY: all clean fclean re

#test:
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
