NAME = so_long

SRCS =	check_map.c\
		map_utils.c\
		main.c\

# SRCS = delme.c

LIB = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

INCLUDES= -I ./includes

VPATH = src

LINK = -ldl -pthread -lm

LIBS = -L /usr/local/lib libmlx.a -lXext -lX11

all: $(NAME)

$(NAME): $(SRCS) $(LIB)
	$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIB) $(LIBS) $(LINK) -o $(NAME) -g

$(LIB):
	@$(MAKE) -s -C libft
	@mv libft/$(LIB) .
	@$(MAKE) -s -C libft clean
	@echo "libft OK."

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME) $(LIB)

re: fclean all

.SILENT: clean fclean re

.PHONY: all clean fclean re

valgrind: clean all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) $(map)
