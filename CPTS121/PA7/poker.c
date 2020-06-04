/* Name: Mikaela Dean
Course: CPTS121, WSU
Date: November 2019

PA 7: Poker
*/

#include "poker.h"

// *** Premade Functions ***

void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], Hand *user, int player)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0; /* card counter */
	int counter = 0; 

	if (player == PLAYER)
	{
		/* deal each of the 8 cards */
		for (card = 1; card <= 8; card++) // puts the first 8 cards in the player struct
		{
			/* loop through rows of wDeck */
			for (row = 0; row <= 3; row++)
			{
				/* loop through columns of wDeck for current row */
				for (column = 0; column <= 12; column++)
				{
					/* if slot contains current card, display card */
					if (wDeck[row][column] == card)
					{
						user->hand[card - 1].face = column;
						user->hand[card - 1].suit = row;
					}
				}
			}
		}
	}
	else // if it's the computer
	{
		/* deal each of the 8 cards */
		for (card = 9; card <= 16; card++, ++counter) // puts the next 8 cards in the computer struct/deck
		{
			/* loop through rows of wDeck */
			for (row = 0; row <= 3; row++)
			{
				/* loop through columns of wDeck for current row */
				for (column = 0; column <= 12; column++)
				{
					/* if slot contains current card, display card */
					if (wDeck[row][column] == card)
					{
						user->hand[counter].face = column;
						user->hand[counter].suit = row;
					}
				}
			}
		}
	}
}

// *** Main Menu ***

void main_menu(void)
{
	printf("Mikaela's Poker\n");
	printf("1. View game rules\n");
	printf("2. Play the game\n");
	printf("3. Exit\n\n");
}

int int_answer(void)
{
	int answer = 0;
	scanf("%d", &answer);
	return answer;
}

void print_rules(void)
{
	char answer = '\0';
	system("cls");
	printf("- You will be dealt 5 cards. You want a good hand.\nThe best result is four-of-a-kind, which is 4 of the same face.\nNext best is flush, 5 of the same suit.\nNext is straight, 5 faces that are in a row.\nNext is three-of-a-kind, 3 of the same face.\nNext is two pairs, two pairs of two cards of the same face (2 4s and 2 6s, for example).\nNext is one pair, two cards of the same face.\nLast is high card, which is where none of the above apply.\nIf you don't have the cards you need, you can redraw up to 3 cards to try and get a higher result.\nReady to go back to the main menu? Enter y for yes.\n");
	scanf(" %c", &answer);
	system("cls");
}

// *** Gameplay ***

void play_game(const char* wFace[], const char* wSuit[])
{
	system("cls");

	/* initalize deck array */
	int deck[4][13] = { 0 };

	Hand player = { { 0 } }, computer = { { 0 } }; // initalizes the decks for player and computer
	int p_array[13] = { 0 }, c_array[13] = { 0 }; // arrays for the faces of the player and computer decks

	shuffle(deck);
	deal(deck, wFace, wSuit, &player, PLAYER); // deals the player's cards
	deal(deck, wFace, wSuit, &computer, COMPUTER); // deals the computer's cards

	int p_hand_num = 0, c_hand_num = 0, c_redraw_num = 0; // the first two variables are what hand result (0 through 6) the player and computer get (high card through four-in-a-row), the c_redraw_num is the computer's number of cards they should redraw
	char answer = '\0';

	num_faces(player, p_array); // numbers the faces of the player's deck in the array
	num_faces(computer, c_array); // does the same for the computer

	c_hand_num = check_check(computer, c_array); // finds what the result of the computer's hand is
	c_redraw_num = evaluate_hand(c_hand_num, c_array); // finds how many cards should be redrawn
	com_redrawing(&computer, c_hand_num, c_array, c_redraw_num); // redraws those
	clear_array(c_array); // cleans up the array of faces
	num_faces(computer, c_array); // fills it up with the new cards
	c_hand_num = check_check(computer, c_array); // finds the new result of the computer's hand

	player_redrawing(&player, wFace, wSuit); // allows the player to redraw
	p_hand_num = check_check(player, p_array); // finds the result of the player's hand

	printf("Here is your new hand:\n");
	printf("1. %s of %s\n", wFace[player.hand[0].face], wSuit[player.hand[0].suit]);
	printf("2. %s of %s\n", wFace[player.hand[1].face], wSuit[player.hand[1].suit]);
	printf("3. %s of %s\n", wFace[player.hand[2].face], wSuit[player.hand[2].suit]);
	printf("4. %s of %s\n", wFace[player.hand[3].face], wSuit[player.hand[3].suit]);
	printf("5. %s of %s\n", wFace[player.hand[4].face], wSuit[player.hand[4].suit]);
	printf("\n");
	compare_hands(c_hand_num, p_hand_num); // compares the hands/results and prints out who won
	printf("\n");
	printf("Here was the computer's hand:\n");
	printf("1. %s of %s\n", wFace[computer.hand[0].face], wSuit[computer.hand[0].suit]);
	printf("2. %s of %s\n", wFace[computer.hand[1].face], wSuit[computer.hand[1].suit]);
	printf("3. %s of %s\n", wFace[computer.hand[2].face], wSuit[computer.hand[2].suit]);
	printf("4. %s of %s\n", wFace[computer.hand[3].face], wSuit[computer.hand[3].suit]);
	printf("5. %s of %s\n", wFace[computer.hand[4].face], wSuit[computer.hand[4].suit]);

	printf("\nReady to move on? ");
	scanf(" %c", &answer);
	system("cls");
}

