/*
Name: Mikaela Dean
Class: CPTS121, Lab Section 16
	WSU Fall Semester 2019
Date: 9/2019

Purpose: PA 3 
*/

#include "calculate.h"

double read_double(FILE* infile)
{
	double num = 0.0;
	fscanf(infile, "%lf", &num);

	return num;
}

int read_integer(FILE* infile)
{
	int num = 0;
	fscanf(infile, "%d", &num);

	return num;
}

double calculate_sum(double gpa1, double gpa2, double gpa3, double gpa4, double gpa5)
{
	double gpa_sum = 0.0;

	gpa_sum = gpa1 + gpa2 + gpa3 + gpa4 + gpa5;

	return gpa_sum;
}

double calculate_mean(double gpa_sum)
{
	int number = 5;
	double mean = 0.0;

	if (number == 0)
	{
		return -1.0;
	}
	else
	{
		mean = gpa_sum / number;
		return mean;
	}
}

double calculate_deviation(double number, double mean)
{
	double deviation = 0.0;

	deviation = number - mean;

	return deviation;
}

double calculate_variance(double deviation1, double deviation2, double deviation3, double deviation4, double deviation5)
{
	double variance = 0.0;

	variance = (pow(deviation1, 2) + pow(deviation2, 2) + pow(deviation3, 2) + pow(deviation4, 2) + pow(deviation5, 2)) / 5;

		return variance;
}

double calculate_standard_deviation(double variance)
{
	double total = 0.0;
	
	total = sqrt(variance);

	return total;
}

double find_max(double number1, double number2, double number3, double number4, double number5)
{
	double result = number1;

	if (number2 > result)
	{
		result = number2;
	}
	if (number3 > result)
	{
		result = number3;
	}
	if (number4 > result)
	{
		result = number4;
	}
	if (number5 > result)
	{
		result = number5;
	}

	return result;
}

double find_min(double number1, double number2, double number3, double number4, double number5)
{
	double result = number1;

	if (number2 < result)
	{
		result = number2;
	}
	if (number3 < result)
	{
		result = number3;
	}
	if (number4 < result)
	{
		result = number4;
	}
	if (number5 < result)
	{
		result = number5;
	}

	return result;
}

void print_double(FILE* outfile, double number)
{
	fprintf(outfile, "%.2lf\n", number);
}