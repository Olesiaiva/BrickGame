CC = gcc -Wall -Werror -Wextra

all: clean
	$(CC) main.c util.c screen.c move.c -o tetris -lncurses -g && ./tetris

clean:
	rm -rf a.* tetris tetris.d*