void num_faces(Hand user, int array[])
{
	for (int i = 0; i < 5; ++i)
	{
		array[user.hand[i].face] += 1; 
	}
}

void player_redrawing(Hand *user, const char* wFace[], const char* wSuit[])
{
	int amount_cards_player = 0, num_card_to_redraw = 0, redrawn_num = 0;

	printf("Here is your hand:\n");
	printf("1. %s of %s\n", wFace[user->hand[0].face], wSuit[user->hand[0].suit]);
	printf("2. %s of %s\n", wFace[user->hand[1].face], wSuit[user->hand[1].suit]);
	printf("3. %s of %s\n", wFace[user->hand[2].face], wSuit[user->hand[2].suit]);
	printf("4. %s of %s\n", wFace[user->hand[3].face], wSuit[user->hand[3].suit]);
	printf("5. %s of %s\n", wFace[user->hand[4].face], wSuit[user->hand[4].suit]);
		
	do
	{
		printf("\nHow many cards do you want to redraw?: ");
		scanf("%d", &amount_cards_player);
	} while (amount_cards_player > 3 || amount_cards_player < 0); // can only redraw 0, 1, 2, or 3 cards

	if (amount_cards_player > 0) // if the player entered zero, it skips the redrawning bit
	{
		do
		{
			do
			{
				printf("\nWhich card do you want to redraw?: ");
				scanf("%d", &num_card_to_redraw);
			} while (num_card_to_redraw > 5 || num_card_to_redraw < 1); // only allows to redraw a card from 1 through 5

			redraw_one_card(&*user, num_card_to_redraw - 1, redrawn_num); // redraws that card
			--amount_cards_player; // takes away one from the amount of cards the player wants to do
			++redrawn_num; // adds one so when the card is redrawn it picks the correct card and doesn't repeat
		} while (amount_cards_player != 0); // once this is zero, player has redrawn all the cards they want to
	} 

	system("cls");
}

void com_redrawing(Hand *user, int hand_num, int array[], int cards_to_redraw)
{
	/* Result Meanings
0 - High Card
1 - One Pair
2 - Two Pairs
3 - Three-of-a-kind
6 - Four-of-a-kind */

	int kicker = 0;

	if (hand_num > 1) // if the result is bigger than a high card or one pair
	{
		kicker = find_kicker(array); // find the smallest card
		array[kicker] -= 1; // get rid of it in the array so if we need to, we can use the find_kicker() function again for the next smallest card
		kicker = which_card_in_hand(kicker, &*user); // find where the kicker card is in hand
		redraw_one_card(&*user, kicker, 0); // redraw said card
		if (cards_to_redraw == 2) // if we need to redraw another one,
		{
			kicker = find_kicker(array);
			array[kicker] -= 1;
			kicker = which_card_in_hand(kicker, &*user);
			redraw_one_card(&*user, kicker, 1);
		}
	}
	else // this means the result is either a high card or one pair
	{
		for (int i = 0; i < 3; ++i) // so we know they need to redraw three times
		{
			kicker = find_kicker(array);
			array[kicker] -= 1;
			kicker = which_card_in_hand(kicker, &*user);
			redraw_one_card(&*user, kicker, i);
		}
	}
	
}

