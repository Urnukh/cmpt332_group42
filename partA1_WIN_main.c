/*
Urnukh Tsogt
URT633
11267557

Mitchell Risling
MJR810
11221612

CMPT332
a01-phase01
09:00, 19/09/2022

main file for partA1
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "partA_main.h"

#define SIZE 512
int size;
int part;
int keepRunning;
unsigned long int childIndexes[SIZE] = {0};
int callsToFib[SIZE] = {0};


/*
 * put everythuing together in msin
 * checlk and validate input,
 * create global array, and variable for child
 * threads to update and check respectively
 * windows has functions for waiting for children to
 * finish execution, will use this here to keep the parent
 * from exiting before all children have the chance to print out their resutlt
 */
int main( int argc, char *argv[] ){
    int threads, n;
    unsigned long int deadline;
    procArgs args;

	if ( checkValidArgNumber( argc - 1 ) == 0 ||
        checkValidInput( (char*) argv[1], ( char*) argv[2], ( char*) argv[3] )
        == 0 ){
        fprintf( stderr, "invalid input\n" );
        return 1;
	}
    /* declare and fill argStruct with the arguments */
    threads = atoi( argv[1] );
    deadline = strtol( argv[2], NULL, 10  );
    n = atoi( argv[3] );

    args.numberOfChildren = threads;
    args.time = deadline;
    args.n = n;

    size = SIZE;
    part = 1;
    keepRunning = 1;

    createWINParent( (void*) &args);




	return 0;
}
