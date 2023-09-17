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
#include <pthread.h>
#include <standards.h>
#include <os.h>
#include "partA_main.h"
                    /* 10,000*/
const int STACK_SIZE =10000;
/*
 * Linux threads
 */

unsigned long int getLinuxThreadID(){
    if ( part == 2 )
       return MyPid();
    return  pthread_self();

}


/* create UBC thread to run callcallFib
 * precond: parent thread was created succesfully
 *  args:
 *      args: void pointer to struct containing threads, deadline, size
 * postcond: threads children are created who calculate fibs
 * return: none
 */
void createUBCChildren( void *args ){
    int child, i, stackSize;
    PID thread;

    stackSize = STACK_SIZE;

    for ( i = 0; i < ( (procArgs*)args)->numberOfChildren; i++ ){
        thread = Create(
                callCallFib,
                stackSize,
                (char*) &i,
                (void *) &((( procArgs*)args)->n),
                NORM,
                USR );
        if ( thread == PNUL ){
            printf("error creating thread number: %d\nquitting...\n", i);
            exit(1);
        }
        /* i know theres a faster way to do this byt im low on time and
         * want to get as much done as possible.
         * could give those a uniwue name and use that to index in
         * fib file. will change if i have time.
         */
        childIndexes[i] = thread;
    }
    for ( child = 0; child < ((procArgs*)args)->numberOfChildren; child ++ ) {
        Kill( childIndexes[child] );
    }
    Sleep( ((procArgs  *)args)->time * 10 ); /*i think this is 1 second */
    Sleep( 10 ); /*i think this is 1 second */
    return;
}

/* create Parent thread that will create threads children who will run
 * callFib
 * precond: arguments have peen properly added to struct and given as void ptr
 *  args:
 *      args: void pointer struct containng threads deadline and size
 * return 0 if successfull, 1 otherwise
 */
int createUBCParent( void *args ){
    PID  thread;
    int stackSize;
    char *parent = "daddy";

    stackSize = STACK_SIZE;
    thread = Create(
            (void(*)())createUBCChildren,
            stackSize,
            parent,
            (void *) &args,
            NORM,
            USR );
    if ( thread != 0 ) {
        printf("Error creating parent thread. error: %ld\nQuitting...\n",
                thread);
        exit(1);
        return 1;
    }
    return 0;
}
/*
 * create POSIX thread that calcs fib number starting at 1 and ending at n
 * precond: args have been validated on command line and are cast to int
 *          parent was created successfully
 *  args: n - number to calculate fib to
 * postcond: a thread is created that will begin calculating fibs
 *           global variable callsToFib will have one if its indices
 *           incremented a number of times
 * return: 0 on success, error number on failure
 */
void *createPOSIXChildren( void *args ) {
    int i, thread;
    for ( i = 0; i < ( (procArgs*)args)->numberOfChildren; i++ ){
        pthread_t  threadID;
        thread = pthread_create(
                &threadID,
                NULL,
                callFib,
                (void *) &((( procArgs*)args)->n));
        if ( thread != 0 ){
            printf("error creating thread number: %d\nquitting...\n", i);
            exit(1);
        }
        childIndexes[i] = threadID;
    }
    return 0;
}


/* create Posix parent that will create children threads and then sleep
 * for deadline time before changing a variable and sleeping a lil so the
 * kiddies can print
 * precond: args have been validated on the command line and cast.
 *  args:
 *      args: void pointer to a struct containing the args for
 *      creating children thread routines
 *  return 0 on success, 1 otherwise
 */
int createPOSIXParent( void *args ) {
    int i;
    pthread_t parent;
    i = pthread_create(
            &parent,
            NULL,
            &createPOSIXChildren,
            (void *) args );
    if ( i != 0 ) {
        printf("error creating parent thread. error: %d\nquitting...\n", i);
        exit(1);
        return 1;
    }
    sleep( ((procArgs*)args)->time );
    keepRunning = 0;
    sleep (1); /* should give kids time to print */
    return 0;
}

/*
 * this will be the main function that all linux parts will call.
 * takes args and puts in struct and calls appropriate createxxxParent
 * to actually create the parent thread and begin the fibs
 * precond: input has been validated and converted to ints
 *  args:
 *      threads: char string that has been converted to an integer
 *      deadline: char string..    " "                  a long unsigned int
 *      size: a char string...     " "                  an integer
 *      part: int 2-4 inclusive indicating which part to create..
 *                          which type of thread POSIX ro UBC or UNIX
 *  postcond: none
 *  return: the return value of createxxxparents which is 0 on success
 *                                                        1 on fauilure
 */
int createLinuxParent(int threads, unsigned long int deadline,
        int size, int whichPart) {

    /* declare and fill argStruct with the arguments */
    procArgs args;
    int parentReturn;
    args.numberOfChildren = threads;
    args.time = deadline;
    args.n = size;

    switch (whichPart) {
        case 2:
            parentReturn = createUBCParent( (void*) &args );
            break;
        case 3:
            parentReturn = createPOSIXParent( (void*) &args );
            break;
        default:
            fprintf(stderr, "invalid part\n");
            parentReturn = 1;
            break;
    }
    return parentReturn;
}
/* createUNIXThread(); */
