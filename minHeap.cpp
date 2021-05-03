#include "minHeap.h"
using namespace std;
// Hash Table Functions

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
    hash<string> hash_string;
    return (hash_string(key) % total_elements); 
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
    int originalValue = hashValue;
      if(table.at(hashValue)->str == key){//NULL or Deleted
            return hashValue;
        }else{
            for (int j = 1; j < total_elements; j++){
              int t = ((hashValue + (j * j)) % tableSize);
              if (table.at(t)->str == key){
                    return t;
                }
              if (table.at(t)->str == "NULL"){
                    return -1;
                }
              if (originalValue == t){
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
            for (int j = 1; j < total_elements; j++){
              int t = ((hashValue + (j * j)) % tableSize);
              if (table.at(t)->str == key){
                    return table.at(t)->indexArray;
                }
              if (table.at(t)->str == "NULL"){
                    return -1;
                }
              if (originalValue == t){
                    return -1;
                }

            }
            return -1;
        }
}
// min Heap Definitions
minHeap::minHeap(int k){
    size = 0;
    vdata.resize(0);
    h1 = new HashTable(k);
    //h1.setTotalElements(k);
    //h1.setTableSize();
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
    swap(vdata[i], vdata[p]);
    i = p;
}else{
    break;
  }
}
}
//Cant Swap: Reach Bottom, Hit a value that there is no need to swap
void minHeap::perculateDown(){
int i = 0;
  //bubbleling up
  while(true){
    int left = (2*i)+1;
    int right = (2*i)+2;
    //the left and right index should be smaller than the size of the vector. If not, break!
    if( (left < vdata.size()) && (right < vdata.size()) ){
      //if both children are larger than the parent, nothing needs to be done!
      if(compareEntries(vdata[left], vdata[i]) && compareEntries(vdata[right], vdata[i])){
          break;
        }
      //when the right child has the largest value out of the parent and the left child ,bubble down the left side.
      if(compareEntries(vdata[right],vdata[left]) ){
        swap(vdata[left], vdata[i]);
      //else, if the left child has the largest value, bubble down the right side.
      }else{
         swap(vdata[right], vdata[i]);
      }
    }
    //the left and right index should be smaller than the size of the vector. If not, break,. nothing needs to be done.
    else if(right >= vdata.size() && left >= vdata.size()){
              break;
          }else{
              //if both children are larger, don't do anything!
              if(compareEntries(vdata[left], vdata[i]) && compareEntries(vdata[right], vdata[i])){
                break;
              }
            //swap(vdata[left], vdata[i]);
            break;
    }
  }
}

string minHeap::printHeap(){
  ostringstream out;
    for(int i = 0; i < vdata.size(); i++){
      out << vdata.at(i)->str << ":" << vdata.at(i)->frequency << ",";
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
        e1->ageCounter = 1;
        e1->indexArray = vdata.size() - 1;
        vdata.push_back(e1);
        size++;
        perculateUp();
      // If there is no space on the table, then delete the min value(the root)
      }else{
          int freq = vdata[0]->frequency;
          popMin();
          entry *e1 = new struct entry;        
          e1->str = value;
          e1->frequency = freq + 1;
          e1->ageCounter = 1;
          e1->indexArray = vdata.size() - 1;
          vdata.push_back(e1);
          perculateUp();
      }
    //Check if the element is on the table, Increase frequency on both table and minHeap
    }else{
      int num = h1->searchElementinTable(value);
      h1->table.at(num)->frequency++;
      vdata.at(h1->searchElementinArray(value))->frequency ++;
      perculateDown();
  }

//Insert Element in Table
  // Element not on table
  if(h1->searchElementinTable(value) == -1){
  int hashValue = h1->getHash(value);
  int originalValue = hashValue;
      if(h1->table.at(hashValue)->str == "NULL"){//NULL or Deleted
            h1->table.at(hashValue) = new struct entry;
            h1->table.at(hashValue)->str = value;
            h1->table.at(hashValue)->frequency = 1;
            h1->table.at(hashValue)->indexArray = vdata.size() - 1;;
        }else{
            for (int j = 1; j < h1->table.size(); j++){
              int t = ((hashValue + (j * j)) % h1->table.size());
              if (h1->table.at(t)->str == "NULL"){
                    h1->table.at(hashValue) = new struct entry;
                    h1->table.at(hashValue)->str = value;
                    h1->table.at(hashValue)->frequency = 1;
                    h1->table.at(hashValue)->indexArray = vdata.size() - 1;;
                    break;
                }else if(originalValue == t){
                    // this is the case where table is full
                    popMin();
                    insert(value);
                    break;
                }
            }
        }
    }
    //Print array after every insert
    for(int i = 0; i < vdata.size(); i++){
      cout << vdata.at(i)->str << ":" << vdata.at(i)->frequency << ",";
    }
      cout << endl;
         
}

void minHeap::popMin(){
  string str = vdata[0]->str;
  //replace rightmost value with the root
  vdata[0] = vdata[vdata.size()-1];
  //delete the rightmost value
  vdata.erase(vdata.end()-1);
  int i = 0;
  //bubbleling up
  while(true){
    int left = (2*i)+1;
    int right = (2*i)+2;
    //the left and right index should be smaller than the size of the vector. If not, break!
    if( ( left < vdata.size() ) && ( right < vdata.size() ) ){
      //if both children are larger than the parent, nothing needs to be done!
      if(vdata[i]<=vdata[left] && vdata[i]<=vdata[right]){
          break;
      }
      //when the right child has the largest value out of the parent and the left child ,bubble down the left side.
      if(vdata[left]->frequency<=vdata[right]->frequency){
        swap(vdata[left], vdata[i]);
      //else, if the left child has the largest value, bubble down the right side.
      }else{
         swap(vdata[right], vdata[i]);

      }
    }
    //the left and right index should be smaller than the size of the vector. If not, break,. nothing needs to be done.
    else if(right >= vdata.size() && left >= vdata.size()){
              break;
          }else{
              //if both children are larger, don't do anything!
              if(vdata[i]->frequency<=vdata[left]->frequency && vdata[i]->frequency<=vdata[right]->frequency){
                break;
              }
            swap(vdata[left], vdata[i]);
    }
  }
// Delete Element in Hashtable
    int hashValue = h1->getHash(str);
    int originalValue = hashValue;
      if(h1->table.at(hashValue)->str == str){//NULL or Deleted
            h1->table[hashValue]->str = "NULL";
            h1->table[hashValue]->frequency = 0;
            h1->table[hashValue]->indexArray = 0;
            h1->table[hashValue]->ageCounter = 0;
        }else{
            for (int j = 1; j < h1->table.size(); j++){
              int t = ((hashValue + (j * j)) % h1->table.size());
              if (h1->table.at(t)->str == str){
                  h1->table[t]->str = "NULL";
                  h1->table[t]->frequency = 0;
                  h1->table[t]->indexArray = 0;
                  h1->table[t]->ageCounter = 0;                }
            }
        }

}
