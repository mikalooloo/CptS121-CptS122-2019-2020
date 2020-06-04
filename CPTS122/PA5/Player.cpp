/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 5
Date: March 27, 2020
Description: Offbrand Yu Gi Oh! Game
Player.cpp for Player class
*/

#include "Header.h"
#include "Player.h"

#include <string>


Player::Player()
{
	life_points = 8000;
	hand = nullptr;
}

Player::~Player()
{
	std::cout << "Player object destroyed." << std::endl;
}

// Some Setters
void Player::setName(void)
{
	std::cin >> name;
}
void Player::setLifePoints(void)
{
	life_points = 8000;
}

// Some Getters
std::string Player::getName(void) const
{
	return name;
}
int Player::get_lp(void) const
{
	return life_points;
}

// Battle Card Operations

/*
	Function: deal_cards()
	-Description: Takes cards from the top of the deck and puts them into the hand until the hand has 5 cards total
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: there are 5 cards in the hand unless the deck is empty
	*/
void Player::deal_cards(void)
{
	int count = 0;

	CardStackNode* temp = hand;

	while (temp != nullptr) // count how many cards are in the hand
	{
		temp = temp->next;
		++count;
	}

	temp = hand;

	if (!deck.emptyDeck()) // if the deck isn't empty
	{
		while (count != 5) // and there's less than 5 cards
		{
			if (hand == nullptr) // if entirely empty start the hand
			{
				hand = deck.pop();
				++count;
				temp = hand;
			}
			else //  otherwise add it to the end
			{
				while (temp->next != nullptr)
				{
					temp = temp->next;
				}

				temp->next = deck.pop();
				++count;
			}
		}
	}
	else
	{
		std::cout << "Deck is empty. Error." << std::endl; // if this happens that's an uhoh
	}
}
/*
	Function: enqueue_attack()
	-Description: Removes the card specificed by the index from the hand and puts it into the attack queue
	-Input parameters: int card_index
	-Returns: n/a
	-Preconditions: there are cards in the hand
	-Postconditions: there is now one less card in the hand and one more card in the attack queue
	*/
void Player::enqueue_attack(int card_index)
{
	CardStackNode* attack_card = hand;
	CardStackNode* temp = hand;

	int count = 1;

	while (count != card_index) // while it's not at the right index
	{
		attack_card = attack_card->next;
		++count;
	}
	
	switch (card_index)
	{
	case 1:
		hand = hand->next;				// #2 card is now #1
		break;
	case 2:
		hand->next = attack_card->next; // #1 card is now connected to #3 card
		break;
	case 3:
		temp = temp->next;				// moving temp from #1 to #2
		temp->next = attack_card->next; // #2 card is now connected to #4 card
		break;
	case 4:
		temp = temp->next;				// moving temp from #1 to #2
		temp = temp->next;				// moving temp from #2 to #3
		temp->next = attack_card->next; // #3 card is now connected to #5 card
		break;
	case 5:
		temp = temp->next;				// moving temp from #1 to #2
		temp = temp->next;				// moving temp from #2 to #3
		temp = temp->next;				// moving temp from #3 to #4
		temp->next = nullptr;			// #4 card is now connected to nothing
		break;
	}

	attack.enqueue_card(attack_card);
}
/*
	Function: enqueue_defense()
	-Description: Removes the card specificed by the index from the hand and puts it into the defense queue
	-Input parameters: int card_index
	-Returns: n/a
	-Preconditions: there are cards in the hand
	-Postconditions: there is now one less card in the hand and one more card in the defense queue
	*/
void Player::enqueue_defense(int card_index)
{
	CardStackNode* defense_card = hand;
	CardStackNode* temp = hand;

	int count = 1;

	while (count != card_index)
	{
		defense_card = defense_card->next;
		++count;
	}

	switch (card_index)
	{
	case 1:
		hand = hand->next;				// #2 card is now #1
		break;
	case 2:
		hand->next = defense_card->next; // #1 card is now connected to #3 card
		break;
	case 3:
		temp = temp->next;				// moving temp from #1 to #2
		temp->next = defense_card->next; // #2 card is now connected to #4 card
		break;
	case 4:
		temp = temp->next;				// moving temp from #1 to #2
		temp = temp->next;				// moving temp from #2 to #3
		temp->next = defense_card->next; // #3 card is now connected to #5 card
		break;
	case 5:
		temp = temp->next;				// moving temp from #1 to #2
		temp = temp->next;				// moving temp from #2 to #3
		temp = temp->next;				// moving temp from #3 to #4
		temp->next = nullptr;			// #4 card is now connected to nothing
		break;
	}

	defense.enqueue_card(defense_card);
}
/*
	Function: print_hand()
	-Description: prints the hand
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: up to 5 cards were printed to the screen
	*/
