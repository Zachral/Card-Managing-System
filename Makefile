PROG=inlamning2
CC=gcc
CFLAGS=-g -Wall -Werror
DEPS = safeinput.h 
OBJ = menu.o Main.o safeinput.o doorControl.o cardManaging.o empty_stdin.o

all: $(PROG) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
 
$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)