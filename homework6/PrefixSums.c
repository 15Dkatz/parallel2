/*
 ============================================================================
 Name        : PrefixSums.c //SERIAL
 Author      : David Katz
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


/*-------------------------------------------------------------------
 * SERIAL VERSION of the prefix sums function
 * Guides the user in building an array.
 * First asks the user to choose a size, and then asks the user to
 * fill the array with values.
 * Once the array is created, the array of prefix sums is printed.
 */

int* calculatePrefix(int size, int *arr);
void printPrefixSums(int size, int *arr);

int main(void) {
	printf("Let's calculate the prefix sum for an array of your choosing.\n");
	printf("Choose an array size: ");
	int size;
	scanf("%d", &size);

	int *arr = malloc(size);

	for (int i=0; i<size; i++) {
		printf("Provide a value for index %d of your array: ", i);
		int num;
		scanf("%d", &num);
		arr[i] = num;
	}

	int* r = calculatePrefix(size, arr);

	printPrefixSums(size, r);

	return EXIT_SUCCESS;
}


/*-------------------------------------------------------------------
 * Function:    calculatePrefix
 * Purpose:     Calculate the prefix values for an array
 * In args:    	int size: the size of the argued array
 * 				int *arr: the array of values to calculate the prefix
 * 				sums for
 * Outputs:     Returns the array of prefix sums
 */
int* calculatePrefix(int size, int *arr) {
	int *psums = malloc(size);
	for (int i=0; i<size; i++) {
		int t=0;

		for (int j=0; j<=i; j++) {
			t += arr[j];
		}
		psums[i] = t;
	}
	return psums;
}

/*-------------------------------------------------------------------
 * Function:    printPrefixSums
 * Purpose:     print the values of an array of prefix sums
 * In args:    	int size: the size of the argued array
 * 				int *arr: the array of values to print the values of
 * Outputs:     No returned output
 */
void printPrefixSums(int size, int *arr) {
	printf("Printing the prefix sums of your array:\n");
	for (int p=0; p<size; p++) {
		printf("ps[%d] = %d \n", p, arr[p]);
	}
}