void Player::print_hand(void)
{
	CardStackNode* temp = hand;
	int count = 1;

	while (temp != nullptr)
	{
		std::cout << "*" << count << "* " << temp->name << std::endl;
		std::cout << "Attack: " << temp->attack << std::endl;
		std::cout << "Defense: " << temp->defense << std::endl;
		std::cout << "Type: " << temp->type << std::endl << std::endl;
		temp = temp->next;
		++count;
	}
}
/*
	Function: print_firstCard_q()
	-Description: Prints just the name and (attack OR defense) points of the first card in the specified queue
	-Input parameters: bool attack_q (true if in attack queue, false if in defense queue), int num (0 for all of the cards to be printed in the queue, 1 for the first card in attack, 2 for the first card in defense)
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: n/a
	-Notes: this could've been better optimized but it works
	*/
void Player::print_firstCard_q(bool attack_q, int num)
{
	if (attack_q)
	{
		std::cout << name << " & the ";
		attack.print_cards(1);
		std::cout << std::endl;
	}
	else
	{
		std::cout << name << " & the ";
		defense.print_cards(2);
		std::cout << std::endl;
	}
}
/*
	Function: print_queues()
	-Description: prints both of the queues with appropiate labels
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: both queues have been printed
	*/
void Player::print_queues(void)
{
	std::cout << "Attack Queue: " << std::endl;
	attack.print_cards(0);
	std::cout << "Defense Queue: " << std::endl;
	defense.print_cards(0);
}
/*
	Function: print_attack_q()
	-Description: prints all of the cards in the attack queue
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: printed cards in attack queue
	*/
void Player::print_attack_q(void)
{
	std::cout << "Attack Queue: ";
	attack.print_cards(0);
}
/*
	Function: print_defense_q()
	-Description: print all cards in defense queue
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: printed all defense cards
	*/
void Player::print_defense_q(void)
{
	std::cout << "Defense Queue: ";
	defense.print_cards(0);
}
/*
	Function: subtract_lp()
	-Description: Subtracts the amount from the player's Life Points value
	-Input parameters: int amount
	-Returns: n/a
	-Preconditions: player has more than zero life points
	-Postconditions: player's life points -= amount
	*/
void Player::subtract_lp(int amount)
{
	life_points -= amount;
}

// Battle Operations

/*
	Function: turn()
	-Description: allows one player to do an entire round: picks two cards from hand to put into queues, picks which queue to activate
	-Input parameters: Player& player, int round
	-Returns: int (the queue they activated: 1 for attack, 2 for defense)
	-Preconditions: n/a
	-Postconditions: player has removed 2 cards from hand, chose attack or defense queue
	*/
