/*
Name: Mikaela Dean
Date: 10/2019
Course: CPTS121 Section 1, Lab Section 16 - WSU Fall Semester 2019

Description: Assignment PA 4 - Blackjack - Due 10/09/2019 at midnight.
- Function definitions
*/

#include "blackjack.h"

// Menu Screen Functions

void display_menu(int times_played)
{
	printf("\n***********Blackjack Dice************\n\n");
	printf("1. Display game rules\n");
	if (times_played == 0) // if played already, you cannot change the initial game funds 
	{
		printf("2. Change initial game funds\n");
		printf("3. Play game\n");
	}
	else
	{
		printf("3. Play again\n");
	}
	printf("4. Exit\n\n");
}

int get_option(void)
{
	int option = 0;

	scanf("%d", &option);

	return option;
}

int menu_select(int times_played)
{
	int option = 0;
	if (times_played != 0) // if you've already played once
	{
		do
		{
			display_menu(times_played);
			option = get_option();
		} while (option != GAME_RULES && option != PLAY && option != EXIT); // do not allow to reinitalize balance
	}
	else // first time playing
	{
		do
		{
			display_menu(times_played);
			option = get_option();
		} while (option < GAME_RULES || option > EXIT); // allow to intialize balance
	}

	return option;
}

void determine_option(int option, double * balance)
{
	
	switch (option)
	{
	case GAME_RULES: // show game rules
		display_rules();
		break;
	case BALANCE: // prompt for balance
		*balance = get_bank_balance();
		break;
	default: // catch all for other values
		break; // last break is not necessary for last case
	}

}

void display_rules(void)
{
	printf("\n***Blackjack Dice Rules***\n");
	printf("\nBlackjack Dice is a two to five multiplayer game that invovles rolling a single six-sided die multiple times,\nwith the objective of obtaining as close to 21 without going over.\n");
	printf("\nDuring your turn, you will roll the die multiple times. Before rolling you will bet a certain amount from your bank, \nwith the default initial amount being $100.00.\n");
	printf("\nEach die roll is added to your total. You can roll the single die as many times as you wish.\n");
	printf("Once you have rolled at least a 16, you may choose to stop rolling if you desire. \nOnce you stop rolling, the next player's turn begins.\n");
	printf("\nIf your total exceeds 21, you automatically lose.\n");
	printf("After all players have gone, your totals will be compared. All players who rolled a 21 earn twice their bet.\n");
	printf("If no player scores 21, then the player closest without going over earns 1.5 times the money he/she bet. \nIf multiple players earn the same high score for the game, and it is not 21, \nthen the players get the money they bet back. All other players lose their bet.\n");
	printf("The game can be played as many times as you wish.\n");
	Sleep(3000);
}

double get_bank_balance(void)
{
	double balance = 0.0;

	printf("\n******New Bank Balance*******\n\n");
	do
	{
		printf("Enter a new initial bank balance for the players: ");
		scanf("%lf", &balance);
	} while (balance < 0);

	return balance;
}

// Game Play Functions

int player_numbers(void)
{
	int num = 0, count = 0;
	do
	{
		if (count != 0) // if count is more than zero that means the user has entered an invalid input
		{
			printf("Please enter a valid integer of 2 through 5.\n\n");
		}
		printf("\nHow many players will be playing? Up to five are allowed.\n");
		scanf("%d", &num);
		++count;
	} while (num > 5 || num < 2);

	return num;
}

