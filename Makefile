PROG=lab28-2
CC=gcc
CFLAGS=-g -Wall
DEPS = safeinput.h
OBJ = menu.o main.o safeinput.o circumference.o fileList.o longestWord.o

all: $(PROG) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
 
$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)