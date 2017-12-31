//
// Created by ahmed on 12/15/17.
//

#ifndef HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H
#define HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H


#include <map>
#include <vector>
#include <queue>
#include <iostream>
#include <bitset>
#include <algorithm>
#include "Node.h"

#define ENCODED "\\\\ENCODED\\\\"

using namespace std;

class Huffman {
public:
    /**
     * @brief de-compression constructor
     * @param loaded_code codes read from encoded file header
     */
    explicit Huffman(map<string, int> loaded_code);

    /**
     * @brief compression constructor
     * @param freq_map char's occurrence frequency
     */
    explicit Huffman(map<int, int> freq_map);

    string get_codes();

    vector<int> decode(deque<int> encoded_file);

    string encode(deque<int> str);

private:
    Node *root;
    map<int, string> generated_codes;
    map<string, int> loaded_codes;
    priority_queue<Node *, vector<Node *>, order_by_freq> heap;

    void __print(Node *node, const string &code_str = "");

    void __generate(map<int, int> freq_map);
};


#endif //HUFFMAN_COMPRESSION_DECOMPRESSION_HUFFMAN_H
