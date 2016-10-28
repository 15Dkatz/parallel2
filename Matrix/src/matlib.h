// ======================================================================== //
// This library allows you to use Matrices in C
// Simply use the struct type to create a Matrix
// Each Matrix has rows, columns, and an array of pointers for its values
// Use the Mx macro to access and set values in a Matrix
// Use MatPrint to print out a Matrix in a nice format
// Use MatAlloc to allocate the memory of a Matrix
// Use MatFree to properly free memory space after using MatAlloc
// Use MatAdd to add the values of one Matrix to another
// ======================================================================== //

#define MATLIB_H
#define Mx(arg,r,c) ((arg).pX[r][c])

struct Matrix {
	int rows;
	int cols;
	double **pX;
};


/*-------------------------------------------------------------------
 * Function:    MatPrint
 * Purpose:     Print the values of a Matrix struct to the Console
 * In args:     m: the Matrix to print
 *              messg: a message to print before the struct
 * Outputs:     none
 */
void MatPrint(struct Matrix M, char messg[]) {
	int r, c;
	// Print the message
	printf("%s\n",messg);
	// print the matrix
	for (r = 0; r < M.rows; r++) {
		for (c = 0; c < M.cols; c++) {
			printf("%7.3lf ", Mx(M,r,c));
		}
		printf("\n");
	}
}

/*-------------------------------------------------------------------
 * Function:    MatAlloc
 * Purpose:     Allocate the proper amount of memory for the Matrix struct
 * In args:     r: the number of rows in the Matrix
 *              c: the number of columns in the Matrix
 * Outputs:     Returns a Matrix struct with properly allocated memory
 * 				based on rows and columns
 */
struct Matrix MatAlloc(int r, int c) {
	// the struct to return after dynamic allocation
	struct Matrix m;
	m.rows = r;
	m.cols = c;
	// allocating memory for the array of pointers of
	// size: rows * sizeof a double pointer
	m.pX = (double**) malloc(r*sizeof(double *));
	// if m.pX has been defined, then loop through the rows for memory allocation
	if (m.pX) {
		int x;
		for (x = 0; x < r; x++) {
			// in each row allocate memory for the array of doubles of
			// size: columns * sizeof a double
			m.pX[x] = (double*) malloc(c * sizeof(double));
		}
	}

	// return the properly allocated Matrix struct
	return m;
}

/*-------------------------------------------------------------------
 * Function:    MatFree
 * Purpose:     Free the Matrix struct's allocated memory
 * In args:     m: the Matrix struct to free
 * Outputs:     none
 */
void MatFree(struct Matrix m) {
	// iterate through the rows
	for (int r=0; r < m.rows; r++) {
		// iterate through the columns
		for (int c=0; c < m.cols; c++) {
			// set the value to 0
			Mx(m, r, c) = 0.0;

		}
		// free the memory associated with each row
		free(m.pX[r]);
	}
	// finally free the memory associated with the array of pointers
	free(m.pX);
}

/*-------------------------------------------------------------------
 * Function:    MatAdd
 * Purpose:     Add the values of one Matrix struct to another
 * In args:     a: the first Matrix (whose values will be augmented)
 *              b: the second Matrix (whose values will be used for
 *             	   augmentation)
 * Outputs:     Returns a Matrix struct with augmented values.
 */
void MatAdd(struct Matrix a, struct Matrix b) {
	// create a new Matrix of memory size a*b
	// but if the dimensions are different, exit the program
	if (a.rows != b.rows) {
		printf("\nError: Your matrices have unmatched rows. Exiting...");
		exit(0);
	}
	if (a.cols != b.cols) {
		printf("\nError: Your matrices have unmatched columns. Exiting...");
		exit(0);
	}

	// iterate through the rows of a and b
	// having a.rows as the limit is safe because we know a.rows == b.rows
	for (int r=0; r < a.rows; r++) {
		// iterate through the columns of a and b
		// having a.cols is the limit is safe because we know a.cols == b.cols
		for (int c=0; c < a.cols; c++) {
			// add to the value of a[r][c] with b[r][c]
			Mx(a, r, c) = Mx(a, r, c) + Mx(b, r, c);
		}
	}
}
