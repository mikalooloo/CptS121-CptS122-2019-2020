#include "yahtzee.h"

// Main Menu Functions 

int menu_select(void)
{
	int option = 0;

	do
	{
		print_menu(); // prints menu 
		option = get_option(); // finds which option
	} while (option < GAMERULES && option > EXIT); // must be between 1 and 3, otherwise repeats

	return option;
}

void print_menu(void)
{
	printf("********Mikaela's Yahtzee********\n");
	printf("1. Print game rules\n");
	printf("2. Play game\n");
	printf("3. Exit\n\n");
}

int get_option(void)
{
	int option = 0;

	scanf("%d", &option);

	return option;
}

// Gameplay Functions

int game_play(void) // declare int combo[]
{
	int round = 1, // keeps track of the rounds, as after round 14 it is over
		winner = 0, total1 = 0, total2 = 0, // all used at the end of game (this function returns the winning player)
		combo1[14] = { 0 }, combo2[14] = { 0 }; // the scorecards for player 1 and 2

	for (int i = 0; i < 14; ++i) // for the entire combo array
	{
		combo1[i] = -1;
		combo2[i] = -1; // make them -1, to mean they're an invalid number
	}

	for (; round < 15; ++round) // this ensures the turns are done 14 times
	{
		player_turn(1, combo1, round);
		player_turn(2, combo2, round);
	}

	total1 = calculate_scores(combo1); // now that the game is over, calculate the scores
	total2 = calculate_scores(combo2);
	winner = find_winner(total1, total2); // find the bigger of the two
	print_scores(total1, total2, winner); // print the winner and totals

	return winner; // gameplay over
}

void player_turn(int player, int combo[], int round) // declare int dice[], freq[] here
{
	int dice[6] = { 0 }; // the die values themselves in an array
	int freq[7] = { 0 }; // the frequency of each die value (to make assigning the points from combos much easier)

	int reroll_num = 0, // how many dice the player wants to reroll
		combo_num = 0, // what combo number the player wants to use
		times = 1; // lets player only reroll twice
	char answer = '\0'; // the answer to whether the player wants to reroll again or not

	printf("********Round %d********\n", round);
	printf("\n****Player %d's Turn****\n", player);

	if (round != 1) // if this isn't the first round,
	{
		print_combos(player, combo); // print the combo so the player can be reminded of what they've already done and what they still need
	}

	printf("Press any key to roll your five dice: ");
	scanf(" %c");
	roll_diceForArray(dice); // finds the values for the dice array
	display_dice(dice); // prints said values for the dice array

	do 
	{
		printf("\nDo you want to reroll any dice? Enter Y for Yes or N for No: ");
		scanf(" %c", &answer);
		if (answer == 'Y' || answer == 'y') // if they said yes to rerolling
		{
			do
			{
				printf("\nHow many dice do you want to reroll? ");
				scanf("%d", &reroll_num);
			} while (reroll_num < 1 || reroll_num > 5); // does not allow them to reroll more dice than they have

			reroll_diceNum(dice, reroll_num); // rerolls the number of dice the user wanted
			++times;
		}
	} while ((answer == 'Y' || answer == 'y') && times < 3); // keeps asking if the player wants to reroll unless they say no or they have already rerolled twice

	freq_array(dice, freq); // finds the frequency of each die value
	printf("\nPlease enter the number of what combination you'd like to use your roll for.\n");
	print_combos(player, combo); // prints the scoresheet
	scanf("%d", &combo_num);
	combo[combo_num] = verify_points(combo_num, freq); // returns the number of points for the combo the user selected
	system("cls");
}

