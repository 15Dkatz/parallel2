/*
 ============================================================================
 Name        : HelloWorld.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


/*-------------------------------------------------------------------
 * To run, locate the src directory and execute the following commands:
 * Build: mpicc -g -Wall -o HelloWorld HelloWorld.c
 * Exec: mpiexec HelloWorld
 */

int main(void) {
	MPI_Init(NULL, NULL);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	printf("Hello world from processor %s, rank %d"
			" out of %d processes\n",
			processor_name, world_rank, world_size);

	MPI_Finalize();
	return EXIT_SUCCESS;
}
