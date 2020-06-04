/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 3
Date: February 24, 2020
Description: Basic Video Playlist Manager, Additional Commands
*/

#include "header.h"
#include "test.h"

int main(void)
{
	Node* head_ref = NULL;
	FILE* movies = NULL;

	srand(time(NULL));

	int answer = 0;
	char anykey = '\0';

	while (answer != 11) // only exits the program once the user has chosen to exit
	{
		print_menu();
		printf("\nWhat do you want to do?: ");
		answer = scan_choice();
		system("cls");

		switch (answer) // runs what menu option was chosen
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
			insert(&head_ref);
			break;
		case 5: // Delete
			delete(&head_ref);
			break;
		case 6: // Edit
			edit(&head_ref);
			break;
		case 7: // Sort
			printf("*WARNING* Sort does not work entirely... Thought I would turn in what I have for at least some extra credit. *WARNING*\n\n");
			sort(&head_ref);
			break;
		case 8: // Rate
			rate(&head_ref);
			break;
		case 9: // Play
			play(head_ref);
			break;
		case 10: // Shuffle
			shuffle(head_ref);
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
		case 12: // Test
			printf("Test\n\n");
			printf("1. Insert Test\n");
			printf("2. Delete Test\n");
			printf("3. Shuffle Test\n");
			printf("\nPlease pick a test function to perform: ");
			scanf("%d", &answer);
			if (answer < 0 || answer > 3)
			{
				printf("Invalid number.\n\n");
			}
			else
			{	// if the user entered a valid number (1 through 3) then it runs the selected test function
				switch (answer)
				{
				case 1: // Insert Test
					system("cls");
					printf("Test: Insert\n\n");
					insert_test();
					break;
				case 2: // Delete Test
					system("cls");
					printf("Test: Delete\n\n");
					delete_test();
					break;
				case 3: // Shuffle Test
					system("cls");
					shuffle_test();
					break;
				}
			}
			break;
		default: // user did not enter a number between 1 and 12
			printf("\nPlease input a valid command number!\n");
			break;
		}
	}
}