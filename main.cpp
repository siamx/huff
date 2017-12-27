#include <dirent.h>
#include <set>
#include "huffman/Huffman.h"
#include "files/Files.h"

void run_encoding(const string &in_file, const string &out_file);

void run_decoding(const string &in_file, const string &out_file);

set<string> dir_files;

void tree(const string &path) {
    DIR *dir;
    struct dirent *cur_dir;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((cur_dir = readdir(dir)) != nullptr) {
            string sub_dir = cur_dir->d_name;
            if (sub_dir == "." || sub_dir == "..") continue;
            tree(path + "/" + sub_dir); // NOLINT
        }
        closedir(dir);
    } else
        dir_files.insert(path);
}

int main(int argc, char **argv) {
    tree("test");

//    string file_name;
//    if (argc == 2) {
//        cout << "Compressing..\n";
//        file_name = argv[1];
//        My_File my_file = read_file(file_name);
//        Huffman huffman(my_file.freq);
//        string compressed = huffman.encode(my_file.content);
//        write_encoded_file(file_name, compressed, huffman.get_codes());
//    } else if (argc == 3) {
//        string flag = argv[1];
//        if (flag != "-x") {
//            cout << "invalid params only -x is not_valid\n";
//            exit(1);
//        }
//        cout << "Extracting..\n";
//        file_name = argv[2];
//        My_File my_file = read_encoded_file(file_name);
//        Huffman huffman(my_file.loaded_codes);
//        vector<int> original_file = huffman.decode(my_file.content);
//        write_file(file_name.substr(file_name.find_last_of('.')), original_file);
//    } else {
//        cout << "invalid params\nCompress file -> ./huff [file name]\nExtract file  -> ./huff -x [file name]\n\n";
//        exit(1);
//    }
    for (const string &file_name: dir_files) {
        run_encoding(file_name, file_name + EXTENSION);
        run_decoding(file_name + EXTENSION, file_name);
    }

    return 0;
}

void run_encoding(const string &in_file, const string &out_file) {
    My_File file = read_file(in_file);

    Huffman huffman(file.freq);

    string compressed = huffman.encode(file.content);

    write_encoded_file(out_file, compressed, huffman.get_codes());
}

void run_decoding(const string &in_file, const string &out_file) {
    My_File file = read_encoded_file(in_file);

    if (file.not_valid) return;

    Huffman huffman(file.loaded_codes);

    vector<int> decoded_data = huffman.decode(file.content);

    write_file(out_file, decoded_data);
}
