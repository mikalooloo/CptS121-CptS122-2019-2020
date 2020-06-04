/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 2
Date: February 10, 2020
Description: Basic Video Playlist Manager
*/

#include "header.h"

void print_menu(void)
{
	puts("Video Playlist Commands");
	puts("1. Load");
	puts("2. Store");
	puts("3. Display");
	puts("4. Insert");
	puts("5. Delete");
	puts("6. Edit");
	puts("7. Sort");
	puts("8. Rate");
	puts("9. Play");
	puts("10. Shuffle");
	puts("11. Exit");
}

int scan_choice(void)
{
	int answer = 0;
	scanf("%d", &answer);
	return answer;
}

// returns 1 if node was correctly allocated
int insertFront(Node** head_ref)
{
	int result = 1;

	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->p_node = NULL;

	if (*head_ref == NULL)
	{
		new_node->n_node = NULL;
	}
	else
	{
		new_node->n_node = *head_ref;
		(*head_ref)->p_node = new_node;
	}

	*head_ref = new_node;

	if (*head_ref == NULL) // if new_node did not get allocated correctly
	{
		result = 0;
	}
	
	return result;
}

void load(Node** head_ref, FILE* movies)
{
	char garbage[200], temp[400];
	int success = 0;

	fgets(garbage, 200, movies); // gets in the first line that says Film Title, Director, etc.
	while (!feof(movies))
	{
		fgets(temp, 400, movies);
		success = insertFront(head_ref);
		strcpy((*head_ref)->data.film_title, strtok(temp, ","));
		strcpy((*head_ref)->data.director, strtok(NULL, ","));
		strcpy((*head_ref)->data.description, strtok(NULL, ","));
		strcpy((*head_ref)->data.genre, strtok(NULL, ","));
		(*head_ref)->data.running_time.hours = atof(strtok(NULL, ":"));
		(*head_ref)->data.running_time.minutes = atof(strtok(NULL, ","));
		(*head_ref)->data.year = atof(strtok(NULL, ","));
		(*head_ref)->data.number_times_played = atof(strtok(NULL, ","));
		(*head_ref)->data.rating = atof(strtok(NULL, ","));
	}
}

