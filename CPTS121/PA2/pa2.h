/*
Name: Mikaela Dean
Date: 9/10/2019
Course: CPTS121 Section 1, Lab Section 16 - WSU Fall Semester 2019

Description: Assignment PA 2 with seven total parts. Due 9/13/2019 at midnight.
- Function declarations
*/

#define _CRT_SECURE_NO_WARNINGS
#define PI 3.1415

#include <stdio.h>
#include <math.h>

/*
Part 1
Function: calculate_series_resistance ()                                      
Date Created: 9/12/2019                                             
Date Last Modified: 9/12/2019                                      
-Description: Adds the three user-inputed resistor values together and prints the result as the series' resistance    
-Input parameters: int r1, int r2, int r3                                    
-Returns: int series_resistance                                          
-Preconditions: User input of r1, r2, and r3                          
-Postconditions: Calculated and printed the series_resistance
*/
int calculate_series_resistance(int r1, int r2, int r3);

/*
Part 2
Function: calculate_total_sales_tax ()
Date Created: 9/12/2019
Date Last Modified: 9/12/2019
-Description: Multiplies the user-inputted tax rate and item cost and prints the result as the total sales tax
-Input parameters: double sales_tax_rate, double item_cost
-Returns: double total_sales_tax
-Preconditions: User input of sales_tax_rate and item_cost
-Postconditions: Calculated and printed total_sales_tax
*/
double calculate_total_sales_tax(double sales_tax_rate, double item_cost);

/*
Part 3
Function: calculate_volume_pyramid ()
Date Created: 9/12/2019
Date Last Modified: 9/12/2019
-Description: Multiplies and then divides by 3 the user-inputed length, width, and height, and prints the result as the pyramid's volume
-Input parameters: double l, double w, double h
-Returns: double volume_pyramid
-Preconditions: User input of l, w, and h
-Postconditions: Calculated and printed volume_pyramid
*/
double calculate_volume_pyramid(double l, double w, double h);

/*
Part 4
Function: calculate_parallel_resistance ()
Date Created: 9/12/2019
Date Last Modified: 9/12/2019
-Description: Calculates the equation with user-inputted values for the 3 resistors and prints the result as the parallel resistance
-Input parameters: int r4, int r5, int r6
-Returns: double parallel_resistance
-Preconditions: User input of r4, r5, and r6
-Postconditions: Calculated and printed total parallel_resistance
*/
double calculate_parallel_resistance(int r4, int r5, int r6);

/*
Part 5
Function: 
Date Created: 9/12/2019
Date Last Modified: 9/12/2019
-Description: Changes the user's character's value by adding and subtracting various values including a self-inputted shift and prints the
			  result as the new encoded character
-Input parameters: char plaintext_character, char shift
-Returns: char encoded_character
-Preconditions: User input of plaintext_character and shift
-Postconditions: Calculated and printed encoded_character
*/
char calculate_encoded_character(char plaintext_character, char shift);

/*
Part 6
Function:
Date Created: 9/12/2019
Date Last Modified: 9/12/2019
-Description: Calculates the equation with user-inputted values for the 2 points (x, y) and prints the result as the distance between the two
-Input parameters: double x1, double x2, double y1, double y2
-Returns: double calculate_distance
-Preconditions: User input of (x1, y1) and (x2, y2)
-Postconditions: Calculated and printed distance
*/
double calculate_distance(double x1, double x2, double y1, double y2);

/*
Part 7
Function:
Date Created: 9/12/2019
Date Last Modified: 9/12/2019
-Description: Calculates the equation with user-inputted values for y, z, x, and a, and prints the result as y
-Input parameters: double y, double z, double x, int a
-Returns: double y
-Preconditions: User input of y, z, x, a
-Postconditions: Calculated and printed a new value for y
*/
double calculate_y(double y, double z, double x, int a);
