/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 5
Date: March 27, 2020
Description: Offbrand Yu Gi Oh! Game
Queue.cpp for Queue class
*/

#include "Header.h"
#include "Player.h"
#include "Queue.h"
#include "Stack.h"
#include "Stats.h"

// Constructor
Queue::Queue()
{
	mode = nullptr;
}
Queue::~Queue()
{
	std::cout << "Queue destroyed." << std::endl;
}

// Setters
void Queue::setAttack(int num)
{
	mode->attack += num;
}
void Queue::setDefense(int num)
{
	mode->defense += num;
}

// Getters
std::string Queue::getCardName(void)
{
	return mode->name;
}
std::string Queue::getAndPrintType(void)
{
	std::cout << mode->name << " - ";
	std::cout<< mode->type << std::endl;

	return mode->type;
}
int Queue::getAttack(void)
{
	return mode->attack;
}
int Queue::getDefense(void)
{
	return mode->defense;
}

// Queue Operators

/*
	Function: enqueue_card()
	-Description: makes the inputted card at the back of the list
	-Input parameters: CardStackNode* card
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: at least one card is in the queue
	*/
void Queue::enqueue_card(CardStackNode* card) // adds to the back
{
	CardStackNode* temp = mode;

	if (mode == nullptr)
	{
		mode = card;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = card;
	}

	card->next = nullptr;
}
/*
	Function: dequeue_card()
	-Description: removes the card at the front
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: one card was removed
	*/
void Queue::dequeue_card() // removes from the front
{
	if (mode == nullptr)
	{
		std::cout << "Error! There are no cards in this queue." << std::endl;
	}
	else
	{
		CardStackNode* temp = mode;
		mode = mode->next;
		free(temp);
	}
}
/*
	Function: print_cards()
	-Description: prints cards in the queue
	-Input parameters: int num - if 0, prints all cards in queue, if 1, prints one card in attack queue, if 2 prints one card in defense queue
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: n/a
	*/
void Queue::print_cards(int num)
{
	CardStackNode* temp = mode;
	
	if (num == 0)
	{
		int count = 1;

		while (temp != nullptr)
		{
			std::cout << count << ". " << temp->name << std::endl;
			std::cout << std::setw(3) << "Attack Points: " << temp->attack << std::endl;
			std::cout << std::setw(3) << "Defense Points: " << temp->defense << std::endl;
			std::cout << std::setw(3) << "Type: " << temp->type << std::endl << std::endl << std::endl;
			temp = temp->next;
			++count;
		}
	}
	else if (num == 1)
	{
		std::cout << temp->name << std::endl;
		std::cout << std::setw(3) << "Attack Points: " << temp->attack << std::endl;
	}
	else if (num == 2)
	{
		std::cout << temp->name << std::endl;
		std::cout << std::setw(3) << "Defense Points: " << temp->defense << std::endl;
	}
}

