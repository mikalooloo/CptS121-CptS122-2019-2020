#include "battleship.h"

// ********* Set Up *********

void game_play(FILE * log)
{
	Stats player = { 0, 0, 0, 0.0, 0 }; // the player's stats
	Stats com = { 0, 0, 0, 0.0, 0 }; // the computer's stats

	char player_board[10][10] = { " " }; // the player's own board
	char com_board[10][10] = { " " };
	char com_board_display[10][10] = { " " }; // what the player sees of the computer's board

	char placement = '\0', ans = '\0'; // user-inputted answers

	int player_ships[5] = { 5, 4, 3, 3, 2 }; // keeps track of how many segments of each ship the player has
	int com_ships[5] = { 5, 4, 3, 3, 2 }; // and same with the computer
	int first = 0;

	initialize_game_board(player_board); // initialize the game board
	welcome_screen(); // welcome the player and ask if they want the rules
	initialize_game_board(player_board); // redo that again because we messed with it in the rules
	initialize_game_board(com_board_display); // initialize the two other boards too
	initialize_game_board(com_board);

	printf("\nDo you want to place your ships manually? If no, they will be placed randomly for you.\n");
	printf("Answer: ");
	scanf(" %c", &placement); 

	placement = toupper(placement); // makes capital

	if (placement == 'Y') // If the answer is not Y, then it will be assumed you want it to be placed randomly
	{
		manually_place_ships(player_board);
		randomly_place_ships(com_board);
	}
	else
	{
		randomly_place_ships(player_board);
		randomly_place_ships(com_board);
	}

	first = select_who_starts_first();

	printf("Here is your board:\n\n");
	display_board(player_board);
	printf("\nReady to continue? ");
	scanf(" %c", &ans);
	
	if (first == 0)
	{
		printf("You are the First Player. Here is your opponent's board:\n\n");
		user_turn(com_board, com_board_display, player_ships, &player, log);
	}
	else
	{
		printf("You are the Second Player. Your opponent goes first.\n");
		com_turn(player_board, com_ships, &com, log);
		user_turn(com_board, com_board_display, player_ships, &player, log);
	}

	int winner = 0;

	do
	{
		com_turn(player_board, com_ships, &com, log);
		winner = check_winner(com_ships, &com);
		user_turn(com_board, com_board_display, player_ships, &player, log);
		winner = check_winner(player_ships, &player);
	} while (winner == 0);
	
	output_stats(player, com, log);
}

void welcome_screen(void)
{
	char answer = '\0';
	printf("Welcome to Battleship.\n");

	printf("\nHope you're ready to play, because there's no menu option this time. We're cutting right to the chase.\n");
	printf("Do you need the rules? Enter Y for Yes or N for No: ");
	scanf(" %c", &answer);
	answer = toupper(answer);

	if (answer == 'Y')
	{
		printf("\nGreat!\nIn Battleship, you'll be given 5 ships that need to be placed upon your game board.\n");
		printf("To place your various ships onto the board, you'll be asked to provide cell names of where you want it to be placed.\n");

		printf("\nLet's take the Carrier, for example. The Carrier ship is 5 cells long, which means you'll need to provide 5 cell names.\n");
		printf("I want to place my Carrier on the bottom left, so I'll be entering: A 10 B 10 C 10 D 10 E 10.\n");
		printf("You'll see that I named 5 cells, with the letter and number spaced apart from one another.\n");
		printf("Eventually, I will need to place my Destroyer. The Destroyer is only 2 cells, so I'd only be entering 2 cells.\n");
		printf("Ships may be vertical or horizontal, so as my Carrier was horizontal, I'm going to place my Destroyer vertically. \nThe cells I would enter would be: F 2 F 3.");
		printf("You won't be allowed to overlap your ships or to place them off the board.\n");

		printf("\nAfter placement of the ships, the computer will place theirs as well. Random draw will decide the first player.\n");
		printf("On your turn, you will be shown your opponent's game board and be asked one cell to shoot.\nYou want to shoot your opponent's ships down before yours are shot down.\n");
		printf("As like with placing ships, you'll enter the cell you want, but this time, you will receive news on whether you hit a ship or not.");
		printf("If a ship has been hit, it will turn into a '*'. If the shot missed, it will turn into a 'm'.\n");
		printf("Shot down all of the computer's ships before they shoot down all of yours to win.\n");
	}
	else
	{
		printf("\nSuit yourself. Good luck!\n");
	}
}

