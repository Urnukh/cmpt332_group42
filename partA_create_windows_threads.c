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
*/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include "partA_main.h"
                    /* 10,000 */
const int STACK_SIZE = 10000;

/*
 * used to get threadID of winthread inside the fib func
 * precond: called from a win thread
 * postcond: none
 * return: lu - dword - thread id of calling thread
 */
unsigned long int getWINThreadID(){
    return (unsigned long int) GetCurrentThreadId();
}


/*
 create a windows thread that calculates threadFunc up to n
precond: FIBCOUNTS is defined
postcond: new thread is created calculating threadFunc up to n
return 1
*/
unsigned int createWINChildren( void *args) {
    int i;
    HANDLE thread;
    LPDWORD threadID;

    for ( i = 0; i < ( (procArgs*)args)->numberOfChildren; i++ ){
        if ( ! ( threadID = (LPDWORD) malloc( 1 * sizeof(LPDWORD)  ))){
            fprintf( stderr, "Error allocating memory\n");
            exit(1);
        }
        thread = CreateThread(
                NULL,
                STACK_SIZE,
                &winCallFib,
                args,
                0,
                threadID );
        if ( ! thread ){
            printf("error creating thread number: %d\nquitting...\n", i);
            exit(1);
        }
        childIndexes[i] = *(long unsigned int *) threadID;
    }

    return 1;
}

/* create a windows parent thread who will run createWINThread
 * precond: command line args valid, put in struct and cast to void
 *  args:
 *      args: struct containing threads deadline and size
 *  postconds: children threads are created who run fib
 *  return 0 if successful, 1 otherwise
 */
unsigned int createWINParent( void *args ){
    HANDLE thread;

    thread = CreateThread(
            NULL,
            STACK_SIZE,
            &createWINChildren,
            args,
            0,
            NULL );

    if ( ! thread ){
        fprintf( stderr, "error creating parent thread\nquitting...\n");
        exit(1);
    }
    Sleep( ((procArgs*)args)->time * 1000 );

    return 0;
}
