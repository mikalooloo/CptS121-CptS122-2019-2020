/*
Name: Mikaela Dean
Date: 10/2019
Course: CPTS121 Section 1, Lab Section 16 - WSU Fall Semester 2019

Description: Assignment PA 4 - Blackjack - Due 10/09/2019 at midnight.
- Function declarations
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define GAME_RULES 1
#define BALANCE 2
#define PLAY 3
#define EXIT 4

// Menu Screen Functions
/*
Function: display_menu()
Date Created: 10/01/2019
Date Last Modified: 10/05/2019
-Description: Prints the game menu
-Input parameters: int times_played (if the game has already played once, it takes away the change initial balance value option)
-Returns: n/a
-Preconditions: program has started
-Postconditions: n/a
*/
void display_menu(int times_played);

/*
Function: get_option()
Date Created: 10/01/2019
Date Last Modified: 10/01/2019
-Description: Scans the user's input of an integer
-Input parameters: n/a
-Returns: int 1 through 4
-Preconditions: menu_select is running
-Postconditions: user inputs a number
*/
int get_option(void);

/*
Function: menu_select()
Date Created: 10/01/2019
Date Last Modified: 10/01/2019
-Description: Uses display_menu() and get_option(). Only allows an appropiate integer. If the game has been played before, 
-Input parameters: int times_played (if the game has already played once, does not allow user to select the option to change starting balance)
-Returns: int 1 through 4 
-Preconditions: program is running
-Postconditions: a number 1 through 4 (excluding 2 if times_played is more than zero) is entered in get_option();
*/
int menu_select(int times_played);

/*
Function: determine_option()
Date Created: 10/01/2019
Date Last Modified: 10/04/2019
-Description: Displays game rules/sets beginning balance
-Input parameters: int option, double*balance - the option is to know which case to run and the balance pointer is to establish the beginning balance
-Returns: n/a 
-Preconditions: menu_select() has finished running
-Postconditions: n/a
*/
void determine_option(int option, double* balance);

/*
Function: display_rules()
Date Created: 10/01/2019
Date Last Modified: 10/04/2019
-Description: Prints the rules and then waits 3 seconds
-Input parameters: n/a
-Returns: n/a
-Preconditions: option 1 was chosen in menu_select() and determine_option() is running
-Postconditions: n/a
*/
void display_rules(void);

/*
Function: get_bank_balance()
Date Created: 10/01/2019
Date Last Modified: 10/05/2019
-Description: Allows user to input an initial bank balance for the game as long as it is not zero or below zero
-Input parameters: n/a
-Returns: double (bank balance)
-Preconditions: option 2 is chosen in menu_select() and determine_option() is running
-Postconditions: user enters a number that is above zero
*/
double get_bank_balance(void);

// Game Play Functions

/*
Function: player_numbers()
Date Created: 10/01/2019
Date Last Modified: 10/05/2019
-Description: Allows user to enter number of players (2 through 5).
-Input parameters: n/a
-Returns: int 2 through 5
-Preconditions: option 3 was chosen in menu_select()
-Postconditions: user entered an integer 2 through 5
*/
int player_numbers(void);

/*
Function: determine_play()
Date Created: 10/04/2019
Date Last Modified: 10/05/2019
-Description: Uses player_turn and the winning functions to execute a round of Blackjack dice (each player bets, rolls, and wins/loses)
-Input parameters: int num_play, pointers for balance 1 through 5
-Returns: n/a
-Preconditions: number of players from player_numbers()
-Postconditions: n/a
*/
void determine_play(int num_play, double* balance1, double* balance2, double* balance3, double* balance4, double* balance5);

/*
Function: player_turn()
Date Created: 10/02/2019
Date Last Modified: 10/05/2019
-Description: Takes bet and does the rolling sequence, returns sum of dice
-Input parameters: int player (which number), pointer for balance, current sum, and pointer for bet
-Returns: sum of dice
-Preconditions: determine_play() is running
-Postconditions: n/a
*/
int player_turn(int player, double* balance, int current_sum, double* bet);

// Die Functions

/*
Function: roll_die()
Date Created: 10/01/2019
Date Last Modified: 10/01/2019
-Description: generates a random number 1 through 6
-Input parameters: n/a
-Returns: int (1 through 6)
-Preconditions: n/a
-Postconditions: n/a
*/
int roll_die(void);

/*
Function: calculate_sum_dice()
Date Created: 10/01/2019
Date Last Modified: 10/01/2019
-Description: adds the result from roll_die() to the total sum of all previous die rolls
-Input parameters: int current_sum, int die_value
-Returns: int (new current_sum)
-Preconditions: roll_die() has finished
-Postconditions: n/a
*/
int calculate_sum_dice(int current_sum, int die_value);

/*
Function: rolling()
Date Created: 10/03/2019
Date Last Modified: 10/03/2019
-Description: makes the dice roll look cool
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void rolling(void);

/*
Function: rolling_sequence()
Date Created: 10/03/2019
Date Last Modified: 10/03/2019
-Description: lets a player roll until they decide to stop
-Input parameters: int player, int current_sum, char answer
-Returns: int (the sum)
-Preconditions: n/a
-Postconditions: n/a
*/
int rolling_sequence(int player, int current_sum, char answer);

// Winning Functions

/*
Function: finding_winner()
Date Created: 10/05/2019
Date Last Modified: 10/05/2019
-Description: finds the highest player and sum (the winner)
-Input parameters: two sums, two players, pointer for the winning sum and the count (the count is used if two sums are equal)
-Returns: int (the # player)
-Preconditions: two sums have been calculated
-Postconditions: n/a
*/
int finding_winner(int sum1, int sum2, int player1, int player2, int* win, int* count);

/*
Function: pay_out()
Date Created: 10/05/2019
Date Last Modified: 10/08/2019
-Description: prints and pays out the money won or lost by each players
-Input parameters: int winning_sum, int sum1, int player1, double bet1, double*balance1
-Returns: n/a
-Preconditions: winning_sum has been figured out
-Postconditions: n/a
*/
void pay_out(int winning_sum, int sum1, int player1, double bet1, double* balance1);

/*
Function: pay_outTie()
Date Created: 10/05/2019
Date Last Modified: 10/08/2019
-Description: does the same as pay_out(), but when there is more than one player who has the same winning sum
-Input parameters: int winning_sum, int sum1, int player1, double bet1, double* balance1
-Returns: n/a
-Preconditions: winning_sum has been figured out and count is more than zero
-Postconditions: n/a
*/
void pay_outTie(int winning_sum, int sum1, int player1, double bet1, double* balance1);

// Chatter Functions

/*
Function: bet_chatter()
Date Created: 10/9/2019
Date Last Modified: 10/9/2019
-Description: makes fun of you for betting
-Input parameters: double *bet, double * balance (to tell what percentage of your bank balance you are betting)
-Returns: n/a
-Preconditions: player has inputted a bet
-Postconditions: n/a
*/
void bet_chatter(double * bet, double* balance);


/*
Function: 
Date Created: 
Date Last Modified: 
-Description: 
-Input parameters: 
-Returns:
-Preconditions: 
-Postconditions: 
*/