# Test a makefile by adding a bunch of shit
CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits
DBGFLAGS = -std=gnu99 -pedantic -Wall -Werror -Wsign-compare -Wwrite-strings -Wtype-limits -ggdb3 -DDEBUG
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
DBGOBJS = $(patsubst %.c,%.dbg.o,$(SRCS))
.PHONY: clean depend all
all: encrypt encrypt-debug
encrypt: $(OBJS)
	gcc -o $@ $(OBJS)
encrypt-debug: $(DBGOBJS)
	gcc -o $@ -ggdb3 $(DBGOBJS)
%.dbg.o: %.c
	gcc $(DBGFLAGS) -c -o $@ $<
clean:
	rm -f *.o *.c~ *.h~
depend:
	makedepend $(SRCS)
	makedepend -a -o .dbg.o $(SRCS)

# DO NOT DELETE

hello.o: /usr/include/stdio.h /usr/include/stdlib.h

hello.dbg.o: /usr/include/stdio.h /usr/include/stdlib.h
