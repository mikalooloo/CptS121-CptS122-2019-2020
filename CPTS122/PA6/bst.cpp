/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 6
Date: April 10, 2020
Description: Morse Code Translator
BST class function definitions
*/

#include "bst.h"
#include "fstream"

using namespace std;

// private
void BST::insert(TreeNode*&nodePtr, TreeNode*&newNode) // inserts the newNode into the nodePtr
{
    if (nodePtr == nullptr)
    {
        nodePtr = newNode; // inserting node
    }
    else if (newNode->english < nodePtr->english)
    {
        insert(nodePtr->left, newNode); // searching left
    }
    else
    {
        insert(nodePtr->right, newNode); // searching right
    }
}

void BST::destroySubTree(TreeNode*nodePtr) // destroys the subtree
{
    if (nodePtr)
    {
        if (nodePtr->left) // if nodePtr->left isn't null
        {
            destroySubTree(nodePtr->left);
        }
        if (nodePtr->right) // if nodePtr->right isn't null
        {
            destroySubTree(nodePtr->right);
        }
        delete nodePtr; // if both are null then delete it
    }
}
void BST::displayInOrder(TreeNode*nodePtr) const // prints the English characters in order
{
    if (nodePtr)
    {
        displayInOrder(nodePtr->left);
        cout << nodePtr->english << endl;
        displayInOrder(nodePtr->right);
    }
}

// public
// Constructor
BST::BST()
{
    char e;
    string m;
    root = nullptr;

    std::ifstream file;
    file.open("MorseTable.txt", std::ios::in);

    if (file.is_open()) // if MorseTable.txt opened fine
    {
        while (file >> e) // read in the english character that is first
        {
            file >> m; // then the string of morse code after it
            insertNode(e, m); // and insert into tree
        }

        file.close();
    }
    else
    {
        cout << "MorseTable.txt failed to open!" << endl;
    }
}

BST::BST(char e, std::string m)
{
    root->english = e;
    root->morse = m;
}

// Destructor
BST::~BST()
{
    destroySubTree(root);
}

// Binary tree operations
void BST::insertNode(char e, string m) // inserts the English character and the Morse Code string into the BST
{
    TreeNode* newNode = new TreeNode;	
    // initializing new node
    newNode->english = e;
    newNode->morse = m;
    newNode->left = nullptr;
    newNode->right = nullptr;

    insert(root, newNode);
}

string BST::lookUp(char e) const // finds the English character in the BST and returns the Morse Code string
{
    TreeNode* nodePtr = root;

    while (nodePtr) // while not null
    {
        if (nodePtr->english == e) // if this node's english character matches the one we are searching for
        {
            return nodePtr->morse; // return the morse code that represents that english character
        }
        else if (e < nodePtr->english) // otherwise, go left if it is less than
        {
            nodePtr = nodePtr->left;
        }
        else // or go right if it is more than
        { 
            nodePtr = nodePtr->right;
            }
    }

    return "[NO TRANSLATION]"; // if it is a character not found in our morse code, print out [No translation]
}

void BST::displayInOrder() const // prints the English characters in order
{
    displayInOrder(root); // start at the root
}