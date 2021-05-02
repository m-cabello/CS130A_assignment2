#include "minHeap.h"
using namespace std;
// Hash Table Functions
HashTable::HashTable(int k){
    cout << k << endl;
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
    // Setting all the pointers on table to point to a NULL Struct
    for(int i = 0; i < tableSize; i++){
        table.at(i) = NULL;
    }
    total_elements = k;
}
int HashTable::getHash(string key){
    hash<string> hash_string;
    return (hash_string(key) % total_elements); 
}
int HashTable::getSize(){
    return total_elements;
}
int HashTable::searchElementinTable(string key){
    // cout << getHash(key) << endl;
    int hashValue = getHash(key);
    // cout << "hey2" << endl;
    int originalValue = hashValue;
    // cout << "hey3" << endl;
      if(table.at(hashValue)->str == key){//NULL or Deleted
            return hashValue;
        }else{
            for (int j = 1; j < total_elements; j++){
              int t = ((hashValue + (j * j)) % tableSize);
              if (table.at(t)->str == key){
                    return t;
                }
              if (table.at(t) == NULL){
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
              if (table.at(t) == NULL){
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
    vdata.resize(k);
    HashTable h1(k);
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
string minHeap::printHeap(){
  ostringstream out;
    for(int i = 0; i < vdata.size(); i++){
      out << vdata.at(i)->str << ":" << vdata.at(i)->frequency << ",";
    }
  return out.str();
}
void minHeap::insert(string value){
  //Element not on table
  if (h1.searchElementinTable(value) == -1){
      int i = vdata.size();
      // check if there is space in the table *check THIS IF STATEMENT*
      if(i != h1.getSize()){
        entry * e1;
        e1->str = value;
        e1->frequency = 1;
        e1->indexArray = vdata.size() - 1;
        vdata.push_back(e1);
            // perculate up
            while(i!=0){
            //key to parent node
            int p = (i-1)/2;
            //if the parent key is greater than the key of the node inserted, bubble up!
            if(vdata[i]<vdata[p]){
                vdata[i] = vdata[p];
                vdata[p]->str = value;
                i = p;
            }else{
                break;
            }
          }
      // If there is no space on the table, then delete the min value(the root)
      }else{
          int freq = vdata[0]->frequency;
          popMin();
          int i = vdata.size();
          entry * e1;
          e1->str = value;
          e1->frequency = freq + 1;
          e1->indexArray = vdata.size() - 1;
          vdata.push_back(e1);
          // perculate up
          while(i!=0){
            //key to parent node
            int p = (i-1)/2;
            //if the parent key is greater than the key of the node inserted, bubble up!
            if(vdata[i]<vdata[p]){
                vdata[i] = vdata[p];
                vdata[p]->str = value;
                i = p;
            }else{
                break;
            }
          }
      }
    //Check if the element is on the table, Increase frequency
    }else{
      int num = h1.searchElementinTable(value);
      vdata.at(num)->frequency ++;
  }

//Insert Element in Table
// Check if element is already in the table
  if(h1.searchElementinTable(value) != -1){ 
    int num = h1.searchElementinTable(value);
    h1.table[num]->frequency++;
  }
  // Element not on table
  if(h1.searchElementinTable(value) == -1){
  int hashValue = h1.getHash(value);
  int originalValue = hashValue;
      if(h1.table.at(hashValue) == NULL){//NULL or Deleted
            h1.table.at(hashValue) = new struct entry;
            h1.table.at(hashValue)->str = value;
            h1.table.at(hashValue)->frequency += 1;
            h1.table.at(hashValue)->indexArray = vdata.size() - 1;;
        }else{
            for (int j = 1; j < h1.table.size(); j++){
              int t = ((hashValue + (j * j)) % h1.table.size());
              if (h1.table.at(t) == NULL){
                    h1.table.at(hashValue) = new struct entry;
                    h1.table.at(hashValue)->str = value;
                    h1.table.at(hashValue)->frequency = 1;
                    h1.table.at(hashValue)->indexArray = vdata.size() - 1;;
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
      //if a complete bst is not in the correct formatt, 
      //when the right child has the largest value out of the parent and the left child ,bubble down the left side.
      if(vdata[left]<=vdata[right]){
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
              if(vdata[i]<=vdata[left] && vdata[i]<=vdata[right]){
                break;
              }
            swap(vdata[left], vdata[i]);
    }
  }
// Delete Element in Hashtable
    int hashValue = h1.getHash(str);
    int originalValue = hashValue;
      if(h1.table.at(hashValue)->str == str){//NULL or Deleted
            delete h1.table[hashValue];
        }else{
            for (int j = 1; j < h1.table.size(); j++){
              int t = ((hashValue + (j * j)) % h1.table.size());
              if (h1.table.at(t)->str == str){
                  delete h1.table[hashValue];
                }
            }
        }

}


// Extra Code for insert
/*
}else if(originalValue == t){
                    // this is the case where table is full
                    int minimumValue = -1;
                    for(int i = 0; i < h1.table.size();i++){
                      if(h1.table.at(i)->frequency > minimumValue){
                        minimumValue = h1.table.at(i)->frequency;
                      }
                    }
                    int index = 0;
                    for(int j = 0; j < h1.table.size();j++){
                      if(h1.table.at(j)->frequency == minimumValue){
                        index = j;                      
                      }
                    }
                    string str = h1.table.at(index)->str;
                    h1.deleteElement(str);
                    h1.insertElement(value);
                    break;
*/