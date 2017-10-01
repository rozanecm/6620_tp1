CC = gcc
CFLAGS = -Wall -std=c99 -lm

default: src/main.o
		$(CC) -o common src/main.o $(CFLAGS) 
