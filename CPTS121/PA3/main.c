/*
Name: Mikaela Dean
Class: CPTS121, Lab Section 16
	WSU Fall Semester 2019
Date: 9/2019

Purpose: PA 3 
*/

#include "calculate.h"

int main(void)
{
	FILE* infile = NULL;
	FILE* outfile = NULL;

	infile = fopen("input.dat", "r");
	outfile = fopen("output.dat", "w");

	int id1 = 0, id2 = 0, id3 = 0, id4 = 0, id5 = 0, // student id
		rank1 = 0, rank2 = 0, rank3 = 0, rank4 = 0, rank5 = 0; // ranking
	double gpa1 = 0.0, gpa2 = 0.0, gpa3 = 0.0, gpa4 = 0.0, gpa5 = 0.0, gpa_sum = 0.0, gpa_mean = 0.0, gpa_variance = 0.0, gpa_standard = 0.0, gpa_max = 0.0, gpa_min = 0.0, // gpa
		deviation1 = 0.0, deviation2 = 0.0, deviation3 = 0.0, deviation4 = 0.0, deviation5 = 0.0, // gpa deviation
		age1 = 0.0, age2 = 0.0, age3 = 0.0, age4 = 0.0, age5 = 0.0, // age
		rank_sum = 0.0, age_sum = 0.0, rank_mean = 0.0, age_mean = 0.0;

	// read the numbers from the file and put them into their own variables
	id1 = read_integer(infile);
	gpa1 = read_double(infile);
	rank1 = read_integer(infile);
	age1 = read_double(infile);

	// repeat again but for the second set, and then so on
	id2 = read_integer(infile);
	gpa2 = read_double(infile);
	rank2 = read_integer(infile);
	age2 = read_double(infile);

	id3 = read_integer(infile);
	gpa3 = read_double(infile);
	rank3 = read_integer(infile);
	age3 = read_double(infile);

	id4 = read_integer(infile);
	gpa4 = read_double(infile);
	rank4 = read_integer(infile);
	age4 = read_double(infile);

	id5 = read_integer(infile);
	gpa5 = read_double(infile);
	rank5 = read_integer(infile);
	age5 = read_double(infile);

	// finds the sum for the gpa, class standing/ranking, and ages
	gpa_sum = calculate_sum(gpa1, gpa2, gpa3, gpa4, gpa5);
	rank_sum = calculate_sum(rank1, rank2, rank3, rank4, rank5);
	age_sum = calculate_sum(age1, age2, age3, age4, age5);

	// uses the ages to find the means for gpa, class ranking, ages
	gpa_mean = calculate_mean(gpa_sum);
	rank_mean = calculate_mean(rank_sum);
	age_mean = calculate_mean(age_sum);

	// finds the deviation of each gpa from the gpa mean
	deviation1 = calculate_deviation(gpa1, gpa_mean);
	deviation2 = calculate_deviation(gpa2, gpa_mean);
	deviation3 = calculate_deviation(gpa3, gpa_mean);
	deviation4 = calculate_deviation(gpa4, gpa_mean);
	deviation5 = calculate_deviation(gpa5, gpa_mean);

	// then uses that to find the gpa variance
	gpa_variance = calculate_variance(deviation1, deviation2, deviation3, deviation4, deviation5);

	// which we then use to find the standard deviation
	gpa_standard = calculate_standard_deviation(gpa_variance);

	// this is finding the max of the gpas
	gpa_max = find_max(gpa1, gpa2, gpa3, gpa4, gpa5);
	
	// and the min
	gpa_min = find_min(gpa1, gpa2, gpa3, gpa4, gpa5);

	// writing results to the output file
	print_double(outfile, gpa_mean);
	print_double(outfile, rank_mean);
	print_double(outfile, age_mean);
	print_double(outfile, gpa_standard);
	print_double(outfile, gpa_min);
	print_double(outfile, gpa_max);

	// closing the files
	fclose(infile);
	fclose(outfile);

	return 0;
}