void redraw_one_card(Hand* user, int card, int redrawn_num)
{
	user->hand[card].face = user->hand[5 + redrawn_num].face; // changes the card to one of the three extra cards drawn earlier
	user->hand[card].suit = user->hand[5 + redrawn_num].suit;
}

int which_card_in_hand(int kicker, Hand *user)
{
	int hand_index = -1;

	for (int i = 0; hand_index == -1; ++i)
	{
		if (kicker == user->hand[i].face)
		{
			hand_index = i;
		}
	}

	return hand_index;
}

// *** Checking Hands ***

int check_check(Hand user, int array[])
{
	/* Result Meanings
	   0 - High Card
	   1 - One Pair
	   2 - Two Pairs
	   3 - Three-of-a-kind
	   4 - Straight
	   5 - Flush
	   6 - Four-of-a-kind */
	int result = 0, of_a_kind;

	of_a_kind = check_of_a_kind(array); // is it a three or four of a kind?

	if (of_a_kind != 6) // if it's a four of a kind, skip this
	{
		result = check_flush(user); // otherwise, is it a flush?
		if (result != 5) // if it isn't,
		{
			result = check_straight(array); // is it a straight?
			if (result != 4) // if it isn't,
			{
				result = of_a_kind;
				if (result != 3) // are there any pairs?
				{
					result = check_pair(array, of_a_kind);
				}
			}
		}
	}

	if (of_a_kind != 0 && result == 0) // makes sure that it correctly displays three of a kind
	{
		result = of_a_kind;
	}

	return result;
}

int check_pair(int array[], int of_a_kind)
{
	int pair = 0; // pair is false
	int flag = 0;

	for (int i = 0; i < 13; ++i)
	{
		if (array[i] > 1)
		{
			if (pair == 1)
			{
				flag = 1;
			}

			pair = 1; // there is a pair!
		}
	}

	if (flag == 1 && of_a_kind == 0)
	{
		pair = 2; // there are two pairs!
	}

	return pair; // if it returns 1, there is 1 pair, if it returns 2, there are two pairs
}

int check_of_a_kind(int array[])
{
	int kind = 0; // three-of-a-kind is 3, four-of-a-kind is 6

	for (int i = 0; i < 13; ++i)
	{
		if (array[i] == 3)
		{
			kind = 3;
		}
		else if (array[i] == 4)
		{
			kind = 6;
		}
	}

	return kind; // returns 3 for three-of-a-kind, 6 for four-of-a-kind, 0 for neither
}

int check_flush(Hand user)
{
	int flush = 0; // 0 is no flush, 5 is flush

	int suit_array[5] = { 0 };

	for (int i = 0; i < 5; ++i)
	{
		suit_array[user.hand[i].suit] += 1;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (suit_array[i] == 5) 
		{
			flush = 5;
		}
	}

	return flush; // returns 5 for flush, 0 for none
}

int check_straight(int array[])
{
	int straight = 0;

	for (int i = 0; i < 13 && straight == 0; ++i)
	{
		if (array[i] == 1)
		{
			straight = check_straight_array(&array[i]); // puts the address of the 1 in the array so we can see if the next 4 are also 1s
		}
	}

	return straight; // returns 0 if there is no straight, 4 if there is
}

int check_straight_array(int array[])
{
	int straight = 0;
	
	for (int i = 0; i < 5; ++i)
	{
		if (array[i] == 1) // if each one equals one in a row, straight should equal 5
		{
			++straight; 
		}
	}

	if (straight == 5) // so if there is 5 ones in a row, we will confirm there is a straight
	{
		straight = 4;
	}
	else
	{
		straight = 0;
	}

	return straight; // returns 0 if no straight, 4 if there is a straight
}

