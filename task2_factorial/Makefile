CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic

all: factorial.o
	$(CC) $(CFLAGS) factorial.o -o factorial
factorial.o: factorial.c
	$(CC) $(CFLAGS) -c factorial.c

clean:
	rm -rf *.o task2_factorial
