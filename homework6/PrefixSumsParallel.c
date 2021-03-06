/*
 ============================================================================
 Name        : PrefixSumsParallel.c // PARALLEL
 Author      : David Katz
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>



/*-------------------------------------------------------------------
 * PARALLEL VERSION
 * The program builds an array of values from 1 to the number of
 * processes in process 0.
 * It then uses the MPI Library to broadcast this array of values to
 * all processes. Each process then calculates the prefix value for
 * its portion of the initial array. It then sends that value back to
 * the first process which stores that prefix value by gathering it
 * into a second array. The final array of prefix values then prints.
 */

/*-------------------------------------------------------------------
 * To run, locate the src directory and execute the following commands:
 * Build: mpicc -g -Wall -o PrefixSumsParallel PrefixSumsParallel.c
 * Exec: mpiexec -n <number of processes> PrefixSumsParallel
 */

int main(void) {
	int master = 0;
	int id;
	int numprocs;
	int i;
	MPI_Status status;

	/*Initialize MPI*/
	MPI_Init(NULL, NULL);

	/*Get the number of processes*/
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/*Get the rank of this process among all the processes*/
	MPI_Comm_rank(MPI_COMM_WORLD, &id);


	int array1[numprocs];
	int array2[numprocs+1];

	if (id==0) {
		// initialize array1
		for (i=0; i<numprocs; i++) {
			array1[i] = i+1;
		}
	}

	// Send array1 to all processes
	MPI_Bcast(array1, numprocs, MPI_INT, master, MPI_COMM_WORLD);

	int prefix_sum=0;
	// calculate the prefix sum
	for (int c=0; c<=id; c++) {
		prefix_sum += array1[c];
	}
	array2[id] = prefix_sum;

	MPI_Gather(&id, 1, MPI_INT, &array2[id], 1, MPI_INT, 0, MPI_COMM_WORLD);

	// For all the processes that are not 0 or the master
	// send the prefix sum to the master and the master receives the sum
	// and adds it to the array2
	for (i=1; i<numprocs; i++) {
		if (id!=master) {
			MPI_Send(&prefix_sum, 1, MPI_INT, master, 1, MPI_COMM_WORLD);
		} else {
			array2[id] = prefix_sum;
			MPI_Recv(&array2[i], 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
		}
	}

	if (id==master) {
		printf("\n");
		printf("The start array is\n");
		for (int c=0; c<numprocs; c++) {
			printf("%d   ", array1[c]);
		}
		printf("\n\n");
		printf("The prefix sums array is\n");
		for (int c=0; c<numprocs; c++) {
			printf("%d   ", array2[c]);
		}
		printf("\n");
	}


	// Shutdown MPI
	MPI_Finalize();
	return EXIT_SUCCESS;
}
