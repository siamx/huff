//
// Created by ahmed on 12/15/17.
//

#ifndef HUFFMAN_COMPRESSION_DECOMPRESSION_FILES_H
#define HUFFMAN_COMPRESSION_DECOMPRESSION_FILES_H


#include <queue>
#include <string>
#include <map>

#define ENCODED "\\\\ENCODED\\\\"

using namespace std;

typedef struct {
    bool not_valid;
    map<string, int> loaded_codes;
    map<int, int> freq;
    deque<int> content;
} My_File;

My_File read_file(const string &in_file);

void write_file(const string &out_file, vector<int> &content);

My_File read_encoded_file(const string &in_file);

void write_encoded_file(const string &out_file, const string &content, const string &codes);

void compare_file_size(const string &in_file, const string &out_file);


#endif //HUFFMAN_COMPRESSION_DECOMPRESSION_FILES_H
