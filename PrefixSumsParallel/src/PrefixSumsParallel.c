/*
 ============================================================================
 Name        : PrefixSumsParallel.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>


// Personal Notes
// Build: mpicc -g -Wall -o PrefixSumsParallel PrefixSumsParallel.c
// Exec: mpiexec -n <number of processes> PrefixSumsParallel


const int MAX_STRING = 100;

int main(void) {
	char greeting[MAX_STRING];
	int my_rank, p, q;

	/* Start up MPI */
	MPI_Init(NULL, NULL);

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		printf("Greetings from process %d of %d\n", my_rank, p);
		for (q=1; q<p; q++) {
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", greeting);
		}
	} else {
		sprintf(greeting, "Greetings from process %d of %d", my_rank, p);
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}

	/* Shut down MPI */
	MPI_Finalize();
	return EXIT_SUCCESS;
}
