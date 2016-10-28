/*
 ============================================================================
 Name        : CircularShift.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void menu();
void circular_shift(int shift);
void print_arr();

int main_arr[20];
int limit = 0;

int main(void) {
	menu();
	return EXIT_SUCCESS;
}

void menu() {

	printf("Let's do some circular shifting.");

	int retry = 1;
	while (retry == 1) {
		printf("\nHow many elements will be in your array?");
		printf("\nPlease choose a limit less than or equal to 20: ");
		scanf("%d", &limit);
		if (limit <= 20) {
			retry = 0;
			break;
		} else {
			retry = 1;
		}
	}


	int e = 0;

	while (e < limit) {
		printf("\nWhat is your next number: ");
		int n = 0;
		scanf("%d", &n);
		main_arr[e] = n;
		e++;
	}

	int shift = 0;
	printf("\nOk. Now how much should we shift the array? ");
	scanf("%d", &shift);
	circular_shift(shift);
}

void print_arr() {
	printf("\nThe shifted arr:");
	int p = 0;
	printf("\n[ ");
	while (p < limit-1) {
		printf("%d, ", main_arr[p]);
		p++;
	}
	printf("%d ]", main_arr[limit-1]);
}

void circular_shift(int shift) {
	printf("Shifting the array by %d", shift);

	int new_arr[limit];

	int s = limit-shift;
	int i = 0;
	while (s < limit) {
		new_arr[i] = main_arr[s];
		s++;
		i++;
	}

	int r = 0;
	s = limit-shift;

	while(r <= s) {
		new_arr[i] = main_arr[r];
		r++;
		i++;
	}

	int c = 0;
	while (c < limit) {
		main_arr[c] = new_arr[c];
		c++;
	}

	print_arr();
}
