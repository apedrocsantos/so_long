NAME = so_long

SRCS =	map_check.c\
		map_utils.c\
		utils2.c\
		utils.c\
		main.c\

B_SRCS = map_check_bonus.c\
		map_utils_bonus.c\
		animation_bonus.c\
		utils2_bonus.c\
		utils_bonus.c\
		main_bonus.c\

LIBFT = libft.a

LIBMLX = libmlx.a

CFLAGS = -Wall -Wextra -Werror -DDEBUG=1 -fsanitize=address

INCLUDES = -I ./includes

HEADERFILES = ./includes/so_long.h

VPATH = src

LIBS = -L /usr/local/lib libmlx.a -lXext -lX11 -ldl -pthread -lm

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIBFT) $(LIBMLX) $(LIBS) -o $(NAME) -g
	@echo "Compilation OK."

bonus: $(B_SRCS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIBFT) $(LIBMLX) $(LIBS) -o $(NAME) -g
	@echo "Compilation OK."

$(LIBFT):
	@echo "Compiling libft."
	@$(MAKE) -s -C libft
	@mv libft/$(LIBFT) .
	@$(MAKE) -s -C libft clean
	@echo "Libft OK."

$(LIBMLX):
	@echo "Compiling libmlx."
	@$(MAKE) -s -C minilibx-linux
	@mv minilibx-linux/$(LIBMLX) .
	@echo "Libmlx OK."

clean:
	@echo "Removing ./so_long."
	@rm -f $(NAME)

fclean:
	@echo "Removing ./so_long, libft.a and libmlx.a."
	@rm -f $(NAME) $(LIBFT) $(LIBMLX)

re: fclean all

# valgrind: clean all
# 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./$(NAME) $(map)

.SILENT: $(LIBMLX)

.PHONY: all clean fclean re bonus

