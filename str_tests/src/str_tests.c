/*
 ============================================================================
 Name        : str_tests.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	const char str1[] = "42 is a bad answer";
	const char str2[] = "42 is a bad answawefer";

	int i;


	for (i = strlen(str1); i > 0; i--) {
		if (strncmp(str1, str2, i)==0) {
			printf("The first %d chars of str1 and str2 are the same\n", i);
			break;
		}
	}

}
