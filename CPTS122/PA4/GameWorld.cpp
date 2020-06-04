/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 4
Date: March 6, 2020
Description: Hunt the Wumpus - walk through caves to find the gold while avoiding pits and the Wumpus! Earn points for each move and try to get the high score.
Source for the class GameWorld
*/

#include "header.h"

// **************Displaying Worlds************** 
/*
Function: GameWorld::displayEntireWorld()
-Description: Prints the entire cave system to the console
-Input parameters: n/a
-Returns: n/a
-Preconditions: user entered 'c' or 'C' at the game_menu
-Postconditions: entire world has been printed
*/
void GameWorld::displayEntireWorld() // should display the game state to the screen
{
	printf("  _____________________________\n");
	for (int r = 0; r < 5; ++r) // traverse through all rows
	{
		for (int c = 0; c < 5; ++c) // and columns
		{

			printf(" |  %c ", board[r][c]);

		}

		printf("| \n");
	}
	printf("  _____________________________\n");
}
/*
Function: GameWorld::displayVisibleWorld()
-Description: Prints only the caves surrounding the player in the cave system to the console
-Input parameters: n/a
-Returns: n/a
-Preconditions: user entered 'v' or 'V' at the game_menu
-Postconditions: visible world has been printed
*/
void GameWorld::displayVisibleWorld() // displays all squares one away from the player
{
	printf("  _____________________________\n");
	for (int r = 0; r < 5; ++r)
	{
		for (int c = 0; c < 5; ++c)
		{
			// only print the character if it is +- 1 row or column away from the player ('U')
			if ((r == you.row || r == you.row+1 || r == you.row-1) && (c == you.column || c == you.column+1 || c == you.column-1))
			{
				printf(" |  %c ", board[r][c]);
			}
			else
			{
				printf(" |    ");
			}
		}

		printf("| \n");
	}
	printf("  _____________________________\n");
}
/*
Function: GameWorld::displayBlankWorld()
-Description: Prints only the location of the player in the cave system to the console
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: blank world has been printed
*/
void GameWorld::displayBlankWorld()
{
	cout << "  _____________________________\n";
	for (int r = 0; r < 5; ++r)
	{
		for (int c = 0; c < 5; ++c)
		{
			// only print the character if it is +- 1 row or column away from the player ('U')
			if (r == you.row && c == you.column)
			{
				cout << " |  " << board[r][c] << " ";
			}
			else
			{
				cout << " |    ";
			}
		}

		cout << "| \n";
	}
	cout << "  _____________________________\n";
}

// **************Returns************** 
/*
Function: GameWorld::returnsRow()
-Description: Returns a copy of the private variable you.row in the class GameWorld
-Input parameters: n/a
-Returns: int copy of you.row
-Preconditions: n/a
-Postconditions: copy of you.row has been returned
*/
int GameWorld::returnsRow()
{
	return you.row;
}
/*
Function: GameWorld::returnsColumn()
-Description: Returns a copy of the private variable you.column in the class GameWorld
-Input parameters: n/a
-Returns: int copy of you.column
-Preconditions: n/a
-Postconditions: copy of you.column has been returned
*/
int GameWorld::returnsColumn()
{
	return you.column;
}
/*
Function: GameWorld::validMove()
-Description: Checks to see if the move entered is valid (it is invalid only if they try to move off the board/out of the array)
-Input parameters: int r (row, found with returnsRow()) and int c (column, found with returnsColumn())
-Returns: bool (true if move is valid, false if invalid 
-Preconditions: user entered one of the movement keys
-Postconditions: found if move is valid (true) or not (false)
*/
bool GameWorld::validMove(int r, int c)
{
	if (r < 5 && c < 5 && r > -1 && c > -1) 
		// if the space is not the border 
	{
		return true; // allow player to move there
	}

	return false;
}

