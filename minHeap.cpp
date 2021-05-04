#include "minHeap.h"
using namespace std;
// Hash Table Functions
bool ascendingOrder(entry* e1, entry* e2) {
    if(e1->frequency != e2->frequency){
        return (e1->frequency < e2->frequency);
    }else{
        return (e1->ageCounter > e2->ageCounter);
    }
}
HashTable::HashTable(int k){
    int firstPrime = 2 * k; 
	  int i,j,count=0,b=0;
	  for(i=firstPrime;i>0;i++){
		  for(j=2;j<=i/2;j++){
			  if(i%j==0){
				  b=1;
				  break;
			  }
		  } 
		if(b==0){
      tableSize = i;
			count++;
		}
		b=0;
		if(count==1)
			break;
	  }
    //table.resize(tableSize);
    // Setting all the pointers on table to point to a NULL Struct
    for(int i = 0; i < tableSize; i++){
        entry *e1 = new struct entry;
        e1->str = "NULL";
        e1->frequency = 0;
        e1->indexArray = 0;
        e1->ageCounter = 0;
        table.push_back(e1);
    }
    total_elements = k;
}
int HashTable::getHash(string key){
    return (hash_string(key) % tableSize); 
}
int HashTable::getStatus(){
  return 0;
}
int HashTable::getTotalElements(){
    return total_elements;
}
int HashTable::getTableSize(){
    return tableSize;
}
void HashTable::setTotalElements(int k){
  total_elements = k;
}
void HashTable::setTableSize(){
int k = total_elements;
int firstPrime = 2 * k; 
	  int i,j,count=0,b=0;
	  for(i=firstPrime;i>0;i++){
		  for(j=2;j<=i/2;j++){
			  if(i%j==0){
				  b=1;
				  break;
			  }
		  } 
		if(b==0){
      tableSize = i;
			count++;
		}
		b=0;
		if(count==1)
			break;
	  }
    table.resize(tableSize);
}
int HashTable::searchElementinTable(string key){
    int hashValue = getHash(key);
      if(table.at(hashValue)->str == key){
            return hashValue;
        }else{
            for (int j = 1; j < tableSize; j++){
              int t = ((hashValue + (j * j)) % tableSize);
              if (table.at(t)->str == key){
                    return t;
                }
              if (table.at(t)->str == "NULL"){
                    return -1;
                }
            }
            return -1;
        }
}
int HashTable::searchElementinArray(string key){
    int hashValue = getHash(key);
    int originalValue = hashValue;
      if(table.at(hashValue)->str == key){//NULL or Deleted
            return table.at(hashValue)->indexArray;
        }else{
            for (int j = 1; j < tableSize; j++){
              int t = ((hashValue + (j * j)) % tableSize);
              if (table.at(t)->str == key){
                    return table.at(t)->indexArray;
                }
              if (table.at(t)->str == "NULL"){
                    return -1;
                }
            }
            return -1;
        }
}
void minHeap::printHashTable(){
  for(int i = 0; i < h1->getTableSize(); i++){
    cout << h1->table[i]->str << "at" << i <<",";
  }
}


// min Heap Definitions
minHeap::minHeap(int k){
    inserted = 0;
    size = 0;
    vdata.resize(0);
    h1 = new HashTable(k);
}

int minHeap::getSize(){
  return size;
}
bool minHeap::isFull(){
  if(size == vdata.size()){
    return true;
  }else{
    return false;
  }
}
int minHeap::minChild(int index){
  int left = (2*index)+1;
  int right = (2*index)+2;
  if(right >= vdata.size()){
    return left;
  }else{
    if(vdata[left]->frequency < vdata[right]->frequency){
      return left;
    }else if(vdata[left]->frequency > vdata[right]->frequency){
      return right;
    }else if(vdata[left]->frequency == vdata[right]->frequency){
        if(vdata[left]->ageCounter > vdata[right]->ageCounter){
          return left;
        }else{
          return right;
        }
    }
  }
  return 0;
}

void minHeap::insertHashTable(string value){
  // Insert in Hashtable
  int hashValue = h1->getHash(value);
  //int originalValue = hashValue;
  if((h1->table.at(hashValue)->str == "NULL") || (h1->table.at(hashValue)->str == "DELETED")){
    h1->table.at(hashValue) = new struct entry;
    h1->table.at(hashValue)->str = value;
    h1->table.at(hashValue)->frequency = 1;
    h1->table.at(hashValue)->indexArray = vdata.size() - 1;;
  }else{
      for (int j = 1; j < h1->table.size(); j++){
        int t = ((hashValue + (j * j)) % h1->table.size());
        if ((h1->table.at(t)->str == "NULL") || (h1->table.at(t)->str == "DELETED")){
          h1->table.at(t) = new struct entry;
          h1->table.at(t)->str = value;
          h1->table.at(t)->frequency = 1;
          h1->table.at(t)->indexArray = vdata.size() - 1;
          break;
        }
    }
  }
}

