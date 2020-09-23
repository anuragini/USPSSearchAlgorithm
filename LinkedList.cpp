#include "LinkedList.hpp"

#include<iostream> 
#include<fstream>
#include <chrono>
using namespace std; 

//Helper functions

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


// Add a new node to the list
void LinkedList::insert(Node* prev, int newKey)
{

  //Check if head is Null i.e list is empty
  if(head == NULL)
  {
    head = new Node;
    head->key = newKey; //this is the new node to be inserted
    head->next = NULL;
  }

  // if list is not empty, look for prev and append our node there
  else if(prev == NULL)
  {
      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = head; 
      head = newNode;
  }

  else
  {
      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = prev->next;
      prev->next = newNode;

    }
}


// Print the keys in your list
void LinkedList::printList(){
  Node* temp = head;

  while(temp->next != NULL){
    cout<< temp->key <<" -> ";
    temp = temp->next;
  }

  cout<<temp->key<<endl;
}

// Search for a specified key and return a pointer to that node
Node* LinkedList::searchList(int key) {

    Node* ptr = head;
    while (ptr != NULL && ptr->key != key)
    {
        ptr = ptr->next; //traverse through the list looking for the value
    }
    return ptr;
}


//main driver
int main()
{
    LinkedList li;
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
    float insert[400];
    float search[400];
    
    while(getline(file, s)) // getline function that takes both file and string s
    {
        if (s.length() > 0 ) // if the length of the string is more than zero check next if
        {
            int x = split(s,  delimiter, myarr, len);
            
            for(int i = 0; i<len;i++)
            {
                //cout<<myarr[i]<<endl;
                int x = stoi(myarr[i]);
                //li.insert(NULL, x);
                data[i] = x;
                count ++; // count will increment for each line
            }
       }
        numCount = count;
        
    }
    ofstream out_file;
    out_file.open("LinkedList_A.csv");
    
    //print insert times
    auto start = chrono::steady_clock::now();
    count = 0;
    for (int i=0; i<40000; i++)
    {
      int x = data[i];
      li.insert(NULL, x); //inserting at head
      if ((i+1)%100 == 0)
      {
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
          Node* n = li.searchList(value);
        }
        end = chrono::steady_clock::now();
        search[count] = float(chrono::duration_cast<chrono::nanoseconds>(end - start).count()/100.0);
        cout<<count+1 << " search " << search[count]<<endl;
        start = end;
        out_file<<count<<","<<insert[count]<<","<<search[count]<<endl;
        count++;
      }
      
    }
    return 0;
    
    
    
    
    
    //cout<<numCount<<endl;
    //Node* n = li.searchList(70018);
    //cout<<n->key<<endl;
    //li.printList();
    
    return 0;
}
  

 