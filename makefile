CC = g++
CFLAGS = -Wall

BIN = ../bin
LIB = ../lib


all: main

$(BIN)/main.o: main.cpp $(LIB)/Card.h $(LIB)/utils.h
	$(CC) -c -o $@ $< $(CFLAGS) -std=c++11

$(BIN)/main: $(BIN)/main.o $(LIB)/Card.h $(LIB)/utils.h
	$(CC) -g -o $@ $< $(CFLAGS) -std=c++11

.PHONY: clean

clean:	
	rm -rf $(BIN)/*