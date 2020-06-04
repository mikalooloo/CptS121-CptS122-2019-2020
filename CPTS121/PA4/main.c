/*
Name: Mikaela Dean
Date: 10/2019
Course: CPTS121 Section 1, Lab Section 16 - WSU Fall Semester 2019

Description: Assignment PA 4 - Blackjack - Due 10/09/2019 at midnight.
- Main()
*/

#include "blackjack.h"

int main(void)
{
	//****Bank Balances****
	double balance = 100.0, balance1 = 0.0, balance2 = 0.0, balance3 = 0.0, balance4 = 0.0, balance5 = 0.0;
	//****Misc****
	int option = 0, //User inputted option for the menu
		num_play = 0, //Number of players playing, inputted by user
		times_played = 0; //How many times the game play has run

	srand(time(NULL)); //randomizes die rolls
	
	do
	{
		option = menu_select(times_played); // Prints menu, allows user to select 1 through 4
		determine_option(option, &balance); // Executes user's choice
		if (times_played == 0) // If this is the first time playing, then equal the balance set by the user (which is put into the variable balance) or the default $100 for the game
		{
			balance1 = balance2 = balance3 = balance4 = balance4 = balance5 = balance;
		} //otherwise, keep the balances in the game so as to not reset the players' progress

		if (option == PLAY) // If the option inputted by the user was 3, or PLAY, execute the game
		{
			num_play = player_numbers(); // Lets user input the number of players
			determine_play(num_play, &balance1, &balance2, &balance3, &balance4, &balance5); // Starts the game
			++times_played; // Adds one to times_played, letting the program know that for the above if function on line 18 do not reset the balances if the user decides to play again
		} // If it is not 3 (or PLAY) or 4 (EXIT), reprints the menu to allow for reselection

	} while (option != EXIT);
}