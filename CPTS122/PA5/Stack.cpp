/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 5
Date: March 27, 2020
Description: Offbrand Yu Gi Oh! Game
Stack.cpp for Stack class
*/

#include "Header.h"
#include "Stack.h"


// CONSTRUCTOR - makes a deck of 30 cards
//template <class S>
//Deck<S>::
Deck::Deck()
{
	prefixHead = NULL; suffixHead = NULL;

	std::ifstream prefix;
	prefix.open("Prefix.txt", std::ios::in);
	prefixHead = buildCards(prefix, prefixHead); // read in all prefixes
	prefix.close();

	std::ifstream suffix;
	suffix.open("Suffix.txt", std::ios::in);
	suffixHead = buildCards(suffix, suffixHead); // read in all suffixes
	suffix.close();

	int size_prefix = lengthofList(prefixHead); // find the length of both
	int size_suffix = lengthofList(suffixHead);

	for (int c = 0; c < 30; ++c) // make 30 cards
	{
		CardStackNode* card = new CardStackNode;

		int rand_prefix_num = rand() % size_prefix + 1; // randomly pick a prefix
		NameList* rand_prefix = findPos(prefixHead, rand_prefix_num);

		int rand_suffix_num = rand() % size_suffix + 1; // and a suffix
		NameList* rand_suffix = findPos(suffixHead, rand_suffix_num);

		card->name = rand_prefix->name + ' ' + rand_suffix->name; // and combine them with their points
		card->attack = rand_prefix->points;
		card->defense = rand_suffix->points;

		int type = rand() % 4 + 1; // randomize the type

		switch (type)
		{
		case 1:
			card->type = "Earth";
			break;
		case 2:
			card->type = "Air";
			break;
		case 3:
			card->type = "Fire";
			break;
		case 4:
			card->type = "Water";
			break;
		}

		if (entireDeck == NULL) // if the deck is empty, start it
		{
			entireDeck = card;
			card->next = NULL;
		}
		else
		{
			card->next = entireDeck;
			entireDeck = card;
		}
	}

}

// DESTRUCTOR
//template <class S>
Deck::~Deck()
{
	std::cout << "Deck destroyed." << std::endl;
}

/*
	Function: buildCards()
	-Description: combines attack and defense points together into one final card
	-Input parameters: ifstream&file, NameList* head
	-Returns: NameList*
	-Preconditions: n/a
	-Postconditions: combined cards
	*/
NameList* Deck::buildCards(std::ifstream& file, NameList* head)
{
	std::string name;

	if (file.is_open()) // if Prefix.txt is open
	{
		NameList* prevNode = new NameList;
		while (file >> name)
		{
			//NameList* temp = (NameList*)malloc(sizeof(NameList));
			NameList* temp = new NameList;

			temp->name = '\0';
			temp->points = 0;

			if (head == NULL)
			{
				head = temp;
				temp->prev = NULL;
				temp->next = NULL;
			}
			else
			{
				prevNode->next = temp;
				temp->prev = prevNode;
				temp->next = NULL;
			}

			temp->name = name;
			temp->points = rand() % 4000 + 1; // make range between 1 and 4000

			if (temp->points < 200) // but if it's less than 200 just make it 200
			{
				temp->points = 200;
			}
			else
			{
				while (temp->points % 10 != 0) // make it divisble by 10
				{
					temp->points += 1;
				}
			}

			prevNode = temp;
		}
	}
	else // otherwise it did not open correctly
	{
		std::cout << "File did not open correctly when initializing the Deck!" << std::endl;
	}

	return head;
}
/*
	Function: lengthofList()
	-Description: finds how many items were in the .txt files
	-Input parameters: NameList* head
	-Returns: int (the length)
	-Preconditions: n/a
	-Postconditions: counted
	*/
int Deck::lengthofList(NameList* head)
{
	int count = 0;

	while (head != NULL)
	{
		head = head->next;
		++count;
	}

	return count;
}
/*
	Function: findPos()
	-Description: finds the card in the rand_pos position
	-Input parameters: NameList* head, int rand_pos
	-Returns: NameList* (card in rand_pos position)
	-Preconditions: a card exsists in the rand_pos
	-Postconditions: found card
	*/
NameList* Deck::findPos(NameList* head, int rand_pos)
{
	int position = 1, direction = 0;

	NameList* prev = new NameList;
	NameList* current = new NameList;

	current = head;

	while (position != rand_pos)
	{
		if (current != NULL) // if it's not the end of the list
		{
			if (direction == 0) // go left to right 
			{
				prev = current;
				current = current->next;
				++position;
			}
			else // or right to left, looking for the current number playing
			{
				prev = current;
				current = current->prev;
				--position;
			}
		}

		if (current == NULL) // if it is the end of the list
		{
			if (direction == 0) // switch directions
			{
				direction = 1;
				--position;
			}
			else
			{
				direction = 0;
				++position;
			}

			current = prev;
		}
	}

	return current;
}


// Stack Operations

/*
	Function: pop()
	-Description: pops off the top of the stack
	-Input parameters: n/a
	-Returns: CardStackNode *
	-Preconditions: n/a
	-Postconditions: popped
	*/
CardStackNode * Deck::pop(void)
{
	CardStackNode* temp = entireDeck;

	if (entireDeck != NULL)
	{
		entireDeck = entireDeck->next;
		temp->next = nullptr;
	}
	else
	{
		std::cout << "Deck is empty! Last round!!" << std::endl;
	}

	return temp;
}
/*
	Function: printDeck()
	-Description: prints the entire deck
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: printed
	*/
void Deck::printDeck(void)
{
	CardStackNode* temp = entireDeck;
	int count = 1;

	while (temp != NULL)
	{
		std::cout << count << ". " << temp->name << std::endl;
		std::cout << std::setw(3) << "Attack: " << temp->attack << std::endl;
		std::cout << std::setw(3) << "Defense: " << temp->defense << std::endl;
		std::cout << std::setw(3) << "Type: " << temp->type << std::endl << std::endl;
		temp = temp->next;
		++count;
	}
}
/*
	Function: lengthofDeck()
	-Description: returns length of deck. forgot i had this i could've used this instead of emptydeck but it's fine
	-Input parameters: n/a
	-Returns: int (length of deck)
	-Preconditions: n/a
	-Postconditions: n/a
	*/
int Deck::lengthofDeck(void)
{
	CardStackNode* temp = entireDeck;
	int count = 0;

	while (temp != NULL)
	{
		temp = temp->next;
		++count;
	}

	return count;
}
/*
	Function: emptyDeck()
	-Description: returns 0 if not empty 1 if empty
	-Input parameters: n/a
	-Returns: int
	-Preconditions: n/a
	-Postconditions: n/a
	*/
int Deck::emptyDeck(void)
{
	int empty = 0;

	if (entireDeck == nullptr)
	{
		empty = 1;
	}

	return empty;
}
/*
	Function: find()
	-Description: finds the card at the index in the deck
	-Input parameters: int index
	-Returns: CardStackNode*
	-Preconditions: n/a
	-Postconditions: found card
	*/
CardStackNode* Deck::find(int index)
{
	CardStackNode* temp = entireDeck;
	int count = 1;

	while (index != count)
	{
		temp = temp->next;
		++count;
	}

	return temp;
}