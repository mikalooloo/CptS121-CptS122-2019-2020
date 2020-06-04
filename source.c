/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 1
Date: January 24, 2020
Description: Analyzes Fitbit Data over 24 hours
*/

#include "header.h"

void isEmpty(char string[100])
{
	int index = 0, // index of the string - to keep track of where empty values are
		comma = 0, // count of the commas - if the count is more than one that means there are commas next to each other, hence, an empty value
		moving_index = 0; // holds the length of the string and is used in moving the values in the string over one for data cleansing

	do // repeats until it has gone through every element of the string passed through
	{
		if (string[index] == ',') // if the current element is a string
		{
			if (comma != 0) // and the previous element was also a string
			{			    // then we are going to move all the elements from this point over to the right one to insert an "x" to show it was			  // empty
				int moving_index = strlen(string); // make moving_index the length
				// shifting forward
				for (; moving_index > index; --moving_index) // stop once the moving_index reaches the index (where we need to insert the "x")
				{
					string[moving_index] = string[moving_index - 1]; // moves the values to the right
				}
				// once the above for loop is done, it is now time to add the "x" to where the empty spot was
				string[moving_index] = 'x';
				++index; // add one to index so it does not start at the same comma again
			}
			++comma; // adds a point to comma, so the program can tell when it has encounted two or more in a row
		}
		else
		{
			comma = 0; // if the current element does not contain a comma, then reset the comma streak
		}
		++index;
	} while (string[index] != '\n'); // continue until it reaches the newline

	if (string[index-1] == ',') // if the last character of the string is a comma
	{
		string[index] = 'x'; // then change it to the 'x' as well because that means even though there isn't two commas next to each other						// there is an empty value at the end
		string[index + 1] = '\0'; // idk if this is needed but i have it
	}
}

void readFile_insertStruct(FILE* rawData, FitbitData day_array[1442])
{
	char string[100] = { " " }; // takes in lines from FitbitData one at a time
	char title[100] = { " " }; // filler string to take in the title
	char* read_data; // holds each sectioned line from string/strtok
	int i_min = 0, i_stat = 0; // i_min stands for the line of data from each minute and i_stat stands for each individual item in the struct for FitbitData

	fgets(title, 100, rawData); // reads in the title

	do // repeat through every line of the file
	{
		fgets(string, 100, rawData); 
		isEmpty(string); // replaces ,, values with x
		read_data = strtok(string, ","); // splits the string, so now this holds the patient ID

		
		if (strcmp(read_data, "12cx7") == 0) // if the patient ID is 12cx7, 
		{
			for (i_stat = 0; i_stat < 8; ++i_stat) // record each line of data in the appropiate section of the struct
			{
				switch (i_stat) // used to correctly read in 
				{
				case 0:
					strcpy(day_array[i_min].patient, read_data); // reads in the patient ID to the struct
					read_data = strtok(NULL, ","); // separates the minute 
					break;
				case 1:
					strcpy(day_array[i_min].minute, read_data); // reads the minute into the struct
					read_data = strtok(NULL, ","); // separates the calories
					break;
				case 2:
					day_array[i_min].calories = atof(read_data); // calories into struct
					read_data = strtok(NULL, ","); // separates distance
					break;
				case 3:
					day_array[i_min].distance = atof(read_data); // distance into struct
					read_data = strtok(NULL, ","); // separates floorsr
					break;
				case 4:
					day_array[i_min].floors = atof(read_data); // floors into struct
					read_data = strtok(NULL, ","); // separates heartrate
					break;
				case 5:
					day_array[i_min].heartRate = atof(read_data); // heartrate into struct
					read_data = strtok(NULL, ","); // separates steps
					break;
				case 6:
					day_array[i_min].steps = atof(read_data); // steps into struct
					read_data = strtok(NULL, ","); // separates sleepLevel
					break;
				case 7:
					day_array[i_min].sleepLevel = atof(read_data); // sleepLevel into struct
					break;
				}
			}
		}
		++i_min; // go to the next min
	} while (i_min < 1442);
}

double total_calories(FitbitData day_array[1442])
{
	double total = 0;

	for (int i = 0; i < 1442; ++i)
	{
		total += day_array[i].calories;
	}

	return total;
}

double total_distanceMiles(FitbitData day_array[1442])
{
	double total = 0;

	for (int i = 0; i < 1442; ++i)
	{
		total += day_array[i].distance;
	}

	return total;
}

unsigned int total_floors(FitbitData day_array[1442])
{
	unsigned int total = 0;

	for (int i = 0; i < 1442; ++i)
	{
		total += day_array[i].floors;
	}

	return total;
}

double avg_heartRate(FitbitData day_array[1442])
{
	double total = 0;
	int minutes = 1442;

	for (int i = 0; i < 1442; ++i)
	{
		if (day_array[i].heartRate != 0) 
		{
			total += day_array[i].heartRate;
		}
		else // if heartrate is zero take out the minutes so it doesn't affect the average
		{
			--minutes;
		}
	}
	total = total / minutes;

	return total;
}

unsigned int max_steps(FitbitData day_array[1442], unsigned int * total_steps)
{
	unsigned int max = 0;

	for (int i = 0; i < 1442; ++i)
	{
		*total_steps += day_array[i].steps; // finds total steps here

		if (day_array[i].steps > max)
		{
			max = day_array[i].steps; // finds max steps at any one minute here
		}
	}

	return max;
}

void poorest_sleep(FitbitData day_array[1442], int * pStarting_element, int * pEnding_element)
{
	*pStarting_element = -1; *pEnding_element = -1; // makes them invalid to start
	int starting_element = -1, max_total = 0, total = 0;

	for (int i = 0; i < 1442; ++i) // for every index of the array
	{
		if (day_array[i].sleepLevel > 1) // if it's over 1 (that means poor sleep)
		{
			if (starting_element == -1) // then check to see if the starting_element is invalid (if it is, this is the start of the range
			{
				starting_element = i; // so make the starting_element the current index
			}
			total += day_array[i].sleepLevel; // and add the sleepLevel to the total to help find the poorest sleep
		}
		else // if it's not over one
		{
			if (starting_element != -1) // check to see if it has reached the end of the range
			{
				if (total > max_total) // if yes, is the total bigger than the max total? (was the range that just passed poorer sleep?)
				{
					max_total = total; // if yes that's the new total and the new range \/
					*pStarting_element = starting_element;
					*pEnding_element = i - 1;
				}
				starting_element = -1; // remake the starting_element invalid
				total = 0; // and reset the total
			}
		}

	}

	if (starting_element != -1) // now this is just cause I realized if the range ends at the last minute, it'll never realize it's the end of the range because it won't ever become under sleepLevel 1
	{
		if (total > max_total) // so if the total is more than the max
		{
			max_total = total; // do the same stuff
			*pStarting_element = starting_element;
			*pEnding_element = 1442-1; // except i is invalid out here so do the same thing it was doing but with what it would've been
		}
		starting_element = -1; // and this is just for funsies I guess
		total = 0;
	}
}