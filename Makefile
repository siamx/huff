all:
	g++ -O3 -std=c++11 main.cpp huffman/Huffman.cpp huffman/Huffman.h huffman/Node.h files/Files.cpp files/Files.h -o huff
