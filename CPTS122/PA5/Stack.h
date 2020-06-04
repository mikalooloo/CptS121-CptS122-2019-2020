/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 5
Date: March 27, 2020
Description: Offbrand Yu Gi Oh! Game
Stack class (the deck)
*/

#ifndef STACK_H
#define STACK_H

#include "Header.h"
#include <iostream>
#include <string.h>

//template <class S>
class Deck
{
private:
	CardStackNode* entireDeck;
	NameList* prefixHead;
	NameList* suffixHead;
public:
	// Constructor
	Deck();
	// Destructor
	~Deck();

	/*
	Function: buildCards()
	-Description: combines attack and defense points together into one final card
	-Input parameters: ifstream&file, NameList* head
	-Returns: NameList*
	-Preconditions: n/a
	-Postconditions: combined cards
	*/
	NameList* buildCards(std::ifstream& file, NameList* head);
	/*
	Function: lengthofList()
	-Description: finds how many items were in the .txt files
	-Input parameters: NameList* head
	-Returns: int (the length)
	-Preconditions: n/a
	-Postconditions: counted
	*/
	int lengthofList(NameList* head);
	/*
	Function: findPos()
	-Description: finds the card in the rand_pos position
	-Input parameters: NameList* head, int rand_pos
	-Returns: NameList* (card in rand_pos position)
	-Preconditions: a card exsists in the rand_pos
	-Postconditions: found card
	*/
	NameList* findPos(NameList* head, int rand_pos);

	// Stack Operations

	/*
	Function: pop()
	-Description: pops off the top of the stack
	-Input parameters: n/a
	-Returns: CardStackNode *
	-Preconditions: n/a
	-Postconditions: popped
	*/
	CardStackNode * pop(void);
	/*
	Function: printDeck()
	-Description: prints the entire deck
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: printed
	*/
	void printDeck(void);
	/*
	Function: lengthofDeck()
	-Description: returns length of deck. forgot i had this i could've used this instead of emptydeck but it's fine
	-Input parameters: n/a
	-Returns: int (length of deck)
	-Preconditions: n/a
	-Postconditions: n/a
	*/
	int lengthofDeck(void);
	/* 
	Function: emptyDeck()
	-Description: returns 0 if not empty 1 if empty
	-Input parameters: n/a
	-Returns: int
	-Preconditions: n/a
	-Postconditions: n/a
	*/
	int emptyDeck(void);
	/*
	Function: find()
	-Description: finds the card at the index in the deck
	-Input parameters: int index
	-Returns: CardStackNode*
	-Preconditions: n/a
	-Postconditions: found card
	*/
	CardStackNode* find(int index);

	
};


#endif STACK_H