bool minHeap::compareEntries(entry* e1, entry* e2){
  if(e1->frequency > e2->frequency){
    return true;
  }else if(e1->frequency < e2->frequency){
    return false;
  }else{
    if(e1->ageCounter < e2->ageCounter){
      return true;
    }else{
      return false;
    }
  }
}
void minHeap::perculateUp(){
int i = vdata.size() - 1;
// perculate up
while(i!=0){
//key to parent node
int p = (i-1)/2;
//if the parent key is greater than the key of the node inserted, bubble up!
  if(compareEntries(vdata[p],vdata[i])){
    int a = h1->searchElementinTable(vdata[p]->str);
    int b = h1->searchElementinTable(vdata[i]->str);
    h1->table[a]->indexArray = i;
    h1->table[b]->indexArray = p;
    swap(vdata[i], vdata[p]);
    i = p;
}else{
    break;
  }
}
}
//Cant Swap: Reach Bottom, Hit a value that there is no need to swap
void minHeap::perculateDown(int index){
  while( ((index * 2) + 1) <= vdata.size() - 1){
    int minc = minChild(index);
    if((vdata[index]->frequency > vdata[minc]->frequency) || ( (vdata[index]->frequency == vdata[minc]->frequency) && (vdata[index]->ageCounter < vdata[minc]->ageCounter) )){
        int a = h1->searchElementinTable(vdata[minc]->str);
        int b = h1->searchElementinTable(vdata[index]->str);
        h1->table[a]->indexArray = index;
        h1->table[b]->indexArray = minc;
        swap(vdata[index], vdata[minc]);
    }
    index = minc;
  }
}

string minHeap::printHeap(){
  ostringstream out;
    for(int i = 0; i < vdata.size(); i++){
      out << vdata.at(i)->str << ":" << to_string(vdata.at(i)->frequency) << ",";
    }
  return out.str();
}
string minHeap::printAscendingOrder(){
  sort(vdata.begin(), vdata.end(), ascendingOrder);
  ostringstream out;
  for(int i = 0; i < vdata.size(); i++){
    out << (vdata[i]->str) << ":" << to_string(vdata[i]->frequency) << ",";
  }
  return out.str();
}

void minHeap::insert(string value){
  //Element not on table
  if (h1->searchElementinTable(value) == -1){
      int i = vdata.size();
      // check if there is space in the table 
      if(size < (h1->getTotalElements()) ){
        entry *e1 = new struct entry;        
        e1->str = value;
        e1->frequency = 1;
        e1->ageCounter = i + 1;
        e1->indexArray = vdata.size() - 1;
        vdata.push_back(e1);
        size++;
        inserted++;
        insertHashTable(value);
        perculateUp();
      // If there is no space on the table, then delete the min value(the root)
      }else{
          int freq = vdata[0]->frequency;
          popMin();
          entry *e1 = new struct entry;        
          e1->str = value;
          e1->frequency = freq + 1;
          inserted++;
          e1->ageCounter = inserted;
          e1->indexArray = vdata.size() - 1;
          vdata.push_back(e1);
          insertHashTable(value);
          perculateUp();
      }
    //Check if the element is on the table, Increase frequency on both table and minHeap
    }else{
      int num = h1->searchElementinTable(value);
      h1->table.at(num)->frequency++;
      vdata.at(h1->searchElementinArray(value))->frequency ++;
      perculateDown(h1->searchElementinArray(value));
  }
    //Print array after every insert
    // for(int i = 0; i < vdata.size(); i++){
    //   cout << vdata.at(i)->str << ":" << vdata.at(i)->frequency << ",";
    // }
    //   cout << endl;
}

void minHeap::popMin(){
  string str = vdata[0]->str;
  //replace rightmost value with the root
  vdata[0] = vdata[vdata.size()-1];
  //delete the rightmost value
  vdata.erase(vdata.end()-1);
  perculateDown(0);
  // Delete Element in Hashtable
  int hashValue = h1->getHash(str);
      if(h1->table.at(hashValue)->str == str){
          h1->table[hashValue]->str = "DELETED";
          h1->table[hashValue]->frequency = 0;
          h1->table[hashValue]->indexArray = 0;
          h1->table[hashValue]->ageCounter = 0;
      }else{
          for (int j = 1; j < h1->table.size(); j++){
            int t = ((hashValue + (j * j)) % h1->table.size());
            if (h1->table.at(t)->str == str){
              h1->table.at(t)->str = "DELETED";
              h1->table.at(t)->frequency = 0;
              h1->table.at(t)->indexArray = 0;
              h1->table.at(t)->ageCounter = 0;                
            }
          }
      }
}