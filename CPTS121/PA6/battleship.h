#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>

#define CARRIER_SIZE 5
#define BATTLESHIP_SIZE 4
#define CRUISER_SIZE 3
#define SUBMARINE_SIZE 3
#define DESTROYER_SIZE 2

#define CARRIER_SYM 'c'
#define BATTLESHIP_SYM 'b'
#define CRUISER_SYM 'r'
#define SUBMARINE_SYM 's'
#define DESTROYER_SYM 'd'

typedef struct stats
{
	int hits;
	int misses;
	int shots;
	double ratio;
	int win;
} Stats;


// ********* Set Up *********

/*
Function: game_play()
-Description: plays the entire game
-Input parameters: FILE * log
-Returns: n/a
-Preconditions: n/a
-Postconditions: someone has won
*/
void game_play(FILE * log);

/*
Function: welcome_screen()
-Description: tells the rules
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void welcome_screen(void);

/*
Function: initialize_game_board()
-Description: make all of the elements in the board '-'
-Input parameters: char board[][10]
-Returns: n/a
-Preconditions:
-Postconditions:
*/
void initialize_game_board(char board[][10]);

// Placing Ships

/*
Function: manually_place_ships()
-Description: asks the user the coordinates of where they want the ships on the board
-Input parameters: char board[][10]
-Returns: n/a
-Preconditions: player entered y
-Postconditions: all ships have been placed
*/
void manually_place_ships(char board[][10]);

/*
Function: enter_ships()
-Description: enter the coordinates
-Input parameters: int size, int col[], int row[], char board[][10]
-Returns: n/a
-Preconditions: player chose to manually placed ships
-Postconditions: player entered coordinates that work
*/
void enter_ships(int size, int col[], int row[], char board[][10]);

/*
Function: place_ships()
-Description: place the ships on the respective board
-Input parameters: char board[][10], int col[], int row[], char ship
-Returns: n/a
-Preconditions: n/a
-Postconditions: placed ships
*/
void place_ships(char board[][10], int col[], int row[], char ship);

/*
Function: enter_coords()
-Description: scans the coords entered
-Input parameters: int col[], int row[]
-Returns: n/a
-Preconditions: n/a
-Postconditions: entered in a col and row
*/
void enter_coords(int col[], int row[]);

/*
Function: is_valid_placement()
-Description: makes sure the ship is inside the boundaries and isn't overlapping
-Input parameters: int size, int col[], int row[], char board[][10]
-Returns: int (1 if valid, 0 if not)
-Preconditions: n/a
-Postconditions: found if valid or not
*/
int is_valid_placement(int size, int col[], int row[], char board[][10]);

// Randomly Placing Ships

/*
Function: randomly_place_ships()
-Description: places all the ships randomly on the board
-Input parameters: char board[][10]
-Returns: n/a
-Preconditions: n/a
-Postconditions: placed ships
*/
void randomly_place_ships(char board[][10]);

/*
Function: randomly_place_ships_func()
-Description: places one ship randomly, used by randomly_place_ships()
-Input parameters: char board[][10], int size, char symbol
-Returns: n/a
-Preconditions:
-Postconditions: randomly_place_ships() is running
*/
void randomly_place_ships_func(char board[][10], int size, char symbol);

/*
Function: randomly_place_horizontal()
-Description: randomly places a ship horizontally on the board
-Input parameters: char board[][10], int size, char symbol
-Returns: n/a
-Preconditions: int direction in randomly_place_ships_func() is zero
-Postconditions: n/a
*/
void randomly_place_horizontal(char board[][10], int size, char symbol);

/*
Function: randomly_place_vertical()
-Description: randomly places a ship vertically
-Input parameters: char board[][10], int size, char symbol
-Returns: n/a
-Preconditions: int direction in randomly_place_ships_func() is one
-Postconditions: n/a
*/
void randomly_place_vertical(char board[][10], int size, char symbol);

// Misc Set Up

