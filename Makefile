NAME = so_long

SRCS =	main.c\

CC = cc

FLAGS = -Wall -Wextra -Werror DEBUG=1

LINK = -ldl -pthread -lm

LIBS = -L /usr/local/lib libmlx.a -lXext -lX11

all: main

main:
	$(CC) $(CFLAGS) main.c $(LIBS) $(LINK) -o $(NAME)

test:
	$(CC) $(CFLAGS) main_test.c $(LIBS) $(LINK) -o $(NAME)

#test:
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
