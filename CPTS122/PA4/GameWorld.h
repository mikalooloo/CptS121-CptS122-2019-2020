/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 4
Date: March 6, 2020
Description: Hunt the Wumpus - walk through caves to find the gold while avoiding pits and the Wumpus! Earn points for each move and try to get the high score. 
Header, Class: GameWorld - the game board and positions of pieces
*/

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "header.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> // for rand()

typedef struct setup // for placement of 
{
	int row;
	int column;
} Setup;

class GameWorld
{
private:
	char board[5][5];
	Setup you;
	Setup wumpus;
	Setup gold;
	int pit[2][10];
public:

	// **************Constructor************** 
	GameWorld() // creates the game with a random startup
	{
		int pit_number = 0, valid = 0, found = 0;

		you.row = rand() % 5; you.column = rand() % 5;				// initializing player pos
		wumpus.row = rand() % 5; wumpus.column = rand() % 5;		// initializing wumpus pos
		gold.row = rand() % 5; gold.column = rand() % 5;			// initializing gold pos
		for (int i = 0; i < 10; ++i)								// initializing pit array (-1 is an invalid pos,		
		{															// so for noPit() it can tell if there's no more
			pit[0][i] == -1;										// placed pits) 
		}

		while (valid == 0)
		{
			valid = 1;

			if (you.row == wumpus.row)
			{
				if (you.column == wumpus.column)
				{
					valid = 0;
					wumpus.row = rand() % 2;
					wumpus.column = rand() % 2;
				}
			}

			if (you.row == gold.row)
			{
				if (you.column == gold.column)
				{
					valid = 0;
					gold.row = rand() % 2;
					gold.column = rand() % 2;
				}
			}

			if (wumpus.row == gold.row)
			{
				if (wumpus.column == gold.column)
				{
					valid = 0;
					gold.row = rand() % 2;
					gold.column = rand() % 2;
				}
			}
		}

		while (pit_number > 10 || pit_number < 5)
		{
			pit_number = rand() % 11;
		}

		for (int r = 0; r < 5; ++r)
		{
			for (int c = 0; c < 5; ++c)
			{
				board[r][c] = ' ';

				if (r == you.row && c == you.column)
				{
					board[r][c] = 'U';
				}
				else if (r == wumpus.row && c == wumpus.column)
				{
					board[r][c] = 'W';
				}
				else if (r == gold.row && c == gold.column)
				{
					board[r][c] = 'G';
				}

			}
		}

		int p_c = 0;
		while (pit_number != 0)
		{
			pit[0][p_c] = rand() % 5; pit[1][p_c] = rand() % 5;

			for (int r = 0; r < 5; ++r)
			{
				for (int c = 0; c < 5 && found == 0; ++c)
				{
					if (r == pit[0][p_c] && c == pit[1][p_c])
					{
						found = 1;
						if (board[r][c] == ' ')
						{
							board[r][c] = 'P';
							--pit_number;
							++p_c;
						}
					}
				}
				found = 0;
			}
		}
	}
	
	// **************Displaying Worlds************** 
	/*
	Function: GameWorld::displayEntireWorld()
	-Description: Prints the entire cave system to the console
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: user entered 'c' or 'C' at the game_menu
	-Postconditions: entire world has been printed
	*/
	void displayEntireWorld();		// should display the game state to the screen
	/*
	Function: GameWorld::displayVisibleWorld()
	-Description: Prints only the caves surrounding the player in the cave system to the console
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: user entered 'v' or 'V' at the game_menu
	-Postconditions: visible world has been printed
	*/
	void displayVisibleWorld();		// displays all squares one away from the player
	/*
	Function: GameWorld::displayBlankWorld()
	-Description: Prints only the location of the player in the cave system to the console
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: n/a
	-Postconditions: blank world has been printed
	*/
	void displayBlankWorld();		// displays only where the player is

	// **************Returns************** 
	/*
	Function: GameWorld::returnsRow()
	-Description: Returns a copy of the private variable you.row in the class GameWorld
	-Input parameters: n/a
	-Returns: int copy of you.row
	-Preconditions: n/a
	-Postconditions: copy of you.row has been returned
	*/
	int returnsRow();				// returns the row of the player
	/*
	Function: GameWorld::returnsColumn()
	-Description: Returns a copy of the private variable you.column in the class GameWorld
	-Input parameters: n/a
	-Returns: int copy of you.column
	-Preconditions: n/a
	-Postconditions: copy of you.column has been returned
	*/
	int returnsColumn();			// returns the column of the player
	/*
	Function: GameWorld::validMove()
	-Description: Checks to see if the move entered is valid (it is invalid only if they try to move off the board/out of the array)
	-Input parameters: int r (row, found with returnsRow()) and int c (column, found with returnsColumn())
	-Returns: bool (true if move is valid, false if invalid
	-Preconditions: user entered one of the movement keys
	-Postconditions: found if move is valid (true) or not (false)
	*/
	bool validMove(int r, int c);	// checks whether the move the player wants to make is valid

	// **************Moving**************
	/*
	Function: GameWorld::moveUp()
	-Description: Moves the player's piece on the board ('U') one square up
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: moving one square up is a valid move (validMove())
	-Postconditions: 'U' has been moved up one square
	*/
	void moveUp();					// moves the player up one square
	/*
	Function: GameWorld::moveDown()
	-Description: Moves the player's piece on the board ('U') one square down
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: moving one square down is a valid move (validMove())
	-Postconditions: 'U' has been moved down one square
	*/
	void moveDown();				// moves the player down one square
	/*
	Function: GameWorld::moveRight()
	-Description: Moves the player's piece on the board ('U') one square to the right
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: moving one square to the right is a valid move (validMove())
	-Postconditions: 'U' has been moved to the right one square
	*/
	void moveRight();				// moves the player right one square
	/*
	Function: GameWorld::moveLeft()
	-Description: Moves the player's piece on the board ('U') one square to the left
	-Input parameters: n/a
	-Returns: n/a
	-Preconditions: moving one square to the left is a valid move (validMove())
	-Postconditions: 'U' has been moved to the left one square
	*/
	void moveLeft();				//  moves the player left one square

	// **************End of Turn Checks************** 
	/*
	Function: GameWorld::haveIWon()
	-Description: Checks to see if the player has landed on the gold (if so, they win)
	-Input parameters: n/a
	-Returns: bool (true if player has won/landed on the gold, false if they have not)
	-Preconditions: n/a
	-Postconditions: compared player's and gold's position
	*/
	bool haveIWon();				// returns true or false if the player has won
	/*
	Function: GameWorld::amIAlive()
	-Description: Checks to see if the player is alive or dead (they died if they landed on a pit or a Wumpus)
	-Input parameters: n/a
	-Returns: bool (true if they are safe, false if they died)
	-Preconditions: n/a
	-Postconditions: compared the position of the player, pits, and wumpus
	*/
	bool amIAlive();				// returns true or false depending on if player hit Wumpus or pit
	/*
	Function: GameWorld::noPit()
	-Description: Checks to see if the player is on a pit
	-Input parameters: n/a
	-Returns: bool (true if there is no pit, false if there is one ((they're dead)))
	-Preconditions: amIAlive() is running
	-Postconditions: pit or lack of a pit has been found
	*/
	bool noPit();					// returns true if there is no pit underneath player, false if there is
};

#endif GAMEWORLD_H