/*
Function: column_to_num()
-Description: changes the character to a num. ah just realized i'm stupid but it's okay. too late it's 9:30 on the day it's due
-Input parameters: char col
-Returns: int (the num)
-Preconditions: n/a
-Postconditions: n/a
*/
int column_to_num(char col);
/*
Function: clear_invalid()
-Description: clears the arrays
-Input parameters: int col[], int row[]
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void clear_invalid(int col[], int row[]);
/*
Function: select_who_starts_first()
-Description: returns zero or one to determine who goes first
-Input parameters: n/a
-Returns: int (zero or one)
-Preconditions: n/a
-Postconditions: n/a
*/
int select_who_starts_first(void);


// ********* Game Play *********

/*
Function: user_turn()
-Description: plays one round for the user
-Input parameters: char com_board[][10], char com_board_display[][10], int ships[], Stats* player, FILE* log
-Returns: n/a
-Preconditions: n/a
-Postconditions: a turn has been done
*/
void user_turn(char com_board[][10], char com_board_display[][10], int ships[], Stats* player, FILE* log);

/*
Function: com_turn()
-Description: same thing as user_turn but for the computer
-Input parameters: player_board[][10], int ships[], Stats* com, FILE* log
-Returns: n/a
-Preconditions: n/a
-Postconditions: turn is over
*/
void com_turn(char player_board[][10], int ships[], Stats* com, FILE* log);

/*
Function: random_shot()
-Description: for the com_turn, finds a random cell name
-Input parameters: int* r, int* c
-Returns: n/a/
-Preconditions: n/a
-Postconditions: n/a
*/
void random_shot(int* r, int* c);

// Checks

/*
Function: check_shot()
-Description: checks what the shot hit in the board
-Input parameters: int r, int c, char board[][10], int ships[], Stats* p, char string[], int* ship_num
-Returns: char ('m' for miss, '*' for hit)
-Preconditions: n/a
-Postconditions: n/a
*/
char check_shot(int r, int c, char board[][10], int ships[], Stats* p, char string[], int* ship_num);

/*
Function: which_ship()
-Description: finds out which ship was hit
-Input parameters: int r, int c, char board[][10], char ship[]
-Returns: int (index of what ship was hit)
-Preconditions: n/a
-Postconditions: n/a
*/
int which_ship(int r, int c, char board[][10], char ship[]);

/*
Function: check_sunk()
-Description: check if the ship has been sunk
-Input parameters: int ships[], int ship
-Returns: int (1 if sunk, 0 if not sunk)
-Preconditions: n/a
-Postconditions: n/a
*/
int check_sunk(int ships[], int ship);

/*
Function: check_winner()
-Description: see if someone won
-Input parameters: int ships[], Stats* p
-Returns: int (1 if winner, 0 if not)
-Preconditions: n/a
-Postconditions: n/a
*/
int check_winner(int ships[], Stats* p);

// Boards

/*
Function: update_board()
-Description: updates a cell on the board
-Input parameters: char board[][10], int r, int c, char result
-Returns: n/a
-Preconditions: an update needs to be made
-Postconditions: update has been done
*/
void update_board(char board[][10], int r, int c, char result);

/*
Function: display_board()
-Description: prints out the board, with columns A through J and rows 1 through 10. fills in the array board[][10]'s characters into board
-Input parameters: char board[][10] (which array do you want printed into the battleship board?)
-Returns: n/a
-Preconditions: n/a
-Postconditions: board has been printed
*/
void display_board(char board[][10]);


// ********* Output *********

/*
Function: output_current_move()
-Description: prints out the current move to battleship.log
-Input parameters: int r, char c, char shot, int sunk, char ship[], FILE* log, int player
-Returns: n/a
-Preconditions: a turn has finished
-Postconditions: printed to file
*/
void output_current_move(int r, char c, char shot, int sunk, char ship[], FILE* log, int player);

/*
Function: output_stats()
-Description: prints the stats to the file
-Input parameters: Stats player, Stats com, FILE* log
-Returns: n/a
-Preconditions: game is over
-Postconditions: printed to file
*/
void output_stats(Stats player, Stats com, FILE* log);

/*
Function:
Date Created:
Date Last Modified:
-Description:
-Input parameters:
-Returns:
-Preconditions:
-Postconditions:
*/