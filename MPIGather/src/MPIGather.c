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
		// read in elements
		FILE * fp;
		fp = fopen("matrix.txt", "r");
		for (int n=0; n<numprocs; n++) {
			int i=n*3;
			fscanf(fp, "%d %d %d", &vector[i], &vector[i+1], &vector[i+2]);
		}
		fclose(fp);
	}



	// initialize a subarray to receive elements from scatter
	int *vector_sub = malloc(sizeof(int) * numprocs);
	// Scatter the numbers to all processes
	MPI_Scatter(vector, numprocs, MPI_INT, vector_sub, numprocs, MPI_INT, 0, MPI_COMM_WORLD);

	// **** do some function for calculating a value with the subarray **** //
	//	example squaring the element
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

	// print the final vector
	if (rank == 0) {
		printf("\n Final Vector: ");
		for (int i=0; i<size; i++) printf(" %d ", vector_sub[i]);
	}

	printf("\n");

	MPI_Finalize();
	return EXIT_SUCCESS;
}
