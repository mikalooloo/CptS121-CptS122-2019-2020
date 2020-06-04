/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 2
Date: February 10, 2020
Description: Basic Video Playlist Manager
Hopefully cut down on the amount of comments successfully. I use very descriptive variable and function names, so I hope that also cuts down on the amount of comments needed.
*/

#include "header.h"

int main(void)
{
	Node* head_ref = NULL;
	FILE* movies = NULL;

	int answer = 0;
	char anykey = '\0';

	while (answer != 11)
	{
		print_menu();
		printf("\nWhat do you want to do?: ");
		answer = scan_choice(); 
		system("cls");

		switch (answer)
		{
		case 1: // Load
			movies = fopen("moviePlayList.csv", "r");
			if (!movies)
			{
				printf("Unable to open file for mode read.\n");
			}
			else
			{
				load(&head_ref, movies);
				fclose(movies);
				printf("Movies successfully loaded.\n\n");
			}
			break;
		case 2: // Store
			if (head_ref == NULL)
			{
				printf("Did not store movies into file as there are no movies to store.\n\n");
			}
			else 
			{
				movies = fopen("moviePlayList.csv", "w");
				if (!movies)
				{
					printf("Unable to open file for mode write.\n");
				}
				else
				{
					store(head_ref, movies);
					fclose(movies);
					printf("Movies successfully stored.\n\n");
				}
			}
			break;
		case 3: // Display
			display(head_ref);
			printf("Press any key to move on. ");
			scanf(" %c", &anykey);
			system("cls");
			break;
		case 4: // Insert
			break;
		case 5: // Delete
			break;
		case 6: // Edit
			edit(&head_ref);
			break;
		case 7: // Sort
			break;
		case 8: // Rate
			rate(&head_ref);
			break;
		case 9: // Play
			play(head_ref);
			break;
		case 10: // Shuffle
			break;
		case 11: // Exit
			printf("Exiting...\n\n");
			movies = fopen("moviePlayList.csv", "w");
			if (!movies)
			{
				printf("Unable to open file for mode write.\n");
			}
			else
			{
				if (head_ref == NULL)
				{
					printf("Did not store movies into file as there are no movies to store.\n\n");
				}
				else
				{
					store(head_ref, movies);
					fclose(movies);
					printf("Movies successfully stored.\n\n");
				}
			}
			break;
		default:
			printf("\nPlease input a valid command number!\n");
			break;
		}
	}
}