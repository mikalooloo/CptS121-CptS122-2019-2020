/*
Name: Mikaela Dean
Class: CPTS121, Lab Section 16
	WSU Fall Semester 2019
Date: 9/2019

Purpose: PA 3 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

/*
Function: read_double ()
Date Created: 9/18/2019
Date Last Modified: 9/18/2019
-Description: reads a double from a .dat 
-Input parameters: FILE* infile
-Returns: double
-Preconditions: infile is open
-Postconditions: finished reading a double
*/
double read_double(FILE* infile);

/*
Function: read_integer ()
Date Created: 9/18/2019
Date Last Modified: 9/18/2019
-Description: reads an integer a .dat
-Input parameters: FILE* infile
-Returns: int
-Preconditions: infile is open
-Postconditions: finished reading an integer
*/
int read_integer(FILE* infile);

/*
Function: calculate_sum ()
Date Created: 9/20/2019
Date Last Modified: 9/20/2019
-Description: adds together 5 numbers
-Input parameters: five doubles
-Returns: double (the sum of the numbers)
-Preconditions: five numbers are needed
-Postconditions: five numbers have been added
*/
double calculate_sum(double gpa1, double gpa2, double gpa3, double gpa4, double gpa5);

/*
Function: calculate_mean ()
Date Created: 9/20/2019
Date Last Modified: 9/20/2019
-Description: divides the number by 5
-Input parameters: double (a sum)
-Returns: double (the mean of the sum inputted)
-Preconditions: needs sum (from calculate_sum)
-Postconditions: calculated mean
*/
double calculate_mean(double gpa_sum);

/*
Function: calculate_deviation ()
Date Created: 9/23/2019
Date Last Modified: 9/23/2019
-Description: finds the deviation of each number with the mean
-Input parameters: double number, double mean
-Returns: double (deviation of the number)
-Preconditions: needs a number and the mean (from calculate_mean)
-Postconditions: calculated deviation
*/
double calculate_deviation(double number, double mean);

/*
Function: calculate_variance ()
Date Created: 9/23/2019
Date Last Modified: 9/23/2019
-Description: finds the variance from all the deviations (from calculate_deviation)
-Input parameters: five doubles (all deviations)
-Returns: double (variance from all five deviations)
-Preconditions: needs five deviations
-Postconditions: calculated variance
*/
double calculate_variance(double deviation1, double deviation2, double deviation3, double deviation4, double deviation5);

/*
Function: standard_deviation ()
Date Created: 9/23/2019
Date Last Modified: 9/23/2019
-Description: finds the standard deviation from the variance
-Input parameters: double (variance from calculate_variance)
-Returns: double (standard_deviation from the variance)
-Preconditions: needs variance
-Postconditions: calculated standard_deviation
*/
double calculate_standard_deviation(double variance);

/*
Function: find_max ()
Date Created: 9/23/2019
Date Last Modified: 9/23/2019
-Description: finds the max of the five numbers given
-Input parameters: five doubles
-Returns: double (the max of the numbers)
-Preconditions: needs five numbers
-Postconditions: found the max
*/
double find_max(double number1, double number2, double number3, double number4, double number5);

/*
Function: find_in ()
Date Created: 9/23/2019
Date Last Modified: 9/23/2019
-Description: finds the min of the five numbers given
-Input parameters: five doubles
-Returns: double (the min of the numbers)
-Preconditions: needs five numbers
-Postconditions: found the min
*/
double find_min(double number1, double number2, double number3, double number4, double number5);

/*
Function: print_double ()
Date Created: 9/23/2019
Date Last Modified: 9/23/2019
-Description: prints the value into the outfile
-Input parameters: FILE* outfile, double number (number being the one you want printed)
-Returns: void
-Preconditions: outfile is opened in writing
-Postconditions: printed into outfile
*/
void print_double(FILE* outfile, double number);