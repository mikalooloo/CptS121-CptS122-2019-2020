/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 6
Date: April 10, 2020
Description: Morse Code Translator
Main file
*/

#include "header.h"
#include "bst.h"

#include <fstream>
using namespace std;

int main(void)
{
	char oneC = '\0';
	string line;
	const BST example;
	
	fstream convert;
	convert.open("Convert.txt", ios::in);

	if (convert.is_open()) // if Convert.txt opened successfully
	{
		while (getline(convert, line)) // reads in the whole line
		{
			for (int i = 0; line[i] != NULL; ++i) // and then finds each character in said line
			{
				oneC = line[i];
				if (oneC != ' ') // if it is not a space, find the letter in the BST
				{
					oneC = toupper(oneC);
					cout << example.lookUp(oneC) << " ";
				}
				else // if it is a space, make it three spaces not just one
				{
					cout << "   ";
				}

			}
			cout << endl; // if there is more than one line, they will be separated by new lines
		}
	}
	else
	{
		cout << "Convert.txt failed to open!" << endl;
	}
}