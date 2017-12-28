//
// Created by ahmed on 12/15/17.
//

#ifndef HUFFMAN_COMPRESSION_DECOMPRESSION_NODE_H
#define HUFFMAN_COMPRESSION_DECOMPRESSION_NODE_H


#define INTERNAL (-2147483648)

class Node {
public:
    int data = INTERNAL;
    int freq;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int data, int freq) {
        this->data = data;
        this->freq = freq;
    }
};

struct order_by_freq {
    bool operator()(Node *l, Node *r) {
        return (l->freq > r->freq);
    }
};


#endif //HUFFMAN_COMPRESSION_DECOMPRESSION_NODE_H
