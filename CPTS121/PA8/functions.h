/* Name: Mikaela Dean
Course: CPTS121 @ WSU
Date: 11/2019
Assignment: PA 8 with seven parts
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ********PART ONE********

/*
Function: my_str_n_cat()
-Description: copies the source[] string onto the end of the dest[] string, either till the end of source[] or up to n characters, using only pointer arthimetic
-Input parameters: char dest[], char source[], int n
-Returns: char *
-Preconditions: n/a
-Postconditions: n/a
*/
char* my_str_n_cat(char* dest[], char* source[], int n);

// ********PART TWO********

/*
Function: binary_search()
-Description: searches a sorted array for the target value. returns the target's index if found, otherwise returns -1
-Input parameters: int sorted[], int target, int size
-Returns: int (-1 if not found, otherwise is index of target in the sorted[] array)
-Preconditions: the int array sorted[] must be sorted smallest to largest
-Postconditions: n/a
*/
int binary_search(int sorted[], int target, int size);

// ********PART THREE********

/*
Function: bubble_sort()
-Description: sorts through an array of pointers to strings and abcs them
-Input parameters: char * array[], int num
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/
void bubble_sort(char * array[], int num);

// ********PART FOUR********

/*
Function: is_palindrome()
-Description: checks to see if the string entered is a palindrome and returns 1 if it is and 0 if it is not
-Input parameters: char string[], int length, int spaces
-Returns: int 1 or 0 (1 for yes 0 for no)
-Preconditions: n/a
-Postconditions: n/a
*/
int is_palindrome(char string[], int length, int spaces);

/*
Function: remove_whitespace()
-Description: removes the whitespace in the string entered
-Input parameters: char string[], int length
-Returns: char * 
-Preconditions: n/a
-Postconditions: all whitespaces are removed
*/
char * remove_whitespace(char string[], int length);

// ********PART FIVE********

/*
Function: sum_primes()
-Description: adds all of the prime numbers there are from 2 to n
-Input parameters: unsigned int n
-Returns: int (the sum)
-Preconditions: n/a
-Postconditions: n/a
*/
int sum_primes(unsigned int n);

/*
Function: check_prime()
-Description: checks to see if the number n is prime or not
-Input parameters: unsigned int n
-Returns: int 1 (prime) or 0 (not prime)
-Preconditions: n/a
-Postconditions: n/a
*/
int check_prime(unsigned int n);

// ********PART SIX********

typedef struct occurrences
{
	int num_occurrences;
	double frequency;
} Occurrences;

/*
Function: maxium_occurences()
-Description: returns through pointers the character that appears the most time in the string and the number of times it does appear
-Input parameters: char string[], Occurrences array[], int * num, char * c
-Returns: (through pointers)
-Preconditions: n/a
-Postconditions: n/a
*/
void maximum_occurences(char string[], Occurrences array[], int * num, char * c);

/*
Function: make_array()
-Description: initializes the array
-Input parameters: Occurrences array[]
-Returns: n/a
-Preconditions: n/a
-Postconditions: array is now initialized
*/
void make_array(Occurrences array[]);

// ********PART SEVEN********

//does not work
void max_consecutive_integers(signed int array[][5], int rows, int columns, int* num, int** address_ptr);


#endif FUNCTIONS_H





/*
Function:
-Description:
-Input parameters: n/a
-Returns: n/a
-Preconditions: n/a
-Postconditions: n/a
*/