int find_kicker(int array[])
{
	int lowest_kicker = -1;

	for (int i = 1; i < 13 && lowest_kicker == -1; ++i)
	{
		if (array[i] == 1)
		{
			lowest_kicker = i;
		}
	}

	return lowest_kicker;
}

// *** Dealer ***

int evaluate_hand(int hand_num, int array[])
{
	int cards_to_redraw = 0, kicker = 0;

	switch (hand_num)
	{
	case 6: //four-of-a-kind
		if ((find_kicker(array) / (double)6) <= 1) // if the lowest card is 6 or lower, redraw
		{
			cards_to_redraw = 1;
		}
		break;
	case 5: //flush
		cards_to_redraw = 0; //do not redraw any cards
		break;
	case 4: //straight
		cards_to_redraw = 0; //do not redraw any cards
		break;
	case 3: //three-of-a-kind
		kicker = find_kicker(array);
		if (kicker / (double)6 <= 1) // if the lowest card is 6 or lower, redraw
		{
			cards_to_redraw = 1;
			array[kicker] -= 1;
			if ((find_kicker(array) / 6) <= 1) // if the next lowest card is 6 or lower, redraw it too
			{
				cards_to_redraw = 2;
				array[kicker] += 1;
			}
		}
		else
		{
			cards_to_redraw = 0;
		}
		break;
	case 2: //two pairs
		cards_to_redraw = 1;
		break;
	case 1: //one pair
		cards_to_redraw = 3;
		break;
	case 0: //high card
		cards_to_redraw = 3;
		break;
	}

	return cards_to_redraw;
}

// *** Misc ***

void clear_array(int array[])
{
	for (int i = 0; i < 13; ++i)
	{
		array[i] = 0;
	}
}

// *** Winning ***

void compare_hands(int c_hand_num, int p_hand_num)
{
	/* Result Meanings
	 0 - High Card
	 1 - One Pair
	 2 - Two Pairs
	 3 - Three-of-a-kind
	 4 - Straight
	 5 - Flush
	 6 - Four-of-a-kind */
	char results[7][30] = { { "High Card" }, { "One Pair"}, {"Two Pairs"}, {"Three-of-a-kind"}, {"Straight"}, {"Flush"}, {"Four-of-a-kind"} };

	if (c_hand_num > p_hand_num)
	{
		printf("****WINNER****\nThe computer wins! %s > %s\n", results[c_hand_num], results[p_hand_num]);
	}
	else if (p_hand_num > c_hand_num)
	{
		printf("****WINNER****\nThe player wins! %s < %s\n", results[c_hand_num], results[p_hand_num]);
	}
	else
	{
		printf("****WINNER****\nIt was a tie! %s = %s\n", results[c_hand_num], results[p_hand_num]);
	}
}

// did not give myself enough time to figure out ties,
// and I was making it way too complicated than it should've been, 
// but I don't have the mental capacity rn honestly to think about it more rationally
// so I'm just gonna leave this here for now and maybe finish it later 
// ||
// ||
// \/


