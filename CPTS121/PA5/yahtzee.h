#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define GAMERULES 1
#define PLAY 2
#define EXIT 3

// Main Menu Functions 

/*
Function: menu_select()
Date Created: 10/9/2019
Date Last Modified: 10/9/2019
-Description: uses print_menu() and get_option() to display the main menu as well as get the user's option
-Input parameters: n/a
-Returns: the option the user chose for the main menu
-Preconditions: player has not chosen exit
-Postconditions: player has chosen an acceptable option
*/
int menu_select(void);

/*
Function: print_menu()
Date Created: 10/9/2019
Date Last Modified: 10/9/2019
-Description: prints the menu
-Input parameters: n/a
-Returns: n/a
-Preconditions: menu_select is running
-Postconditions: menu has been printed
*/
void print_menu(void);

/*
Function: get_option()
Date Created: 10/9/2019
Date Last Modified: 10/9/2019
-Description: scans for the user's input
-Input parameters: n/a
-Returns: int (the option the user chose for the main menu)
-Preconditions: menu_select() is running
-Postconditions: the user entered an interger between 1 and 3
*/
int get_option(void);

// Gameplay Functions

/*
Function: game_play()
Date Created: 10/9/2019
Date Last Modified: 10/21/2019
-Description: declares the combo arrays, has a loop for the rounds, uses functions to find the winner, and returns the winner to main
-Input parameters: n/a
-Returns: int (1 or 2 - the winner of the game)
-Preconditions: user has chosen 2 in menu_select()
-Postconditions: a winner has been found (player 1 or 2)
*/
int game_play(void);

/*
Function: player_turn()
Date Created: 10/9/2019
Date Last Modified: 10/21/2019
-Description: declares the dice and freq functions, lets user roll dice and uses loops and functions to reroll them, allows player to choose a combination and gives the points to the player for chosen combo
-Input parameters: int player (for printfs), int combo[] (to remember what combos player has already chosen), int round (for printfs mostly)
-Returns: n/a
-Preconditions: round is not 14
-Postconditions: player has gained points for a combo
*/
void player_turn(int player, int combo[], int round); // declare int dice[], freq[] here

/*
Function: print_combos()
Date Created: 10/21/2019
Date Last Modified: 10/21/2019
-Description: prints the combinations and points gained 
-Input parameters: int player (for printf) and int combo[] (to fill the points column)
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void print_combos(int player, int combo[]);

/*
Function: verify_points()
Date Created: 10/9/2019
Date Last Modified: 10/21/2019
-Description: uses a switch/case for what combo the player wants and sees if the player actually has the requirements needed for the combo, and if so, returns the points earned
-Input parameters: int combo_num (1 through 13), and int freq[] (frequency of each die value)
-Returns: int (the number of points the player earned for the combo they chose)
-Preconditions: the player has chosen a combo and needs it verified
-Postconditions: n/a
*/
int verify_points(int combo_num, int freq[]);

// Dice Functions

/*
Function: roll_dice()
Date Created: 10/9/2019
Date Last Modified: 10/9/2019
-Description: generates a number from 1 through 6
-Input parameters: n/a
-Returns: int (1 through 6)
-Preconditions: n/a
-Postconditions: n/a
*/
int roll_dice(void);

/*
Function: display_dice()
Date Created: 10/9/2019
Date Last Modified: 10/11/2019
-Description: prints the dice and uses pretty_dice()
-Input parameters: int dice[] (to print it)
-Returns: n/a
-Preconditions: player is ready to roll dice
-Postconditions: n/a
*/
void display_dice(int dice[]); 

/*
Function: display_rerolledDice()
Date Created: 10/20/2019
Date Last Modified: 10/20/2019
-Description: just like display_dice(), but only 'rolls' dice that need to be rerolled
-Input parameters: int dice[], int rerolled_dice[]
-Returns: n/a
-Preconditions: player wants to reroll dice
-Postconditions: n/a
*/
void display_rerolledDice(int dice[], int rerolled_dice[]);

/*
Function: roll_diceForArray
Date Created: 10/20/2019
Date Last Modified: 10/20/2019
-Description: rolls the dice and puts it into the dice[] array
-Input parameters: int dice[]
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void roll_diceForArray(int dice[]);

/*
Function: pretty_dice()
Date Created: 10/9/2019
Date Last Modified: 10/9/2019
-Description: makes the dice look pretty for the user
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void pretty_dice(void);

/*
Function: freq_array()
Date Created: 10/9/2019
Date Last Modified: 10/11/2019
-Description: finds the frequency of each die value
-Input parameters: int dice[], int freq[]
-Returns: n/a
-Preconditions: dice have been rolled and are done rerolling
-Postconditions: n/a
*/
void freq_array(int dice[], int freq[]);

/*
Function: reroll_diceNum()
Date Created: 10/20/2019
Date Last Modified: 10/21/2019
-Description: uses reroll_dice() to reroll the specific dice the user wants
-Input parameters: int dice[], int reroll_num
-Returns: n/a
-Preconditions: the user wants to reroll some dice
-Postconditions: n/a
*/
void reroll_diceNum(int dice[], int reroll_num);

/*
Function: reroll_dice()
Date Created: 10/9/2019
Date Last Modified: 10/20/2019
-Description: rerolls the dice the user wants
-Input parameters: int dice[], int reroll_diceArray[]
-Returns: n/a
-Preconditions: the user wants to reroll dice
-Postconditions: n/a
*/
void reroll_dice(int dice[], int reroll_diceArray[]);

// End of Game Functions

/*
Function: calculate_scores()
Date Created: 10/9/2019
Date Last Modified: 10/21/2019
-Description: adds up all of the points from the combo array, including adding an additional 35 points if the first 6's total is above 63
-Input parameters: int combo[]
-Returns: int (the total points for the combo array inputted)
-Preconditions: 14 rounds have been played (ie all of the combos have been accounted for)
-Postconditions: n/a
*/
int calculate_scores(int combo[]);

/*
Function: find_winner()
Date Created: 10/9/2019
Date Last Modified: 10/21/2019
-Description: finds which total is bigger and returns the winner (the bigger number)
-Input parameters: int total1 (player 1's total determined by calculate_scores), int total2 (same)
-Returns: int (1 or 2 - whichever had the bigger total)
-Preconditions: calculate_scores is done
-Postconditions: n/a
*/
int find_winner(int total1, int total2);

/*
Function: print_scores()
Date Created: 10/9/2019
Date Last Modified: 10/21/2019
-Description: prints the winner and the scores
-Input parameters: int total1, int total2, int winner (all for printing)
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void print_scores(int total1, int total2, int winner);