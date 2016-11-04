/*
 ============================================================================
 Name        : MPIPingPong.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>


// TODO add docs
int main(void) {
	MPI_Init(NULL, NULL);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	char *message = malloc(256);

	// UNCOMMENT below code to keep track of the run time for the MPI processes
	//	double starttime, endtime;
	//	starttime = MPI_Wtime();

	// run this 1m times
	int number;
	for (int i=0; i<1000000; i++) {
		if (rank == 0) {
			strcpy(message, "ping");
			// send message to process 1 with tag 0
			MPI_Send(message, 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
			// receive message from process 1 with tag 1
			MPI_Recv(message, 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("i: %d | Process 0 received a %s from process 1\n", i, message);
		} else if (rank == 1) {
			strcpy(message, "pong");
			// send message to process 0 with tag 1
			MPI_Send(message, 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
			// receive message from process 0 with tag 0
			MPI_Recv(message, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("i: %d | Process 1 received a %s from process 0\n", i, message);
		}
	}

	// UNCOMMENT below code to keep track of the run time for the MPI processes
	//	endtime = MPI_Wtime();
	//	printf("That took %f seconds\n", endtime-starttime);

	MPI_Finalize();
	return EXIT_SUCCESS;
}