int Player::turn(Player& player, int round)
{
	int card_selection = 0, card_selection2 = 0, temp_card = 0;

	system("cls");

	std::cout << "Round " << round << " - " << player.getName() << " - " << player.get_lp() << std::endl << std::endl;

	player.deal_cards();
	std::cout << "*Your hand*:" << std::endl;
	player.print_hand();

	std::cout << "You get to pick one card to put into Attack Mode and one card to put into Defense Mode." << std::endl;
	std::cout << "Enter the number besides the card you want to put into Attack Mode: ";
	std::cin >> card_selection;


	while (card_selection < 1 || card_selection > 5) // while the card selected is not 1 through 5 (the hand)
	{
		if (std::cin.fail()) // if a character is entered instead of a number
		{
			std::cout << "That was not a valid number. Please only enter a number between 1 and 5!" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> card_selection;
		}
		else
		{
			std::cout << "That was not a valid number. Please only enter a number between 1 and 5!" << std::endl;
			std::cin >> card_selection;
		}
	}

	player.enqueue_attack(card_selection); // puts into the attack queue

	std::cout << "Now enter the number besides the card you want to put into Defense Mode: ";
	std::cin >> card_selection2;
	temp_card = card_selection2;

	if (card_selection2 > card_selection) // when enqueue is used, it removes the card from the hand, but this isn't shown to the user, so this allows the user to still enter '5' as the index even though that card is now in position '4'
	{
		card_selection2 -= card_selection2 - card_selection;
	}

	while (card_selection2 < 1 || card_selection2 > 4 || card_selection == temp_card)
	{
		if (std::cin.fail()) // if a character is entered instead of a number
		{
			std::cout << std::endl << "That was not a valid number. Please only enter a number between 1 and 5 that you haven't already chosen!" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> card_selection2;
			temp_card = card_selection2;
		}
		else
		{
			std::cout << std::endl << "That was not a valid number. Please only enter a number between 1 and 5 that you haven't already chosen!" << std::endl;
			std::cin >> card_selection2;
			temp_card = card_selection2;
		}
	}

	player.enqueue_defense(card_selection2); // adds card to defense queue

	system("cls");

	player.print_queues();

	// I didn't allow the players to choose which card in the queue because FIFO structure
	std::cout << "Now, choose which Mode to activate. The first card in that Mode will be activated." << std::endl;
	std::cout << "Enter 1 for Attack, 2 for Defense: ";
	std::cin >> card_selection;

	while (card_selection < 1 || card_selection > 2)
	{
		if (std::cin.fail()) // if a character is entered instead of a number
		{
			std::cout << "That was not a valid number! Please enter 1 or 2 (one for attack, two for defense)." << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> card_selection;
		}
		else
		{
			std::cout << "That was not a valid number! Please enter 1 or 2 (one for attack, two for defense)." << std::endl;
			std::cin >> card_selection;
		}
	}

	return card_selection;
}
/*
	Function: battle()
	-Description: compares the cards of the two players and finds the winner
	-Input parameters: Player& player1, Player& player2, int p1mode (which queue activated), int p2mode (queue activated)
	-Returns: int winner (1 if player 1 won, 2 if player 2 won)
	-Preconditions: 2 turns have passed
	-Postconditions: 1 player has won
	*/