void store(Node* head_ref, FILE* movies)
{
	while (head_ref->n_node != NULL)
	{
		head_ref = head_ref->n_node;
	}
	
	fprintf(movies, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating");

	while (head_ref != NULL)
	{
		fprintf(movies, "\n%s,%s,%s,%s,%d:%d,%d,%d,%d", head_ref->data.film_title, head_ref->data.director, head_ref->data.description, head_ref->data.genre, head_ref->data.running_time.hours, head_ref->data.running_time.minutes, head_ref->data.year, head_ref->data.number_times_played, head_ref->data.rating);
		head_ref = head_ref->p_node;
	}
}

void display(Node* head_ref)
{
	int answer = 0, year = 0, count = 0; char director[100];

	printf("Display\n\n");
	printf("Would you like to:\n1. Print all movies.\n2. Print all records that match a director.\n3. Print all records that match a year.\n");
	scanf("%d", &answer);
	system("cls");
	printf("Display ");

	if (head_ref == NULL)
	{
		printf("\nThere are no movies loaded.\n");
		return;
	}

	switch (answer)
	{
	case 1:
		printf("- All\n\n");
		while (head_ref != NULL)
		{
			printf("%s\n", head_ref->data.film_title);
			printf("-%s\n", head_ref->data.director);
			printf("-%s\n", head_ref->data.description);
			printf("-%s\n", head_ref->data.genre);
			printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
			printf("-%d\n", head_ref->data.year);
			printf("-%d\n", head_ref->data.number_times_played);
			printf("-%d\n\n", head_ref->data.rating);
			head_ref = head_ref->n_node;
		}
		break;
	case 2:
		printf("- Director\n\n");
		printf("What director do you want to search for? ");
		gets(director); gets(director);
		printf("\n");
		while (head_ref != NULL)
		{
			if (strcmp(head_ref->data.director, director) == 0)
			{
				++count;
				printf("%s\n", head_ref->data.film_title);
				printf("-%s\n", head_ref->data.director);
				printf("-%s\n", head_ref->data.description);
				printf("-%s\n", head_ref->data.genre);
				printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
				printf("-%d\n", head_ref->data.year);
				printf("-%d\n", head_ref->data.number_times_played);
				printf("-%d\n\n", head_ref->data.rating);
			}
			head_ref = head_ref->n_node;
		}

		if (count == 0)
		{
			printf("\nNo movies found with director \"%s\".\n\n", director);
		}
		break;
	case 3: 
		printf("- Year\n\n");
		printf("What year do you want to search for? ");
		scanf("%d", &year);
		printf("\n");
		while (head_ref != NULL)
		{
			if (head_ref->data.year == year)
			{
				++count;
				printf("%s\n", head_ref->data.film_title);
				printf("-%s\n", head_ref->data.director);
				printf("-%s\n", head_ref->data.description);
				printf("-%s\n", head_ref->data.genre);
				printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
				printf("-%d\n", head_ref->data.year);
				printf("-%d\n", head_ref->data.number_times_played);
				printf("-%d\n\n", head_ref->data.rating);
			}
			head_ref = head_ref->n_node;
		}

		if (count == 0)
		{
			printf("\nNo movies found with the year \"%d\".\n\n", year);
		}
		break;
	}
}

void edit(Node** head_ref)
{
	int count = 0, choose_answer = 0, edit_answer = 0;  char director[100];
	
	Node* temp = *head_ref;
	Node* first = NULL;
	printf("Edit\n\n");
	printf("To edit a record, please enter its director: ");
	gets(director); gets(director);

	if (*head_ref == NULL)
	{
		printf("There are no movies loaded to edit.\n\n");
		return;
	}

	while (*head_ref != NULL)
	{
		if (strcmp((*head_ref)->data.director, director) == 0)
		{
			++count;
			if (count > 1) // if there's more than one movie with the same director
			{
				printf("%d. %s\n", count, (*head_ref)->data.film_title);
			}
			else
			{
				printf("1. %s\n", (*head_ref)->data.film_title);
				first = *head_ref;
			}
		}
		*head_ref = (*head_ref)->n_node;
	}

	*head_ref = temp;

	if (count == 0)
	{
		printf("No directors found under the name \"%s\".\n\n", director);
		return;
	}
	else if (count > 1)
	{
		do
		{
			printf("There was more than one record found with the director \"%s\".\nPlease choose one record to edit: ", director);
			scanf("%d", &choose_answer);
			system("cls");
		} while (choose_answer > count || choose_answer < 0);

		if (choose_answer != 1)
		{
			count = 0;
			while (count != choose_answer)
			{
				*head_ref = (*head_ref)->n_node;
				if (strcmp((*head_ref)->data.director, director) == 0)
				{
					++count;
				}
			}
		}


	}

	if (choose_answer == 1 || count == 1)
	{
		*head_ref = first; // so it does not make the program have to rego through the entire list again, as we saved the first node found with the entered director
	}

		while (edit_answer != 9)
		{
			system("cls");
			printf("Edit\n\n");
			printf("What attribute would you like to edit?\n");
			printf("1. Film Title: %s\n", (*head_ref)->data.film_title);
			printf("2. Director: %s\n", (*head_ref)->data.director);
			printf("3. Description: %s\n", (*head_ref)->data.description);
			printf("4. Genre: %s\n", (*head_ref)->data.genre);
			printf("5. Running Time: %d:%d\n", (*head_ref)->data.running_time.hours, (*head_ref)->data.running_time.minutes);
			printf("6. Year: %d\n", (*head_ref)->data.year);
			printf("7. Number Times Played: %d\n", (*head_ref)->data.number_times_played);
			printf("8. Rating: %d/5\n", (*head_ref)->data.rating);
			printf("9. None. (Exit Edit)\n\n");

			scanf("%d", &edit_answer);
			system("cls");
			printf("Edit\n\n");

				switch (edit_answer)
				{
				case 1:
					printf("Previous Film Title: %s\n", (*head_ref)->data.film_title);
					printf("Please enter a new film title: ");
					gets((*head_ref)->data.film_title); gets((*head_ref)->data.film_title);
					system("cls");
					break;
				case 2:
					printf("Previous Director: %s\n", (*head_ref)->data.director);
					printf("Please enter a new director: ");
					gets((*head_ref)->data.director); gets((*head_ref)->data.director);
					system("cls");
					break;
				case 3:
					printf("Previous Description: %s\n", (*head_ref)->data.description);
					printf("Please enter a new description: ");
					gets((*head_ref)->data.description); gets((*head_ref)->data.description);
					system("cls");
					break;
				case 4:
					printf("Previous Genre: %s\n", (*head_ref)->data.genre);
					printf("Please enter a new genre: ");
					gets((*head_ref)->data.genre); gets((*head_ref)->data.genre);
					system("cls");
					break;
				case 5:
					printf("Previous Running Time: %d:%d\n", (*head_ref)->data.running_time.hours, (*head_ref)->data.running_time.minutes);
					printf("Please enter a new digit for the hours: ");
					scanf("%d", &((*head_ref)->data.running_time.hours));
					printf("\nand enter a new digit for the minutes: ");
					scanf("%d", &((*head_ref)->data.running_time.minutes));
					system("cls");
					break;
				case 6: 
					printf("Previous Year: %d\n", (*head_ref)->data.year);
					printf("Please enter a new year: ");
					scanf("%d", &((*head_ref)->data.year));
					system("cls");
					break;
				case 7: 
					printf("Previous Number of Times Played: %d\n", (*head_ref)->data.number_times_played);
					printf("Please enter a new number: ");
					scanf("%d", &((*head_ref)->data.number_times_played));
					system("cls");
					break;
				case 8: 
					printf("Previous Rating: %d\n", (*head_ref)->data.rating);
					do
					{
						printf("Please enter a new rating: ");
						scanf("%d", &((*head_ref)->data.rating));
					} while ((*head_ref)->data.rating < 1 || (*head_ref)->data.rating > 5);
					system("cls");
					break;
				case 9: 
					break;
				default:
					printf("That was not a valid number.\n\n");
					break;
				}
				
			}

		*head_ref = temp;
	}

void rate(Node** head_ref)
{
	char film_title[100]; int rating = 0;
	Node* temp = *head_ref;

	printf("Rate\n\n");
	printf("Please enter the title of the film you'd like to rate: ");
	gets(film_title); gets(film_title);

	if (*head_ref == NULL)
	{
		printf("There are no movies loaded to rate.\n\n");
		return;
	}

	*head_ref = find_title(temp, film_title);
	system("cls");
	printf("Rate\n\n");
	if (head_ref == NULL) // if find_title returns NULL it mean it didn't find a movie with that title
	{
		printf("No films found under the name \"%s\".", film_title);
		return;
	}
	printf("You have chosen the movie \"%s\", which has a current rating of %d.", (*head_ref)->data.film_title, (*head_ref)->data.rating);
	do
	{
		printf("\nWhat would you like to change the rating to? ");
		scanf("%d", &rating);
	} while (rating < 1 || rating > 5); // so you cannot change the rating below 1 or above 5
	(*head_ref)->data.rating = rating;

	*head_ref = temp;

	system("cls");
}

void play(Node* head_ref)
{
	char film_title[100];

	printf("Play\n\n");
	printf("What movie do you want to play first: ");
	gets(film_title); gets(film_title);

	if (head_ref == NULL)
	{
		printf("There are no movies to play.\n\n");
		return;
	}

	head_ref = find_title(head_ref, film_title);
	system("cls");

	if (head_ref == NULL)
	{
		printf("No movie was found with the title \"%s\".\n\n", film_title);
		return;
	}

	while (head_ref != NULL)
	{
		printf("Play\n\n");
		printf("%s\n", head_ref->data.film_title);
		printf("-%s\n", head_ref->data.director);
		printf("-%s\n", head_ref->data.description);
		printf("-%s\n", head_ref->data.genre);
		printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
		printf("-%d\n", head_ref->data.year);
		printf("-%d\n", head_ref->data.number_times_played);
		printf("-%d\n\n", head_ref->data.rating);
		Sleep(3000);
		system("cls");
		head_ref = head_ref->n_node;
	}

	printf("All movies have been played.\n\n");
}

Node * find_title(Node* head_ref, char title[100])
{
	while (head_ref != NULL)
	{
		if (strcmp(head_ref->data.film_title, title) == 0)
		{
			return head_ref;
		}

		head_ref = head_ref->n_node;
	}

	return NULL;
}