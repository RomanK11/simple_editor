CC = gcc
CFLAGS = -Wall -Wextra -g

app: main.o funcs.o
	$(CC) $(CFLAGS) -o app main.o funcs.o

main.o: main.c funcs.h
	$(CC) $(CFLAGS) -c main.c

funcs.o: funcs.c funcs.h
	$(CC) $(CFLAGS) -c funcs.c

clean:
	rm -f app main.o editor.o