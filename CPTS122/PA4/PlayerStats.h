/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 4
Date: March 6, 2020
Description: Hunt the Wumpus - walk through caves to find the gold while avoiding pits and the Wumpus! Earn points for each move and try to get the high score.
Header, Class: PlayerStats - keeps track of a player's stats for the games they have played
*/

#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include "header.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for rand()

class PlayerStats
{
private:
	std::string initials;	// name of player
	int current_points;		// points for the current game
	int total_points;		// all points earned from wins
	int avg_points;			// total amount of points / the number of wins
	int current_moves;		// number of moves for the current game
	int total_moves;		// all moves done in finished games
	int avg_moves;			// total amount of moves / the number of wins and loses combined
	int wins;				// total number of games player has won (found gold)
	int loses;				// total number of games player has lost (ran into wumpus or pit)
	int restarts;			// total number of games restarted (neither won nor lost)

public:
	PlayerStats()
	{
		current_points = 0;
		total_points = 0;		
		avg_points = 0;			
		current_moves = 0;		
		total_moves = 0;		
		avg_moves = 0;			
		wins = 0;				
		loses = 0;				
		restarts = 0;
	}

	// **************In-Game************** 
	/*
	Function: updateName()
	-Description: Reads in the user's name and stores the first three letters in all capitals
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: User has entered in a name that's at least 2 characters
	*/
	void updateName();

	//***Point Updaters***
	/*
	Function: returnsPoints()
	-Description: Getter function for points - Returns a copy of the private variable current_points in the class GameWorld
	-Input parameters: n/a
	-Returns: int (value of current_points)
	-Preconditions: n/a
	-Postconditions: returned an int with the value of current_points
	*/
	int returnsPoints();
	/*
	Function: movementPoint()
	-Description: Adds five points to the current_points for moving a space successfully
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: Player moved without dying
	-Postconditions: +5 points to current_points
	*/
	void movementPoint();
	/*
	Function: visible()
	-Description: Subtracts 2 points from current_points for pressing 'v' or 'V' in the game_menu
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: user entered 'v' or 'V'
	-Postconditions: -2 points to current_points
	*/
	void visible();
	/*
	Function: entire()
	-Description: Subtracts 5 points from current_points for pressing 'c' or 'C' in the game_menu
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: user entered 'c' or 'C'
	-Postconditions: -5 points to current_points
	*/
	void entire();

	// **************End-Game************** 
	/*
	Function: end_game()
	-Description: Takes care of end of game stats like total and average points and more
	-Input parameters: char status (R for Restart, D for Dead, W for Win)
	-Returns: n/a
	-Preconditions: game has ended
	-Postconditions: points have been correctly allocated and calculated
	*/
	void end_game(char status); // statuses are: R for Restart, D for Dead/Loss, W for Win

	/*
	Function: file << 
	-Description: formats the output to the end of a file when outputting PlayerStats statistics
	-Input parameters: output file, PlayerStats 
	-Returns: n/a
	-Preconditions: a file is opened and ready to be written to
	-Postconditions: the formatted statistics are added to the end of the file 
	*/
	friend std::ostream& operator<<(std::ostream& out, PlayerStats const& stats);
};



#endif PLAYERSTATS_H