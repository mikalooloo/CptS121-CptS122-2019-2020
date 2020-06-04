/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 1
Date: January 24, 2020
Description: Analyzes Fitbit Data over 24 hours
*/

#include "header.h"

int main(void)
{
	FitbitData day_array[1442] = { { 0 } }; 

	FILE* rawData = NULL; // for FitbitData.csv
	FILE* results = NULL; // for Results.csv
	
	double t_cal = 0, avg_hrtR = 0, t_dis = 0; // these are all values to hold
	unsigned int t_flo = 0, m_steps = 0, t_steps = 0; // the totals, averages, etc.
	int sleep_start = 0, sleep_end = 0; // found from doing calculations to the data 
	

	rawData = fopen("FitbitData.csv", "r");

	if (rawData == NULL) // if rawData is still null it's not open
	{
		printf("File did not open correctly. Terminating program...\n");
	}
	else // otherwise it is open so:
	{
		readFile_insertStruct(rawData, day_array); // reads in every line of the file and puts it into the structs
		t_cal = total_calories(day_array); // returns the total calories throughout the day
		t_dis = total_distanceMiles(day_array); // same but for total distance
		t_flo = total_floors(day_array); // total floors
		m_steps = max_steps(day_array, &t_steps); // max steps through return value and total steps through pointer t_steps
		avg_hrtR = avg_heartRate(day_array); // average heartrate
		poorest_sleep(day_array, &sleep_start, &sleep_end); //and range of poorest sleep (returned through pointers sleep_start and sleep_end

		fclose(rawData); // close FitbitData.csv because we are done reading lines in
		results = fopen("Results.csv", "w"); // open Results.csv to print our results found above

		fprintf(results, "Line 1: Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
		fprintf(results, "Line 2: %5lf, %11lf, %8d, %15d, %15lf, %7d, %14s:%s\n", t_cal, t_dis, t_flo, t_steps, avg_hrtR, m_steps, day_array[sleep_start].minute, day_array[sleep_end].minute);

		printf("\nLine 1: Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
		printf("Line 2: %5lf, %11lf, %8d, %15d, %15lf, %7d, %14s:%s\n", t_cal, t_dis, t_flo, t_steps, avg_hrtR, m_steps, day_array[sleep_start].minute, day_array[sleep_end].minute);

		fclose(results); // close Results.csv
	}


	return 0;
}