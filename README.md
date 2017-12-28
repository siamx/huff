# Huffman compression

* build 
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
