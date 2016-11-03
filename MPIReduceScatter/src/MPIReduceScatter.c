/*
 ============================================================================
 Name        : MPIReduceScatter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


// TODO add docs
// including how to run the program
int main(void) {
	MPI_Init(NULL, NULL);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int sendarr[size];
	int recvnum;

	// TODO read input from a separate file with fscanf
	for (int i=0; i<size; i++) sendarr[i] = 1 + rank + size*i;


	int recvarr[size];
	for (int i=0; i<size; i++) recvarr[i] = 1;





	// the last line of input is the 3x1 multiplication
	int multarr[size];
	// TODO read input from a separate file with fscanf
	for (int i=0; i<size; i++) multarr[i] = i+1;
	// perform the matrix multiplication
	for (int i=0; i<size; i++) sendarr[i] = sendarr[i] * multarr[rank];


	printf("Proc %d: ", rank);
	for (int i=0; i<size; i++) printf("%d ", sendarr[i]);
	printf("\n");

	MPI_Reduce_scatter(sendarr, &recvnum, recvarr, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	printf("Proc %d: %d\n", rank, recvnum);

	MPI_Finalize();





	// multiply according to the rank and the second array




	// use MPI_Scatter_reduce


	return EXIT_SUCCESS;
}
