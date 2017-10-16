CC = gcc
CFLAGS = -Wall -std=c99 -lm

default: src/v1/main.o
		$(CC) -o common src/v1/main.o $(CFLAGS) 