void initialize_game_board(char board[][10])
{
	for (int r = 0; r < 10; ++r)
	{
		for (int c = 0; c < 10; ++c)
		{
			board[r][c] = '-'; // defaults every character in the board array to -
		}
	}
}

// Placing Ships

void manually_place_ships(char board[][10])
{
	int col[10] = { 0 };
	int row[10] = { 0 };

	int x = 0, y = 0;

	display_board(board);

	printf("The first ship that needs placed is the Carrier.\nThe Carrier is 5 cells long. Please enter 5 cell names: ");
	enter_ships(CARRIER_SIZE, col, row, board);
	place_ships(board, col, row, CARRIER_SYM);
	display_board(board);
	printf("The second ship that needs placed is the Battleship.\nThe Battleship is 4 cells long. Please enter 4 cell names: ");
	enter_ships(BATTLESHIP_SIZE, col, row, board);
	place_ships(board, col, row, BATTLESHIP_SYM);
	display_board(board);
	printf("The third ship that needs placed is the Cruiser.\nThe Cruiser is 3 cells long. Please enter 3 cell names: ");
	enter_ships(CRUISER_SIZE, col, row, board);
	place_ships(board, col, row, CRUISER_SYM);
	display_board(board);
	printf("The fourth ship that needs placed is the Submarine.\nThe Submarine is 3 cells long. Please enter 3 cell names: ");
	enter_ships(SUBMARINE_SIZE, col, row, board);
	place_ships(board, col, row, SUBMARINE_SYM);
	display_board(board);
	printf("The fifth ship that needs placed is the Destroyer.\nThe Destroyer is 2 cells long. Please enter 2 cell names: ");
	enter_ships(DESTROYER_SIZE, col, row, board);
	place_ships(board, col, row, DESTROYER_SYM);
	display_board(board);
}

void enter_ships(int size, int col[], int row[], char board[][10])
{
	int not_valid_message_flag = 0;

	do
	{
		if (not_valid_message_flag > 0) // if this is more than one then they've already entered something invalid
		{
			printf("Please enter valid coordinates!\n");
			clear_invalid(col, row); // clears the col and row arrays
		}
		for (int i = 0; i < size; ++i)
		{
			enter_coords(col, row); // only allows the amount of coords for the size of the ship

		}
		++not_valid_message_flag;
	} while (is_valid_placement(size, col, row, board) == 0); // if not valid it repeats
}

void place_ships(char board[][10], int col[], int row[], char ship)
{
	for (int r = 0; r < 10; ++r) // Checks all rows
	{
		if (row[r] != 0) // row[r] represents how many ships are in that row. So enter this if there is a ship in that row
		{
			do // do this for all of the ships in this row
			{ 
				for (int c = 0, flag = 0; flag == 0; ++c) // initialize c so it checks each column. the flag is so it stops once we've found a column for the row (this way it won't place ships all along the row unless there's actually that many ship segments)
				{
					if (col[c] != 0) // col[c] represents how many ships are in that column. So enter this if there is a ship in that column
					{
						board[r][c] = ship; // place it in the row and column
						col[c] -= 1; // take away one from the column to show we've placed a ship in that column
						flag = 1; // say we found the column (the flag clears after it exits this)
					}
				}
				row[r] -= 1; // take away one from the row to show we've placed a ship in that row
			} while (row[r] != 0); // if it is still not zero, then repeat for the rest of the ships in the row
		}
	}
}


void enter_coords(int col[], int row[])
{
	char xc = '\0'; // stores the column ('A' through 'J')
	int x = 0, y = 0;

		scanf(" %c %d", &xc, &y);
		xc = toupper(xc); // makes the column letter capital just in case user did not capitalize
		x = column_to_num(xc); // change the column into its appropiate index number
		col[x] += 1; // add one to show there's a ship in column x
		row[y - 1] += 1; // add one to show there's a ship in row y-1 (since the rows appear to be +1 to user, subtract 1 for the index)
}

