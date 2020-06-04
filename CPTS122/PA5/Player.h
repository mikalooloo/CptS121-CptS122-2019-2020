/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 5
Date: March 27, 2020
Description: Offbrand Yu Gi Oh! Game
Player Class
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Header.h"
#include "Stats.h"
#include "Queue.h"
#include "Stack.h"

class Player //: public Stats
{
private:
	std::string name;
	int life_points;
	Queue attack;
	Queue defense;
	Deck deck;
	CardStackNode* hand;
	//Stats stats;
public:
	// Constructor
	Player();
	// Destructor
	~Player();
	// Some Setters
	void setName(void);
	void setLifePoints(void);

	// Some Getters
	std::string getName(void) const;
	int get_lp(void) const;

	// Battle Card Operations
	/*
	Function: deal_cards()
	-Description: Takes cards from the top of the deck and puts them into the hand until the hand has 5 cards total
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: there are 5 cards in the hand unless the deck is empty
	*/
	void deal_cards(void);
	/*
	Function: enqueue_attack()
	-Description: Removes the card specificed by the index from the hand and puts it into the attack queue
	-Input parameters: int card_index
	-Returns: n/a
	-Preconditions: there are cards in the hand
	-Postconditions: there is now one less card in the hand and one more card in the attack queue
	*/
	void enqueue_attack(int card_index);
	/*
	Function: enqueue_defense()
	-Description: Removes the card specificed by the index from the hand and puts it into the defense queue
	-Input parameters: int card_index
	-Returns: n/a
	-Preconditions: there are cards in the hand
	-Postconditions: there is now one less card in the hand and one more card in the defense queue
	*/
	void enqueue_defense(int card_index);
	/*
	Function: print_hand()
	-Description: prints the hand 
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: up to 5 cards were printed to the screen
	*/
	void print_hand(void);
	/*
	Function: print_firstCard_q()
	-Description: Prints just the name and (attack OR defense) points of the first card in the specified queue
	-Input parameters: bool attack_q (true if in attack queue, false if in defense queue), int num (0 for all of the cards to be printed in the queue, 1 for the first card in attack, 2 for the first card in defense)
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: n/a
	-Notes: this could've been better optimized but it works
	*/
	void print_firstCard_q(bool attack_q, int num);
	/*
	Function: print_queues()
	-Description: prints both of the queues with appropiate labels
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: both queues have been printed
	*/
	void print_queues(void);
	/*
	Function: print_attack_q()
	-Description: prints all of the cards in the attack queue
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: printed cards in attack queue
	*/
	void print_attack_q(void);
	/*
	Function: print_defense_q()
	-Description: print all cards in defense queue
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: printed all defense cards 
	*/
	void print_defense_q(void);
	/*
	Function: subtract_lp()
	-Description: Subtracts the amount from the player's Life Points value
	-Input parameters: int amount 
	-Returns: n/a
	-Preconditions: player has more than zero life points
	-Postconditions: player's life points -= amount
	*/
	void subtract_lp(int amount); 

	// Battle Operations
	/*
	Function: turn()
	-Description: allows one player to do an entire round: picks two cards from hand to put into queues, picks which queue to activate
	-Input parameters: Player& player, int round
	-Returns: int (the queue they activated: 1 for attack, 2 for defense)
	-Preconditions: n/a
	-Postconditions: player has removed 2 cards from hand, chose attack or defense queue
	*/
	int turn(Player& player, int round);
	/*
	Function: battle()
	-Description: compares the cards of the two players and finds the winner
	-Input parameters: Player& player1, Player& player2, int p1mode (which queue activated), int p2mode (queue activated)
	-Returns: int winner (1 if player 1 won, 2 if player 2 won)
	-Preconditions: 2 turns have passed
	-Postconditions: 1 player has won
	*/
	int battle(Player& player1, Player& player2, int p1mode, int p2mode);
	/*
	Function: type_advantage()
	-Description: finds out whether p1type or p2type has an advantage over the other 
	-Input parameters: string p1type, string p2type
	-Returns: int 0 if no advantage, 1 if p1type has an advantage, 2 if p2type has an advantage
	-Preconditions: n/a
	-Postconditions: n/a
	*/
	int type_advantage(std::string p1type, std::string p2type);
	/*
	Function: win_check()
	-Description: checks to see if a player has zero life points
	-Input parameters: Player& loser
	-Returns: bool (true if a player has won because the player has zero life points, or false if the player has more than zero)
	-Preconditions: a player has lost points (so must check to see if it went below zero)
	-Postconditions: n/a
	*/
	bool win_check(Player& loser);

	// Card Operations
	/*
	Function: trade_cards()
	-Description: finds the card the player wants to trade and returns the value
	-Input parameters: n/a
	-Returns: CardStackNode * (card to be traded)
	-Preconditions: n/a
	-Postconditions: player chose a card to trade
	*/
	CardStackNode * trade_cards(void);
	/*
	Function: swap()
	-Description: swaps the values of 2 cards to "trade"
	-Input parameters: CardStackNode* card1, CardStackNode* card2 - copies card2 to card1
	-Returns: returns the values of card1
	-Preconditions: n/a 
	-Postconditions: card1 now has the values of card2
	*/
	CardStackNode* swap(CardStackNode* card1, CardStackNode* card2);
	/*
	Function: new_card()
	-Description: replaces a current card with new values entered by user
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: new card
	*/
	void new_card(void); 
	/*
	Function: deckEmpty()
	-Description: checks if the deck is empty
	-Input parameters: n/a
	-Returns: bool (true if empty, false if not empty)
	-Preconditions: n/a
	-Postconditions: n/a
	*/
	bool deckEmpty(void);

};

#endif PLAYER_H

