//
// Created by ahmed on 12/15/17.
//

#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <iomanip>
#include <bitset>
#include "Files.h"

My_File read_file(const string &in_file) {
    My_File file = My_File();
    ifstream in(in_file, ios::binary);

    while (true) {
        int c = in.get();
        if (c == EOF) break;
        file.content.push_back(c);
        file.freq[c]++;
    }

    in.close();
    return file;
}

void write_file(const string &out_file, vector<int> &content) {
    ofstream out(out_file, ios::out);
    for (int i: content)
        out << (char) i;
    out.close();
}

string int_to_bits(int c) {
    return bitset<8>((unsigned int) c).to_string();
}

My_File read_encoded_file(const string &in_file) {
    ifstream in(in_file, ios::binary);
    string str;
    My_File my_file;

    in >> str;
    if (str != ENCODED) {
        my_file.not_valid = true;
        cout << "Unrecognized encoding format.\n";
        return my_file;
    }

    int cnt = 0;
    in >> cnt;
    map<string, int> loaded_codes;
    while (cnt--) {
        string new_code;
        int key;
        in >> key >> new_code >> new_code;
        loaded_codes[new_code] = key;
    }

    in >> cnt;          // last byte bits
    getline(in, str);   // discard the new line char '\n'

    deque<int> content;
    int c;
    while ((c = in.get()) != EOF) {
        string binary_str = int_to_bits(c);
        for (int bit: binary_str)
            content.push_back(bit);
    }

    while (cnt--)
        content.pop_back();

    my_file.not_valid = false;
    my_file.content = content;
    my_file.loaded_codes = loaded_codes;
    return my_file;
}

void write_encoded_file(const string &out_file, const string &content, const string &codes) {
    ofstream out(out_file, ios::out);
    out << codes;
    out << (8 - (content.size() % 8)) % 8 << endl;
    string str_to_int;
    for (char c: content) {
        str_to_int.push_back(c);
        if (str_to_int.size() == 8) {
            out << (char) stoi(str_to_int, nullptr, 2);
            str_to_int = "";
        }
    }

    if (!str_to_int.empty()) {
        while (str_to_int.size() < 8)
            str_to_int.push_back('0');
        out << (char) stoi(str_to_int, nullptr, 2);
    }

    out.close();
}

void compare_file_size(const string &in_file, const string &out_file) {
    double original = 0, compressed = 0;
    struct stat st{};

    if (stat(in_file.c_str(), &st) == 0)
        original = st.st_size;

    if (stat(out_file.c_str(), &st) == 0)
        compressed = st.st_size;

    cout << "\n\n" << in_file << " size: " << original / 1024 << " KB\n";
    cout << out_file << " size: " << compressed / 1024 << " KB\n";
    cout << "compression Ratio: " << (original - compressed) / original * 100 << " %\n\n";
}