int is_valid_placement(int size, int col[], int row[], char board[][10])
{
	int valid = 0, count = 0, flag = 0, r1 = 0, c1 = 0;
	int open = 0, starting_row = 0, starting_column = 0;

	for (int r = 0; r < 10; ++r) // check all rows
	{
		if (row[r] == 1) // if a row equals one, then there must be a size-amount of rows that equal one and one of the columns must be equal to size. 
		{
			count += 1; // we will check to see if this equals the size at the end
		}

		if (row[r] == size) // if a row equals the size, then there must be a size-amount of columns that equal one and only this row must be equal to the size
		{
			++flag; // we will check to see if one of the columns equals the size at the end
		}
	}


	for (int c = 0; c < 10; ++c) // now onto checking the columns
	{
		if (flag == 0) // if the flag is zero, it means that the count is equal to ships in one column
		{
			if (col[c] == size) // so we will check for that
			{
				++flag; // if yes, add one to flag. we will then see if this and the count for the rows is equal to size at the end, and if so, make it valid
			}
		}
		else // if the flag is not zero, it means that there was the size of the ship in one row, and that must mean there is one in (number of size) separate columns
		{
			if (col[c] == 1) 
			{
				count += 1; // we will check to see if this equals the size at the end
			}
		}
	}

	if (count == size && flag == 1) // if the count is equal to the size (that means there's 1 in a size-amount of rows/columns) and the flag is equal to one (there is a size-amount in one row/column)
	{
		valid = 1; // then it is valid
	}

	if (board)

	// Now that we know the initial placement is okay, let's make sure it doesn't overlap over other ships

	for (int r = 0; r < 10; ++r)
	{
		for (int c = 0; c < 10; ++c)
		{
			if (row[r] > 0 && col[c] > 0)
			{
				if (board[r][c] == '-')
				{
					++open;
				}
			}
		}
	}

	if (open != size)
	{
		valid = 0;
	}

	return valid;
}


// Randomly Placing Ships

void randomly_place_ships(char board[][10])
{
	randomly_place_ships_func(board, CARRIER_SIZE, CARRIER_SYM);
	randomly_place_ships_func(board, BATTLESHIP_SIZE, BATTLESHIP_SYM);
	randomly_place_ships_func(board, CRUISER_SIZE, CRUISER_SYM);
	randomly_place_ships_func(board, SUBMARINE_SIZE, SUBMARINE_SYM);
	randomly_place_ships_func(board, DESTROYER_SIZE, DESTROYER_SYM);

}

void randomly_place_ships_func(char board[][10], int size, char symbol)
{
	int direction = 0;

	direction = rand() % 2;

	if (direction == 0)
	{
		randomly_place_horizontal(board, size, symbol);
	}
	else
	{
		randomly_place_vertical(board, size, symbol);
	}
}

void randomly_place_horizontal(char board[][10], int size, char symbol)
{

	int starting_column = 0, ending_column = 0, row_num = 0, valid = 0;
	int col[10] = { 0 }, row[10] = { 0 };
	do
		{
		clear_invalid(col, row); // clears it if it was invalid

		row_num = rand() % 9; // randomizes the row for the whole ship to be in

		do
		{
			starting_column = rand() % 9; // finds the starting
			ending_column = starting_column + size - 1; // and ending column
		} while (ending_column > 9 || ending_column < 0); // only allows good values

		for (int c = ending_column; c > starting_column - 1; --c)
		{
			col[c] += 1; // inputs the values into the column array
		}

		row[row_num] = size; // inputs the values into the row array
		valid = is_valid_placement(size, col, row, board); // checks if valid
	} while (valid == 0); // if not repeat

	place_ships(board, col, row, symbol);
}

