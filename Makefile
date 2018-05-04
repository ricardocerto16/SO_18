CC = gcc

parser: parser.c struct.c
	$(CC) parser.c struct.c -o parser

clean:
	rm parser