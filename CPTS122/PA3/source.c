/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 3
Date: February 24, 2020
Description: Basic Video Playlist Manager, Additional Commands
*/

#include "header.h"
#include "test.h"

// PA 2

/*
Function: print_menu()
-Description: prints the main menu
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
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
	puts("12. Test");
}

/*
Function: scan_choice()
-Description: takes the user's input
-Input parameters: n/a
-Returns: int (the num the user inputs)
-Preconditions: n/a
-Postconditions: user has entered one number
*/
int scan_choice(void)
{
	int answer = 0;
	scanf("%d", &answer);
	return answer;
}

/*
Function: insertFront()
-Description: creates a new node and inserts it at the front of the list
-Input parameters: Node ** head_ref
-Returns: int - 1 if space was allocated and 0 if not
-Preconditions: n/a
-Postconditions: There is now at least one node in the list
*/
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

/*
Function: load()
-Description: reads in all of the lines in the file, utilizes insertFront() and creates a Linked List of all of the movies and its attributes in a struct Node
-Input parameters: Node ** head_ref, FILE * movies
-Returns: n/a
-Preconditions: n/a
-Postconditions: all lines have been read in the file
*/
void load(Node** head_ref, FILE* movies)
{
	char garbage[200], temp[400];
	int success = 0;

	fgets(garbage, 200, movies); // gets in the first line that says Film Title, Director, etc.
	while (!feof(movies)) // while not at the end of the file
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

/*
Function: store()
-Description: stores all Nodes in the Linked List into the file
-Input parameters: Node * head_ref, FILE * movies
-Returns: n/a
-Preconditions: n/a
-Postconditions: movies file has the new entries writte
*/
void store(Node* head_ref, FILE* movies)
{
	while (head_ref->n_node != NULL)
	{
		head_ref = head_ref->n_node;
	}

	fprintf(movies, "Film Title, Director, Description, Genre, Running Time, Year, Times Played, Rating");

	while (head_ref != NULL)
	{
		if (head_ref->data.running_time.minutes < 10) // prints with the 0 before the minutes
		{
			fprintf(movies, "\n%s,%s,%s,%s,%d:0%d,%d,%d,%d", head_ref->data.film_title, head_ref->data.director, head_ref->data.description, head_ref->data.genre, head_ref->data.running_time.hours, head_ref->data.running_time.minutes, head_ref->data.year, head_ref->data.number_times_played, head_ref->data.rating);
		}
		else
		{
			fprintf(movies, "\n%s,%s,%s,%s,%d:%d,%d,%d,%d", head_ref->data.film_title, head_ref->data.director, head_ref->data.description, head_ref->data.genre, head_ref->data.running_time.hours, head_ref->data.running_time.minutes, head_ref->data.year, head_ref->data.number_times_played, head_ref->data.rating);
		}
		head_ref = head_ref->p_node;
	}
}

/*
Function: display()
-Description: prints out the movies, either all of them, ones with specific directors, or ones with specific years
-Input parameters: Node * head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: movies have been printed out
*/
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

	switch (answer) //if 1, user wants all movies. if 2, only ones that match a director. if 3, ones that match a year
	{
	case 1:
		printf("- All\n\n");
		while (head_ref != NULL)
		{
			printf("%s\n", head_ref->data.film_title);
			printf("-%s\n", head_ref->data.director);
			printf("-%s\n", head_ref->data.description);
			printf("-%s\n", head_ref->data.genre);
			if (head_ref->data.running_time.minutes < 10)
			{
				printf("-%d:0%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
			}
			else
			{
				printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
			}
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
		while (head_ref != NULL) // prints only files with the same director as entered
		{
			if (strcmp(head_ref->data.director, director) == 0)
			{
				++count;
				printf("%s\n", head_ref->data.film_title);
				printf("-%s\n", head_ref->data.director);
				printf("-%s\n", head_ref->data.description);
				printf("-%s\n", head_ref->data.genre);
				if (head_ref->data.running_time.minutes < 10)
				{
					printf("-%d:0%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
				}
				else
				{
					printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
				}
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
			if (head_ref->data.year == year) // prints only records with the same year
			{
				++count;
				printf("%s\n", head_ref->data.film_title);
				printf("-%s\n", head_ref->data.director);
				printf("-%s\n", head_ref->data.description);
				printf("-%s\n", head_ref->data.genre);
				if (head_ref->data.running_time.minutes < 10)
				{
					printf("-%d:0%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
				}
				else
				{
					printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
				}
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

/*
Function: edit()
-Description: allows user to select a movie based on an entered director and edit each attribute of said movie
-Input parameters: Node ** head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
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

	if (count == 0) // there were no directors found
	{
		printf("No directors found under the name \"%s\".\n\n", director);
		return;
	}
	else if (count > 1) // there was more than one director found
	{
		do
		{
			printf("There was more than one record found with the director \"%s\".\nPlease choose one record to edit: ", director);
			scanf("%d", &choose_answer);
			system("cls");
		} while (choose_answer > count || choose_answer < 0); // can only pick a number in the records given

		if (choose_answer != 1)
		{
			count = 0;
			while (count != choose_answer) // finds the correct record based on the number
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

	while (edit_answer != 9) // while it is not 'Exit'
	{
		system("cls");
		printf("Edit\n\n");
		printf("What attribute would you like to edit?\n");
		printf("1. Film Title: %s\n", (*head_ref)->data.film_title);
		printf("2. Director: %s\n", (*head_ref)->data.director);
		printf("3. Description: %s\n", (*head_ref)->data.description);
		printf("4. Genre: %s\n", (*head_ref)->data.genre);
		if ((*head_ref)->data.running_time.minutes < 10)
		{
			printf("5. Running Time: %d:0%d\n", (*head_ref)->data.running_time.hours, (*head_ref)->data.running_time.minutes);
		}
		else
		{
			printf("5. Running Time: %d:%d\n", (*head_ref)->data.running_time.hours, (*head_ref)->data.running_time.minutes);
		}
		printf("6. Year: %d\n", (*head_ref)->data.year);
		printf("7. Number Times Played: %d\n", (*head_ref)->data.number_times_played);
		printf("8. Rating: %d/5\n", (*head_ref)->data.rating);
		printf("9. None. (Exit Edit)\n\n");

		scanf("%d", &edit_answer);
		system("cls");
		printf("Edit\n\n");

		switch (edit_answer) // allows certain editing of the selected file
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

/*
Function: rate()
-Description: allows user to enter film title then rate entered movie
-Input parameters: Node ** head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
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

/*
Function: play()
-Description: prints out each movie starting from the title entered, waits a few seconds, then clears screen
-Input parameters: Node * head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
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
		printf("Play\n\n"); // prints out the node
		printf("%s\n", head_ref->data.film_title);
		printf("-%s\n", head_ref->data.director);
		printf("-%s\n", head_ref->data.description);
		printf("-%s\n", head_ref->data.genre);
		if (head_ref->data.running_time.minutes < 10) // adds the zero if needed
		{
			printf("-%d:0%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
		}
		else
		{
			printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
		}
		printf("-%d\n", head_ref->data.year);
		printf("-%d\n", head_ref->data.number_times_played);
		printf("-%d\n\n", head_ref->data.rating);
		Sleep(3000);
		system("cls");
		head_ref = head_ref->n_node;
	}

	printf("All movies have been played.\n\n");
}

/*
Function: find_title()
-Description: finds the title in the linked list and returns pointer to where that title is
-Input parameters: Node * head_ref, char title[100]
-Returns: Node *
-Preconditions: n/a
-Postconditions: n/a
*/
Node* find_title(Node* head_ref, char title[100])
{
	while (head_ref != NULL)
	{
		if (strcmp(head_ref->data.film_title, title) == 0) // if the title in node is the same as the title entered, we found it
		{
			return head_ref;
		}

		head_ref = head_ref->n_node;
	}

	return NULL;
}

// PA 3

/*
Function: insert()
-Description: inserts a movie into the list
-Input parameters: Node **head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: a new node is in the list
*/
void insert(Node** head_ref)
{
	insertFront(head_ref);

	printf("Insert\n\n");
	printf("For the new movie record, please enter\n");

	printf("Movie Title: ");
	gets((*head_ref)->data.film_title); gets((*head_ref)->data.film_title); fflush(stdin);

	printf("\nDirector: ");
	gets((*head_ref)->data.director); fflush(stdin);

	printf("\nDescription: ");
	gets((*head_ref)->data.description); fflush(stdin);

	printf("\nGenre: ");
	gets((*head_ref)->data.genre); fflush(stdin);

	do
	{
		printf("\nRunning Time, Hours: ");
		scanf("%d", &((*head_ref)->data.running_time.hours));
	} while ((*head_ref)->data.running_time.hours < 0); // can only be positive
	
	do
	{
		printf("\nRunning Time, Minutes: ");
		scanf("%d", &((*head_ref)->data.running_time.minutes));
	} while ((*head_ref)->data.running_time.minutes < 0); // can only be positive

	printf("\nYear: ");
	scanf("%d", &((*head_ref)->data.year));

	do
	{
		printf("\nNumber of Times Played: ");
		scanf("%d", &((*head_ref)->data.number_times_played));
	} while ((*head_ref)->data.number_times_played < 0); // can only be positive

	do
	{
		printf("\nRating (out of 5): ");
		scanf("%d", &((*head_ref)->data.rating));
	} while ((*head_ref)->data.rating > 5 || (*head_ref)->data.rating < 1);  // can only enter 1 through 5

	system("cls");
	printf("\n...Inserted the movie '%s' successfully...\n", (*head_ref)->data.film_title);
}

/*
Function: delete()
-Description: deletes a movie from the list
-Input parameters: Node** head_ref
-Returns: n/a
-Preconditions: there is at least one movie in the list
-Postconditions: a movie has been deleted
*/
void delete(Node** head_ref)
{
	char movie_title[100];
	Node* temp = *head_ref;
	Node* temp2 = NULL;

	printf("Delete\n\n");

	if (*head_ref == NULL)
	{
		printf("List is empty, so nothing can be deleted.\n\n");
		return;
	}

	printf("What movie title do you want to delete from the list? ");
	gets(movie_title); gets(movie_title);

	temp = find_title(temp, movie_title); // returns the placement of said title
	 
	if (temp == NULL) // if it returned NULL there is no movie
	{
		printf("No movie title with the name '%s' to delete.\n\n", movie_title);
	}
	else
	{
		temp2 = temp->p_node;
		if (temp2 != NULL) // if the previous node is not null (it's not at the front of the list)
		{
			temp2->n_node = temp->n_node;
		}
		else // if it is the front of the list update the head ref
		{
			*head_ref = temp->n_node;
		}
		temp2 = temp->n_node;
		if (temp2 != NULL) 
		{
			temp2->p_node = temp->p_node;
		}
		free(temp);
		printf("The movie title with the name '%s' has been deleted from the list successfully.\n", movie_title);
	}
}

/*
Function: shuffle()
-Description: plays the nodes in a random order
-Input parameters: Node * head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void shuffle(Node* head_ref)
{
	int count = -1; // I want to start at 0 for the count, so if there's only 1 movie loaded the count of movies will be 0 not 1
	int copy = 1;

	if (head_ref == NULL) // if empty, leave
	{
		printf("\nThere are no movies loaded to play.\n");
		return;
	}

	Node* prev2 = head_ref;
	while (head_ref != NULL) // counts how many movies are in the list
	{
		++count;
		head_ref = head_ref->n_node;
	}
	head_ref = prev2;

	Shuffle_Num *head_shuffle = (Shuffle_Num*)malloc(sizeof(Shuffle_Num));  // makes the first node
	head_shuffle->pos = 0;													// and labels it node 0
	head_shuffle->prev = NULL;			// initalizing node 0
	Shuffle_Num* temp = NULL;					
	Shuffle_Num* prev = head_shuffle;			
	head_shuffle->next = temp;			// initalizing node 0

	while (copy <= count) // makes a linked list 0 through however many movies are loaded
	{
		temp = (Shuffle_Num*)malloc(sizeof(Shuffle_Num)); 
		temp->pos = copy; // label it what position it is 
		++copy;
		temp->next = NULL; 
		prev->next = temp; // make the previous node point to current node
		temp->prev = prev; 
		prev = temp; // change the previous node to current node
		temp = temp->next; // change the current node to the next node
	}

	temp = head_shuffle; //reset temp and prev
	prev = head_shuffle;

	while (temp != NULL && count != 0) // randomly assigns a number (0 through count of movies) to each node made above
	{
		int rand_num = 0;
		do
		{
			prev = head_shuffle;
			rand_num = rand() % count;
			if (rand() % 2 == 0) // allows rand_num to be 0 and count (if I add 1 it eliminates 0, if I don't add 1 it eliminates the highest num)
			{
				rand_num += 1;
			}

			while (prev->pos != rand_num) // find the position of the number you randomly generated
			{
				prev = prev->next;
			} 

		} while (prev->taken == 1); // so you can tell if that number has been used or not. if so, generate a new one. if not, assign it:

		temp->order = rand_num;
		prev->taken = 1;
		temp = temp->next; // and continue until all positions have been assigned an order number
	}

	if (count == 0)
	{
		head_shuffle->order = 0;
	}

	int dir = 0; // direction 0 is left to right, 1 is right to left
	// reset the following for the next while() loop
	copy = 0;
	temp = head_shuffle;
	prev = head_shuffle;
	prev2 = head_ref;

	while (copy <= count) // prints out all movies in order
	{
		while (temp->order != copy) // while the current position's order is not the current number playing
		{
			if (head_ref != NULL) // if it's not the end of the list
			{
				if (dir == 0) // go left to right 
				{
					prev = temp;
					temp = temp->next;
					prev2 = head_ref;
					head_ref = head_ref->n_node;
				}
				else // or right to left, looking for the current number playing
				{
					prev = temp;
					temp = temp->prev;
					prev2 = head_ref;
					head_ref = head_ref->p_node;
				}
			}
			
			if (head_ref == NULL) // if it is the end of the list
			{
				if (dir == 0) // switch directions
				{
					dir = 1;
					temp = prev;
					head_ref = prev2;
				}
				else
				{
					dir = 0;
					temp = prev;
					head_ref = prev2;
				}
			}
		}
		++copy; // increase the current number playing
		printf("Shuffle\n\n");
		printf("%s\n", head_ref->data.film_title);
		printf("-%s\n", head_ref->data.director);
		printf("-%s\n", head_ref->data.description);
		printf("-%s\n", head_ref->data.genre);
		if (head_ref->data.running_time.minutes < 10)
		{
			printf("-%d:0%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
		}
		else
		{
			printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
		}
		printf("-%d\n", head_ref->data.year);
		printf("-%d\n", head_ref->data.number_times_played);
		printf("-%d\n\n", head_ref->data.rating);
		Sleep(3000);
		system("cls");
	}

	printf("All movies have been played.\n\n");


	// Deleting all of the shuffle_num
	prev = head_shuffle;
	while (head_shuffle != NULL)
	{
		prev = head_shuffle->next;
		free(head_shuffle);
		head_shuffle = prev;
	}
}

/*
Function: sort()
-Description: sorts it by director, movie title, rating, and times played
-Input parameters: Node** head_ref
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void sort(Node** head_ref)
{
	int answer = 0; // what sort they want
	int invalid = 0; // if entered invalid number for what sort

	printf("Sort\n\n");
	printf("Do you want to:\n");
	printf("1. Sort by director (A-Z)\n");
	printf("2. Sort by movie title (A-Z)\n");
	printf("3. Sort by rating (1-5)\n");
	printf("4. Sort by times played (largest-smallest)\n");

	do // only allows a valid number (1 through 4)
	{
		if (invalid != 0)
		{
			printf("\nPlease enter a valid number. ");
		}
		scanf("%d", &answer);
	} while (answer < 1 || answer > 4);

	Node* head = *head_ref;
	Node* current = (*head_ref)->n_node;
	Node* prev = NULL;
	Node* temp = NULL;
	Node* top = *head_ref;
	char head_caps[50] = { '\0' };
	char current_caps[50] = { '\0' };
	char prev_caps[50] = { '\0' };
	int count = 0;

	switch (answer) // sorts based on answer found above (entered by user, 1 through 4)
	{				// decided to do insertion sort \/
	case 1: // Director
		while (current != NULL)
		{
			strcpy(head_caps,head->data.director);
			strcpy(current_caps,current->data.director);
			if (strcmp(_strupr(head_caps), _strupr(current_caps)) > 0) // if str2 is less than str1 (str2 comes before str1)
			{
				if (prev != NULL)
				{
					strcpy(prev_caps, prev->data.director);
					strcpy(current_caps, current->data.director);
					while (strcmp(_strupr(prev_caps), _strupr(current_caps)) > 0) // while str2 is less than str1 (str2 comes before str1)
					{
						if (prev->p_node == NULL)
						{
							break;
						}

						prev = prev->p_node;
					}

					temp = prev;
					prev->n_node = current; // prev -> current
					current->p_node = prev; // prev <- current
					head->n_node = current->n_node;
					current->n_node = head; // current -> next
					head->p_node = current; // current <- next

					prev = current;
					current = head->n_node;
				}
				else
				{
					current->p_node = NULL; //  <- current
					current->n_node = head; // current -> next
					head->p_node = current; // current <- next

					prev = head;
					head = head->n_node;
					current = head->n_node;
				}
			}
			else
			{
				prev = head;
				head = current;
				current = head->n_node;
			}

		}
		break;
	case 2: // Movie Title

		while (current != NULL)
		{
			strcpy(head_caps, head->data.film_title);
			strcpy(current_caps, current->data.film_title);
			if (strcmp(_strupr(head_caps), _strupr(current_caps)) > 0) // if str2 is less than str1 (str2 comes before str1)
			{
				if (prev != NULL)
				{
					strcpy(prev_caps, prev->data.film_title);
					strcpy(current_caps, current->data.film_title);
					while (strcmp(_strupr(prev_caps), _strupr(current_caps)) > 0) // while str2 is less than str1 (str2 comes before str1)
					{
						if (prev->p_node == NULL)
						{
							break;
						}

						prev = prev->p_node;
					}

					if (top == head)
					{
						*head_ref = current;
						top = *head_ref;
					}

					temp = prev;
					prev->n_node = current; // prev -> current
					current->p_node = prev; // prev <- current
					head->n_node = current->n_node;
					if (current->n_node != NULL)
					{
						current->n_node = head; // current -> next
					}
					head->p_node = current; // current <- next

					prev = current;
					current = head->n_node;
				}
				else
				{
					if (top == head)
					{
						*head_ref = current;
						top = *head_ref;
					}
					current->p_node = NULL; // prev <- current
					head->n_node = current->n_node;
					current->n_node = head; // current -> next
					head->p_node = current; // current <- next

					prev = current;
					current = head->n_node;
				}
			}
			else
			{
				prev = head;
				head = current;
				current = head->n_node;
			}

		}


		//while (current != NULL)
		//{
		//	strcpy(head_caps, head->data.film_title);
		//	strcpy(current_caps, current->data.film_title);
		//	if (strcmp(_strupr(head_caps), _strupr(current_caps)) > 0) // if str2 is less than str1 (str2 comes before str1)
		//	{
		//		if (prev != NULL)
		//		{
		//			strcpy(prev_caps, prev->data.film_title);
		//			strcpy(current_caps, current->data.film_title);
		//			while (strcmp(_strupr(prev_caps), _strupr(current_caps)) > 0 && prev->p_node != NULL) // while str2 is less than str1 (str2 comes before str1)
		//			{
		//				++count;
		//				prev = prev->p_node;
		//				strcpy(prev_caps, prev->data.film_title);
		//			}

		//			if (prev->p_node == NULL)
		//			{
		//				*head_ref = current;
		//			}

		//			temp = prev;
		//			if (count > 3)
		//			{
		//				current->n_node = prev->n_node;
		//			}
		//			else
		//			{
		//				current->n_node = head; // current -> next
		//			}
		//			prev->n_node = current; // prev -> current
		//			current->p_node = prev; // prev <- current
		//			head->n_node = current->n_node;

		//			if (count == 0)
		//			{
		//				head->p_node = current; // current <- next
		//			}

		//			count = 0;
		//			prev = head->p_node;
		//			current = head->n_node;
		//		}
		//		else
		//		{
		//			*head_ref = current;
		//			current->p_node = NULL; //  <- current
		//			head->n_node = current->n_node;
		//			temp = head->n_node;
		//			temp->p_node = head;
		//			current->n_node = head; // current -> next
		//			head->p_node = current; // current <- next

		//			prev = current;
		//			if (count == 0)
		//			{
		//				head = current->n_node;
		//			}
		//			count = 0;
		//			current = head->n_node;
		//		}
		//	}
		//	else
		//	{
		//		prev = head;
		//		head = current;
		//		current = head->n_node;
		//	}

		//}

		break;
	case 3: // Rating
		while (current != NULL)
		{
			if (head->data.rating > current->data.rating) // if str2 is less than str1 (str2 comes before str1)
			{
				if (prev != NULL)
				{
					while (prev->data.rating > current->data.rating) // while str2 is less than str1 (str2 comes before str1)
					{
						if (prev->p_node == NULL)
						{
							break;
						}

						prev = prev->p_node;
					}

					if (*head_ref == head)
					{
						*head_ref = current;
					}

					temp = prev;
					prev->n_node = current; // prev -> current
					current->p_node = prev; // prev <- current
					head->n_node = current->n_node;
					current->n_node = head; // current -> next
					head->p_node = current; // current <- next

					prev = current;
					current = head->n_node;
				}
				else
				{
					if (*head_ref == head)
					{
						*head_ref = current;
					}
					current->p_node = NULL; //  <- current
					current->n_node = head; // current -> next
					head->p_node = current; // current <- next

					prev = head;
					head = head->n_node;
					current = head->n_node;
				}
			}
			else
			{
				prev = head;
				head = current;
				current = head->n_node;
			}

		}
		break;
	case 4: // Times Played
		while (current != NULL)
		{
			if (head->data.number_times_played > current->data.number_times_played) // if str2 is less than str1 (str2 comes before str1)
			{
				if (prev != NULL)
				{
					while (prev->data.number_times_played > current->data.number_times_played) // while str2 is less than str1 (str2 comes before str1)
					{
						if (prev->p_node == NULL)
						{
							break;
						}

						prev = prev->p_node;
					}

					if (*head_ref == head)
					{
						*head_ref = current;
					}

					temp = prev;
					prev->n_node = current; // prev -> current
					current->p_node = prev; // prev <- current
					head->n_node = current->n_node;
					current->n_node = head; // current -> next
					head->p_node = current; // current <- next

					prev = current;
					current = head->n_node;
				}
				else
				{
					if (*head_ref == head)
					{
						*head_ref = current;
					}
					current->p_node = NULL; //  <- current
					current->n_node = head; // current -> next
					head->p_node = current; // current <- next

					prev = head;
					head = head->n_node;
					current = head->n_node;
				}
			}
			else
			{
				prev = head;
				head = current;
				current = head->n_node;
			}

		}
		break;
	}
}

// Test PA 3

/*
Function: insert_test()
-Description: tests the insert function
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void insert_test(void)
{
	int failed = 0;

	Node* head_ref = NULL;
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->p_node = NULL;

	if (head_ref == NULL)
	{
		new_node->n_node = NULL;
	}
	else
	{
		new_node->n_node = head_ref;
		head_ref->p_node = new_node;
	}

	head_ref = new_node;

	strcpy((head_ref)->data.film_title, "Bohemian Rhapsody");
	strcpy((head_ref)->data.director, "Bryan Singer"); 
	strcpy((head_ref)->data.description, "Freddie Mercury the lead singer of Queen defies stereotypes and convention to become one of history's most beloved entertainers.");
	strcpy((head_ref)->data.genre, "Drama"); 
	head_ref->data.running_time.hours = 2;
	if (head_ref->data.running_time.hours < 0)
	{
		printf("Running Time, Hours invalid number (%d).\n", head_ref->data.running_time.hours);
		++failed;
	}
	head_ref->data.running_time.minutes = 13;
	if (head_ref->data.running_time.minutes < 0)
	{
		printf("Running Time, Minutes is an invalid number (%d).\n", head_ref->data.running_time.minutes);
		++failed;
	}
	head_ref->data.year = 2018;
	head_ref->data.number_times_played = -1;
	if (head_ref->data.number_times_played < 0)
	{
		printf("Number of Times Played is an invalid number (%d).\n", head_ref->data.number_times_played);
		++failed;
	}
	head_ref->data.rating = 6;
	if (head_ref->data.rating > 5 || head_ref->data.rating < 1)
	{
		printf("Rating is an invalid number (%d).\n", head_ref->data.rating);
		++failed;
	}

	if (failed != 0)
	{
		printf("\nFor reason(s) printed above, the insert of the movie '%s' has failed.\n", head_ref->data.film_title);

		if (new_node->n_node == NULL)
		{
			head_ref = NULL;
			printf("Head pointer has been updated. There are no other items in the list\n\n");
			free(new_node);
		}
		else
		{
			head_ref = new_node->n_node;
			printf("Head pointer has been updated.\n\n");
			free(new_node);
		}
	}

}

/*
Function: delete_test(
-Description: tests the delete function
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void delete_test(void)
{
	Node* head_ref = NULL;
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->p_node = NULL;

	if (head_ref == NULL)
	{
		new_node->n_node = NULL;
	}
	else
	{
		new_node->n_node = head_ref;
		head_ref->p_node = new_node;
	}

	head_ref = new_node;

	strcpy((head_ref)->data.film_title, "Bohemian Rhapsody");
	strcpy((head_ref)->data.director, "Bryan Singer");
	strcpy((head_ref)->data.description, "Freddie Mercury the lead singer of Queen defies stereotypes and convention to become one of history's most beloved entertainers.");
	strcpy((head_ref)->data.genre, "Drama");
	head_ref->data.running_time.hours = 2;
	head_ref->data.running_time.minutes = 13;
	head_ref->data.year = 2018;
	head_ref->data.number_times_played = -1;
	head_ref->data.rating = 6;
	
	if (head_ref == NULL) // isEmpty
	{
		printf("Cannot delete anything from an empty list.\n");
		return;
	}

	if (head_ref->n_node == NULL)
	{
		head_ref = NULL;
		free(new_node);
		printf("Head pointer was updated. No other items in the list, so list is now empty.\n");
	}
	else
	{
		head_ref = head_ref->n_node;
		free(new_node);
		printf("Head pointer was updated to the next item in the list.\n");
	}
}

/*
Function: shuffle_test()
-Description: tests the shuffle function with 3 movies
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void shuffle_test(void)
{
	Node* head_ref = NULL;

	// Movie 1 Insert
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->p_node = NULL;

	if (head_ref == NULL)
	{
		new_node->n_node = NULL;
	}
	else
	{
		new_node->n_node = head_ref;
		head_ref->p_node = new_node;
	}

	head_ref = new_node;

	strcpy((head_ref)->data.film_title, "Bohemian Rhapsody");
	strcpy((head_ref)->data.director, "Bryan Singer");
	strcpy((head_ref)->data.description, "Freddie Mercury the lead singer of Queen defies stereotypes and convention to become one of history's most beloved entertainers.");
	strcpy((head_ref)->data.genre, "Drama");
	head_ref->data.running_time.hours = 2;
	head_ref->data.running_time.minutes = 13;
	head_ref->data.year = 2018;
	head_ref->data.number_times_played = 1;
	head_ref->data.rating = 5;

	// Movie 2 Insert
	Node* new_node2 = (Node*)malloc(sizeof(Node));
	new_node2->p_node = NULL;

	if (head_ref == NULL)
	{
		new_node2->n_node = NULL;
	}
	else
	{
		new_node2->n_node = head_ref;
		head_ref->p_node = new_node2;
	}

	head_ref = new_node2;

	strcpy((head_ref)->data.film_title, "Frozen");
	strcpy((head_ref)->data.director, "Jennifer Lee");
	strcpy((head_ref)->data.description, "When their kingdom becomes trapped in perpetual winter fearless Anna joins forces with mountaineer Kristoffand his reindeer sidekick to find Anna's sister Snow Queen Elsa and break her icy spell.");
	strcpy((head_ref)->data.genre, "Family");
	head_ref->data.running_time.hours = 1;
	head_ref->data.running_time.minutes = 49;
	head_ref->data.year = 2013;
	head_ref->data.number_times_played = 5;
	head_ref->data.rating = 3;

	// Movie 3 Insert
	Node* new_node3 = (Node*)malloc(sizeof(Node));
	new_node3->p_node = NULL;

	if (head_ref == NULL)
	{
		new_node3->n_node = NULL;
	}
	else
	{
		new_node3->n_node = head_ref;
		head_ref->p_node = new_node3;
	}

	head_ref = new_node3;

	strcpy((head_ref)->data.film_title, "Creep");
	strcpy((head_ref)->data.director, "Patrick Kack-Brice");
	strcpy((head_ref)->data.description, "The film follows Aaron a videographer who answers an ad created by Josef.As they get closer together he discovers that his client is not who he was expecting.");
	strcpy((head_ref)->data.genre, "Horror");
	head_ref->data.running_time.hours = 1;
	head_ref->data.running_time.minutes = 22;
	head_ref->data.year = 2014;
	head_ref->data.number_times_played = 2;
	head_ref->data.rating = 4;

	// Shuffle Time

	int count = -1; // I want to start at 0 for the count, so if there's only 1 movie loaded the count of movies will be 0 not 1
	int copy = 1;

	if (head_ref == NULL) // if empty, leave
	{
		printf("\nThere are no movies loaded to play.\n");
		return;
	}

	Node* prev2 = head_ref;
	Node* start = head_ref;
	while (head_ref != NULL) // counts how many movies are in the list
	{
		++count;
		head_ref = head_ref->n_node;
	}
	head_ref = prev2;

	Shuffle_Num* head_shuffle = (Shuffle_Num*)malloc(sizeof(Shuffle_Num));  // makes the first node
	head_shuffle->pos = 0;													// and labels it node 0
	head_shuffle->prev = NULL;			// initalizing node 0
	Shuffle_Num* temp = NULL;
	Shuffle_Num* prev = head_shuffle;
	head_shuffle->next = temp;			// initalizing node 0

	while (copy <= count) // makes a linked list 0 through however many movies are loaded
	{
		temp = (Shuffle_Num*)malloc(sizeof(Shuffle_Num));
		temp->pos = copy; // label it what position it is 
		++copy;
		temp->next = NULL;
		prev->next = temp; // make the previous node point to current node
		temp->prev = prev;
		prev = temp; // change the previous node to current node
		temp = temp->next; // change the current node to the next node
	}

	temp = head_shuffle; //reset temp and prev
	prev = head_shuffle;

	int order1 = 0, order2 = 0, order3 = 0, c = 0; // to store the order numbers
	
	while (temp != NULL && count != 0) // randomly assigns a number (0 through count of movies) to each node made above
	{
		int rand_num = 0;

		do
		{
			prev = head_shuffle;
			rand_num = rand() % count;
			if (rand() % 2 == 0) // allows rand_num to be 0 and count (if I add 1 it eliminates 0, if I don't add 1 it eliminates the highest num)
			{
				rand_num += 1;
			}

			while (prev->pos != rand_num) // find the position of the number you randomly generated
			{
				prev = prev->next;
			}

		} while (prev->taken == 1); // so you can tell if that number has been used or not. if so, generate a new one. if not, assign it:

		temp->order = rand_num;
		prev->taken = 1;
		temp = temp->next; // and continue until all positions have been assigned an order number
		++c;

		if (temp != NULL)
		{
			if (c == 1)
			{
				order3 = rand_num + 1;
			}
			else
			{
				order2 = rand_num + 1;
			}
		}
		else
		{
			order1 = rand_num + 1;
		}
	}

	if (count == 0)
	{
		head_shuffle->order = 0;
	}

	int dir = 0; // direction 0 is left to right, 1 is right to left
	// reset the following for the next while() loop
	copy = 0;
	temp = head_shuffle;
	prev = head_shuffle;
	prev2 = head_ref;

	while (copy <= count) // prints out all movies in order
	{
		while (temp->order != copy) // while the current position's order is not the current number playing
		{
			if (head_ref != NULL) // if it's not the end of the list
			{
				if (dir == 0) // go left to right 
				{
					prev = temp;
					temp = temp->next;
					prev2 = head_ref;
					head_ref = head_ref->n_node;
				}
				else // or right to left, looking for the current number playing
				{
					prev = temp;
					temp = temp->prev;
					prev2 = head_ref;
					head_ref = head_ref->p_node;
				}
			}

			if (head_ref == NULL) // if it is the end of the list
			{
				if (dir == 0) // switch directions
				{
					dir = 1;
					temp = prev;
					head_ref = prev2;
				}
				else
				{
					dir = 0;
					temp = prev;
					head_ref = prev2;
				}
			}
		}
		++copy; // increase the current number playing
		printf("Test: Shuffle\n\n");
		printf("Position: Bohemian Rhapsody, Frozen, Creep\n");
		printf("Order:           %d             %d       %d\n\n", order1, order2, order3);
		printf("%s\n", head_ref->data.film_title);
		printf("-%s\n", head_ref->data.director);
		printf("-%s\n", head_ref->data.description);
		printf("-%s\n", head_ref->data.genre);
		if (head_ref->data.running_time.minutes < 10)
		{
			printf("-%d:0%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
		}
		else
		{
			printf("-%d:%d\n", head_ref->data.running_time.hours, head_ref->data.running_time.minutes);
		}
		printf("-%d\n", head_ref->data.year);
		printf("-%d\n", head_ref->data.number_times_played);
		printf("-%d\n\n", head_ref->data.rating);
		Sleep(3000);
		system("cls");
	}

	printf("All movies have been played.\n\n");


	// Deleting all of the shuffle_num
	prev = head_shuffle;
	while (head_shuffle != NULL)
	{
		prev = head_shuffle->next;
		free(head_shuffle);
		head_shuffle = prev;
	}

	// Deleting all of the nodes
	head_ref = start;
	while (head_ref != NULL)
	{
		start = head_ref->n_node;
		free(head_ref);
		head_ref = start;
	}
}