void randomly_place_vertical(char board[][10], int size, char symbol)
{
	int starting_row = 0, ending_row = 0, col_num = 0, valid = 0; // same as randomly_place_horizontal
	int col[10] = { 0 }, row[10] = { 0 };

	do
	{
		clear_invalid(col, row);
		
		do
		{
			starting_row = rand() % 9;
			ending_row = starting_row + size - 1;
		} while (ending_row > 9 || ending_row < 0);
		
		col_num = rand() % 9;



		for (int r = ending_row; r > starting_row - 1; --r)
		{
			row[r] += 1;
		}

		col[col_num] = size;

		valid = is_valid_placement(size, col, row, board);
	} while (valid == 0);
	place_ships(board, col, row, symbol);
}

// Misc Set Up
int column_to_num(char col)
{
	int num_column = 0;

	num_column = col - 'A';

	return num_column;
}
void clear_invalid(int col[], int row[])
{
	for (int i = 0; i < 10; ++i)
	{
		col[i] = 0;
		row[i] = 0;
	}
}
int select_who_starts_first(void)
{
	int first = rand() % 2;

	return first;
}


// ********* Game Play *********

void user_turn(char com_board[][10], char com_board_display[][10], int ships[], Stats* player, FILE*log)
{
	system("cls");

	char cc = '\0', result = '\0';
	int r = 0, c = 0, sunk = 0, ship_num = 0;
	char ship_name[20] = { '\0' };

	printf("               ***Your Turn***\n");

	printf("\n            ~~Computer's Board~~\n");
	display_board(com_board_display);

	do
	{
		printf("What cell do you want to hit: ");
		scanf(" %c %d", &cc, &r);

		cc = toupper(cc);
		c = column_to_num(cc);
	} while (com_board_display[r-1][c] != '-' || r < 0 || r > 10 || c > 10 || c < 0); // only allows a valid one

	result = check_shot(r - 1, c, com_board, ships, &*player, ship_name, &ship_num); // sees what was hit
	sunk = check_sunk(ships, ship_num); // did it sink a ship?
	update_board(com_board, r - 1, c, result); // update both of the boards
	update_board(com_board_display, r - 1, c, result);

	system("cls");

	printf("\n               ***Your Turn***\n");

	printf("\n      You shot at %c%d. ", cc, r);
	if (result == 'm')
	{
		printf("It was a miss!\n");
	}
	else
	{
		printf("It was a hit!\n");
	}

	printf("\n            ~~Computer's Board~~\n");
	display_board(com_board_display);

	// Printing to log
	output_current_move(r, cc, result, sunk, ship_name, log, 0); 


	char ans = '\0';
	printf("\nReady to move on? ");
	scanf(" %c", &ans);
}

void com_turn(char player_board[][10], int ships[], Stats* com, FILE * log)
{
	system("cls");

	int r = 0, c = 0, sunk = 0, num_ship = 0;
	char ship_name[20] = { '\0' };
	char result = '\0', cc = 'A';

	do
	{
		random_shot(&r, &c);
	} while (player_board[r][c] == 'm' || player_board[r][c] == '*'); // this way it does not hit ones it already has

	result = check_shot(r, c, player_board, ships, &*com, ship_name, &num_ship); // what did it actuall hit?
	sunk = check_sunk(ships, num_ship); // did it sinka  ship?
	update_board(player_board, r, c, result);
	cc = cc + c;

	printf("\n            ***Computer's Turn***\n\n");
	printf("The Computer shot at the cell %c%d. ", cc, r + 1);
	if (result == 'm')
	{
		printf("It was a miss!\n");
	}
	else
	{
		printf("It was a hit!\n");
	}

	printf("\n               ~~Your Board~~\n");
	display_board(player_board);

	// Printing to log
	output_current_move(r, cc, result, sunk, ship_name, log, 1);


	char ans = '\0';
	printf("\nReady to move on? ");
	scanf(" %c", &ans);
}

void random_shot(int* r, int* c)
{
	*r = rand() % 10;
	*c = rand() % 10;
}

// Checks

