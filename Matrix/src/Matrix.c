/*
 =========================================================================
 Name        : Matrix.c
 Author      : David Katz
 =========================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "./matlib.h"

int main(void) {
	struct Matrix m = MatAlloc(2, 2);

	Mx(m, 0, 0) = 1.0;
	Mx(m, 0, 1) = 2.0;
	Mx(m, 1, 0) = 3.0;
	Mx(m, 1, 1) = 5.0;

	MatPrint(m, "Pre-free");

	MatFree(m);

	MatPrint(m, "Post-free");

	printf("Now testing MatAdd");

	struct Matrix a = MatAlloc(2, 2);
	struct Matrix b = MatAlloc(2, 2);

	Mx(a, 0, 0) = 1.0;
	Mx(a, 0, 1) = 1.0;
	Mx(a, 1, 0) = 1.0;
	Mx(a, 1, 1) = 1.0;

	Mx(b, 0, 0) = 3.0;
	Mx(b, 0, 1) = 4.0;
	Mx(b, 1, 0) = 5.0;
	Mx(b, 1, 1) = 6.0;

	MatPrint(a, "\npre-add");

	MatAdd(a, b);

	MatPrint(a, "post-add");

	MatFree(a);
	MatFree(b);

	MatPrint(a, "A postfree");
	MatPrint(b, "B postfree");

	printf("post frees");

	return EXIT_SUCCESS;
}
