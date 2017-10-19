CC = gcc
CFLAGS = -Wall -std=c99 -lm

default: src/portable\ version/main.o
		$(CC) -o common src/portable\ version/main.o $(CFLAGS) 
