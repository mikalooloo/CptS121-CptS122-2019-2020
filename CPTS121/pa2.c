/*
Name: Mikaela Dean
Date: 9/10/2019
Course: CPTS121 Section 1, Lab Section 16 - WSU Fall Semester 2019

Description: Assignment PA 2 with seven total parts. Due 9/13/2019 at midnight.
- Function definitions
*/

#include "pa2.h"

// Part 1
int calculate_series_resistance(int r1, int r2, int r3)
{
	double series_resistance = 0;

	series_resistance = r1 + r2 + r3;

	printf("The series resistance is: \nR1 + R2 + R3 = %d + %d + %d = %.2lf.\n", r1, r2, r3, series_resistance);

	return series_resistance;
}

// Part 2
double calculate_total_sales_tax(double sales_tax_rate, double item_cost)
{
	double total_sales_tax = 0;
	
	total_sales_tax = sales_tax_rate * item_cost;

	printf("The total sales tax for your item is: \nTax Rate * Item's Cost = $%.2lf * $%.2lf = $%.2lf.\n", sales_tax_rate, item_cost, total_sales_tax);

	return total_sales_tax;
}

// Part 3
double calculate_volume_pyramid(double l, double w, double h)
{
	double volume_pyramid = 0;
	
	volume_pyramid = (l * w * h) / 3;

	printf("The volume of your pyramid is: \n(l * w * h) / 3 = (%.1lf * %.1lf * %.1lf) / 3 = %.1lf\n", l, w, h, volume_pyramid);

	return volume_pyramid;
}

// Part 4
double calculate_parallel_resistance(int r4, int r5, int r6)
{
	double parallel_resistance = 0.0;
	
	parallel_resistance = 1 / (1 / (double)r4 + 1 / (double)r5 + 1 / (double)r6);

	printf("The total parallel resistance is: \n1 / (1 / R1 + 1 / R2 + 1 / R3) = 1 / (1 / %d + 1 / %d + 1 / %d) = %.3lf.\n", r4, r5, r6, parallel_resistance);
}

// Part 5
char calculate_encoded_character(char plaintext_character, char shift)
{
	char encoded_character = 0;

	encoded_character = (plaintext_character - 'a') + 'A' - shift;

	printf("Your character is now %c.\n", encoded_character);

}

// Part 6
double calculate_distance(double x1, double x2, double y1, double y2)
{
	double distance = 0.0;

	distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

	printf("The distance of your two points is: \nsqrt((x1 - x2)^2 + (y1 - y2)^2) = sqrt((%.2lf - %.2lf)^2 + (%.2lf - %.2lf)^2) = %.2lf.\n", x1, x2, y1, y2, distance);
}

// Part 7
double calculate_y(double y, double z, double x, int a)
{
	y = y / (3 / (double)17) - z + x / (a % 2) + PI;

	printf("The resulting value from the equation is %lf.\n\n", y);
}