void print_combos(int player, int combo[])
{
	int scored = 0;

	printf("\nPlayer %d's Scoresheet\n", player);
	printf("__________________________\n");
	printf("  Upper Section | Points\n");
	printf("--------------------------\n");
	if (combo[1] == -1) // if the combo has not been used yet
	{
		printf("  Sum of ones   |    *   \n"); // show the points as an * 
	}
	else // if it has already been used
	{
		printf("  Sum of ones   |    %d   \n", combo[1]); // display the points earned
	}
	if (combo[2] == -1)
	{
		printf("  Sum of twos   |    *    \n");
	}
	else
	{
		printf("  Sum of twos   |    %d    \n", combo[2]);
	}
	if (combo[3] == -1)
	{
		printf("  Sum of threes |    *    \n");
	}
	else
	{
		printf("  Sum of threes |    %d    \n", combo[3]);
	}
	if (combo[4] == -1)
	{
		printf("  Sum of fours  |    *    \n");
	}
	else
	{
		printf("  Sum of fours  |    %d    \n", combo[4]);
	}
	if (combo[5] == -1)
	{
		printf("  Sum of fives  |    *    \n");
	}
	else
	{
		printf("  Sum of fives  |    %d    \n", combo[5]);
	}
	if (combo[6] == -1)
	{
		printf("  Sum of sixes  |    *    \n");
	}
	else
	{
		printf("  Sum of sixes  |    %d    \n", combo[6]);
	}
	printf("__________________________\n");
	printf("  Lower Section | Points\n");
	printf("--------------------------\n");
	if (combo[7] == -1)
	{
		printf("Three-of-a-kind |    *    \n");
	}
	else
	{
		printf("Three-of-a-kind |    %d    \n", combo[7]);
	}
	if (combo[8] == -1)
	{
		printf(" Four-of-a-kind |    *    \n");
	}
	else
	{
		printf(" Four-of-a-kind |    %d    \n", combo[8]);
	}
	if (combo[9] == -1)
	{
		printf(" Full house     |    *    \n");
	}
	else
	{
		printf(" Full house     |    %d    \n", combo[9]);

	}
	if (combo[10] == -1)
	{
		printf(" Small straight |    *    \n");
	}
	else
	{
		printf(" Small straight |    %d    \n", combo[10]);
	}
	if (combo[11] == -1)
	{
		printf(" Large straight |    *    \n");
	}
	else
	{
		printf(" Large straight |    %d    \n", combo[11]);

	}
	if (combo[12] == -1)
	{
		printf(" ~Yahtzee~      |    *    \n");
	}
	else
	{
		printf(" ~Yahtzee~      |    %d    \n", combo[12]);

	}
	if (combo[13] == -1)
	{
		printf(" Chance         |    *    \n");
	}
	else
	{
		printf(" Chance         |    %d    \n", combo[13]);
	}
	printf("__________________________\n\n");
}

int verify_points(int combo_num, int freq[])
{
	int points = 0, check = 0;

	switch (combo_num)
	{
	case 1: // *********sum of ones*********
		points = freq[1];
		break;
	case 2: // *********sum of twos*********
		points = freq[2] * 2;
		break;
	case 3: // *********sum of threes*********
		points = freq[3] * 3;
		break;
	case 4: // *********sum of fours*********
		points = freq[4] * 4;
		break;
	case 5: // *********sum of fives*********
		points = freq[5] * 5;
		break;
	case 6: // *********sum of sixes*********
		points = freq[6] * 6;
		break;
	case 7: // *********three-of-a-kind*********
		for (int i = 0; i < 7; ++i) // check the frequency of each die to see if there is a three of a kind
		{
			if (freq[i] > 2) // if this is true, then that means there are at least 3 of that die value
			{
				check = 1; // make check equal one, to ensure the points are all added together
			}

			points += freq[i] * i; // this will be set to zero if the check is still zero, meaning there are no die values that show up at least three times
		}

		if (check == 0) // if check equals zero, which means no die value shows up at least 3 times,
		{
			points = 0; // then you get no points for three-of-a-kind
		}
		break; 
	case 8: // *********four-of-a-kind*********
		for (int i = 0; i < 7; ++i) // check the frequency of each die to see if there is a four of a kind
		{
			if (freq[i] > 3) // if this is true, then that means there are at least 4 of that die value
			{
				check = 1; // make check equal one, to ensure the points are all added together
			}
			points += freq[i] * i; // this will be set to zero if the check is still zero, meaning there are no die values that show up at least four times
		}

		if (check == 0) // if check equals zero, which means no die value shows up at least 4 times,
		{
			points = 0; // then you get no points for four-of-a-kind
		}
		break;
	case 9: // *********full house*********
		for (int i = 0; i < 7; ++i) // check the frequency of each die to see if there is a three of a kind and a pair
		{
			if (freq[i] == 2) // if this is true, then that means there are 2 of that die value
			{
				check += 1; // add one to check, there is at least a pair
			}
			else if (freq[i] == 3) 
			{
				check += 1; // add one to check, there is at least three-of-a-kind
			}
			else if (freq[i] == 5) // since there's only one yahtzee, if you do happen to get another one full house works too
			{
				check = 2; // has to equal two to say the two requirements are met
			}

		}

		if (check < 2) // if check is less than two, then the requirements have not been met (either no pair, no three-of-a-kind, or none)
		{
			points = 0; // then you get no points
		}
		else // otherwise, the requirements ARE met (check is 2), so give points:
		{
			points = 25;
		}
		break;
	case 10: // *********small straight*********
		if (freq[3] == 0)
		{
			points = 0; // there is no way to get a small straight without one three
		}
		else if (freq[1] > 0 && freq[2] > 0 && freq[4] > 0 || freq[4] > 0 && freq[5] > 0 && freq[6] > 0)
		{
			points = 30;
		}
		break;
	case 11: // *********large straight*********
		if (freq[1] == 0 && freq[6] == 0)
		{
			points = 0; // there is no way to get a small straight without a one or six
		}
		else if (freq[2] > 0 && freq[3] > 0 && freq[4] > 0 && freq[5] > 0)
		{
			points = 40;
		}
		break;
	case 12: // *********yahtzee*********
		for (int i = 0; i < 7; ++i) 
		{
			if (freq[i] == 5) // if this is true, then that means there are 5 of that die value
			{
				points = 50;
			}
		}
		break;
	case 13: // *********chance*********
		for (int i = 0; i < 7; ++i)
		{
			points += freq[i];
		}
		break;
	}

	return points;
}

