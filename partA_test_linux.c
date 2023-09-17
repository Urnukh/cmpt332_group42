/*
Urnukh Tsogt
URT633
11267557
Mitchell Risling
MJR810
11221612

CMPT332
a01p02
testfile for partA2-4. Linux
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "partA_main.h"

int  keepRunning, callsToFib[512];

int main ( int argc, char **argv) {
	/* declare all variables we need */
	/* flag is used to count errors, testPassed will store return val
	 * failed tests will be used to keep track of which test fail\
	 * test will be array we use to test inputs on checkValidInput */
	int flag, testPassed, i;
	int failedTests[500] = { 0 };
	char **test[3], *threads, *time, *n;

	*test = (char **) malloc(5 * sizeof(char *));
	threads = (char*) malloc(100 * sizeof(char));
	time = (char*) malloc(100 * sizeof(char));
	n = (char*) malloc(100 * sizeof(char));


	strcpy(threads,"123");
	strcpy(time, "69");
	strcpy(n, "420");

	test[0] = &threads;
	test[1] = &time;
	test[2] = &n;


keepRunning = 50;
callsToFib[0] = 1;

 	/* discard error output from functions */
	freopen( "/dev/null", "w", stderr );

	printf("Running Tests...\n");
	printf("\ntesting file: check_input.c\n");
	printf("\ntesting checkValidArgNumber( int argc )...\n");

	flag = 0;
	/* one above expected */
	printf("\ttesting argc = 4...\n");
	testPassed = checkValidArgNumber( 4 );
	if ( testPassed != 0 ){
		failedTests[1] = 1;
		flag += 1;
		printf("test 01 failed - checkValidArgNumber( 4 )\n");
	}

	/* == 0 */
	printf("\ttesting argc = 0...\n");
	testPassed = checkValidArgNumber( 0 );
	if ( testPassed != 0 ){
		failedTests[2] = 1;
		flag += 1;
		printf("test 02 failed - checkValidArgNumber( 0 )\n");
	}

	/* 2 below */
	printf("\ttesting argc = -1...\n");
	testPassed = checkValidArgNumber( -1 );
	if ( testPassed != 0 ){
		failedTests[3] = 1;
		flag += 1;
		printf("test 03 failed - checkValidArgNumber( -1 )\n");
	}

	/* neg of valid */
	printf("\ttesting argc = -3...\n");
	testPassed = checkValidArgNumber( -3 );
	if ( testPassed != 0 ){
		failedTests[4] = 1;
		flag += 1;
		printf("test 04 failed - checkValidArgNumber( -3 )\n");
	}

	/* way above valid */
	printf("\ttesting argc = 100...\n");
	testPassed = checkValidArgNumber( 100 );
	if ( testPassed != 0 ){
		failedTests[5] = 1;
		flag += 1;
		printf("test 05 failed - checkValidArgNumber( 100 )\n");
	}

	/* valid */
	printf("\ttesting argc = 3...\n");
	testPassed = checkValidArgNumber( 3 );
	if ( testPassed != 1 ){
		failedTests[6] = 1;
		flag += 1;
		printf("test 06 failed - checkValidArgNumber( 3 )\n");
	}

	/* tests of checkValidArgNumber done, print message */
	if ( flag == 0 )
		printf("all checkValidArgNumber tests passed\n");
	else
		printf("%d tests failed\n", flag);


	/* set flag zero, print message, and begin testing checkValidInput */
	flag = 0;
	printf("\ntesting checkValidInput( char* char* char*)...\n");


	/* all valid */
	printf("\twith 123 69 420...\n");
	testPassed = checkValidInput( *test[0], *test[1], *test[2]);
	if ( testPassed != 1 ){
		failedTests[7] = 1;
		flag += 1;
		printf("test 07 failed - checkValidInput( 123 69 420 )\n");
				}

		/* number of threads 3 less, 2, less, 1 less than valid */
	for ( i = -2; i < 1; i++){
		sprintf( threads, "%d", i);
		printf("\twith %s 69 420..\n",  *test[0]);
		testPassed = checkValidInput( *test[0], *test[1], *test[2]);
		if ( testPassed != 0 ){
			failedTests[ i + 10 ] = 1;
			flag += 1;
			printf("test 0%d failed - checkValidInput( %s 69 420 )\n", i+10, *test[0] );
		}
	}

	/* number of threads at min valid */
	sprintf( threads, "%d", 1);
	testPassed = checkValidInput( *test[0], *test[1], *test[2]);
	if ( testPassed != 1 ){
		failedTests[11] = 1;
		flag += 1;
		printf("test 11 failed - checkValidInput( 1 69 420 )\n");
	}

	/* number of threads 1, 2 and 3 above valid */
	for ( i = 2; i < 5; i++){
		sprintf( threads, "%d", i);
		printf("\twith %s 69 420..\n", *test[0]);
		testPassed = checkValidInput( *test[0], *test[1], *test[2]);
		if ( testPassed != 1 ){
			failedTests[ i + 10 ] = 1;
			flag += 1;
			printf("test 0%d failed - checkValidInput( %s 69 420 )\n", i+10, *test[0] );
		}
	}


	/* number of threads 1, 2 and 3 below and at max valid */
	for ( i = 509; i < 513; i++){
		sprintf( threads, "%d", i);
		printf("\twith %s 69 420..\n", *test[0]);
		testPassed = checkValidInput( *test[0], *test[1], *test[2]);
		if ( testPassed != 1 ){
			failedTests[ i - 496 ] = 1;
			flag += 1;
			printf("test 0%d failed - checkValidInput( %s 69 420 )\n", i-496, *test[0] );
		}
	}

	/* number of threads 1, 2 and 3 above max valid */
	for ( i = 513; i < 515; i++){
		sprintf( threads, "%d", i);
		printf("\twith %s 69 420..\n", *test[0]);
		testPassed = checkValidInput( *test[0], *test[1], *test[2]);
		if ( testPassed != 0 ){
			failedTests[ i - 496 ] = 1;
			flag += 1;
			printf("test 0%d failed - checkValidInput( %s 69 420 )\n", i-496, *test[0] );
		}
	}

	/* set  threads to valid val */
	sprintf( threads, "%d", 50);

