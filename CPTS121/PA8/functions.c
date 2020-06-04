/* Name: Mikaela Dean
Course: CPTS121 @ WSU
Date: 11/2019
Assignment: PA 8 with seven parts
*/
#include "functions.h"

// ********PART ONE********

char * my_str_n_cat(char * dest[], char * source[], int n)
{
	int count = 0;
	while (**dest != '\0') 
	{
		++*dest;
		++count;
	}
	for (int i = 0; i < n && *source != '\0'; i++) 
	{
		*dest = *source;
	}
	*dest -= count;
	return dest;
}

// ********PART TWO********

int binary_search(int sorted[], int target, int size)
{
	int left = 1, right = size, mid = 0,
		found = 0, target_index = -1;

	do
	{
		mid = (left + right) / 2;

		if (target == sorted[mid])
		{
			found = 1;
			target_index = mid;
		}
		else if (target < sorted[mid])
		{
			right = mid - 1;
		}
		else 
		{
			left = mid + 1;
		}

	} while (found == 0 && left <= right);

	return target_index;
}

// ********PART THREE********

void bubble_sort(char * array[], int num)
{
	int U = num, C = 1, index = 1;
	int temp = 0;
	//char temp = '\0';
	
	for (; C < U; ++C) 
	{
		for (int i2 = 0; i2 < (U - C); ++i2) 
		{
			if (strcmp(array[i2], array[i2 + 1]) > 0) // if the ascii value of first string is higher than second string
			{
				temp = array[i2 + 1]; //then swap them so the lower ascii stopping value (earlier in the abcs)
				array[i2 + 1] = array[i2]; //goes towards the front
				array[i2] = temp;
			}

		}

	}
}

// ********PART FOUR********

int is_palindrome(char string[], int length, int spaces)
{
	int palindrome = 0;

	if (spaces == 0) // if there might be spaces, get rid of them
	{
		strcpy(string, remove_whitespace(string, length));
	}
	else if (string[0] == '\0') // if no spaces, and it has reached the end of the word, then it's a palindrome
	{
		return 1;
	}

	if (string[0] == string[length - 1]) 
	{
		return is_palindrome(string + 1, length - 2, 1);
	}
	else
	{
		return 0;
	}
}

char * remove_whitespace(char string[], int length)
{
	char blank[50];

	for (int i = 0, i2 = 0; i2 <= length; ++i, ++i2)
	{
		if (string[i] == ' ')
		{
			++i2;
			blank[i] = string[i2];
		}
		else
		{
			blank[i] = string[i2];
		}
	}

	return blank;
}

// ********PART FIVE********

int sum_primes(unsigned int n)
{
	int total = 0;

	if (n == 2) // once it reaches 2 it's just 2
	{
		return 2;
	}

	if (check_prime(n) == 1) // if it is a prime number make it the total
	{
		total = n;
	}
	else
	{
		total = 0; // if it's not a prime number don't add anything
	}

	return total + sum_primes(n - 1); // as all of the totals (all of the primes) will be added up
} 

int check_prime(unsigned int n)
{
	int result = 0;

	if (n > 2 && n % 2 != 0) // if it's over 2 and not divisible by 2
	{
		for (int i = 3; i < n / 2; i = i + 2) // find out if n is divisble by prime numbers equal to half of n
		{
			if (n % i == 0) // if the number is not prime:
			{
				result = -1; // make result equal -1. if result equals -1 by the end of the for loop, which it will be if the number is not prime, one will be added to it and it'll be returned as zero
			}
		}
		++result; // if result never equaled -1, then adding one to it here will have it returned as one
	}
	
	return result;
}

// ********PART SIX********

void maximum_occurences(char string[], Occurrences array[], int* num, char* c)
{
	int length = strlen(string), count = 0;

	for (int i = 0; string[i] != '\0'; ++i) // do it until the string is done
	{
		if (string[i] != ' ') // if it's not a space count the letter
		{
			array[string[i] - 'a'].num_occurrences += 1; // adds one for that character
			++count; // keeps track of the number of characters in the string (basically the length without spaces)
		}
	}

	for (int i = 0; i < length; i++)
	{
		array[i].frequency = (double) array[i].num_occurrences / count; // find the freq
	}

	*num = 0, *c = '\0'; // make sure they're actually zero and null otherwise it could mess up the function

	for (int i = 0; i < 27; ++i) // do this for all letters
	{
		if (array[i].num_occurrences > * num) // the num is the max so we're just figuring out the max here
		{
			*num = array[i].num_occurrences; // if it is bigger than the max make it the new max
			*c = i + 'a'; // make the character the new max
		}
	}
}

void make_array(Occurrences array[])
{
	for (int i = 0; i < 26; i++)
	{
		array[i].num_occurrences = 0;
		array[i].frequency = 0.0;
	}
}

// ********PART SEVEN********

void max_consecutive_integers(signed int array[][5], int rows, int columns, int* num, int** address_ptr)
{
	int* starting_ptr = array[0][0];
	int* current_ptr = NULL;
	int max = 0, count = 0;

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			current_ptr = &array[r][c];
			if (*starting_ptr == current_ptr)
			{
				++count;
			}
			else
			{
				if (count > max)
				{
					*address_ptr = starting_ptr;
					max = count;
				}
				count = 0;
			}
			if (count == 0)
			{
				starting_ptr = &array[r][c];
			}
		}
	}

	*num = max;

	printf("most: %d\n", *num);
}