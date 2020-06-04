/* Name: Mikaela Dean
Course: CPTS121, WSU
Date: November 2019

PA 7: Poker
*/

#ifndef POKER_H
#define POKER_H

#define _CRT_SECURE_NO_WARNINGS
#define PLAYER 1
#define COMPUTER 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct card
{
	int face;
	int suit;
} Card;

typedef struct hand
{
	Card hand[8]; // 5 cards + 3 extra (if they redraw)
} Hand;

// *** Premade Functions ***

void shuffle(int wDeck[][13]);

void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand* user, int player);

// *** Main Menu ***

/*
Function: main_menu()
-Description: prints the main menu
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void main_menu(void);

/*
Function: int_answer()
-Description: scans for an int
-Input parameters: n/a
-Returns: int (1 through 3)
-Preconditions: n/a
-Postconditions: an int has been entered
*/
int int_answer(void);

/*
Function: print_rules()
-Description: prints the rules
-Input parameters: n/a
-Returns: n/a
-Preconditions: user has entered in 1 during the main_menu()
-Postconditions: user enters a character to move past the end of the function
*/
void print_rules(void);

// *** Gameplay ***

/*
Function: play_game()
-Description: runs through the entire game
-Input parameters: the face and suit arrays
-Returns: n/a
-Preconditions: user has entered in 2 during the main_menu()
-Postconditions: game has finished
*/
void play_game(const char* wFace[], const char* wSuit[]);

/*
Function: num_faces()
-Description: counts the number of the faces
-Input parameters: the deck of the player or computer, and their array
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void num_faces(Hand user, int array[]);

/*
Function: player_redrawing()
-Description: allows the player to redraw cards
-Input parameters: the pointer to the deck so it can be changed with the new cards, as well as the face and suit character arrays
-Returns: n/a
-Preconditions: n/a
-Postconditions: player has chosen whether or not they want to redraw cards and has done so
*/
void player_redrawing(Hand* user, const char* wFace[], const char* wSuit[]);

/*
Function: com_redrawing()
-Description: finds how what cards should be redrawn and redraws them
-Input parameters: Hand* user, int hand_num, int array[], int cards_to_redraw
-Returns: n/a
-Preconditions: n/a
-Postconditions: computer has redrawn the cards it needs to
*/
void com_redrawing(Hand* user, int hand_num, int array[], int cards_to_redraw);

/*
Function: redraw_one_card()
-Description: redraws one card
-Input parameters: Hand* user, int card, int redrawn_num
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void redraw_one_card(Hand* user, int card, int redrawn_num);

/*
Function: which_card_in_hand()
-Description: finds out what hand the card is in (kicker is from the array)
-Input parameters: int kicker, Hand* user
-Returns: int index (the card in which the kicker is in)
-Preconditions: n/a
-Postconditions: n/a
*/
int which_card_in_hand(int kicker, Hand* user);

// *** Checking Hands ***

/*
Function: check_check()
-Description: finds out which hand the user possesses, with 0 being high card and 6 being four-of-a-kind
-Input parameters: Hand user, int array[]
-Returns: 0 through 6 - what hand they possess, with 0 being high card and 6 being four-of-a-kind
-Preconditions: n/a
-Postconditions: n/a
*/
int check_check(Hand user, int array[]);

/*
Function: check_pair()
-Description: does the array show that there is one or two pairs?
-Input parameters: int array[], int of_a_kind
-Returns: 0 if there are no pairs, 1 if there is one pair, 2 if there are two pairs
-Preconditions: n/a
-Postconditions: n/a
*/
int check_pair(int array[], int of_a_kind);

/*
Function: check_of_a_kind()
-Description: does the array have a three or four of a kind?
-Input parameters: int array[]
-Returns: 3 if there is a three of a kind, 6 if there is a four of a kind, 0 if neither
-Preconditions: n/a
-Postconditions: n/a
*/
int check_of_a_kind(int array[]);

/*
Function: check_flush()
-Description: does the hand have a flush?
-Input parameters: Hand user
-Returns: 5 if there is a flush, 0 if there is no flush
-Preconditions: n/a
-Postconditions: n/a
*/
int check_flush(Hand user);

/*
Function: check_straight()
-Description: does the array have a straight?
-Input parameters: int array[]
-Returns: 0 if there is no straight, 4 if there is
-Preconditions: n/a
-Postconditions: n/a
*/
int check_straight(int array[]);

/*
Function: check_straight_array()
-Description: helps the check_straight() determine if there is a straight
-Input parameters: int array[]
-Returns: 0 if there is no straight, 4 if there is
-Preconditions: n/a
-Postconditions: n/a
*/
int check_straight_array(int array[]);

/*
Function: find_kicker()
-Description: finds the smallest index in the array with the value of 1
-Input parameters: int array[]
-Returns: index of the smallest number
-Preconditions: n/a
-Postconditions: n/a
*/
int find_kicker(int array[]);

// *** Dealer ***

/*
Function: evaluate_hand()
-Description: evalutes the hand of the computer and returns how many cards should be redrawn
-Input parameters: int hand_num, int array[]
-Returns: int (how many cards should be redrawn)
-Preconditions: n/a
-Postconditions: n/a
*/
int evaluate_hand(int hand_num, int array[]);

// *** Misc ***

/*
Function: clear_array()
-Description: makes the array filled with zeroes
-Input parameters: int array[]
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void clear_array(int array[]);

// *** Winning ***

/*
Function: compare_hands()
-Description: finds who the winner is
-Input parameters: int c_hand_num, int p_hand_num
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void compare_hands(int c_hand_num, int p_hand_num);

#endif POKER_H