/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 2
Date: February 10, 2020
Description: Basic Video Playlist Manager
*/

#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct duration
{
	int hours;
	int minutes;
} Duration;

typedef struct record
{
	char film_title[50];
	char director[50];
	char description[200];
	char genre[50];
	Duration running_time;
	int year;
	int number_times_played;
	int rating; // 1 - 5
} Record;

typedef struct node
{
	Record data;
	struct node* n_node; // next node
	struct node* p_node; // previous node
} Node;


/*
Function: print_menu()
-Description: prints the main menu
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void print_menu(void);

/*
Function: scan_choice()
-Description: takes the user's input
-Input parameters: n/a
-Returns: int (the num the user inputs)
-Preconditions: n/a
-Postconditions: user has entered one number
*/
int scan_choice(void);

/*
Function: insertFront()
-Description: creates a new node and inserts it at the front of the list
-Input parameters: Node ** head_ref 
-Returns: int - 1 if space was allocated and 0 if not
-Preconditions: n/a
-Postconditions: There is now at least one node in the list
*/
int insertFront(Node ** head_ref);

/*
Function: load()
-Description: reads in all of the lines in the file, utilizes insertFront() and creates a Linked List of all of the movies and its attributes in a struct Node
-Input parameters: Node ** head_ref, FILE * movies
-Returns: n/a
-Preconditions: n/a
-Postconditions: all lines have been read in the file
*/
void load(Node** head_ref, FILE* movies);

/*
Function: store()
-Description: stores all Nodes in the Linked List into the file
-Input parameters: Node * head_ref, FILE * movies
-Returns: n/a
-Preconditions: n/a
-Postconditions: movies file has the new entries writte
*/
void store(Node* head_ref, FILE* movies);

/*
Function: display()
-Description: prints out the movies, either all of them, ones with specific directors, or ones with specific years
-Input parameters: Node * head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: movies have been printed out
*/
void display(Node* head_ref);

/*
Function: edit()
-Description: allows user to select a movie based on an entered director and edit each attribute of said movie 
-Input parameters: Node ** head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void edit(Node** head_ref);

/*
Function: rate()
-Description: allows user to enter film title then rate entered movie
-Input parameters: Node ** head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void rate(Node** head_ref);

/*
Function: play()
-Description: prints out each movie starting from the title entered, waits a few seconds, then clears screen
-Input parameters: Node * head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void play(Node* head_ref);

/*
Function: find_title()
-Description: finds the title in the linked list and returns pointer to where that title is
-Input parameters: Node * head_ref, char title[100]
-Returns: Node *
-Preconditions: n/a
-Postconditions: n/a
*/
Node* find_title(Node* head_ref, char title[100]);


#endif HEADER_H

/*
Function:
-Description:
-Input parameters:
-Returns:
-Preconditions:
-Postconditions:
*/