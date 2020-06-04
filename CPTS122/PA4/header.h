/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 4
Date: March 6, 2020
Description: Hunt the Wumpus - walk through caves to find the gold while avoiding pits and the Wumpus! Earn points for each move and try to get the high score.
General Header
*/

#ifndef HEADER_H
#define HEADER_H

#include "GameWorld.h"
#include "PlayerStats.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <time.h> // for rand()

using namespace std;

typedef struct highscore
{
	string initials;
	int wins;
	double avg_points;
	struct highscore* next;
} HighScore;

// **************General Functions************** 

/*
Function: print_controls()
-Description: Prints to the console a table of the keybinds
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: has been printed
*/
void print_controls(void);

/*
Function: game_menu()
-Description: Prints the controls (using print_controls()) and if display_blank is true, prints out the blankWorld
-Input parameters: GameWorld game, bool display_blank (if true, prints out blankWorld)
-Returns: n/a
-Preconditions: n/a
-Postconditions: printed out controls
*/
void game_menu(GameWorld game, bool display_blank);

/*
Function: print_rules_info
-Description: Prints the rules and information for Hunt the Wumpus
-Input parameters: n/a
-Returns: n/a
-Preconditions: 1 was pressed in the main menu
-Postconditions: printed rules and info
*/
void print_rules_info(void);

/*
Function: print_rules
-Description: Prints the rules for Hunt the Wumpus
-Input parameters: n/a
-Returns: n/a
-Preconditions: z was pressed during the game
-Postconditions: printed rules 
*/
void print_rules(void);

/*
Function: get_key()
-Description: Reads the key entered from user and converts to uppercase before returning
-Input parameters: n/a
-Returns: char (capital letter)
-Preconditions: n/a
-Postconditions: user has entered a letter
*/
char get_key(void);

/*
Function: single_game()
-Description: Plays out a single game of Hunt the Wumpus
-Input parameters: PlayerStats point_tracker
-Returns: char ('W' if player won, 'D' if player died, 'R' if player wanted to restart with same profile, 'N' if player wanted to restart with a new profile, or 'Q' if player wanted to quit)
-Preconditions: key is not 'Q'
-Postconditions: game has ended for one reason or another
*/
char single_game(PlayerStats &point_tracker);

/*
Function: single_profile()
-Description: Plays as many game as the player wants, keeping track of said player's stats. Prints final stats to file (GameScores.txt) when player is done playing
-Input parameters: n/a
-Returns: char (the key the player inputted last - if Q, it ends the game, if N, creates a new profile in main loop)
-Preconditions: key is not Q
-Postconditions: key is N or Q (new profile or quit) and current player's stats are outputted in GameScores.txt
*/
char single_profile(void);

#endif HEADER_H

/*
Function:
-Description:
-Input parameters:
-Returns:
-Preconditions:
-Postconditions:
*/