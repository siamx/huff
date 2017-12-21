cmake_minimum_required(VERSION 3.9)
project(huff)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(huff main.cpp huffman/Huffman.cpp huffman/Huffman.h huffman/Node.h files/Files.cpp files/Files.h)
