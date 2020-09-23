#include "BST.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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

TreeNode* createNode(int key)
{
    TreeNode* newNode = new TreeNode();
    newNode->key = key;
    newNode->left = NULL; //traverse until NULL
    newNode->right = NULL;
    return newNode;
}

TreeNode* addNodeHelper(TreeNode* currNode, int key) 
{
    if(currNode == NULL){
        return createNode(key);
    }
    else if(currNode->key < key){
        currNode->right = addNodeHelper(currNode->right,key);
    }
    else if(currNode->key > key){
        currNode->left = addNodeHelper(currNode->left,key);
    }
    return currNode;

}

void printTreeHelper(TreeNode* currNode){
     if(currNode)
     {
        printTreeHelper(currNode->left);
        cout<< "Key: " << currNode->key << endl;
        printTreeHelper(currNode->right);
     }
 }
 
 TreeNode* searchKeyHelper(TreeNode* currNode, int data){
    if(currNode == NULL)
        return NULL;

    if(currNode->key == data)
        return currNode;

    if(currNode->key > data)
        return searchKeyHelper(currNode->left, data);

    return searchKeyHelper (currNode->right, data);
}


//--------------------------------


BST::BST() {
  root = NULL; 
}

BST::~BST() {
  //write your code
}


void BST::addNode(int key) 
{
    root = addNodeHelper(root, key); //this acts as the insert function
    //cout<<key<<" has been added"<<endl;
}

TreeNode* BST::searchNode(int key) {
    TreeNode* node = searchKeyHelper(root, key);
    if(node != NULL) {
        //cout<<"Key found:"<< node->key << endl;
        return node;
    }
    else
    {
        //cout <<"Key not found." <<endl;
        return NULL;
    }
}

void BST::printTree() {
    if (root == NULL)
    {
        cout<<"Tree is Empty. Cannot print"<<endl; 
        return;
    }
    printTreeHelper(root);
}

//main driver
int main()
{
    BST tree;
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
    float insert[400];
    float search[400];
    
    while(getline(file, s)) // getline function that takes both file and string s
    {
        if (s.length() > 0 ) // if the length of the string is more than zero check next if
        {
            int x = split(s,  delimiter, myarr, len);
            
            for(int i = 0; i<len;i++)
            {
                int x = stoi(myarr[i]);
                //tree.addNode(x);
                data[i] = x;
                count ++; // count will increment for each line
            }
       }
        numCount = count;
        
    }
    
    ofstream out_file;
    out_file.open("BST_B.csv");
    
    //print insert times
    auto start = chrono::steady_clock::now();
    count = 0;
    for (int i=0; i<40000; i++)
    {
      int x = data[i];
      tree.addNode(x);
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
          TreeNode* n = tree.searchNode(value);
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
    //TreeNode* n = tree.searchNode(70018);
    //tree.printTree();
    
    return 0;
}