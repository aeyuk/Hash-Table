/* CATE YUK
CWID: 11817795
Project 3: Builds a hash table out of words read in from a file.
Outputs number of appearances and collisions.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <locale>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;

struct Node {
    string key;
    string line;
} ;


unsigned long DJB2(string str) {
    unsigned long hash = 5381;
    int c;
    for (unsigned int i = 0; i < str.length(); i++) {
        c = (int) str[i];
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}


int main(int argc, char **argv) {
    ifstream filei; //input file
    ifstream fileq; //query file
    filei.open(argv[1]);
    fileq.open(argv[2]);

    //Try to open files
    if (!filei.is_open()) {
        cout << "Error: could not open input file " << argv[1] << endl;
        return 1;
    }
    if (!fileq.is_open()) {
        cout << "Error: could not open input file " << argv[2] << endl;
        return 1;
    }


    //Variable List
    int size = atoi(argv[3]); //Size of the table
    string fileLine;
    string word;
    int lineCount = 0;
    int wordCount = 0;
    int uniqueCount = 0;
    unsigned long hashValue = 0;
    int tableIndex = 0;
    int numCollisions = 0; //Counts collisions in building the table
    int qCollisions = 0; //Count collisions in searching the table
    int flag = 0;
    int check = 0;
    int loop = 0;


    Node* hashArray = new Node[size]; //Dynamically allocate memory



    //Build the Table
    while (getline(filei, fileLine)) { //Read in text line by line
        lineCount++; //Incremement line count
        istringstream iss(fileLine);
        while (iss >> word) { //Read in line word by word
            hashValue = DJB2(word);
            tableIndex = hashValue % size;
            while (flag == 0) {
                if (hashArray[tableIndex].key == "") uniqueCount++;
                if (hashArray[tableIndex].key == "" ||
                    hashArray[tableIndex].key == word) {
                    hashArray[tableIndex].key = word;
                    if (hashArray[tableIndex].line != "")
                        hashArray[tableIndex].line.push_back(',');
                    //Appends line number
                    hashArray[tableIndex].line += to_string(lineCount);
                    flag = 1;
                }
                //Collision occured
                else {
                    numCollisions++;
                    //LINEAR PROBING//
                    if (strcmp(argv[4], "lp") == 0) {
                        tableIndex++;
                        tableIndex = tableIndex % size;
                    }
                    //QUADRATIC PROBING//
                    if (strcmp(argv[4], "qp") == 0) {
                        loop++;
                        tableIndex = ((hashValue%size) + (loop*loop)) % size;
                    }
                    //DOUBLE HASHING//
                    if (strcmp(argv[4], "dh") == 0) {
                        loop++;
                        int a = atoi(argv[5]);
                        int h2 = 0;
                        h2 = a - ((hashValue % size) % a);
                        tableIndex = (tableIndex + h2) % size;
                    }
                }
            }
        wordCount++; //Incrememnt word count
        flag = 0; //Reset variables
        loop = 0 ;
        }
    }


    //Output
    cout << endl;
    cout << "The number of words found in the file was "
         << wordCount << endl;
    cout << "The number of unique words found in the file was "
         << uniqueCount << endl;
    cout << "The number of collisions was "
         << numCollisions << endl << endl;


    //Searching With Query File
    while (fileq >> word) {
        hashValue = DJB2(word);
        tableIndex = hashValue % size;
        while (check == 0) {
            //Word found
            if (hashArray[tableIndex].key == word) {
                check = 1;
            }
            //Word not in table
            else if (hashArray[tableIndex].key == "") {
                check = 2;
            }
            else {
                qCollisions++;
                //LINEAR PROBING//
                if (strcmp(argv[4], "lp") == 0) {
                    tableIndex++;
                    tableIndex = tableIndex % size;
                }
                //QUADRATIC PROBING//
                if (strcmp(argv[4], "qp") == 0) {
                    loop++;
                    tableIndex = (hashValue % size + loop * loop) % size;
                }
                //DOUBLE HASHING//
                if (strcmp(argv[4], "dh") == 0) {
                    loop++;
                    int a = atoi(argv[5]);
                    int h2 = 0;
                    h2 = a - ((hashValue % size) % a);
                    tableIndex += h2;
                    tableIndex = tableIndex % size;
                }
            }
        }
        if (check == 1) {
            cout << word << " appears on lines ["
                 << hashArray[tableIndex].line;
            cout << "]" << endl;
            cout << "The search had " << qCollisions << " collisions"
                 << endl << endl;
        }
        else if (check == 2) {
            cout << word << " appears on lines []" << endl;
            cout << "The search had " << qCollisions << " collisions"
                 << endl << endl;
        }

        //Resetting variables
        qCollisions = 0;
        check = 0;
        loop = 0;
    }


    delete[] hashArray; //Free memory

    filei.close();
    fileq.close();


    return 0;
}

