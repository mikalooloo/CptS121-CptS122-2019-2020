/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 1
Date: January 24, 2020
Description: Analyzes Fitbit Data over 24 hours
*/

#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum sleep
{

	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3

} Sleep; 

typedef struct fitbit
{

	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;

} FitbitData;

/*
Function: isEmpty()
-Description: checks to see if there's an empty or null value in the line of data (determined by two commas in a row or a comma ending the line) and if there is one, inserts an "x" in between the two commas
-Input parameters: char string[100]: the string you want to check for empty values
-Returns: n/a
-Preconditions: there is a string with comma separated values
-Postconditions: there are no more empty or null values in the line
*/
void isEmpty(char string[100]);

/*
Function: readFile_insertStruct()
-Description: reads lines from the file rawData and inserts them into the struct array day_array
-Input parameters: FILE* rawData: the file you are reading from and FitbitData day_array[1442]: the struct array you're putting the data into
-Returns: n/a
-Preconditions: n/a
-Postconditions: all lines from rawData have been read and put properly into the struct array thing
*/
void readFile_insertStruct(FILE* rawData, FitbitData day_array[1442]);

/*
Function: total_calories()
-Description: adds together all the calories from each minute of the day in day_array
-Input parameters: FitbitData day_array[1442]
-Returns: double: the total calories
-Preconditions: there's a whole bunch of calories
-Postconditions: total calories have been calculated ig idk man
*/
double total_calories(FitbitData day_array[1442]);

/*
Function: total_distanceMiles()
-Description: adds together all the distance from each minute of the day in day_array
-Input parameters: FitbitData day_array[1442]
-Returns: double: the total distance
-Preconditions: there's like, a lot of distance
-Postconditions: total distance
*/
double total_distanceMiles(FitbitData day_array[1442]);

/*
Function: total_floors()
-Description: totals up all the floors and returns it
-Input parameters: FitbitData day_array[1442]
-Returns: unsigned int: the total floors
-Preconditions: floors
-Postconditions: total floors
*/
unsigned int total_floors(FitbitData day_array[1442]);

/*
Function: avg_heartRate()
-Description: adds all of the heartrates and divides them by that to return the average
-Input parameters: FitbitData day_array[1442]
-Returns: double: the average heartrate
-Preconditions: heartrate
-Postconditions: average heartrate
*/
double avg_heartRate(FitbitData day_array[1442]);

/*
Function: max_steps()
-Description: finds the total steps (returns through pointer) and max steps
-Input parameters: FitbitData day_array[1442], unsigned int*total_steps
-Returns: unsigned int: the max steps, and *total_steps: the total steps
-Preconditions: steps
-Postconditions: total and max steps
*/
unsigned int max_steps(FitbitData day_array[1442], unsigned int* total_steps);

/*
Function: poorest_sleep()
-Description: finds the range where the highest level of sleep (which means poor sleep)
-Input parameters: FitbitData day_array[1442], int* pStarting_element, int* pEndingelement
-Returns: n/a but through pointers
-Preconditions: sleeplevel at one point is above one at least
-Postconditions: idk
*/
void poorest_sleep(FitbitData day_array[1442], int* pStarting_element, int* pEndingelement);

/*
Function: 
-Description: 
-Input parameters: 
-Returns:
-Preconditions: 
-Postconditions:
*/

#endif HEADER_H