int Player::battle(Player& player1, Player& player2, int p1mode, int p2mode)
{
	system("cls");

	int winner = 0; // 1 if player 1, 2 if player 2
	int scenario = 0; // 1 if both attack, 2 if p1 is attack and p2 is defense, 3 if p1 is defense and p2 is attack, and 4 if both defend
	int advantage = 0; // 0 if none, 1 if player 1 has advantage, 2 if player 2 has advantage
	int difference = 0; // difference between the two card's values (how many points are taken away)
	std::string p1mode_n, p2mode_n;
	std::string p1type, p2type;
	std::string garbage;

	if (p1mode == 1 && p2mode == 1) // 1
	{
		scenario = 1;
		p1mode_n = "Attack";
		p2mode_n = "Attack";
	}
	else if (p1mode == 1 && p2mode == 2) // 2
	{
		scenario = 2;
		p1mode_n = "Attack";
		p2mode_n = "Defense";
	}
	else if (p1mode == 2 && p2mode == 1) // 3
	{
		scenario = 3;
		p1mode_n = "Defense";
		p2mode_n = "Attack";
	}
	else if (p1mode == 2 && p2mode == 2) // 4
	{
		scenario = 4;
		p1mode_n = "Defense";
		p2mode_n = "Defense";
	}

	std::cout << "***Battle Time***" << std::endl;
	std::cout << player1.getName() << " has chosen " << p1mode_n << " Mode." << std::endl;
	std::cout << player2.getName() << " has chosen " << p2mode_n << " Mode." << std::endl;

	switch (scenario)
	{
	case 1: // both attacking
		std::cout << std::endl << "Let's look at each player's cards!" << std::endl;
		std::cout << std::endl << player1.getName() << "'s Attacking Card: " << std::endl;
		player1.print_firstCard_q(true, 1);
		std::cout << std::endl << player2.getName() << "'s Attacking Card: " << std::endl;
		player2.print_firstCard_q(true, 1);

		std::cout << std::endl << "Enter any character when both players are ready to see the types" << std::endl << "and if that makes a difference in who wins this matchup!" << std::endl;
		std::cin >> garbage;
		system("cls");
		std::cout << player1.getName() << "'s Attacking Card: " << std::endl;
		p1type = player1.attack.getAndPrintType();
		std::cout << std::endl << "vs" << std::endl << std::endl;
		std::cout << player2.getName() << "'s Attacking Card: " << std::endl;
		p2type = player2.attack.getAndPrintType();
		std::cout << std::endl;

		advantage = player1.type_advantage(p1type, p2type); // determines advantage

		if (advantage == 0) // no advantage
		{
			std::cout << "Unfortunately, or fortunately depending on which player you are, the types do not affect anything!" << std::endl;
		}
		else if (advantage == 1) // player 1 has advantage
		{
			std::cout << "In this scenario, " << player1.getName() << "'s card " << player1.attack.getCardName() << " has advantage over " << player2.getName() << "'s card!" << std::endl;
			std::cout << player1.getName() << "'s card gets an added 500 attack points!" << std::endl;
			player1.attack.setAttack(500);
		}
		else // player 2 has advantage
		{
			std::cout << "In this scenario, " << player2.getName() << "'s card " << player2.attack.getCardName() << " has advantage over " << player1.getName() << "'s card!" << std::endl;
			std::cout << player2.getName() << "'s card gets an added 500 attack points!" << std::endl;
			player2.attack.setAttack(500);
		}

		std::cout << "Enter any character to continue. ";
		std::cin >> garbage;
		system("cls");

		player1.print_firstCard_q(true, 1);
		player2.print_firstCard_q(true, 1);

		if (player1.attack.getAttack() > player2.attack.getAttack()) // if player 1's attack is higher than player 2's
		{
			difference = player1.attack.getAttack() - player2.attack.getAttack();
			std::cout << std::endl << player1.getName() << "'s card has a higher attack value by " << difference << " points! " << std::endl << player1.getName() << " wins this round by beating " << player2.getName() << "'s card." << std::endl;
			winner = 1;
			player2.subtract_lp(difference);
			if (player2.get_lp() > 0)
			{
				std::cout << std::endl << player2.getName() << "'s Life Points are now at " << player2.get_lp() << "!" << std::endl << std::endl;
			}
		}
		else
		{
			difference = player2.attack.getAttack() - player1.attack.getAttack();
			std::cout << player2.getName() << "'s card has a higher attack value by " << difference << " points! " << std::endl << player2.getName() << " wins this round by beating " << player1.getName() << "'s card." << std::endl;
			winner = 2;
			player1.subtract_lp(difference);
			std::cout << player1.getName() << "'s Life Points are now at " << player1.get_lp() << "!" << std::endl;
		}

		std::cout << "Enter any character to continue. ";
		std::cin >> garbage;

		player1.attack.dequeue_card();
		player2.attack.dequeue_card();
		break;
	case 2: // p1 is attacking, p2 is defending
		std::cout << std::endl << "Let's look at each player's cards!" << std::endl;
		std::cout << std::endl << player1.getName() << "'s Attacking Card: " << std::endl;
		player1.print_firstCard_q(true, 1);
		std::cout << std::endl << player2.getName() << "'s Defending Card: " << std::endl;
		player2.print_firstCard_q(false, 1);

		std::cout << std::endl << "Enter any character when both players are ready to see the types" << std::endl << "and if that makes a difference in who wins this matchup!" << std::endl;
		std::cin >> garbage;
		system("cls");
		std::cout << player1.getName() << "'s Attacking Card: " << std::endl;
		p1type = player1.attack.getAndPrintType();
		std::cout << std::endl << "vs" << std::endl << std::endl;
		std::cout << player2.getName() << "'s Defending Card: " << std::endl;
		p2type = player2.defense.getAndPrintType();
		std::cout << std::endl;

		advantage = player1.type_advantage(p1type, p2type); // finding advantage

		if (advantage == 0) //none
		{
			std::cout << "Unfortunately, or fortunately depending on which player you are, the types do not affect anything!" << std::endl;
		}
		else if (advantage == 1) //player 1
		{
			std::cout << "In this scenario, " << player1.getName() << "'s card " << player1.attack.getCardName() << " has advantage over " << player2.getName() << "'s card!" << std::endl;
			std::cout << player1.getName() << "'s card gets an added 500 attack points!" << std::endl;
			player1.attack.setAttack(500);
		}
		else // player 2
		{
			std::cout << "In this scenario, " << player2.getName() << "'s card " << player2.defense.getCardName() << " has advantage over " << player1.getName() << "'s card!" << std::endl;
			std::cout << player2.getName() << "'s card gets an added 500 defense points!" << std::endl;
			player2.defense.setDefense(500);
		}

		std::cout << "Enter any character to continue. ";
		std::cin >> garbage;
		system("cls");

		player1.print_firstCard_q(true, 1);
		player2.print_firstCard_q(false, 1);

		if (player1.attack.getAttack() > player2.defense.getDefense()) // if player 1's attack is higher than player 2's defense
		{
			difference = player1.attack.getAttack() - player2.defense.getDefense();
			std::cout << std::endl << player2.getName() << "'s card can only defend so much, but is unable to protect for " << difference << " points! " << std::endl << player1.getName() << " wins this round by beating " << player2.getName() << "'s card in points." << std::endl;
			winner = 1;
			player2.subtract_lp(difference);
			if (player2.get_lp() > 0) // just to make sure negative life points don't occur
			{
				std::cout << std::endl << player2.getName() << "'s Life Points are now at " << player2.get_lp() << "!" << std::endl << std::endl;
			}
		}
		else // if player 2's defense was higher
		{
			std::cout << player2.getName() << "'s card was able to defend all " << player1.attack.getAttack() << " attacks!" << std::endl << player2.getName() << " wins this round by beating " << player1.getName() << "'s card in points." << std::endl;
			winner = 2;
		}

		std::cout << "Enter any character to continue. ";
		std::cin >> garbage;

		player1.attack.dequeue_card();
		player2.defense.dequeue_card();
		break;
	case 3: // p1 is defending, p2 is attacking
		std::cout << std::endl << "Let's look at each player's cards!" << std::endl;
		std::cout << std::endl << player1.getName() << "'s Defending Card: " << std::endl;
		player1.print_firstCard_q(false, 1);
		std::cout << std::endl << player2.getName() << "'s Attacking Card: " << std::endl;
		player2.print_firstCard_q(true, 1);

		std::cout << std::endl << "Enter any character when both players are ready to see the types" << std::endl << "and see if that makes a difference in who wins this matchup!" << std::endl;
		std::cin >> garbage;
		system("cls");
		std::cout << player1.getName() << "'s Defending Card: " << std::endl;
		p1type = player1.defense.getAndPrintType();
		std::cout << std::endl << "vs" << std::endl << std::endl;
		std::cout << player2.getName() << "'s Attacking Card: " << std::endl;
		p2type = player2.attack.getAndPrintType();
		std::cout << std::endl;

		advantage = player1.type_advantage(p1type, p2type);

		if (advantage == 0) // none
		{
			std::cout << "Unfortunately, or fortunately depending on which player you are, the types do not affect anything!" << std::endl;
		}
		else if (advantage == 1) // player 1
		{
			std::cout << "In this scenario, " << player1.getName() << "'s card " << player1.defense.getCardName() << " has advantage over " << player2.getName() << "'s card!" << std::endl;
			std::cout << player1.getName() << "'s card gets an added 500 defense points!" << std::endl;
			player1.defense.setDefense(500);
		}
		else // player 2
		{
			std::cout << "In this scenario, " << player2.getName() << "'s card " << player2.attack.getCardName() << " has advantage over " << player1.getName() << "'s card!" << std::endl;
			std::cout << player2.getName() << "'s card gets an added 500 attack points!" << std::endl;
			player2.attack.setAttack(500);
		}

		std::cout << "Enter any character to continue. ";
		std::cin >> garbage;
		system("cls");

		player1.print_firstCard_q(false, 1);
		player2.print_firstCard_q(true, 1);

		if (player1.defense.getDefense() < player2.attack.getAttack()) // player 1 def is less than player 2's attack
		{
			difference = player2.attack.getAttack() - player1.defense.getDefense();
			std::cout << player1.getName() << "'s card can only defend so much, but is unable to protect for " << difference << " points! " << std::endl << player2.getName() << " wins this round by beating " << player1.getName() << "'s card in points." << std::endl;
			winner = 1;
			player1.subtract_lp(difference);
			if (player1.get_lp() > 0)
			{
				std::cout << std::endl << player1.getName() << "'s Life Points are now at " << player1.get_lp() << "!" << std::endl << std::endl;
			}
		}
		else // player 1's def is higher than player 2's attack
		{
			std::cout << player1.getName() << "'s card was able to defend all " << player2.attack.getAttack() << " attacks!" << std::endl << player1.getName() << " wins this round by beating " << player2.getName() << "'s card in points." << std::endl;
			winner = 2;
		}

		std::cout << "Enter any character to continue. ";
		std::cin >> garbage;

		player1.defense.dequeue_card();
		player2.attack.dequeue_card();
		break;
	case 4: // both defending
		std::cout << std::endl << "Let's look at each player's cards!" << std::endl;
		std::cout << std::endl << player1.getName() << "'s Defending Card: " << std::endl;
		player1.print_firstCard_q(false, 1);
		std::cout << std::endl << player2.getName() << "'s Defending Card: " << std::endl;
		player2.print_firstCard_q(false, 1);

		std::cout << std::endl << "What a shame! No life points will be deducted this round." << std::endl << "Enter a character to move on. ";
		std::cin >> garbage;

		player1.defense.dequeue_card();
		player2.defense.dequeue_card();
		break;
	}

	return winner;
}
/*
	Function: type_advantage()
	-Description: finds out whether p1type or p2type has an advantage over the other
	-Input parameters: string p1type, string p2type
	-Returns: int 0 if no advantage, 1 if p1type has an advantage, 2 if p2type has an advantage
	-Preconditions: n/a
	-Postconditions: n/a
	*/
