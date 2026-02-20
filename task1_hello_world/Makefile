CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99

hello: hello.o
	$(CC) $(CFLAGS) -o hello hello.o

hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c

clean:
	rm -f *.o hello
