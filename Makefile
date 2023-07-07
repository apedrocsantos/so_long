NAME = so_long

SRCS =	main.c\

CC = cc

FLAGS = -Wall -Wextra -Werror DEBUG=1

LINK = -ldl -lglfw -pthread -lm

LIBS = -L /usr/local/lib libmlx.a -lXext -lX11

all:
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) $(LINK) -o $(NAME)
