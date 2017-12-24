# Huffman compression

* build 
    ```bash
    make
    ```

* compress
    ```bash
    # ./huff [input file] [output file]
    
    ./huff src.txt src.compressed
    ```
    
* extract
    ```bash
    # ./huff -x [input file] [output file]

    ./huff -x src.compressed src.txt
    ```
