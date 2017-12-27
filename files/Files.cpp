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
    ifstream in(in_file);

    while (true) {
        int c = in.get();
        if (c == EOF) break;
        if (c == ' ') c = SPACE;
        if (c == '\n') c = NEW_LINE;
        if (c == '\t') c = TAB;
        file.content.push_back(c);
        file.freq[c]++;
    }

    in.close();
    return file;
}

void write_file(const string &out_file, vector<int> &content) {
    ofstream out(out_file, ios::out);
    for (int i: content) {
        if (i == SPACE) out << " ";
        else if (i == NEW_LINE) out << endl;
        else if (i == TAB) out << "\t";
        else out << (char) i;
    }
    out.close();
}

string char_to_bits(char c) {
    return bitset<8>((unsigned char) c).to_string();
}

My_File read_encoded_file(const string &in_file) {
    ifstream in(in_file, ios::in);
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
        string key, code, new_code;
        in >> key >> code >> new_code;
        loaded_codes[new_code] = key[0];
    }


    in >> cnt;          // read number of bits
    getline(in, str);   // discard the new line char '\n'

    deque<int> content;
    string binary_str;
    bool line_cnt = false;

    while (getline(in, str)) {
        if (line_cnt) {
            binary_str = char_to_bits('\n');
            for (int bin: binary_str)
                content.push_back(bin);
        }

        line_cnt = true;
        for (char &i : str) {
            binary_str = char_to_bits(i);
            for (int bin: binary_str)
                content.push_back(bin);
        }
    }

    while (content.size() > cnt)
        content.pop_back();

    my_file.not_valid = false;
    my_file.content = content;
    my_file.loaded_codes = loaded_codes;
    return my_file;
}

void write_encoded_file(const string &out_file, const string &content, const string &codes) {
    ofstream out(out_file + EXTENSION, ios::out);
    out << codes;
    out << content.size() << endl;
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
    compare_file_size(out_file);
}

void compare_file_size(const string &file_name) {
    double original = 0, compressed = 0;
    struct stat st{};

    if (stat(file_name.c_str(), &st) == 0)
        original = st.st_size;

    if (stat((file_name + EXTENSION).c_str(), &st) == 0)
        compressed = st.st_size;

    cout << "\n\n" << file_name << " size: " << original / 1024 << " KB\n";
    cout << file_name << EXTENSION << " size: " << compressed / 1024 << " KB\n";
    cout << "Compression Ratio: " << (original - compressed) / original * 100 << " %\n\n";
}
