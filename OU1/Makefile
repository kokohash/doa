CC=gcc
CLFAGS= -g -Wall -std=c99 -I ../testing/OU1/

all: stack_test

stack_test:	stack.o stack_test.o
	$(CC) $(CLFAGS) -o stack_test stack_test.o stack.o

stack_test_main: stack_test.c 
	$(CC) $(CLFAGS) -o $@ stack_test.c

stack: stack.c stack.h util.h
	$(CC) $(CLFAGS) -o $@ stack.c

.PHONY: clean

clean:
	rm -rf *.o 