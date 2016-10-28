/*
 ============================================================================
 Name        : Homework3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int factorial_orig (int n) {
	int i, ret = 1;
	for (i=2; i <= n; i++)
		ret *= i;
	return ret;
}

int factorial(int n) {
	int i = 1;
	int ret = 1;
	while (i <= n) {
		ret *= i;
		i++;
	}
	return ret;
}

double randdouble () {
	double ret = (double) rand();
	return ret / (RAND_MAX+1);
}
int samplegeometricrv( double p ) {
	double q;
	int n = 0;

	n++;
	q = randdouble();
	while (q >= p) {
		q = randdouble();
		n++;
	}

	return n;
}

int main(void) {
	printf("The result of %f in samplegeometricrv is %d", 1.0, samplegeometricrv(1.0));

	return EXIT_SUCCESS;
}