void determine_play(int num_play, double *balance1, double *balance2, double *balance3, double *balance4, double *balance5)
{
	int winning_player = 0, 
		sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, winning_sum = 0, 
		count = 0; // used if there's a tie
	double bet1 = 0.0, bet2 = 0.0, bet3 = 0.0, bet4 = 0.0, bet5 = 0.0, payout = 0.0;

	switch (num_play) // number of players
	{
	case 5: // if five players, start here
		sum5 = player_turn(5, balance5, sum5, &bet5); // find their sum (as well as bet)
	case 4: // if four players, start here
		sum4 = player_turn(4, balance4, sum4, &bet4);
		winning_player = finding_winner(sum5, sum4, 5, 4, &winning_sum, &count); // see if player 5 or player 4 had a higher sum
	case 3: // if three,
		sum3 = player_turn(3, balance3, sum3, &bet3);
		winning_player = finding_winner(winning_sum, sum3, winning_player, 3, &winning_sum, &count); // see if player 3 or the previous winner has a higher sum
	case 2: // if two, etc.
		sum2 = player_turn(2, balance2, sum2, &bet2);
		winning_player = finding_winner(winning_sum, sum2, winning_player, 2, &winning_sum, &count);
	case 1:
		sum1 = player_turn(1, balance1, sum1, &bet1);
		winning_player = finding_winner(winning_sum, sum1, winning_player, 1, &winning_sum, &count);
		
		printf("\nCalculating winners...\n");
		Sleep(2000);
		if (winning_sum == 0) // All players rolled over 21 during their turn
		{
			printf("\n\n***********You're All Losers***********\n");
			printf("\nSince all players have gone over 21, each player has been returned their bet.\n\n\n");
			bet1 = bet2 = bet3 = bet4 = bet5 = 0;
		}
		else if (count == 0) // Means the winning sum is not shared by more than one player, meaning one player is the sole winner
			{
				printf("\n\n***********Winners and Losers***********\n");
				switch (num_play)
				{
				case 5:
					pay_out(winning_sum, sum5, 5, bet5, balance5);
				case 4:
					pay_out(winning_sum, sum4, 4, bet4, balance4);
				case 3:
					pay_out(winning_sum, sum3, 3, bet3, balance3);
				case 2:
					pay_out(winning_sum, sum2, 2, bet2, balance2);
				case 1:
					pay_out(winning_sum, sum1, 1, bet1, balance1);
					break;

				}
				printf("\n*\n\n");
			}
		else // This means that count is more than zero, meaning that the winning sum is shared by two players or more
			{
				printf("\n\n***********Winners and Losers***********\n");
				switch (num_play)
				{
				case 5:
					pay_outTie(winning_sum, sum5, 5, bet5, balance5);
				case 4:
					pay_outTie(winning_sum, sum4, 4, bet4, balance4);
				case 3:
					pay_outTie(winning_sum, sum3, 3, bet3, balance3);
				case 2:
					pay_outTie(winning_sum, sum2, 2, bet2, balance2);
				case 1:
					pay_outTie(winning_sum, sum1, 1, bet1, balance1);
					break;
				}
				printf("\n*\n\n");
			}

		break;
	}
}

int player_turn(int player, double* balance, int current_sum, double* bet)
{
	char answer = '\0';
	int die_value = 0, count = 0;
	double bet2 = 0.0;

	do
	{
		if (count != 0)
		{
			printf("\nPlease enter a valid bet!");
		}
		printf("\nPlayer %d, it is your turn. How much do you want to bet?\n", player);
		printf("\n--Player %d's Bank Balance: %.2lf\n\n", player, *balance);
		scanf("%lf", &bet2);
		*bet = bet2;
		++count;
	} while (*bet > * balance || bet < 0); // bet cannot be more than balance, bet cannot be less than zero

	bet_chatter(&*bet, &*balance);

	do
	{
		printf("\nReady to roll your first die? Enter Y for yes: ");
		scanf(" %c", &answer);
	} while (answer != 'y' && answer != 'Y');

	answer = '\0';

	current_sum = rolling_sequence(player, current_sum, answer); // finds the player's sum

	return current_sum;
}

// Die Functions

int roll_die(void)
{
	int die_value = 0;

	die_value = rand() % 6 + 1;

	return die_value;
}

int calculate_sum_dice(int current_sum, int die_value)
{
	current_sum += die_value;

	return current_sum;
}

void rolling(void) 
{
	int die_value1 = 0, die_value2 = 0, die_value3 = 0, die_value4 = 0;

	die_value1 = roll_die();
	die_value2 = roll_die();
	die_value3 = roll_die();
	die_value4 = roll_die();

	printf("\n\nYou rolled a:\n%d", die_value1); // this looks so cool
	Sleep(200);
	printf("\r%d", die_value2);
	Sleep(200);
	printf("\r%d", die_value3);
	Sleep(200);
	printf("\r%d", die_value4);
	Sleep(200);
}

int rolling_sequence(int player, int current_sum, char answer)
{
	int die_value = 0;

	do
	{
		die_value = roll_die(); // find the die value
		rolling(); // do the die "animation"
		printf("\r%d", die_value); // prints the real die value
		printf("!\n"); // and puts a ! for emphasis
		current_sum = calculate_sum_dice(current_sum, die_value); // adds the die to the player's sum
		if (current_sum >= 21) // if the sum is over or equal to 21
		{
			if (current_sum == 21) // if equal, you're golden!
			{
				printf("\nCongrats Player %d, your current sum is 21.\n\n", player);
				answer = 'N';
				Sleep(500);
			}
			else // if more than 21, automatic lose
			{
				printf("\nI'm sorry, but your current sum is %d, which is above 21. You have automatically lost.\n\n", current_sum);
				current_sum = 0;
				answer = 'N';
				Sleep(500);
			}
		}
		else if (current_sum >= 16 && current_sum < 21) // if the sum is between 16 and 20 (when you can stop rolling)
		{
			if (current_sum == 16) // if 16, just say a special phrase vs over 16
			{
				Sleep(500);
				printf("\nPlayer %d's Current Sum: %d", player, current_sum);
				Sleep(800);
				printf("\nSince your current sum is now 16, you have the option to stop rolling.\nDo you want to continue rolling? ");
				scanf(" %c", &answer);
				if (answer == 'n' || answer == 'N')
				{
					printf("\nPlayer %d's final sum is %d.\n\n\n", player, current_sum);
					Sleep(800);
				}
			}
			else
			{
				Sleep(500);
				printf("\nPlayer %d's Current Sum: %d", player, current_sum);
				Sleep(800);
				printf("\nSince your current sum is above 16, you have the option to stop rolling.\nDo you want to continue rolling? ");
				scanf(" %c", &answer);
				if (answer == 'n' || answer == 'N')
				{
					printf("\nPlayer %d's final sum is %d.\n\n\n", player, current_sum);
					Sleep(800);
				}
			}
		}
		else // this means the sum is not at least 16
		{
			Sleep(500);
			printf("\nPlayer %d's Current Sum: %d", player, current_sum);
			Sleep(800);
			printf("\nSince your current sum is not at least 16, you must roll again.\n");
			do
			{
				printf("Ready to roll again? ");
				scanf(" %c", &answer);
			} while (answer != 'y' && answer != 'Y');
		}

	} while (answer != 'N' && answer != 'n'); // keeps you in here until you say you would like to stop rolling ('n'/'N')

	return current_sum;
}

