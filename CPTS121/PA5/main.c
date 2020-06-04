#include "yahtzee.h"

int main(void)
{
	int option = 0, winning_player = 0;
	int winners[3] = { 0 };

	srand(time(NULL));

	do
	{

		option = menu_select();
		system("cls");

		if (option == GAMERULES)
		{
			printf("************Yahtzee Game Rules************\n\n");
			printf("Yahtzee is a dice game that was invented by Milton Bradley and Edwin S. Lowe in 1956.\nThe challenge of the game is to outduel the other player by scoring the most points.\nPoints are obtained by rolling five 6-sided die across thirteen rounds.\nDuring each round, each player may roll the dice up to three times to make one of the possible scoring combinations.\nOnce a combination has been achieved by the player, it may not be used again in future rounds.\n");
			printf("Each scoring combination has different point totals.\n\nSome of these totals are achieved through the accumulation of points across rolls\n and some are obtained as fixed sequences of values.\n");
			printf("The scorecard used for Yahtzee is composed of two sections. A upper section and a lower section.\nA total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.\nThe upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\nIf a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12.\nOnce a player has chosen to score a box, it may not be changed\nand the combination is no longer in play for future rounds.\nIf the sum of the scores in the upper section is greater than or equal to 63,\nthen 35 more points are added to the players overall score as a bonus.\nThe lower section contains a number of poker like combinations.\n");
			printf("\nThe lower section includes Three-of-a-kind, which requires three dice with the same face.\nThe scoring for that is the sum of all face values on the 5 dice.\nNext is Four-of-a-kind, which requires four dice with the same face,\nand the scoring for that is the sum of all the face values on the 5 dice.\nAfter that is full house, which needs one pair and a three-of-a-kind. The score for that is 25.\nNext is a small and large straight, one requiring a sequence of four dice and the latter requiring five.\nThe scores for that is 30 and 40, respectively.\nMost importantly is Yahtzee, or five-of-a-kind with a score of 50.\nAfter that there is chance, which may be used for any sequence of dice.\nThe score for that is the sum of all face values on the 5 dice.\n\n\n");
		}

		if (option == PLAY)
		{
			winning_player = game_play();
			winners[winning_player] += 1;
		}

	} while (option != EXIT);

	printf("Player 1 has won %d times, while Player 2 has won %d times.\n", winners[1], winners[2]);
	printf("Have a good day!\n\nExiting...\n");
	Sleep(500);
}