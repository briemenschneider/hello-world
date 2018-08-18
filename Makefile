# Test a makefile by adding a bunch of shit
CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror
hello: hello.o
	gcc -o hello $(CFLAGS) hello.c
.PHONY: clean depend
clean:
	rm -f *.o *.c~ *.h~
depend:
	makedepend hello.c

# DO NOT DELETE

hello.o: /usr/include/stdio.h /usr/include/stdlib.h