/* time 3 less, 2, less, 1 less than valid */
  for ( i = -2; i < 1; i++){
    sprintf( time, "%d", i);
    printf("\twith 50, %s 420..\n",  *test[1]);
    testPassed = checkValidInput( *test[0], *test[1], *test[2]);
    if ( testPassed != 0 ){
      failedTests[ i + 17 ] = 1;
      flag += 1;
      printf("test 0%d failed - checkValidInput( 50 %s 420 )\n", i+17, *test[1] );
    }
  }

  /* time at min valid */
  sprintf( time, "%d", 1);
  testPassed = checkValidInput( *test[0], *test[1], *test[2]);
  if ( testPassed != 1 ){
    failedTests[21] = 1;
    flag += 1;
    printf("test 21 failed - checkValidInput( 50 1 420 )\n");
  }


	/* time 1, 2 and 3 above valid */
	for ( i = 2; i < 5; i++){
		sprintf( time, "%d", i);
		printf("\twith 50 %s 420..\n", *test[1]);
		testPassed = checkValidInput( *test[0], *test[1], *test[2]);
		if ( testPassed != 1 ){
			failedTests[ i + 17 ] = 1;
			flag += 1;
			printf("test 0%d failed - checkValidInput( 50 %s 420 )\n", i+17, *test[1] );
		}
	}


	/* time 1, 2 and 3 below and at max valid */
	for ( i = 9997; i < 9999; i++){
		sprintf( time, "%d", i);
		printf("\twith 50 %s 420..\n", *test[1]);
		testPassed = checkValidInput( *test[0], *test[1], *test[2]);
		if ( testPassed != 1 ){
			failedTests[ i - 9974 ] = 1;
			flag += 1;
			printf("test 0%d failed - checkValidInput( 50 %s 420 )\n", i-9974, *test[1] );
		}
	}

	/* time at max valid */
	sprintf( time, "%d", 10000);
	printf("\twith 50 %s 420..\n", *test[1]);
		testPassed = checkValidInput( *test[0], *test[1], *test[2]);
		if ( testPassed != 0 ){
			failedTests[ 26 ] = 1;
			flag += 1;
			printf("test 26 failed - checkValidInput( 50 %s 420 )\n", *test[1] );
		}

	/* time  1, 2 and 3 above max valid */
	for ( i = 10001; i < 10004; i++){
		sprintf( time, "%d", i);
		printf("\twith 50 %s 420..\n", *test[1]);
		testPassed = checkValidInput( *test[0], *test[1], *test[2]);
		if ( testPassed != 0 ){
			failedTests[ i - 9975 ] = 1;
			flag += 1;
			printf("test 0%d failed - checkValidInput( 50 %s 420 )\n", i-9974, *test[1] );
		}
	}

	/* test file calc_fib.c
	 * function callFib and fib */
	flag = 0;
	testPassed =  fib( 10 );
	if ( testPassed != 55 ){
		flag += 1;
		printf("test failed - fib(10)\tshould be 55 got: %d\n", testPassed );
	}
	i = 10;
	/* callFib((void*) &i ); */


	/* all tests complete.
	 * print message showing which and how many failed
	 * or message saying all passed
	 */
	flag = 0;
	for ( i = 0; i < 500; i ++ ){
		if ( failedTests[i] == 1 ){
			if ( flag == 0 )
				printf("Failed Tests:\n");
			flag++;
			printf("\ttest %d failed\n", i );
		}
	}

	free(threads);
	free(time);
	free(n);
	if ( flag > 0 ){
		printf("%d tests failed!\n", flag);
		return 1;}

	printf("All tests Passed!");
	return 0;
}
