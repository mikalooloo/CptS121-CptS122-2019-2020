/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 5
Date: March 27, 2020
Description: Offbrand Yu Gi Oh! Game
Header.h
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <Windows.h> // for sleep()
#include <time.h> // for rand()

typedef struct namelist
{
	std::string name;		//prefix or suffix;
	int points;				// attack or defense
	struct namelist* next;
	struct namelist* prev;
} NameList;

typedef struct cardstacknode
{
	std::string name;
	int attack;
	int defense;
	std::string type;
	struct cardstacknode* next;
} CardStackNode;

/*
Function: print_main_menu()
-Description: Prints the main menu options to the console
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void print_main_menu(void);

#endif HEADER_H

/*
Function:
-Description:
-Input parameters:
-Returns:
-Preconditions:
-Postconditions:
*/