// Dice Functions

int roll_dice(void)
{
	int die = 0;

	die = rand() % 6 + 1;

	return die;
}

void display_dice(int dice[])
{
	for (int times = 1; times < 6; ++times)
	{
		printf("\nDie %d: \n", times);
		pretty_dice();
		printf("\r%d\n", dice[times-1]);
	}
}

void display_rerolledDice(int dice[], int rerolled_dice[])
{
	for (int times = 1; times < 6; ++times)
	{
		printf("\nDie %d: \n", times);
		if (rerolled_dice[times - 1] == 1) // if this die was rerolled, make it look like it's rolling again
		{
			pretty_dice();
		}
		else
		{
			Sleep(400); // otherwise keep the same
		}
		printf("\r%d\n", dice[times - 1]);
	}
}

void roll_diceForArray(int dice[])
{
	for (int index = 0; index < 5; ++index)
	{
		dice[index] = roll_dice(); // rolls dice and puts it into the dice[] array
	}
}

void pretty_dice(void)
{
	printf("%d", rand() % 6 + 1);
	Sleep(200);
	printf("\r%d", rand() % 6 + 1);
	Sleep(200);
	printf("\r%d", rand() % 6 + 1);
	Sleep(200);
}

void freq_array(int dice[], int freq[])
{
	for (int index = 0; index < 5; ++index)
	{
		freq[dice[index]] += 1; // adds a one for each die value that's in dice[]
	}
}

void reroll_diceNum(int dice[], int reroll_num)
{
	int option = 0, reroll_diceArray[7] = { 0 };

	if (reroll_num < 5) // this is just so I can say "which die do you want" and then later say "what's another die"
	{
		printf("\nWhich die do you want to reroll? ");
		option = get_option();
		dice[option - 1] = roll_dice(); 
		reroll_diceArray[option] = 1;
	}

	switch (reroll_num)
	{
	case 5:
		roll_diceForArray(dice); // this is different than the other ones because we can treat it more like the first time you're rolling since it's all of them
		display_dice(dice);
		break;
	case 4:
		reroll_dice(dice, reroll_diceArray); 
	case 3:
		reroll_dice(dice, reroll_diceArray);
	case 2:
		reroll_dice(dice, reroll_diceArray);
	case 1:
		break;
	}

	display_rerolledDice(dice, reroll_diceArray);
}

void reroll_dice(int dice[], int reroll_diceArray[])
{
	int option = 0, counter = 0;
	
	do
	{
		if (counter != 0) // if counter is one and this repeats it means the user entered a die that has already been rerolled in that reroll
		{
			printf("Please enter a die that's not already been rerolled.\n");
		}
		printf("What's another die do you want to reroll? ");
		option = get_option();
		++counter;
	} while (reroll_diceArray[option] == 1);

	dice[option - 1] = roll_dice(); // reroll said die
	reroll_diceArray[option] = 1;
}

// End of Game Functions

int calculate_scores(int combo[])
{
	int total = 0;

	for (int i = 0; i < 14; ++i)
	{
		total += combo[i]; // adds the combo's points to the total
		if (i == 6 && total >= 63) // if the upper section is equal to or above 63, add 35 points to the total
		{
			total += 35;
		}
	}

	return total;
}

int find_winner(int total1, int total2)
{
	int winner = 1;

	if (total2 > total1)
	{
		winner = 2;
	}

	return winner;
}

void print_scores(int total1, int total2, int winner)
{
	printf("Calculating scores...");
	Sleep(3000);
	system("cls");
	printf("The winner is.............\n");
	Sleep(2000);
	printf("Drumroll please!\n");
	Sleep(2000);
	printf("\n***************************\n");
	printf("Player %d! You were always my favorite.\n", winner);
	printf("***************************\n\n");
	printf("Player 1, your total was %d.\n", total1);
	printf("Player 2, your total was %d.\n\n\n", total2);
	Sleep(3000);
}