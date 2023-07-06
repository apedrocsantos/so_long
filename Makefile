NAME = so_long

SRCS =	main.c\

CC = cc

FLAGS = -Wall -Wextra -Werror

LIBS = -L /usr/local/lib -lmlx -lXext -lX11

all:
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $(NAME)