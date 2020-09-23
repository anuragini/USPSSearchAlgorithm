#include <iostream>
#include<stdlib.h>

struct Node{
      int key;
      Node *next;
};

class LinkedList
{
  private:
    Node *head;

  public:
    LinkedList(){
    	head = NULL;
    }
    void insert(Node *prev, int newKey);
    Node* searchList(int key);
    void printList();
};
