NAME = so_long

SRCS =	tests.c\

CC = cc

FLAGS = -Wall -Wextra -Werror DEBUG=1

LINK = -ldl -pthread -lm

LIBS = -L /usr/local/lib libmlx.a -lXext -lX11

all: main

main:
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) $(LINK) -o $(NAME)

test:
	$(CC) $(CFLAGS) main_test.c $(LIBS) $(LINK) -o $(NAME)

#test:
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
