CC = gcc

execute: writenfile.c execute.c parser.c struct.c
	$(CC) writenfile.c execute.c parser.c struct.c -o program

clean:
	rm program