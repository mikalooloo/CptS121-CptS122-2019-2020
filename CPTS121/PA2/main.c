/*
Name: Mikaela Dean
Date: 9/10/2019
Course: CPTS121 Section 1, Lab Section 16 - WSU Fall Semester 2019

Description: Assignment PA 2 with seven total parts. Due 9/13/2019 at midnight.
- Main code
*/

#include "pa2.h"


int main(void)
{
	int r1 = 0, r2 = 0, r3 = 0, // used in Part 1, each representing resistors
		r4 = 0, r5 = 0, r6 = 0, // used in Part 4, each representing new resistors
		shift = 0, // used in Part 5, shifting the character up or down
		a = 0; // used in Part 7, cannot be even
	double series_resistance = 0, // used in Part 1, representing total resistance
		item_cost = 0, sales_tax_rate = 0, total_sales_tax = 0, // used in Part 2, representing cost of item, tax rate, and total tax
		l = 0, w = 0, h = 0, volume_pyramid = 0, // used in Part 3, with l, w, and h, representing length, width, and height
		parallel_resistance = 0, // used in Part 4, representing parallel resistance
		x1 = 0, x2 = 0, y1 = 0, y2 = 0, distance = 0, // used in Part 6, finding the distance between (x1, y1) and (x2, y2) 
		y = 0, x = 0, z = 0; // used in Part 7, used in the general equation
	char encoded_character = 0, plaintext_character = 0; // used in Part 5, with plaintext as input and encoded as output

	// Part 1 
   // Total series resistance: series_resistance = R1 + R2 + R3, for 3 resistors. R1, R2, and R3 are integers.

	printf("1. Total series resistance\nPlease input the resistance integers for 3 resistors connected in a series: ");
	scanf("%d%d%d", &r1, &r2, &r3);

	series_resistance = calculate_series_resistance(r1, r2, r3);

	// Part 2
	// Sales tax: total_sales_tax = sales_tax_rate * item_cost 
	// (note: it’s OK to show the result beyond the hundredths place, we don’t know how to show to the hundredths place yet)

	printf("\n2. Sales tax\nThank you. Now, please enter the cost of your item and then the tax rate: ");
	scanf("%lf%lf", &item_cost, &sales_tax_rate);

	total_sales_tax = calculate_total_sales_tax(sales_tax_rate, item_cost);

	// Part 3
	// Volume of a right rectangular pyramid: volume_pyramid = (l * w * h) / 3, 
	// where l and w are the length and width of the base, respectively, and h is the height of the pyramid.

	printf("\n3. Volume of a right rectangular pyramid\nThank you. Please enter the length, width, and height of the pyramid: ");
	scanf("%lf%lf%lf", &l, &w, &h);

	volume_pyramid = calculate_volume_pyramid(l, w, h);

	// Part 4
	// Total parallel resistance: parallel_resistance = 1 / (1 / R1 + 1 / R2 + 1 / R3), for 3 resistors. 
	// R1, R2, and R3 are integers. Be sure to prompt for new resistor values for this equation.

	printf("\n4. Total parallel resistance\nFor total parallel resistance, please input 3 new resistors values: ");
	scanf("%d%d%d", &r4, &r5, &r6);

	parallel_resistance = calculate_parallel_resistance(r4, r5, r6);
	
	// Part 5
	// Character encoding: encoded_character = (plaintext_character – 'a') + 'A' - shift; shift is an integer 

	printf("\n5. Character encoding\nPlease input a character and then an integer: ");
	scanf(" %c%d", &plaintext_character, &shift);

	encoded_character = calculate_encoded_character(plaintext_character, shift);

	// Part 6
	// Distance between two points: distance = square root of ((x1 - x2)^2 + (y1 - y2)^2) (note: you will need to use sqrt ( ) out of <math.h>)

	printf("\n6. Distance between two points\nPlease enter the x and y coordinates of your first point: ");
	scanf("%lf%lf", &x1, &y1);

	printf("Please enter the x and y coordinates of your second point: ");
	scanf("%lf%lf", &x2, &y2);

	distance = calculate_distance(x1, x2, y1, y2);

	// Part 7
	// General equation: y = y / (3 / 17) - z + x / (a % 2) + PI
	// (recall: a is an integer; the 3 and 17 constants in the equation should be left as integers initially, 
	// but explicitly type-casted as floating-point values) 

	printf("\n7. General equation\nPlease enter the values for y, z, x, and a: ");
	scanf("%lf%lf%lf%d", &y, &z, &x, &a);

	y = calculate_y(y, z, x, a);

	return 0;
}