int Player::type_advantage(std::string p1type, std::string p2type) // Earth, Air, Fire, Water
{
	// Fire > Earth, Earth > Air, Air > Water, Water > Fire 
	int type_advantage = 0; // 0 means none (they are the same), 1 if player 1 has an advantage, 2 if player 2 has an advantage

	if (p1type == p2type)
	{
		type_advantage = 0; // no advantage
	}
	else if (p1type == "Earth")
	{
		if (p2type == "Fire")
		{
			type_advantage = 2;
		}
		else if (p2type == "Air")
		{
			type_advantage = 1;
		}
		else // Earth vs Water is no advantage
		{
			type_advantage = 0;
		}
	}
	else if (p1type == "Air")
	{
		if (p2type == "Earth")
		{
			type_advantage = 2;
		}
		else if (p2type == "Water")
		{
			type_advantage = 1;
		}
		else // Air vs Fire is no advantage
		{
			type_advantage = 0;
		}
	}
	else if (p1type == "Fire")
	{
		if (p2type == "Water")
		{
			type_advantage = 2;
		}
		else if (p2type == "Earth")
		{
			type_advantage = 1;
		}
		else // Fire vs Air is no advantage
		{
			type_advantage = 0;
		}
	}
	else if (p1type == "Water")
	{
		if (p2type == "Air")
		{
			type_advantage = 2;
		}
		else if (p2type == "Fire")
		{
			type_advantage = 1;
		}
		else // Water vs Earth is no advantage
		{
			type_advantage = 0;
		}
	}

	return type_advantage;
}
/*
	Function: win_check()
	-Description: checks to see if a player has zero life points
	-Input parameters: Player& loser
	-Returns: bool (true if a player has won because the player has zero life points, or false if the player has more than zero)
	-Preconditions: a player has lost points (so must check to see if it went below zero)
	-Postconditions: n/a
	*/
