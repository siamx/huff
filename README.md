# Huffman compression


An implementation of huffman codes, to compress & decompress files, folders & binary files.



* build & run
    ```bash
    git clone https://github.com/siamx/huff
    cd huff
    make
    ```

* compress
    ```bash
    # ./huff [input file] [output file]
    
    ./huff src.txt src.huff
    ```
    
* extract
    ```bash
    # ./huff -d [input file] [output file]

    ./huff -d src.compressed src.txt
    ```


## implementation description

* `Files.h` & `Files.cpp`:
    * These two files are responsible for reading & writing normal & encoded files.
    
* `Node.h` the core data structure of huffman tree, it consists of:
    * Data (int)
    * Frequency (int)
    * Node* pointer to left child
    * Node* pointer to right child
    * order_by_freq used by the priority queue to emulate a min by freq binary heap

* `Huffman.h` & `Huffman.cpp` consist of:
    * `string get_codes();`
    * `vector<int> decode(deque<int> encoded_file);`
    * `string encode(deque<int> str);`

## Header format is:

```bash
\\ENCODED\\           # Encoded flag, must exist. If the decoder did not find it, the program terminates
9                     # Number of written codes
10 00001010 0001      # Code sample, <byte value> <old binary code> <new assigned code>
32 00100000 001
97 01100001 1
98 01100010 01
99 01100011 000000
101 01100101 0000110
102 01100110 000001
103 01100111 000010
104 01101000 0000111
5                     # Trailing bits at last byte, to be removed
```
