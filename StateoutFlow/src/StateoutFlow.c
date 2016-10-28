/*
 ==================================================================
 Name        : StateoutFlow.c
 Author      : David Katz
 ==================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reads stateoutflow0708.txt, searching for Massuchessetts's emigration data
// Assumes stateoutflow0708.txt exists in the same directory
// Prints out the formatted data in the end with the printf() method

int main(void) {

	FILE * infile;
	infile = fopen("stateoutflow0708.txt", "r");

	if (infile == NULL) {
		printf("Unable to open file");
	}

	char throw_header[20];
	for (int i = 0; i < 10; i++) {
		fscanf(infile, "%19s", throw_header);
	}
	// sco = state_code_origin
	// cco = country_code_origin
	// scd = state_code_dest
	// sa = state_abbrv
	// sn = state_name
	char sco[5], cco[6], scd[5], ccd[6], sa[5], sn[30];
	// rn = return_num
	// en = exmpt_num
	// aa = aggr_agi
	int rn, en, aa;

	// total emigration from Massachussetts
	int total_aa = 0;

	printf("STATE			 TOTAL");
	printf("\n-------------------------------\n");

	// 2601 is the number of lines after the header
	for (int r=0; r<2601; r++) {
		fscanf(infile, "%4s %5s %4s %5s %4s %29s", sco, cco, scd, ccd, sa, sn);
		fscanf(infile, "%i %i %i", &rn, &en, &aa);

		// We know that the state_code_origin for Massachusetts is 25
		char mass_co[5] = "\"25\"";
		int result = strcmp(mass_co, sco);
		if (result == 0) {
			// add to the emigration total and print the data
			total_aa += aa;
			int spaces = 25 - strlen(sn);
			printf("%s", sn);
			for (int s = 0; s < spaces; s++) {
				printf(" ");
			}
			printf("%d", aa);
			printf("\n");
		}

	}

	printf("\n-------------------------------\n");
	printf("Total:			%d", total_aa);

	fclose(infile);


	return EXIT_SUCCESS;
}

