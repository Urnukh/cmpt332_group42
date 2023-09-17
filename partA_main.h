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
// a01-phase01
// 09:00, 19/09/2022

// main file for partA1
*/

#ifndef PARTA_MAIN_H_
#define PARTA_MAIN_H_

typedef struct procArgs{
    int numberOfChildren;
    unsigned int time;
    int n;
}procArgs;


/* global variable */
extern int size;
extern int part;
extern int keepRunning;
extern int callsToFib[];
extern unsigned long int childIndexes[];

/*
 * functions
 */

/* part 1 */
unsigned long int getWINThreadID();
unsigned int createWINChildren(void *args );
unsigned int createWINParent( void *args );
/* part 2 */
void createUBCChildren( void *args );
int createUBCParent( void *args );
/* part 3 */
unsigned long int getLinuxThreadID();
void *createPOSIXChildren( void *args );
int createPOSIXParent( void *args );
/* 2 and 3 */
unsigned long int getLinuxThreadID();
int createLinuxParent( int threads, unsigned long int deadline, int size, int part );
/* createUNIXThread(); */


/* 1 2 and 3 */
int checkValidArgNumber( int argc );
int checkValidInput( char *threads, char *time, char *n);


unsigned long int getThreadsID();
int getThreadIndex();
int fib( int n );
void *callFib( void *n );
void callCallFib( void *n );
unsigned int winCallFib( void *n );


#endif
