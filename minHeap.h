#define MINHEAP_H
#include <iostream>
#include <sstream>
#include <ctype.h>
#include <vector>
#include <string>
using namespace std;

struct entry{
  string str;
  int frequency;
  int indexArray; // should update in insert and delete, and 
}; 

class HashTable{
public:
  // Constructor to create a hash table with the next prime number of 2 * n:
  HashTable(int k = 0);
  // Hash function to calculate hash for a value:
  int getHash(string key);
  int getSize();
  int searchElementinTable(string key);
  int searchElementinArray(string key);
  std::vector<entry*> table;
private:
  int total_elements; // actual elements in array
  int tableSize;      // size of table
};

class minHeap{
 public:
    minHeap(int k = 0);
    void insert(string value); //inserts element in the heap, then on the hashTable
    void popMin();  //delets min value, replaces it with furthest value to the right and then perculates down, then deletes value in the hashtable too
    bool isFull(); // checks if size is full
    int getSize(); //returns size of valid entries , vdata.size
    string printHeap(); // prints "String:Frequency"
 private:
    std::vector<entry*> vdata;
    HashTable h1(int k = 0); //Initializes a hastable as soon as a heap is created
    int size; // how many of the nodes are valid, non-empty, vdata.size returns the size of the vector
};
