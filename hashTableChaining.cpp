#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include <math.h>
#include <chrono>
using namespace std;

//Put helper functions here

int split(string s, char delimiter, string inputarr[],int len)// this will take in four parameters
{
    s = s + delimiter;//
    string arr[len];
    int count = 0;
    string word = "";
    if(s.length() == 0 || s == "")// if s is equal to zero or s equals blank return zero
    {
        return 0; 
    }
    for(int i = 0; i < s.length();i++)// for loop cycling thorugh the entire string
    {
        if(s[i] == delimiter) // if the index equals delimiter
        {
            if (word.length() > 0)// when word length is more than zero 
            {
                arr[count] = word;// the count will equal the word 
                word = "";// this will be a blank
                count++;//iterate count
            }
        }
        else
        {
            if (s[i] != delimiter)//is s does not equal the delimter
            {
                word = word + s[i]; // string will be concatenated
            }
           

        }
    }
    for (int i=0; i<len; i++)// cycle through the count for the array
    {
        inputarr[i] = arr[i];// this will equal the new array
        
        
    }
    //return count
    return count;
}



struct HashNode {
  int key;
  int value;
  HashNode* next;
  
  HashNode() {key = 0; value = 0; next = 0;}
  HashNode(int k, int v) {key = k; value = v; next = 0;}
  ~HashNode() {}
};

class HashTable {
  HashNode** table;
  int size;
  int numOfcolision = 0;

public:
  
  HashTable(int s) {
    size = s;
    table = new HashNode *[s];
    for (int i = 0; i < size; i++) table[i] = 0;
  }

  ~HashTable() {
    for (int i = 0; i < size; i++) 
    {
      HashNode* tmp = table[i];
      while (tmp != 0) 
      {
      	HashNode* curr = tmp;
      	tmp = tmp->next;
      	delete curr;
      }
    }

    delete[] table;
  }

  void insert(int key, int value) {
    HashNode* node = new HashNode(key, value);
    int index = hashCode(key, size);
    
    if (table[index] == 0)  
    {
      table[index] = node; //no collision
    }
    else 
    {
      numOfcolision++;
      node->next = table[index];//add the new node at head position of linked list. Add the node at this index to create a linked list of nodes
      table[index] = node;
    }
  }

  HashNode* search(int key) {
    int index = hashCode(key, size);

    if (table[index] == 0)  return 0;
    else {
      HashNode* curr = table[index];
      while (curr != 0) {
	if (curr->key == key) return curr;
	else curr = curr->next;
      }
      return 0;
    }
  }

  int hashCode(int k, int table_size) {
    return k % table_size; //this is the potential index of the array if not use conflict resolution algorithm
  }
  
  void printHashTable() {
    for (int i = 0; i < size; i++) 
    {
      if (table[i] != 0) 
      {
        	cout << "[" << i << "] ";
        	HashNode* curr = table[i];
        	while (curr != 0) {
        	  cout << "-> Key: " << curr->key << " (#" << hashCode(curr->key, size)<< ") Value: " << curr->value; 	  
        	  curr = curr->next;
        	}
        	cout << endl;
      }
      else 
      {
      	cout << "[" << i << "] -> Empty" << endl;
      }
    }
  }
  
  int getNumOfCollision()
  {
    return numOfcolision;
  }
  
}; //end of class



int main() {

    int size = 40009;
  
    HashTable HT(size);
    
    float insert[400];
    float search[400];
    
    ifstream file ("dataSetA.csv");
    if(!file)
    {
        return -1;
    }
    char delimiter = ',';
    int len = 40000;
    string myarr[len];
    string s; 
    int y;
    string a;
    int count = 0;
    int numCount;
    int data[40000];
    
    while(getline(file, s)) // getline function that takes both file and string s
    {
        if (s.length() > 0 ) // if the length of the string is more than zero check next if
        {
            int x = split(s,  delimiter, myarr, len);
            for(int i = 0; i<len;i++)
            {
              int x = stoi(myarr[i]);
              data[i] = x;
            }
       }
        numCount = count;
        
    }
    
    ofstream out_file;
    out_file.open("hashtable_chaining_A.csv");
    
    //print insert times
    auto start = chrono::steady_clock::now();
    int startCollisions = 0;
    int endCollisions = 0;
    count = 0;
    for (int i=0; i<40000; i++)
    {
      int x = data[i];
      HT.insert(x,x);
      if ((i+1)%100 == 0)
      {
        int numCollisions = HT.getNumOfCollision() - startCollisions; //collision for this batch of 100 elements
        startCollisions = HT.getNumOfCollision(); //reset starrt count
        cout<<"--------------------------------"<<endl;
        //insert
        auto end = chrono::steady_clock::now();
        //cout<<count<< "  " << chrono::duration_cast<chrono::nanoseconds>(end - start).count()<<endl;
        insert[count] = float(chrono::duration_cast<chrono::nanoseconds>(end - start).count()/100.0);
        cout<<count+1 << " insert " << insert[count]<<endl;
        start = chrono::steady_clock::now();
        //search
        //Random indexes  
        srand((unsigned) time(0));
        int randomNumber;
        for (int index = 0; index < 100; index++) 
        {
          randomNumber = rand() % ((count+1)*100);
          //cout << randomNumber << endl;
          int value = data[randomNumber];
          HT.search(value);
        }
        end = chrono::steady_clock::now();
        search[count] = float(chrono::duration_cast<chrono::nanoseconds>(end - start).count()/100.0);
        cout<<count+1 << " search " << search[count]<<endl;
        start = end;
        out_file<<count<<","<<insert[count]<<","<<search[count]<<","<<numCollisions<<endl;
        count++;
      }
    }
  int num1=  78179;
  if (HT.search(num1) == 0) cout << num1 << ": Key not found" << endl;
  else cout << "Key: " << num1 << " has value:" << HT.search(num1)->value;
  //HT.printHashTable();
  
  return 0;
}
