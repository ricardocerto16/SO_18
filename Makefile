CC = gcc

execute: writenfile.c execute.c parser.c struct.c main.c
	$(CC) writenfile.c execute.c parser.c struct.c main.c -g -o notebook

clean:
	rm notebook