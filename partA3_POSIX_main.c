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

main file for partA3
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
 * use some mechanism in pthreads to wait for all threadto finish.
 */
int main( int argc, char *argv[] ){
    /* some of this can probablty be pulled out into a function */
    int i, threads, n;
    unsigned long int deadline;

    if (checkValidArgNumber( argc - 1 ) == 0 || checkValidInput(
                (char*) argv[1], ( char*) argv[2], ( char*) argv[3] ) == 0 ){
        fprintf( stderr, "invalid input\n" );
        return 1;
    }
    /* input is valid. do conversions and create parent thread */
    threads = atoi( argv[1] );
    deadline = strtol( argv[2], NULL, 10  );
    n = atoi( argv[3] );

    size = SIZE;
    part = 3;
    keepRunning = 1;

    /* create parent thread and return success value */
    i = createLinuxParent( threads, deadline, n,  3 );
    return i;
}
