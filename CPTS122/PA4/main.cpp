/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 4
Date: March 6, 2020
Description: Hunt the Wumpus - walk through caves to find the gold while avoiding pits and the Wumpus! Earn points for each move and try to get the high score.
Main
*/

#include "header.h"

int main(void)
{
	srand(time(NULL)); // randomize numbers

	char key = '\0';
	int main_menu = 0;

	do // Main Menu
	{
		cout << "Hunt the Wumpus" << endl;
		cout << "1. Rules and Information" << endl;
		cout << "2. Play Game" << endl;
		cout << "3. Credits" << endl;
		cout << "4. Quit" << endl << endl;
		cin >> main_menu;

		if (cin.fail()) // if a character is entered instead of a number
		{
			system("cls");
			cout << "Invalid input, please enter 1, 2, 3, or 4!" << endl << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else
		{
			switch (main_menu) // depending on what the user inputs, displays rules (1) or credits (3), starts the game (2), or quits (4)
			{
			case 1: // prints Rules and Information to screen
				system("cls");
				print_rules_info();
				cout << endl << "Press any key to go back to the Main Menu." << endl;
				cin >> key;
				key = '\0';
				system("cls");
				break;
			case 2: // starts the game
				break;
			case 3: // prints Credits to the screen
				system("cls");
				cout << "Credits" << endl << "Me" << endl << endl;
				break;
			case 4: // Quits
				key = 'Q'; // if key is Q then it'll skip the game loop later on, and just quit
				break;
			default: // invalid input by user
				cout << "Invalid input, please enter 1, 2, 3, or 4!" << endl;
			}
		}
	} while (main_menu != 2 && main_menu != 4); // do not exit loop until they want to play or quit

	ofstream file;
	file.open("GameScores.txt");
	if (file.is_open()) // if GameScores.txt is open
	{
		file << "Initials | Wins | Avg Points" << endl; // write the header
		file.close();
	}
	else // otherwise it did not open correctly
	{
		cout << "GameScores file did not open correctly in main!" << endl;
	}
	

	while (key != 'Q') // while the player(s) do not want to Quit aka
	{ 
		key = single_profile(); // keep making new profiles until they want to quit
	}

	system("cls");
	cout << "Exiting game..." << endl;
}