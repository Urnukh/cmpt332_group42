/*
 * Urnukh Tsogt
// URT633
// 11267557
//
// Mitchell Risling
// MJR810
// 11221612
//
// CMPT332
// a01-phase01
// 09:00, 19/09/2022
*/
#include <stdio.h>
#include <sys/time.h>
#ifdef __linux__
	#include <pthread.h>
    #include <standards.h>
    #include <os.h>
#endif
#ifdef _WIN32
    #include <windows.h>
#endif
#include "partA_main.h"

/* simple function to get the threads id. will use global
 * part variable to determine which to call. doesn't seem to want to
 * work though.....
 */
unsigned long int getThreadsID(){
#ifdef _WIN32
    return  getWINThreadID();
#elif __linux__
    return getLinuxThreadID();
#else
    return  getWINThreadID();
#endif
    return -1;
}
/*
 * used to get the index of counter that should be updated
 * not sure how else to endure that everything gets a unique index other than
 * to put them in incrementally as they're created
 * precond: this is called from thread other than main thread
 * postcond: none
 * return: the index of the callstofib array that should be updated
 */
int getThreadIndex(){
    int arraySize, index;
    unsigned long int threadID;

    threadID = getThreadsID();
    arraySize = size;

    for ( index = 0; index < arraySize; index++ )
        if ( childIndexes[index] == threadID )
            return index;
    return -1;
}

/*
 * calculate fib number while incrementing parent variable each time t
 * precond: none
 * post-cond: count incremented by one.
 * return fib # or recursive calls to base
 */
int fib( int n ){
    /* incremenent global parent count */
    /* check keep running variable with base check */
    unsigned long int index;
    if ( keepRunning == 0 )
        return 0;

    /* update count of fib calls */
    index = getThreadIndex();
    callsToFib[index]++;
    if ( n <= 1 )
        return n;
    return fib(n-1) + fib(n-2);
}

/*
 * wrapper for fab()
 * pthreads and winthreads need void func. so this
 * accomplishes that
 */
void *callFib( void *n ){
    int i, index;
    long secsUsed, microSecsUsed;
    struct timeval start, end;

    index = getThreadIndex();

    /* store start time */
    gettimeofday(&start, NULL);

    for ( i = 1; i <= ( *(int*) n); i++ ){
        fib( i );
        if ( keepRunning == 0 )
            break;
    }

    /* get end time and print results */
    gettimeofday(&end, NULL);
    secsUsed = end.tv_sec - start.tv_sec;
    microSecsUsed = end.tv_usec - start.tv_usec;

    printf("Thread: %16ld - ran for: %4lu seconds, %4lu microseconds, and" \
        " called fib %5d times \n",
            getThreadsID(), secsUsed, microSecsUsed,  callsToFib[index] );
    return 0;
}

/* hahahahahahahahaha */
void callCallFib( void *n ){
    callFib(n);
}

unsigned int winCallFib( void *n ){
    callFib(n);
    return 0;
    }
