/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 4
Date: March 6, 2020
Description: Hunt the Wumpus - walk through caves to find the gold while avoiding pits and the Wumpus! Earn points for each move and try to get the high score.
Source for header
*/

#include "header.h"

using namespace std;

// **************General Functions************** 

/*
Function: print_controls()
-Description: Prints to the console a table of the keybinds
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: has been printed
*/
void print_controls(void)
{
	cout << "Controls:" << endl;
	cout << " ______________________________________________________________________" << endl;
	cout << "|   Key   |    i" << setw(11) << "k" << setw(12) << "j" << setw(12) << "l" << setw(21) << "|" << endl;
	cout << "|Function | Move Up - Move Down - Move Left - Move Right" << setw(16) << "|" << endl;
	cout << "|   Key   |" << setw(11) << "v" << setw(24) << "c" << setw(19) << "z" << setw(7) << "|" << endl;
	cout << "|Function | Show Caves Adjacent - Show Entire Cave System - Show Rules" << setw(2) << "|" << endl;
	cout << "|   Key   |" << setw(14) << "r" << setw(27) << "n" << setw(15) << "q" << setw(5) << "|" << endl;
	cout << "|Function | Restart with Same Player - Restart with New Player - Quit" << setw(3) << "|" << endl;
	cout << " _______________________________________________________________________\n" << endl;
}

/*
Function: game_menu()
-Description: Prints the controls (using print_controls()) and if display_blank is true, prints out the blankWorld
-Input parameters: GameWorld game, bool display_blank (if true, prints out blankWorld)
-Returns: n/a
-Preconditions: n/a
-Postconditions: printed out controls
*/
void game_menu(GameWorld game, bool display_blank)
{
	cout << setw(44) << "Hunt the Wumpus" << endl;
	print_controls();

	if (display_blank) // if true, display blank world
	{
		game.displayBlankWorld();
	}

	cout << endl;
}

/*
Function: print_rules_info
-Description: Prints the rules and information for Hunt the Wumpus
-Input parameters: n/a
-Returns: n/a
-Preconditions: 1 was pressed in the main menu
-Postconditions: printed rules and info
*/
void print_rules_info(void)
{
	cout << "**Hunt the Wumpus Rules and Information**" << endl;
	cout << "Developed in 1972 by Gregory Yob, Hunt the Wumpus was one of the first text-based adventure games for computers." << endl;
	cout << "In the game, you wander around a maze, looking for the gold while  running away from the dreaded Wumpus." << endl;
	cout << "The object of the game is to find the gold without running into the Wumpus or fall into any bottomless pits." << endl << endl;
	cout << "In the game, you'll be presented with a blank grid. The character U represents yourself." << endl << "You can use the keys IJKL to move up, left, down, or right, respectively." << endl << "Controls will be shown during each turn if you forget, however." << endl << "For each move, you earn 5 points." << endl << endl;
	cout << "If you're afraid of moving around blind, you can press V to see what's in the squares surrounding U," << endl << "whether it be a pit, the Wumpus, or the gold!" << endl << "Once you move, it will go back to the blank grid, so memorize before you make a move!" << endl << "What's good to keep in mind is you lose 2 points every time you press V." << endl;
	cout << "You can also press C to see the complete map of everything hiding in the darkness." << endl << "You'll lose 5 points every time you do this." << endl << "And again, the new information will disappear once you move, so be careful." << endl << endl;
	cout << "The game will end when you either die (by falling into a pit or bumping into a Wumpus!) or find the gold." << endl << "You'll only win points if you find the gold." << endl;
	cout << "Good luck!" << endl;
}

/*
Function: print_rules
-Description: Prints the rules for Hunt the Wumpus
-Input parameters: n/a
-Returns: n/a
-Preconditions: z was pressed during the game
-Postconditions: printed rules
*/
void print_rules(void)
{
	cout << "**Hunt the Wumpus Rules**" << endl;
	cout << "You are represented by the character U. Use IJKL to move up, left, down, or right respectively." << endl;
	cout << "Each move you make earns 5 points. Use V to see in the squares around you, losing 2 points every time you do so." << endl;
	cout << "Use C to see the entire map, losing 5 points every time you do so." << endl;
	cout << "You want to find the gold (G) while avoiding pits (P) and the Wumpus (W). You only win points if you find the gold." << endl;
	cout << "Good luck!" << endl << endl;
}

/*
Function: get_key()
-Description: Reads the key entered from user and converts to uppercase before returning
-Input parameters: n/a
-Returns: char (capital letter)
-Preconditions: n/a
-Postconditions: user has entered a letter
*/
char get_key(void)
{
	char key = '\0';

	cin >> key;
	key = toupper(key); // makes the key pressed upper-case

	return key;
}

