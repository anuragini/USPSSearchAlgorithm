#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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


struct HashNode
{
  int key;
  int value;

  HashNode()
  {
    key = 0;
    value = 0;
  }
  HashNode(int k, int v)
  {
    key = k;
    value = v;
  }
  ~HashNode() {}
};

class HashTable
{
  HashNode **table;
  int size;
  int numOfcolision =0;
public:

  HashTable(int s)
  {
    size = s;
    table = new HashNode *[s];
    for (int i = 0; i < size; i++)
      table[i] = 0;
  }

  ~HashTable() { delete[] table; }

  int getNumOfCollision()
  {
    return numOfcolision;
  }
  
  //Insert using linear probing
  void insertLinear(int key, int value)
  {
    HashNode *node = new HashNode(key, value);
    int index = hashCode(key, size);

    if (table[index] == 0)
    {
      table[index] = node;
    }
 //this will be the first available index
    else if(table[index]->key == key)
    {
      //same index postion but different key value
      //cerr << "Key in use with value:" << table[index]->value << " \n";
      numOfcolision++; //will look for next avaliable index position
    }
    else 
    { 
      //looping through a circular array. Once the index reaches the size of array, it is modded and reset to the first element index in array.
      for (int i = (index + 1) % size; i != index; i = (i + 1) % size) 
      {
        if (table[i] == 0)
        {
          table[i] = node; //first avaliable index
          return;
        }
        else if (table[i]->key == key) 
        {
          //cerr << "Key already in use with value:" << table[index]->value << " \n";
          numOfcolision++;
          return;
        }
      }
      cerr << "Can not insert (" << key << ", " << value << ")Table is full" << endl;
      return;
    }
  }

  void insertQuadratic(int key, int value)
  {
    HashNode *node = new HashNode(key, value);
    int index = hashCode(key, size);

    if (table[index] == 0)
      table[index] = node;
    else if (table[index]->key == key)
    {
      //cerr << "Key in use with value:" << table[index]->value << " \n";
      numOfcolision++;
    }
    else
    {
      int j = 0;
      //looping through a circular array. Once the index reaches the size of array, it is modded and reset to the first element index in array.
      for (int i = (index + 1) % size; i != index; i = (i+i) % size)  
      {
        j = j + 1;
        int k = i + (j*j);  //quadratic search for an empty index position
        if (table[k] == 0)
        {
          table[k] = node;
          return;
        }
        else if (table[k]->key == key)
        {
          //cerr << "Key already in use with value:" << table[k]->value << " \n";
          numOfcolision++;
          return;
        }
      }
      cerr << "Can not insert (" << key << ", " << value << ")Table is full" << endl;
      return;
    }
  }



  HashNode *search(int key)
  {
    int index = hashCode(key, size);
    if (index < 0)
    {
      cout<<"Negative index not supported!" << endl;  //edge condition
      return 0;
    }
    if (table[index] == 0)  //value not in hashtable
      return 0;
    else if (table[index]->key == key)  //value found in hashtable
      return table[index];
    else
    {
      //value not found at hashcode index, so loop until you find it
      for (int i = (index + 1) % size; i != index; i = (i + 1) % size) 
      {
        if (table[i] == 0) //value is not in the hash table
          return 0;
        else if (table[i]->key == key)
          return table[i];
      }
      return 0;
    }
  }

  int hashCode(int k, int table_size)
  {
    int hash = k % table_size;
    return hash;
  }
  
  void printHashTable()
  {
    for (int i = 0; i < size; i++)
    {
      if (table[i] != 0)
      {
        cout << "[" << i << "] -> Key: " << table[i]->key << " (#" << hashCode(table[i]->key, size) << ") Value: " << table[i]->value << endl;
      }
      else
      {
        cout << "[" << i << "] -> Empty" << endl;
      }
    }
  }
};

//int main(int argc, char *argv[])
int main()
{

  //if (argc != 2)
  // return 0;
  int size = 40009;

  HashTable HT(size);
  
    float insert[400];
    float search[400];
    
    ifstream file ("dataSetB.csv");
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
    out_file.open("hashtable_quadratic.csv");
    
    //print insert times
    auto start = chrono::steady_clock::now();
    int startCollisions = 0;
    int endCollisions = 0;
    count = 0;
    for (int i=0; i<40000; i++)
    {
      int x = data[i];
      //HT.insertLinear(x, x);
      HT.insertQuadratic(x,x);
      if ((i+1)%100 == 0)
      {
        int numCollisions = HT.getNumOfCollision() - startCollisions;
        startCollisions = HT.getNumOfCollision();
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
    return 0;
    

    

    //Get number of collisions
    int numCollision = HT.getNumOfCollision();
    cout<<"Number of collisions: " << numCollision << endl;
    
    //HT.printHashTable();
    int name1 = 56659;

    if (HT.search(name1) == 0) 
    {
      cout << name1 << ": Key not found" << endl;
    }
    else
    {
      cout << "Key: " << name1 << " has value:" << HT.search(name1)->value <<endl;;
    }

    name1 = -90;

    if (HT.search(name1) == 0) 
    {
      cout << name1 << ": Key not found" << endl;
    }
    else
    {
      cout << "Key: " << name1 << " has value:" << HT.search(name1)->value << endl;
    }
    

  return 0;
}