char check_shot(int r, int c, char board[][10], int ships[], Stats* p, char string[], int *ship_num)
{
	int ship = 0;
	char result = 'm';

	if (board[r][c] != '-') // if it is not -, which means there's a ship
	{
		result = '*'; // show it's been hit
		*ship_num = which_ship(r, c, board, string); // find which ship has been hit
		ships[*ship_num] -= 1; // take away a ship segment from the array
		p->hits += 1; // show that the player has one hit
	}
	else
	{
		p->misses += 1; // if not, then they missed. add one to the player's misses
	}

	p->shots += 1; // overall add one to the player's shots

	return result;
}

int which_ship(int r, int c, char board[][10], char string[])
{
	int shipn = 0;
	char character = '\0';
	character = board[r][c];
	switch (character)
	{
	case 'c':
		strcpy(string, "Carrier");
		break;
	case 'b':
		strcpy(string, "Battleship");
		shipn = 1;
		break;
	case 'r':
		strcpy(string, "Cruiser");
		shipn = 2;
		break;
	case 's':
		strcpy(string, "Submarine");
		shipn = 3;
		break;
	case 'd':
		strcpy(string, "Destroyer");
		shipn= 4;
		break;
	}

	return shipn;
}

int check_sunk(int ships[], int ship)
{
	int sunk = 0;

	if (ships[ship] == 0) // if there is no more ship segments left
	{
		sunk = 1; //then it has sunk
	}

	return sunk;
}

int check_winner(int ships[], Stats* p)
{
	int num = 0, win = 0;
	for (int i = 0; i < 5; ++i)
	{
		if (ships[i] == 0)
		{
			++num; // if all of the ships have no more ship segments
		}
	}

	if (num == 5)
	{
		win = 1; //then someone has won
		p->win += 1;
	}

	return win;
}

// Boards

void update_board(char board[][10], int r, int c, char result)
{
	board[r][c] = result;
}

void display_board(char board[][10]) 
{
	printf("  _________________________________________\n");
	printf("  | A | B | C | D | E | F | G | H | I | J |\n");
	printf("  |---|---|---|---|---|---|---|---|---|---|\n");
	for (int r = 0; r < 9; ++r) // for every row print out each column's value:
	{
		printf(" %d| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", r+1, board[r][0], board[r][1], board[r][2], board[r][3], board[r][4], board[r][5], board[r][6], board[r][7], board[r][8], board[r][9]);
		printf("  |---|---|---|---|---|---|---|---|---|---|\n");
	}
	printf("10| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", board[9][0], board[9][1], board[9][2], board[9][3], board[9][4], board[9][5], board[9][6], board[9][7], board[9][8], board[9][9]); // for ten, the number is two digits instead of 1 so I changed the spacing to make it line up with everything else
	printf("  -----------------------------------------\n");


}

// ********* Output *********

void output_current_move(int r, char c, char shot, int sunk, char ship[], FILE * log, int player)
{
	if (player == 0)
	{
		fprintf(log, "\nPlayer: Shot %c%d. Result: %c\n", c, r, shot);
		if (sunk == 1 && ship != " ")
		{
			fprintf(log, "*** Player has sunk Computer's %s! ***\n", ship);
		} 
	}
	else
	{
		fprintf(log, "\nComputer: Shot %c%d. Result: %c\n", c, r, shot);
		if (sunk == 1)
		{
			fprintf(log, "*** Player has sunk Computer's %s! ***\n", ship);
		}
	}
}

void output_stats(Stats player, Stats com, FILE*log)
{
	printf("player.win = %d", player.win);
	if (player.win == 1)
	{
		fprintf(log, "\n\nThe player has won! Congrats.\n");
	}
	else
	{
		fprintf(log, "\n\nThe computer has won! Sucks to suck.\n");
	}

	fprintf(log, "\n\nPlayer Stats\nNumber Hits: %d\nNumber Misses: %d\nTotal Shots: %d\nHit/Miss Ratio: %.2lf%", player.hits, player.misses, player.shots, ((double)player.hits / player.misses) * 100);
	
	fprintf(log, "\n\nComputer Stats\nNumber Hits: %d\nNumber Misses: %d\nTotal Shots: %d\nHit/Miss Ratio: %.2lf%", com.hits, com.misses, com.shots, ((double)com.hits / com.misses) * 100);
}

