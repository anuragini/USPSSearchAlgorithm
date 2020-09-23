#ifndef BST_HPP
#define BST_HPP

#include <string>

struct TreeNode
{
    int key;
    TreeNode *parent = NULL;     // Pointer to its parent node in BST
    TreeNode *left = NULL;  // Pointer to its leftChild in BST
    TreeNode *right = NULL; // Pointer to its rightChild in BST
};

/* Class for storing and manipulating the TreeNode's of BST*/

class BST
{
    public:
      // Check writeup for detailed function descriptions
     BST();
     ~BST();
      void addNode(int key);
      TreeNode* searchNode(int key);
      void printTree();

    private:
      TreeNode *root;
};

#endif
