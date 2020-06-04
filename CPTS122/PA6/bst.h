/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 6
Date: April 10, 2020
Description: Morse Code Translator
BST class file
*/

#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

class BST
{
private:
	struct TreeNode
	{
		char english; // English character that the
		std::string morse; // Morse Code string represents
		TreeNode* left;
		TreeNode* right;
	};
	TreeNode* root;

	void insert(TreeNode*& nodePtr, TreeNode*& newNode); // inserts the newNode into the nodePtr
	void destroySubTree(TreeNode*nodePtr); // destroys the subtree
	void displayInOrder(TreeNode*nodePtr) const; // prints the English characters in order
public:
    // Constructor
    BST();

    BST(char e, std::string m);

    // Destructor
    ~BST(); 

    // Binary tree operations
    void insertNode(char e, std::string m); // inserts the English character and the Morse Code string into the BST
    std::string lookUp(char e) const; // finds the English character in the BST and returns the Morse Code string
	void displayInOrder() const; // prints the English characters in order


};

#endif BST_H