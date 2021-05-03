//PA-02
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
#include "minHeap.h"
using namespace std;

int main(int argc, char** argv){
// Make Sure I have the right inputs
  if(argc < 4){
    cerr << "Usage: " << argv[ 0 ] << "$INPUT_FILE $OUTPUT_FILE $K" << endl;
    exit(1);
  }
// Declare File 
  ifstream stringFile;
  stringFile.open(argv[1]);
  if (stringFile.fail()){
    cerr << "Could not open file " << argv[1];
    exit(1);
  }

  //Read File   
  int k = stoi(argv[3]);
  minHeap heap1(k);
  string line;
    if (stringFile.is_open()){
        while (getline(stringFile,line, ',')){
                heap1.insert(line); 
              }
    }

// heap1.insert("pine");
// heap1.insert("cat");
// heap1.insert("pear");
// heap1.insert("pine");
// heap1.insert("dog");
// heap1.insert("apple");

  stringFile.close();

  // Writting to File
  ofstream myfile;
  myfile.open(argv[2]);
  myfile << heap1.printHeap();
  myfile.close();
  return 0;
}