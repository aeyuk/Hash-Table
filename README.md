# Hash-Table

## Description
This program builds a hash table. It reads words separated by whitespace from a given file in the directory.
As words are read, they are inserted into the table. 
The word itself is the key value, and each entry in the table stores a list of the line numbers where the word appears.
The number of collisions that occur while inserting words into the hash table are also counted.
Once all words are read from the file, the program outputs the total number of words read, the number of distinct words, and the total number of collisions that occurred.

Finally, words from a query file are read.
The line numbers where the word occurs as well as the number of collisions while searching for the word in the table are outputted. 

## Compiling and Executing
Clone the repository from terminal, or download the zip and extract the files.
```bash
git clone https://github.com/aeyuk/Hash-Table.git
```

Build the project using `make`. There are *four* command line arguments needed to execute the program, following `./hash`:
1. The name of the input file (hashtest1.txt is supplied for you)
2. The name of the query file (hashq1.txt is supplied for you)
3. The size of the hash table
4. The collision resolution strategy:
    * "lp" = linear probing
    * "qp" = quadratic probing
    * "dh" = double hashing (double hash function is h2(x) = a - (x % a), *with 'a' being a fifth command line argument.*
    
## Example
Use the example below to aid in compiling and checking results:

example:~/workspace $ ./hash hashtest1.txt hashq1.txt 13 qp
The number of words found in the file was 10
The number of unique words found in the file was 9 The number of collisions was 5
sample appears on lines [1] The search had 0 collisions
is appears on lines [1,2] The search had 0 collisions
ten appears on lines [2] The search had 0 collisions
this appears on lines [] The search had 1 collisions
a appears on lines [1]
The search had 0 collisions
void appears on lines [] The search had 1 collisions
five appears on lines [] The search had 6 collisions
    
## Additional Notes
This project uses the "djb2" hash function. [Click here to view the function](http://www.cse.yorku.ca/~oz/hash.html).
