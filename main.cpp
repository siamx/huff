#include <dirent.h>
#include <set>
#include <sys/stat.h>
#include <boost/algorithm/string/replace.hpp>
#include "huffman/Huffman.h"
#include "files/Files.h"

set<string> dir_files;
map<string, void (*)(const string &, const string &)> function_pointer;

void run_encoding(const string &in_file, const string &out_file);

void run_decoding(const string &in_file, const string &out_file);

void mother_of_functions(const string &flag, string in, string out);

void help() {
    cout << endl
         << "*** Huffman codes ***" << endl
         << "Author:  Ahmed Lotfy Siam" << endl
         << "Github:  https://github.com/siamx/huff" << endl << endl
         << "Usage:" << endl
         << "        ./huff  <flag>  <input-file>  <output-file>" << endl << endl
         << "Flags:" << endl
         << "        -e | --encode" << endl
         << "                Compress input file (default flag)." << endl << endl
         << "        -d | --decode" << endl
         << "                Extract input file." << endl << endl
         << "        -h | --help" << endl
         << "                Display this help menu." << endl << endl;
}

bool exist(const string &file) {
    struct stat st{};
    return stat(file.c_str(), &st) != -1;
}

void tree(const string &path);

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
    } else if (exist(path))
        dir_files.insert(path);
}

int main(int argc, char **argv) {
    string in = "src.txt", out = "src.huff", flag = "encode";

    if (argc <= 2) {
//        help();
//        exit(1);
    } else if (argc == 3) {
        in = argv[1];
        out = argv[2];
    } else if (argc == 4) {
        flag = argv[1];
        in = argv[2];
        out = argv[3];
    } else {
        cout << "invalid args\n";
        help();
        exit(1);
    }

    function_pointer["-d"] = run_decoding;
    function_pointer["--decode"] = run_decoding;
    function_pointer["decode"] = run_decoding;

    function_pointer["-e"] = run_encoding;
    function_pointer["--encode"] = run_encoding;
    function_pointer["encode"] = run_encoding;

    tree(in);

    if (function_pointer.find(flag) == function_pointer.end()) {
        cout << "invalid flag\n";
        help();
        exit(1);
    }
    if (dir_files.empty()) {
        cout << "no such file or directory\n";
        exit(1);
    }
    if (exist(out)) {
        cout << "out file already exists\n";
        exit(1);
    }

    for (const string &path: dir_files) {
        string new_path = path;
        boost::replace_first(new_path, in, out);

        // if this file is in directory
        if (new_path.find('/') != new_path.npos) {
            string folder_path = new_path.substr(0, new_path.find_last_of('/'));
            if (!exist(folder_path))
                mkdir(folder_path.c_str(), 0700);
        }

        mother_of_functions(flag, path, new_path);
    }

    return 0;
}

void run_encoding(const string &in_file, const string &out_file) {
    My_File file = read_file(in_file);

    Huffman huffman(file.freq);

    string compressed = huffman.encode(file.content);

    write_encoded_file(out_file, compressed, huffman.get_codes());

    compare_file_size(in_file, out_file);
}

void run_decoding(const string &in_file, const string &out_file) {
    My_File file = read_encoded_file(in_file);

    if (file.not_valid) return;

    Huffman huffman(file.loaded_codes);

    vector<int> decoded_data = huffman.decode(file.content);

    write_file(out_file, decoded_data);
}

void mother_of_functions(const string &flag, string in, string out) {
    clock_t time = clock();

    function_pointer[flag](in, out);

    time = clock() - time;
    cout << "run time: " << (double) time / CLOCKS_PER_SEC << " sec\n";
}