/*
Function: single_game()
-Description: Plays out a single game of Hunt the Wumpus 
-Input parameters: PlayerStats point_tracker
-Returns: char ('W' if player won, 'D' if player died, 'R' if player wanted to restart with same profile, 'N' if player wanted to restart with a new profile, or 'Q' if player wanted to quit)
-Preconditions: key is not 'Q'
-Postconditions: game has ended for one reason or another
*/
char single_game(PlayerStats &point_tracker)
{
	GameWorld game;

	char key = '\0';
	bool end = false; 

	game_menu(game, true);
	key = get_key();

	while (key != 'Q' && key != 'R' && key != 'N' && end == false) // if the key is not to quit, restart, or the game is over (end is true), then keep playing
	{
		switch (key) // does the action for the key pressed during game
		{
		case 'I': // moving up
			system("cls");

			if (game.validMove(game.returnsRow() - 1, game.returnsColumn())) // if validMove is true
			{
				game.moveUp(); // move up
				point_tracker.movementPoint();
			}
			else
			{
				cout << "Invalid move direction!" << endl;
			}

			if (game.haveIWon()) // if player is on gold
			{
				key = 'W';
				end = true;
				point_tracker.movementPoint();	// give movement points
				point_tracker.end_game(key);	// end the game
				cout << endl << setw(32) << "Entire World" << endl;
				game.displayEntireWorld();
			}
			else if (game.amIAlive()) // if player is not on gold, is the player alive?
			{
				game_menu(game, true); // if yes continue playing
				key = get_key();
			}
			else // if not, they dead
			{
				key = 'D';
				end = true;
				point_tracker.end_game(key);
				cout << endl << setw(32) << "Entire World" << endl;
				game.displayEntireWorld();
			}

			break;
		case 'K': // moving down
			system("cls");

			if (game.validMove(game.returnsRow() + 1, game.returnsColumn())) // if valid move
			{
				game.moveDown();
				point_tracker.movementPoint();
			}
			else
			{
				cout << "Invalid move direction!" << endl;
			}

			if (game.haveIWon()) // if won
			{
				key = 'W';
				end = true;
				point_tracker.movementPoint();
				point_tracker.end_game(key);
				cout << endl << setw(32) << "Entire World" << endl;
				game.displayEntireWorld();
			}
			else if (game.amIAlive()) // if alive
			{
				game_menu(game, true);
				key = get_key();
			}
			else // if dead
			{
				key = 'D';
				end = true;
				point_tracker.end_game(key);
				cout << endl << setw(32) << "Entire World" << endl;
				game.displayEntireWorld();
			}

			break;
		case 'J': // moving left
			system("cls");

			if (game.validMove(game.returnsRow(), game.returnsColumn() - 1)) // if valid move
			{
				game.moveLeft();
				point_tracker.movementPoint();
			}
			else
			{
				cout << "Invalid move direction!" << endl;
			}

			if (game.haveIWon()) // if won
			{
				key = 'W';
				end = true;
				point_tracker.movementPoint();
				point_tracker.end_game(key);
				cout << endl << setw(32) << "Entire World" << endl;
				game.displayEntireWorld();
			}
			else if (game.amIAlive()) // if alive
			{
				game_menu(game, true);
				key = get_key();
			}
			else // if dead
			{
				key = 'D';
				end = true;
				point_tracker.end_game(key);
				cout << endl << setw(32) << "Entire World" << endl;
				game.displayEntireWorld();
			}

			break;
		case 'L': // moving right
			system("cls");

			if (game.validMove(game.returnsRow(), game.returnsColumn() + 1)) // if valid move
			{
				game.moveRight();
				point_tracker.movementPoint();
			}
			else
			{
				cout << "Invalid move direction!" << endl;
			}

			if (game.haveIWon()) // if won
			{
				key = 'W';
				end = true;
				point_tracker.movementPoint();
				point_tracker.end_game(key);
				cout << endl << setw(32) << "Entire World" << endl;
				game.displayEntireWorld();
			}
			else if (game.amIAlive()) // if alive
			{
				game_menu(game, true);
				key = get_key();
			}
			else // if dead
			{
				key = 'D';
				end = true;
				point_tracker.end_game(key);
				cout << endl << setw(32) << "Entire World" << endl;
				game.displayEntireWorld();
			}

			break;
		case 'V': // display visible world
			system("cls");
			game_menu(game, false); // false so it doesn't display blank world

			game.displayVisibleWorld();
			point_tracker.visible(); // subtract points for using visible world
			key = get_key();

			break;
		case 'C': // display entire world
			system("cls");
			game_menu(game, false); 

			game.displayEntireWorld();
			point_tracker.entire(); // subtract points for using entire world
			key = get_key();

			break;
		case 'R': // restarts game with same player
			point_tracker.end_game(key);

				break;
		case 'N': // restarts game with new player
			break;
		case 'Q': // quits game
			break;
		case 'Z': // prints Rules to the screen
			system("cls");
			print_rules();
			
			game_menu(game, true);
			key = get_key();

			break;
		default: // invalid
			system("cls");
			cout << "Invalid input, " << key << " does not have a function." << endl << endl;
			
			game_menu(game, true);
			key = get_key();
			break;
		}
	}

	return key;
}

/*
Function: single_profile()
-Description: Plays as many game as the player wants, keeping track of said player's stats. Prints final stats to file (GameScores.txt) when player is done playing
-Input parameters: n/a
-Returns: char (the key the player inputted last - if Q, it ends the game, if N, creates a new profile in main loop)
-Preconditions: key is not Q
-Postconditions: key is N or Q (new profile or quit) and current player's stats are outputted in GameScores.txt
*/
char single_profile(void)
{
	PlayerStats point_tracker;
	char key = '\0';

	cout << "Enter your initials: ";
	point_tracker.updateName();

	while (key != 'Q' && key != 'N') // while player wants to keep playing
	{
		key = single_game(point_tracker);
		if (key == 'W' || key == 'D') // if player finished the game,
		{
			cout << endl << "Press R to continue, N to restart as a new player, or Q to quit." << endl;
			cin >> key;
			key = toupper(key);
		}
		system("cls");
	}

	ofstream file;
	file.open("GameScores.txt", ios::app);
	if (file.is_open()) // put the player's stats into GameScores
	{
		file << point_tracker; // using overloaded friend function
		file.close();
	}
	else
	{
		cout << "GameScores file did not open correctly in header!" << endl;
	}

	return key;
}