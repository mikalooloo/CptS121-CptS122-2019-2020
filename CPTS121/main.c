/*
Name: Mikaela Dean
Date: 9/3/2019
Course: CPTS121 Section 1, Lab Section 16 - WSU Fall Semester 2019

Description: Assignment PA 1 with seven total parts. Due 9/6/2019 at midnight.

*/

#define _CRT_SECURE_NO_WARNINGS
#define PI 3.1415

#include <stdio.h>
#include <math.h>

int main(void)
{
	int r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0, shift = 0, a = 0;
	double series_resistance = 0, item_cost = 0, sales_tax_rate = 0, total_sales_tax = 0, l = 0, w = 0, h = 0, volume_pyramid = 0,
		parallel_resistance = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, distance = 0, y = 0, x= 0, z = 0;
	char encoded_character = 0, plaintext_character = 0;

 // Part 1 
// Total series resistance: series_resistance = R1 + R2 + R3, for 3 resistors. R1, R2, and R3 are integers.

	printf("1. Total series resistance\nPlease input the resistance integers for 3 resistors connected in a series: ");
	scanf("%d%d%d", &r1, &r2, &r3);

	series_resistance = r1 + r2 + r3;

	printf("The series resistance is: \nR1 + R2 + R3 = %d + %d + %d = %.2lf.\n", r1, r2, r3, series_resistance);

// Part 2
// Sales tax: total_sales_tax = sales_tax_rate * item_cost 
// (note: it’s OK to show the result beyond the hundredths place, we don’t know how to show to the hundredths place yet)

	printf("\n2. Sales tax\nThank you. Now, please enter the cost of your item and then the tax rate: ");
	scanf("%lf%lf", &item_cost, &sales_tax_rate);

	total_sales_tax = sales_tax_rate * item_cost;

	printf("The total sales tax for your item is: \nTax Rate * Item's Cost = $%.2lf * $%.2lf = $%.2lf.\n", sales_tax_rate, item_cost, total_sales_tax);

// Part 3
// Volume of a right rectangular pyramid: volume_pyramid = (l * w * h) / 3, 
// where l and w are the length and width of the base, respectively, and h is the height of the pyramid.

	printf("\n3. Volume of a right rectangular pyramid\nThank you. Please enter the length, width, and height of the pyramid: ");
	scanf("%lf%lf%lf", &l, &w, &h);

	volume_pyramid = (l * w * h) / 3;

	printf("The volume of your pyramid is: \n(l * w * h) / 3 = (%.1lf * %.1lf * %.1lf) / 3 = %.1lf\n", l, w, h, volume_pyramid); 

// Part 4
// Total parallel resistance: parallel_resistance = 1 / (1 / R1 + 1 / R2 + 1 / R3), for 3 resistors. 
// R1, R2, and R3 are integers. Be sure to prompt for new resistor values for this equation.

	printf("\n4. Total parallel resistance\nFor total parallel resistance, please input 3 new resistors values: ");
	scanf("%d%d%d", &r4, &r5, &r6);
		
	parallel_resistance = 1 / (1 / (double)r4 + 1 / (double)r5 + 1 / (double)r6);
	printf("The total parallel resistance is: \n1 / (1 / R1 + 1 / R2 + 1 / R3) = 1 / (1 / %d + 1 / %d + 1 / %d) = %.3lf.\n", r4, r5, r6, parallel_resistance);

// Part 5
// Character encoding: encoded_character = (plaintext_character – 'a') + 'A' - shift; shift is an integer 

	printf("\n5. Character encoding\nPlease input a character and then an integer: ");
	scanf(" %c%d", &plaintext_character, &shift);

	encoded_character = (plaintext_character - 'a') + 'A' - shift;
	
	printf("Your character is now %c.\n", encoded_character); 

// Part 6
// Distance between two points: distance = square root of ((x1 - x2)^2 + (y1 - y2)^2) (note: you will need to use sqrt ( ) out of <math.h>)

	printf("\n6. Distance between two points\nPlease enter the x and y coordinates of your first point: ");
	scanf("%lf%lf", &x1, &y1);

	printf("Please enter the x and y coordinates of your second point: ");
	scanf("%lf%lf", &x2, &y2);

	distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	printf("The distance of your two points is: \nsqrt((x1 - x2)^2 + (y1 - y2)^2) = sqrt((%.2lf - %.2lf)^2 + (%.2lf - %.2lf)^2) = %.2lf.\n", x1, x2, y1, y2, distance); 

// Part 7
// General equation: y = y / (3 / 17) - z + x / (a % 2) + PI
// (recall: a is an integer; the 3 and 17 constants in the equation should be left as integers initially, 
// but explicitly type-casted as floating-point values) 

	printf("\n7. General equation\nPlease enter the values for y, z, x, and a: ");
	scanf("%lf%lf%lf%d", &y, &z, &x, &a);

	y = y / (3 / (double)17) - z + x / (a % 2) + PI;

	printf("The resulting value from the equation is %lf.\n\n", y);

	return 0;
}