bool Player::win_check(Player& loser)
{
	bool winner = false;

	if (loser.life_points <= 0)
	{
		winner = true;
	}

	return winner;
}

// Card Operations

/*
	Function: trade_cards()
	-Description: finds the card the player wants to trade and returns the value
	-Input parameters: n/a
	-Returns: CardStackNode * (card to be traded)
	-Preconditions: n/a
	-Postconditions: player chose a card to trade
	*/
CardStackNode* Player::trade_cards(void)
{
	CardStackNode* change = new CardStackNode;
	int trade_card = 0;

	std::cout << "Trading Cards - " << name << std::endl;
	deck.printDeck();
	std::cout << "Enter the number of the card you want to trade: " << std::endl;
	std::cin >> trade_card;

	if (trade_card > deck.lengthofDeck()) // the card is longer than the deck
	{
		std::cout << "Please enter a valid number!" << std::endl;
		std::cin >> trade_card;
	}

	change = deck.find(trade_card);

	return change;
}
/*
	Function: swap()
	-Description: swaps the values of 2 cards to "trade"
	-Input parameters: CardStackNode* card1, CardStackNode* card2 - copies card2 to card1
	-Returns: returns the values of card1
	-Preconditions: n/a
	-Postconditions: card1 now has the values of card2
	*/
