SRC_DIR = src
INCLUDE_DIR = include
CC = g++
CFLAGS= -g -Wall -std=c++14
all: prog

test: test_prog

prog:
	$(CC) $(CFLAGS) -o prog $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR)

test_prog:
	$(CC) $(CFLAGS) -o test_prog $(SRC_DIR)/test.cpp -I $(INCLUDE_DIR)

clean:
	$(RM) *.o *~ prog test_prog
