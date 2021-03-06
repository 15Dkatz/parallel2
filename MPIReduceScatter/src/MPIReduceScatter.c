/*
 ============================================================================
 Name        : MPIReduceScatter.c
 Author      : David Katz
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/*-------------------------------------------------------------------
 * Runs a parallelized version of matrix multiplication.
 *
 * Reads data from an included matrix.txt file.
 * FORMAT for matrix.txt:
 * n n n // 1st row of 3 x 3 matrix
 * n n n // 2nd row of 3 x 3 matrix
 * n n n // 3rd row of 3 x 3 matrix
 * n n n // values for the 3 x 1 multiplication array
 *
 * The MPI_Scatter_reduce function:
 * Sends split arrays of data to each process.
 * Each process respectively reduces its data.
 *
 * Outputs: the starting matrix
 * 			and the reduced value from each process
 *
 */

/*-------------------------------------------------------------------
 * Running the program
 * 1) Locate the src folder with MPIReduceScatter.c
 * 2) execute `mpicc -o MPIReduceScatter MPIReduceScatter.c`
 * 		- builds an executable file for MPI to run
 * 3) execute `mpiexec -n 3 MPIReduceScatter`
 * 		- where 3 is the number of processes specified by the -n flag
 */

int main(void) {
	MPI_Init(NULL, NULL);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int sendarr[size];
	int recvnum;

	FILE * fp;
	fp = fopen("matrix.txt", "r");

	for (int r=0; r<=rank; r++) {
		fscanf(fp, "%d %d %d", &sendarr[0], &sendarr[1], &sendarr[2]);
	}

	// print the beginning array
	printf("| %d", sendarr[0]);
	for (int p=1; p<size; p++) {
		printf(" %d", sendarr[p]);
	}
	printf(" | in row %d \n", rank);

	int recvarr[size];
	for (int i=0; i<size; i++) recvarr[i] = 1;
	// the last line of input is the 3x1 multiplication
	int multarr[size];

	// reading the last line of the matrix.txt file to find the multiplication array
	for (int i=0; i<size-rank+1; i++) {
		fscanf(fp, "%d %d %d", &multarr[0], &multarr[1], &multarr[2]);
	}

	// perform the matrix multiplication
	for (int i=0; i<size; i++) sendarr[i] = sendarr[i] * multarr[i];
	// sum the scattered multiplied values and reduce them into the first process
	MPI_Reduce_scatter(sendarr, &recvnum, recvarr, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	// print the reduced number in the specific process
	printf("Proc %d: %d\n", rank, recvnum);

	MPI_Finalize();

	return EXIT_SUCCESS;
}
