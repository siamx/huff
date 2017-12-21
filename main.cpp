#include <dirent.h>
#include <zconf.h>
#include "huffman/Huffman.h"
#include "files/Files.h"

void run_encoding(const string &file_path);

void run_decoding(const string &file_path);

set<string> dir_files;

string extension(const string &file_path) {
    return file_path.substr(file_path.find_last_of('.'));
}

void tree(const string &path) {
    DIR *dir;
    struct dirent *cur_dir;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((cur_dir = readdir(dir)) != nullptr) {
            if (string(cur_dir->d_name) == "." || string(cur_dir->d_name) == "..")
                continue;
            else if (cur_dir->d_type == DT_DIR) // if dir, go deeper
                tree(path + "/" + cur_dir->d_name);
            else { // if file
                string file = path + "/" + cur_dir->d_name;
                dir_files.insert(file);
                printf("%s\n", file.c_str());
            }

        }
        closedir(dir);
    }
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
//            cout << "invalid params only -x is valid\n";
//            exit(1);
//        }
//        cout << "Extracting..\n";
//        file_name = argv[2];
//        My_File my_file = read_encoded_file(file_name);
//        Huffman huffman(my_file.code);
//        vector<int> original_file = huffman.decode(my_file.content);
//        write_file(file_name.substr(file_name.find_last_of('.')), original_file);
//    } else {
//        cout << "invalid params\nCompress file -> ./huff [file name]\nExtract file  -> ./huff -x [file name]\n\n";
//        exit(1);
//    }
    for (const string &s: dir_files) {
        if(extension(s) == EXTENSION || extension(s) == ".decoded") continue;
        run_encoding(s);
        run_decoding(s + EXTENSION);
    }
    return 0;
}

void run_encoding(const string &file_path) {
    if(extension(file_path) == EXTENSION) return;

    My_File file = read_file(file_path);

    Huffman huffman(file.freq);

    string compressed = huffman.encode(file.content);

    write_encoded_file(file_path, compressed, huffman.get_codes());
}

void run_decoding(const string &file_path) {
    if (extension(file_path) != EXTENSION) return;

    My_File my_file = read_encoded_file(file_path);

    Huffman huffman(my_file.code);

    vector<int> original_file = huffman.decode(my_file.content);

    write_file(file_path.substr(0, file_path.find_last_of('.')) + ".decoded", original_file);
}
