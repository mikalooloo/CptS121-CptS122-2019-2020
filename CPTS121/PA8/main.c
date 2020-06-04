/* Name: Mikaela Dean
Course: CPTS121 @ WSU
Date: 11/2019
Assignment: PA 8 with seven parts
*/
#include "functions.h"

int main(void)
{
	// ********PART ONE TEST********

	char* dest, *source;
	char dest2[10] = "hot", source2[10] = "dog";
	dest = dest2;
	source = source2;//*source[10] = { "dog" }; // test[50] = { "ok" };
	int n = 3; 

	printf("********PART ONE********\nRip my brain is broken atm\n\n");

	// ********PART TWO TEST********

	int sorted[10] = { 1, 5, 12, 50, 74, 75, 77, 90 };
	int target_index = 0, target = 74, size = 8;

	target_index = binary_search(sorted, target, size);

	printf("********PART TWO********\nSorted List:\n");

	for (int i = 0; i < size; ++i)
	{
		printf("- %d (index: %d)\n", sorted[i], i);
	}

	printf("\nTarget: %d. ", target);
	if (target_index == -1)
	{
		printf("Target not found.\n\n");
	}
	else
	{
		printf("Found at index %d.\n\n", target_index);
	}

	// ********PART THREE TEST********

	char* str_arr[4] = { "eggs", "milk", "bread", "gravy" };

	printf("********PART THREE********\nList:\n");

	for (int i = 0; i < 4; ++i)
	{
		printf("- %s\n", str_arr[i]);
	}
	printf("\n");
	bubble_sort(str_arr, 4);
	printf("Sorted:\n");
	for (int i = 0; i < 4; ++i)
	{
		printf("- %s\n", str_arr[i]);
	}
	printf("\n");

	// ********PART FOUR TEST********

	printf("********PART FOUR********\n");
	char p[20] = "racecar"; int size2 = 7, result2 = 0;

	result2 = is_palindrome(p, size2, 0);

	if (result2 == 0)
	{
		printf("%s is not a palindrome. :(\n\n", p);
	}
	else
	{
		printf("%s is a palindrome! :)\n\n", p);
	}

	// ********PART FIVE TEST********

	unsigned int result = 0, num = 25;
	result = sum_primes(num);
	printf("********PART FIVE********\n");
	printf("Sum of primes found between 2 and %d: %d\n\n", num, result);

	// ********PART SIX TEST********

	Occurrences array[26];
	char string[30] = "test string";
	int string_num = 0;
	char string_char = '\0';

	printf("********PART SIX********\n");
	printf("String: %s\n", string);

	make_array(array);
	maximum_occurences(string, array, &string_num, &string_char);

	printf("Most common character: %c, appeared %d times\n\n", string_char, string_num);

	// ********PART SEVEN TEST********

	//does not work lmao
	//int array2[4][5] = { { -5, 6, 0, 2, 2 }, {2, 2, 2, 9, 3}, {3, 3, 2, 1, -8}, {7, -2, 6, 0, 4} };
	//int number = 0;
	//int* address_ptr = NULL;
	//max_consecutive_integers(array2, 4, 5, &number, &address_ptr);

	return 0;
}