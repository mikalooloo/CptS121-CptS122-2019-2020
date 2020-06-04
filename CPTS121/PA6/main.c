#include "battleship.h"

int main(void)
{
	srand(time(NULL));
	
	FILE* log = NULL;
	log = fopen("battleship.log", "w");

	if (log == NULL)
	{
		printf("File could not open correctly. Quitting...\n");
	}
	else 
	{
		game_play(log);
		printf("\nThank you for playing.\n");
	}

	fclose(log);
}