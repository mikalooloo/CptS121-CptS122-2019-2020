/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 5
Date: March 27, 2020
Description: Offbrand Yu Gi Oh! Game
Queue class (Attack, Defense queues)
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "Header.h"

//template <class T>
class Queue
{
private:
	CardStackNode* mode;
public:
	// Constructor
	Queue(); // makes mode pointer null
	// Destructor
	~Queue();

	// Setters
	void setAttack(int num);
	void setDefense(int num);

	// Getters
	std::string getCardName(void);
	std::string getAndPrintType(void);
	int getAttack(void);
	int getDefense(void);

	// Queue Operators
	/*
	Function: enqueue_card()
	-Description: makes the inputted card at the back of the list
	-Input parameters: CardStackNode* card
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: at least one card is in the queue
	*/
	void enqueue_card(CardStackNode* card); // adds to the back
	/*
	Function: dequeue_card()
	-Description: removes the card at the front
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: one card was removed
	*/
	void dequeue_card(void); // removes from the front
	/*
	Function: print_cards()
	-Description: prints cards in the queue
	-Input parameters: int num - if 0, prints all cards in queue, if 1, prints one card in attack queue, if 2 prints one card in defense queue
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: n/a
	*/
	void print_cards(int num);
};

#endif QUEUE_H