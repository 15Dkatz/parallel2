/*
 ============================================================================
 Name        : MPIGather.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(void) {
	MPI_Init(NULL, NULL);
	int numprocs;
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int size = numprocs*numprocs;
	int vector[size]; // initialize an array of size^2

	if (rank == 0) {
		// add elements 1-size
		for (int i=0; i<size; i++) {
			vector[i] = i+1;
		}
	}

	// initialize a subarray to receive elements from scatter
	int *vector_sub = malloc(sizeof(int) * numprocs);
	// Scatter the numbers to all processes
	MPI_Scatter(vector, numprocs, MPI_INT, vector_sub, numprocs, MPI_INT, 0, MPI_COMM_WORLD);

	// **** do some function for calculating a value with the subarray **** //
	//	example squaring the lement
	printf("Process %d, vector_sub: ", rank);
	for (int i=0; i<numprocs; i++) {
		int next = vector_sub[i];
		printf(" %d ", next);
		vector_sub[i] = next * next;
	}
	printf("\n squared into \n");
	for (int s=0; s<numprocs; s++) printf(" %d ", vector_sub[s]);
	printf("\n");


	MPI_Gather(&vector_sub[0], numprocs, MPI_INT, vector_sub, numprocs, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	// print the final vector
	if (rank == 0) {
		printf("\n Final Vector: ");
		for (int i=0; i<size; i++) printf(" %d ", vector_sub[i]);
	}

	MPI_Finalize();
	return EXIT_SUCCESS;
}
