CPP = g++
OFLAGS = -O3
CFLAGS = -Wall -Wextra -std=c++11
OBJECT = main.cpp huffman/Huffman.cpp huffman/Huffman.h huffman/Node.h files/Files.cpp files/Files.h
PROJECT = huff

all:
	$(CPP) $(CFLAGS) $(OFLAGS) $(OBJECT) -o $(PROJECT)
