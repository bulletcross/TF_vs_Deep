SRC_DIR = src
INCLUDE_DIR = include
CC = g++
CFLAGS= -g -Wall -std=c++14
all: prog

prog:
	$(CC) $(CFLAGS) -o prog $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR)

clean:
	$(RM) *.o *~ prog
