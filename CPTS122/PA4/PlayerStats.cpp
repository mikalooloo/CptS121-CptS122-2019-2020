/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 4
Date: March 6, 2020
Description: Hunt the Wumpus - walk through caves to find the gold while avoiding pits and the Wumpus! Earn points for each move and try to get the high score.
Source for the class PlayerStats
*/

#include "header.h"

// **************In-Game************** 
/*	
Function: updateName()
-Description: Reads in the user's name and stores the first three letters in all capitals	
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: User has entered in a name that's at least 2 characters
*/
void PlayerStats::updateName()
{
	string name;

	cin >> name;

	while (name.length() < 3) // if the length of their name is less than 2 characters
	{
		cout << "Please enter 3 characters!" << endl << "Enter your initials: ";
		cin >> name;
	}

	for (int i = 0; i < 3; ++i) // convert the first three characters of the name entered to all caps in the string initials
	{
		initials += toupper(name[i]);
	}

	system("cls");
	cout << "Your initials are " << initials << "!\n";
}

//***Point Updaters***
/*
Function: returnsPoints()
-Description: Returns a copy of the private variable current_points in the class GameWorld
-Input parameters: n/a
-Returns: int (value of current_points)
-Preconditions: n/a
-Postconditions: returned an int with the value of current_points
*/
int PlayerStats::returnsPoints()
{
	return current_points;
}
/*
Function: movementPoint()
-Description: Adds five points to the current_points for moving a space successfully
-Input parameters: n/a
-Returns: n/a
-Preconditions: Player moved without dying
-Postconditions: +5 points to current_points
*/
void PlayerStats::movementPoint()
{
	current_points += 5;
	current_moves += 1;
}
/*
Function: visible()
-Description: Subtracts 2 points from current_points for pressing 'v' or 'V' in the game_menu
-Input parameters: n/a
-Returns: n/a
-Preconditions: user entered 'v' or 'V'
-Postconditions: -2 points to current_points
*/
void PlayerStats::visible()
{
	current_points -= 2;
}
/*
Function: entire()
-Description: Subtracts 5 points from current_points for pressing 'c' or 'C' in the game_menu
-Input parameters: n/a
-Returns: n/a
-Preconditions: user entered 'c' or 'C'
-Postconditions: -5 points to current_points
*/
void PlayerStats::entire()
{
	current_points -= 5;
}

// **************End-Game************** 
/*
Function: end_game()
-Description: Takes care of end of game stats like total and average points and more
-Input parameters: char status (R for Restart, D for Dead, W for Win)
-Returns: n/a	
-Preconditions: game has ended	
-Postconditions: points have been correctly allocated and calculated
*/
void PlayerStats::end_game(char status)
{
	// updates stats based on how the game ended
	switch (status)
	{
	case 'R': // if restarted, add one to the amount of restarts
		restarts += 1;
		break;
	case 'D': // if lost, calculate moves and add one to loses
		total_moves += current_moves;
		loses += 1;
		avg_moves = total_moves / (wins + loses);
		cout << "0 points awarded because you lost." << endl;

		current_moves = 0;
		current_points = 0;
		break;
	case 'W': // if won, calculate points and moves, add one to wins
		total_points += current_points;
		total_moves += current_moves;

		wins += 1;

		avg_points = total_points / (wins + loses);
		avg_moves = total_moves / (wins + loses);

		cout << setw(20) << "W I N N E R" << endl;
		cout << "You found the gold! Good job!" << endl << endl;
		cout << current_points << " points awarded for this win. (" << current_moves << " total moves)" << endl;

		current_moves = 0;
		current_points = 0;
		break;
	}

	cout << endl << setw(33.5) << "Complete Stats" << endl;
	cout << setw(28) << initials << endl;
	cout << "Avg Points | Total Points | Avg Moves | Total Moves " << endl;
	cout << setw(6) << avg_points << setw(14) << total_points << setw(13) << avg_moves << setw(13) << total_moves << endl;
	cout << "   Wins    |    Losses    |  Restarts | Skill Rating " << endl;
	cout << setw(6) << wins << setw(14) << loses << setw(13) << restarts << setw(12) << rand() % 10 + 1 << "/10" << endl;
	
}

/*
Function: file <<
-Description: formats the output to the end of a file when outputting PlayerStats statistics
-Input parameters: output file, PlayerStats
-Returns: n/a
-Preconditions: a file is opened and ready to be written to
-Postconditions: the formatted statistics are added to the end of the file
*/
ostream& operator<<(ostream& out, PlayerStats const& stats)
{
	out << stats.initials << setw(10) << stats.wins << setw(10) << stats.avg_points << endl;
	return out;
}
