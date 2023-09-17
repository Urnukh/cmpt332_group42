/*
// Urnukh Tsogt
// URT633
// 11267557
//
// Mitchell Risling
// MJR810
// 11221612
//
// CMPT332
// a01-phase01 part A
// 09:00, 19/09/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/*
 * check whether number of args given is correct.
 * precond: none
 * postond: possible prints to console
 * args: argc - # of commands given
 * return bool
 */
int checkValidArgNumber( int argc ){
	if ( argc != 3 ) return 0;
	return 1;
}

/*
 * check whether the arguments given on the command line are valid
 * precond: arguments given
 * postcond: none
 * return: bool whether the inputs are valid or not
 */
int checkValidInput( char *threads, char *time, char *n ){
	const int THREAD_MAX = 512;	/* says this is default on linux. windows is
								~2000 but that seems like way too many */
    int numberOfThreads, numberOfFibs, flag;
    unsigned long int secondsToRun;
    /* validate all digits before trying to convert */
    if ( ! isdigit((unsigned) *threads ) || ! isdigit((unsigned) *time ) ||
            ! isdigit((unsigned) *n ) ) {
    fprintf(stderr, "all cmd line args must be integers \n");
    flag = 0;
    return flag;
    }

    /* do conversions and check against bounds */
 	numberOfThreads = atoi( threads );
	secondsToRun = strtoul( time, NULL, 10 );
	numberOfFibs = atoi( n );
	flag = 1;

	if ( numberOfThreads > THREAD_MAX || numberOfThreads < 1 ) {
		fprintf(stderr, "size must be between 1 and 512 inclusive\n");
	 flag = 0;
	}

	if ( secondsToRun <= 0 ){
		fprintf( stderr, "time must be a greater than 0...\n");
	 	flag = 0;
	}

	if ( numberOfFibs <= 0 ) {
		fprintf( stderr, "n must be > 0. neg fib too hard for this program\n");
	 	flag = 0;
	}


	return flag;
	}
