NAME = so_long

SRCS =	check_map.c\
		map_utils.c\
		utils.c\
		main.c\

LIBFT = libft.a

LIBMLX = libmlx.a

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -DDEBUG=1

INCLUDES = -I ./includes

HEADERFILES = ./includes/so_long.h

VPATH = src

LIBS = -L /usr/local/lib libmlx.a -lXext -lX11 -ldl -pthread -lm

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIBFT) $(LIBMLX) $(LIBS) -o $(NAME) -g
	@echo "compilation OK."


$(LIBFT):
	@$(MAKE) -s -C libft
	@mv libft/$(LIBFT) .
	@$(MAKE) -s -C libft clean
	@echo "libft OK."

$(LIBMLX):
	@$(MAKE) -s -C minilibx-linux
	@mv minilibx-linux/$(LIBMLX) .
	@echo "libmlx OK."

clean:
	@echo "removing ./so_long."
	@rm -f $(NAME)

fclean:
	@echo "removing ./so_long, libft.a and libmlx.a."
	@rm -f $(NAME) $(LIBFT) $(LIBMLX)

re: fclean all

valgrind: clean all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) $(map)

.SILENT: $(LIBMLX)

.PHONY: all clean fclean re

