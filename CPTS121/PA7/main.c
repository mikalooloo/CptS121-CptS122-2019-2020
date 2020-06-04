/* Name: Mikaela Dean
Course: CPTS121, WSU
Date: November 2019

PA 7: Poker
*/

#include "poker.h"

int main(void)
{
	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };


	srand((unsigned)time(NULL)); /* seed random-number generator */

	int answer = 0;

	do
	{
		main_menu();
		answer = int_answer();

		if (answer == 1)
		{
			print_rules();
		}
		else if (answer == 2)
		{
			play_game(face, suit);
		}

	} while (answer != 3);
	




	return 0;
}