//int compare_hands(int c_hand_num, int p_hand_num, int c_array[], int p_array[])
//{
//	int c_kicker = 0, p_kicker = 0, c_highest = 0, p_highest = 0;
//	int counter = 5;
//
//	if (c_hand_num > p_hand_num)
//	{
//		printf("The computer wins!\n");
//	}
//	else if (p_hand_num > c_hand_num)
//	{
//		printf("The player wins!\n");
//	}
//	else
//	{
//		/* Result Meanings
//   0 - High Card
//   1 - One Pair
//   2 - Two Pairs
//   3 - Three-of-a-kind
//   4 - Straight
//   5 - Flush
//   6 - Four-of-a-kind */
//		switch (c_hand_num)
//		{
//		case 6:
//			c_highest = find_highest(c_array);
//			p_highest = find_highest(p_array);
//			if (c_highest == p_highest)
//			{
//				c_kicker = find_kicker(c_array);
//				p_kicker = find_kicker(p_array);
//				if (c_kicker > p_kicker)
//					{
//						printf("The computer wins! Both had the same four-of-a-kind, but computer had a higher kicker.\n");
//					}
//				else if (p_kicker > c_kicker)
//					{
//						printf("The player wins! Both had the same four-of-a-kind, but player had a higher kicker.\n");
//					}
//				else
//					{
//						printf("Tie! Both had the same four-of-a-kind and same kicker.\n");
//					}
//			}
//			else
//			{
//				if (c_kicker > p_kicker)
//				{
//					printf("The computer wins! Both had four-of-a-kind, but computer had a higher one.\n");
//				}
//				else
//				{
//					printf("The player wins! Both had four-of-a-kind, but player had a higher one.\n");
//				}
//			}
//
//			break;
//		case 5:
//			do
//			{
//				c_highest = find_highest(c_array);
//				c_array[c_highest] -= 1;
//				p_highest = find_highest(p_array);
//				p_array[p_highest] -= 1;
//				--counter;
//			} while (counter != 0 && (c_highest == p_highest));
//
//			if (c_highest > p_highest)
//			{
//				printf("The computer wins! Both had flush, but computer had a higher-ranking card.\n");
//			}
//			else if (p_highest > c_highest)
//			{
//				printf("The player wins! Both had flush, but player had a higher-ranking card.\n");
//			}
//			else
//			{
//				printf("Tie! Both had flush and an identical flush, wtf");
//			}
//			break;
//		case 4:
//			do
//			{
//				c_highest = find_highest(c_array);
//				c_array[c_highest] -= 1;
//				p_highest = find_highest(p_array);
//				p_array[p_highest] -= 1;
//				--counter;
//			} while (counter != 0 && (c_highest == p_highest));
//
//			if (c_highest > p_highest)
//			{
//				printf("The computer wins! Both had straight, but computer had a higher-ranking card.\n");
//			}
//			else if (p_highest > c_highest)
//			{
//				printf("The player wins! Both had straight, but player had a higher-ranking card.\n");
//			}
//			else
//			{
//				printf("Tie! Both had the same exact straight.\n");
//			}
//			break;
//		case 3:
//			c_highest = find_highest(c_array);
//			p_highest = find_highest(p_array);
//			if (c_highest == p_highest)
//			{
//				c_array[c_highest] -= 1;
//				p_array[p_highest] -= 1;
//
//				c_highest = find_highest(c_array);
//				p_highest = find_highest(p_array);
//				if (c_kicker > p_kicker)
//				{
//					printf("The computer wins! Both had the same three-of-a-kind, but computer had a higher kicker.\n");
//				}
//				else if (p_kicker > c_kicker)
//				{
//					printf("The player wins! Both had the same three-of-a-kind, but player had a higher kicker.\n");
//				}
//				else
//				{
//					printf("Tie! Both had same three-of-a-kind with the same two kickers.\n");
//				}
//			}
//			if (c_highest > p_highest)
//			{
//				printf("The computer wins! Both had four-of-a-kind, but computer had a higher one.\n");
//			}
//			else
//			{
//				printf("The player wins! Both had four-of-a-kind, but player had a higher one.\n");
//			}
//			break;
//		case 2:
//			c_highest = find_highest(c_array);
//			p_highest = find_highest(p_array);
//			if (c_highest == p_highest)
//			{
//				c_array[c_highest] -= 1;
//				p_array[p_highest] -= 1;
//				c_highest = find_highest(c_array);
//				p_highest = find_highest(p_array);
//				if (c_highest == p_highest)
//				{
//					c_kicker = find_kicker(c_array);
//					p_kicker = find_kicker(p_array);
//					if (c_kicker == p_kicker)
//					{
//						printf("Tie! same exact two pairs and kicker\n");
//					}
//					else if (c_kicker > p_kicker)
//					{
//						printf("Computer wins. Same two pairs, but computer has a higher kicker\n");
//					}
//					else
//					{
//						printf("Player wins. Same two pairs, but player has a higher kicker\n");
//					}
//				}
//				else if (c_highest > p_highest)
//				{
//
//				}
//			}
//
//			break;
//		case 1:
//			break;
//		case 0:
//			break;
//		}
//	}
//}