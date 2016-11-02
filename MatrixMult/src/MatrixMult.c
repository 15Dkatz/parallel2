/*
 ============================================================================
 Name        : MatrixMult.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

/*-------------------------------------------------------------------
 * To run, locate the src directory and execute the following commands:
 * Build: mpicc -g -Wall -o MatrixMult MatrixMult.c
 * Exec: mpiexec MatrixMult
 */

int main(int argc, char *argv[]) {
	int rank, size;
	int arr_size = 4;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int sendbuf[arr_size];
	int recvbuf[arr_size];




	if (rank == 0) {
		// making a matrix as an array of arr_size values:
		//	[1, 2
		//	 3, 4] in process 0
		for (int i=0; i<arr_size; i++)
		sendbuf[i] = i+1;

		printf("Process %d: ", rank);
		for (int i=0; i<arr_size; i++) printf("%d ", sendbuf[i]);
		printf("\n");
	} else {
		// and a multiplication array in process 1 by [1, 2]
		for (int i=0; i<2; i++) {
			sendbuf[i] = i+1;
		}
		printf("Process %d: ", rank);
		for (int i=0; i<2; i++) printf("%d ", sendbuf[i]);
		printf("\n");
	}





	int recvcounts[size];
	for (int i=0; i<size; i++)
		recvcounts[i] = 3;

	MPI_Reduce_scatter(sendbuf, &recvbuf, recvcounts, MPI_INT, MPI_PROD, MPI_COMM_WORLD);

	printf("Process %d: ", rank);
	for (int i=0; i<2; i++) printf("%d ", recvbuf[i]);
	printf("\n");

	MPI_Finalize();


	return EXIT_SUCCESS;
}
