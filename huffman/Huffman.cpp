//
// Created by ahmed on 12/15/17.
//

#include <iomanip>
#include "Huffman.h"

Huffman::Huffman(map<string, int> loaded_codes) {
    this->loaded_codes = move(loaded_codes);
}

Huffman::Huffman(map<int, int> freq_map) {
    __generate(freq_map);

    cout << "\n\nCodes:\n";
    __print(this->root);
    cout << "\n";
}

vector<int> Huffman::decode(deque<int> encoded_file) {
    string encoded_str;
    vector<int> decoded_str;
    while (!encoded_file.empty()) {
        encoded_str.push_back((char) encoded_file.front());
        encoded_file.pop_front();

        if (this->loaded_codes.find(encoded_str) != this->loaded_codes.end()) {
            decoded_str.push_back(this->loaded_codes[encoded_str]);
            encoded_str.clear();
        }
    }

    return decoded_str;
}

string Huffman::encode(deque<int> str) {
    string encoded_str;
    while (!str.empty()) {
        int c = str.front();
        str.pop_front();
        if (generated_codes.find(c) == generated_codes.end()) {
            cout << "input value with no code found: " << c << endl;
        } else
            encoded_str += this->generated_codes[c];
    }
    return encoded_str;
}

string Huffman::get_codes() {
    string codes;
    codes += ENCODED;
    codes.push_back('\n');
    codes += string(to_string(this->generated_codes.size()) + "\n");
    for (pair<int, string> code: this->generated_codes) {
        string old_code = bitset<8>((unsigned int) code.first).to_string();
        codes += (to_string(code.first) + " " + old_code + " " + code.second + "\n");
    }
    return codes;
}

void Huffman::__print(Node *node, const string &code_str) {
    if (!node) return;

    if (node->data != INTERNAL) {
        string old_code = bitset<8>((unsigned int) node->data).to_string();
        cout << left << setw(4) << node->data << "  " << old_code << "  " << code_str << "\n";
        this->generated_codes[node->data] = code_str;
    }

    this->__print(node->left, code_str + "0");
    this->__print(node->right, code_str + "1");
}

void Huffman::__generate(map<int, int> freq_map) {
    // Create a priority queue & inserts all characters
    for (pair<int, int> cur: freq_map)
        this->heap.push(new Node(cur.first, cur.second));

    if (heap.empty()) {
        cout << "Error: Empty file\n";
        exit(1);
    }

    // Iterate while size of this->heap doesn't become 1
    Node *left, *right, *top;
    while (this->heap.size() != 1) {
        // Extract the two minimum freq items from min this->heap
        left = this->heap.top(), this->heap.pop();
        right = this->heap.top(), this->heap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes frequencies.
        top = new Node(INTERNAL, left->freq + right->freq);
        top->left = left;
        top->right = right;
        this->heap.push(top);
    }
    // set the min this->heap root
    this->root = this->heap.top();
}