// **************Moving************** 
/*
Function: GameWorld::moveUp()
-Description: Moves the player's piece on the board ('U') one square up
-Input parameters: n/a
-Returns: n/a
-Preconditions: moving one square up is a valid move (validMove())
-Postconditions: 'U' has been moved up one square
*/
void GameWorld::moveUp() // moves the player up one square
{
	board[you.row][you.column] = ' '; // replace the old square with nothing
	you.row -= 1;
	board[you.row][you.column] = 'U'; // and the new square with the player
}
/*
Function: GameWorld::moveDown()
-Description: Moves the player's piece on the board ('U') one square down
-Input parameters: n/a
-Returns: n/a
-Preconditions: moving one square down is a valid move (validMove())
-Postconditions: 'U' has been moved down one square
*/
void GameWorld::moveDown() // moves the player down one square
{
	board[you.row][you.column] = ' ';
	you.row += 1;
	board[you.row][you.column] = 'U';
}
/*
Function: GameWorld::moveRight()
-Description: Moves the player's piece on the board ('U') one square to the right
-Input parameters: n/a
-Returns: n/a
-Preconditions: moving one square to the right is a valid move (validMove())
-Postconditions: 'U' has been moved to the right one square
*/
void GameWorld::moveRight() // moves the player right one square
{
	board[you.row][you.column] = ' ';
	you.column += 1;
	board[you.row][you.column] = 'U';
}
/*
Function: GameWorld::moveLeft()
-Description: Moves the player's piece on the board ('U') one square to the left
-Input parameters: n/a
-Returns: n/a
-Preconditions: moving one square to the left is a valid move (validMove())
-Postconditions: 'U' has been moved to the left one square
*/
void GameWorld::moveLeft() //  moves the player left one square
{
	board[you.row][you.column] = ' ';
	you.column -= 1;
	board[you.row][you.column] = 'U';
}

// **************End of Turn Checks************** 
/*
Function: GameWorld::haveIWon()
-Description: Checks to see if the player has landed on the gold (if so, they win)
-Input parameters: n/a
-Returns: bool (true if player has won/landed on the gold, false if they have not)
-Preconditions: n/a
-Postconditions: compared player's and gold's position
*/
bool GameWorld::haveIWon() // returns true or false if the player has won
{
	if (you.row == gold.row && you.column == gold.column) // if the position of the player and the gold are the same
	{
		return true; // then the player has found the gold and has won
	}
	else //ik this else isn't needed but wanted to make more clear that if the positions of the player and the gold are not the same, then they have not won
	{
		return false;
	}
}
/*
Function: GameWorld::amIAlive()
-Description: Checks to see if the player is alive or dead (they died if they landed on a pit or a Wumpus)
-Input parameters: n/a
-Returns: bool (true if they are safe, false if they died)
-Preconditions: n/a
-Postconditions: compared the position of the player, pits, and wumpus
*/
bool GameWorld::amIAlive() // returns true or false depending on if player hit Wumpus or pit
{
	if (((you.row != wumpus.row) || (you.column != wumpus.column))) // if a player did not step on a wumpus
	{
		if (noPit()) // or a pit
		{
			return true; // they are alive
		}
	}
	else // if the player did step on a wumpus
	{
		cout << setw(23) << "L O S E R" << endl;
		cout << "You ran into the Wumpus! You have died." << endl;
	}

	board[you.row][you.column] = 'X';


	return false; // they are dead
}
/*
Function: GameWorld::noPit()
-Description: Checks to see if the player is on a pit
-Input parameters: n/a
-Returns: bool (true if there is no pit, false if there is one ((they're dead)))
-Preconditions: amIAlive() is running
-Postconditions: pit or lack of a pit has been found
*/
bool GameWorld::noPit()
{
	for (int i = 0; pit[0][i] != -1 && i < 10; ++i) // for every pit in the game (-1 is invalid, array size is 10)
	{
		if (you.row == pit[0][i] && you.column == pit[1][i]) // if the player's position and the pit's position equal
		{
			cout << setw(20) << "L O S E R" << endl;
			cout << "You fell in a pit! You have died." << endl;
			return false; // the player has died
		}
	}

	return true; // otherwise the player did not step on a pit
}

/*
Function:
-Description:
-Input parameters:
-Returns:
-Preconditions:
-Postconditions:
*/