CardStackNode * Player::swap(CardStackNode * card1, CardStackNode * card2)
{
	CardStackNode* temp = new CardStackNode;

	temp->name = card1->name;
	temp->attack = card1->attack;
	temp->defense = card1->defense;
	temp->type = card1->type;
	card1->name = card2->name;
	card1->attack = card2->attack;
	card1->defense = card2->defense;
	card1->type = card2->type;

	return temp;
}
/*
	Function: new_card()
	-Description: replaces a current card with new values entered by user
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: new card
	*/
void Player::new_card(void) // asks for the new card info
{
	CardStackNode* change = new CardStackNode;
	int trade_card = 0, type = 0;
	std::string garbage;

	std::cout << "Adding a New Card - " << name << std::endl;
	deck.printDeck();
	std::cout << "Enter the number of the card you want to replace: " << std::endl;
	std::cin >> trade_card;

	if (trade_card > deck.lengthofDeck())
	{
		if (std::cin.fail()) // if a character is entered instead of a number
		{
			std::cout << "Please enter a valid number!" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> trade_card;
		}
		else
		{
			std::cout << "Please enter a valid number!" << std::endl;
			std::cin >> trade_card;
		}
	}

	change = deck.find(trade_card);

	system("cls");
	std::cout << "Adding a New Card - " << name << std::endl;
	std::cout << "What name do you want for your new card? ";
	std::cin.ignore(1000, '\n');
	std::getline(std::cin, garbage);
	change->name = garbage;
	std::cout << std::endl << "How many Attack Points do you want? ";
	std::cin >> change->attack;

	while (change->attack < 0 || std::cin.fail())
	{
		if (std::cin.fail()) // if a character is entered instead of a number
		{
			std::cout << std::endl << "The Attack Points cannot be less than zero. Please enter a new number: ";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> change->attack;
		}
		else
		{
			std::cout << std::endl << "The Attack Points cannot be less than zero. Please enter a new number: ";
			std::cin >> change->attack;
		}
	}

	std::cout << std::endl << "How many Defense Points do you want? ";
	std::cin >> change->defense;

	while (change->defense < 0)
	{
		if (std::cin.fail()) // if a character is entered instead of a number
		{
			std::cout << std::endl << "The Defense Points cannot be less than zero. Please enter a new number: ";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> change->defense;
		}
		else
		{
			std::cout << std::endl << "The Defense Points cannot be less than zero. Please enter a new number: ";
			std::cin >> change->defense;
		}
	}
	std::cout << std::endl << "What type do you want for your new card?" << std::endl;
	std::cout << "1. Earth" << std::endl << "2. Air" << std::endl << "3. Fire" << std::endl << "4. Water" << std::endl;
	
	while (type < 1 || type > 4)
	{
		std::cin >> type;

		switch (type)
		{
		case 1:
			change->type = "Earth";
			break;
		case 2:
			change->type = "Air";
			break;
		case 3:
			change->type = "Fire";
			break;
		case 4:
			change->type = "Water";
			break;
		default:
			if (std::cin.fail()) // if a character is entered instead of a number
			{
				std::cout << "Invalid input. Please enter a number between 1 and 4!" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			else
			{
				std::cout << "Invalid input. Please enter a number between 1 and 4!" << std::endl;
			}
			break;
		}
	}

	system("cls");
	std::cout << "Adding a New Card - " << name << std::endl;
	std::cout << "Your new card:" << std::endl << std::endl;
	std::cout << change->name << std::endl << "Attack: " << change->attack << std::endl << "Defense: " << change->defense << std::endl << "Type: " << change->type << std::endl << std::endl;

	std::cout << "Enter any character to continue.";
	std::cin >> garbage;
}
/*
	Function: deckEmpty()
	-Description: checks if the deck is empty
	-Input parameters: n/a
	-Returns: bool (true if empty, false if not empty)
	-Preconditions: n/a
	-Postconditions: n/a
	*/
bool Player::deckEmpty(void)
{
	bool empty = false;
	if (deck.emptyDeck() == 1)
	{
		empty = true;
	}

	return empty;
}

