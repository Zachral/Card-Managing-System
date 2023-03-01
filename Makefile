PROG=inlamning2
CC=gcc
CFLAGS=-g -Wall
DEPS = safeinput.h 
OBJ = menu.o Main.o safeinput.o

all: $(PROG) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
 
$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)