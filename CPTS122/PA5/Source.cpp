/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 5
Date: March 27, 2020
Description: Offbrand Yu Gi Oh! Game
Source.cpp
*/

#include "Header.h"
#include "Player.h"
#include "Queue.h"
#include "Stack.h"
#include "Stats.h"

/*
Function: print_main_menu()
-Description: Prints the main menu options to the console
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void print_main_menu(void)
{
	std::cout << "Mikaela's Offbrand Yu Gi Oh! Game" << std::endl << std::endl;
	std::cout << "Main Menu" << std::endl;
	std::cout << "1. Create Players" << std::endl;
	std::cout << "2. Add Cards to a Player" << std::endl;
	std::cout << "3. Trade Cards with Other Player" << std::endl;
	std::cout << "4. Battle with Other Player" << std::endl;
	std::cout<< "5. Quit" << std::endl << std::endl;
}