// Winning Functions

int finding_winner(int sum1, int sum2, int player1, int player2, int* win, int* count)
{
	int winner = 0;
	if (sum1 > sum2)
	{
		winner = player1;
		*win = sum1;
	}
	else if (sum1 < sum2)
	{
		winner = player2;
		*win = sum2;
	} // the above finds the highest sum and sets it to the winning_sum variable
	else // however if they are equal
	{
		if (sum1 != 0)
		{
			++* count; // adds one to count, which will then later make pay_outTie run and not pay_out
		}
	}

	return winner;
}

void pay_out(int winning_sum, int sum1, int player1, double bet1, double* balance1)
{
	double payout = 0.0; // We declare this variable so we can print out the payout to the players

	if (sum1 == winning_sum) // If the sum is the winning sum,
	{
		if (sum1 == 21) // and if the sum is 21,
		{
			payout = bet1 * 2; // calculate the payout (2 * their bet)
			*balance1 += payout; // and add their payout to their balance
			printf("\nCongratulations Player %d, you won with a sum of 21. Their payout is %.2lf, based on their bet of %.2lf.\n", player1, payout, bet1); 
		}
		else
		{
			payout = bet1 * 1.5; // calculate the payout (1.5 * their bet because it's not exactly 21)
			*balance1 += payout;
			printf("\nCongratulations Player %d, you won with a sum of %d. Their payout is %.2lf, based on their bet of %.2lf.\n", player1, sum1, payout, bet1);
		}
	}
	else
	{
		*balance1 -= bet1;
		if (sum1 == 0)
		{
			printf("\nPlayer %d has lost with a sum over 21. They have lost their bet of %.2lf.\n", player1, bet1);
		}
		else
		{
			printf("\nPlayer %d has lost with a sum of %d. They have lost their bet of %.2lf.\n", player1, sum1, bet1);
		}
	}
}

void pay_outTie(int winning_sum, int sum1, int player1, double bet1, double* balance1)
{
	double payout = 0.0;

	if (winning_sum == sum1)
	{
		if (sum1 == 21)
		{
			payout = bet1 * 2;
			*balance1 += payout;
			printf("\nOne of the winning players is Player %d, with a sum of 21. Their payout is %.2lf, based on their bet of %.2lf.\n", player1, payout, bet1);
		}
		else
		{
			printf("\nOne of the winning players is Player %d, with a sum of %d. \nSince it is a tie and the winning sum is not 21, Player %d is returned their bet of %.2lf.\n", player1, sum1, player1, bet1);
		}

	}
	else
	{
		*balance1 -= bet1;
		if (sum1 == 0)
		{
			printf("\nPlayer %d has lost with a sum over 21. They have lost their bet of %.2lf.\n", player1, bet1);
		}
		else
		{
			printf("\nPlayer %d has lost with a sum of %d. They have lost their bet of %.2lf.\n", player1, sum1, bet1);
		}
	}
}

// Chatter Functions

void bet_chatter(double * bet, double *balance)
{
	double decimal = 0.0;

	decimal = *bet / *balance;
	if (decimal == 0) // bet nothing
	{
		printf("\nNot confident? Come on, I believe in you!\n");
	}
	else if (decimal > .29 && decimal < .41) // bet between 29 to 41% of their balance
	{
		printf("\nCome on, you can go higher than that!\n");
	}
	else if (decimal > .45 && decimal < .55) // bet between 45 to 55% of their balance
	{
		printf("\nAbout halfway, good idea. You got this!\n");
	}
	else if (decimal == 1) // bet all of their balance
	{
		printf("\nAmazing. I mean the confidence in you is absolutely amazing.\n");
	}
}