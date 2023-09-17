 /* Urnukh Tsogt URT633
 11267557

 Mitchell Risling
 MJR810
 11221612

 CMPT332
 a01-phase01
 09:00, 19/09/2022
 */

/* functions related to finding and executing commands, piping, and redirection
 * of input / output. */

/* standard dirs that we will search for binaries */

#include "partE_shell_get_input.h"
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>
#include <ftw.h>
#include <unistd.h>
#include <sys/wait.h>
#include "partE_shell_commands.h"


const char *BINARY_DIRS[6] = {
    "/usr/local/sbin",
    "/usr/local/bin" ,
    "/usr/sbin" ,
    "/usr/bin",
    "/sbin",
    "/bin" };


char *commandSearched;
/*
 * loop through BINARY_DIRS amd search for command entered.
 * precond: input was able to be split into array of strings
 *  args:
 *      *commandQuery: first index of array string. where the command should
 *                     have been entered.
 * postcond: none
 * return: directory where command was found or NULL if not found
 */
const char *findCommand( char *commandQuery ) {
    int depth, found;
    unsigned long int i;
    commandSearched = commandQuery;
    depth = 13;/* consensus online said unstable after 15 levels slows at 13 */
    for ( i = 0; i < sizeof( BINARY_DIRS ) / sizeof( BINARY_DIRS[0] ); i++ ){
        if (( found = ftw( BINARY_DIRS[i], compareCurrentBinary, depth)) == 1 ){
            return BINARY_DIRS[i];
        }
    }

    return NULL;
}

/*
 * search in directory for command
 * precond: first index of string array was properly passed to findcommand
 *  args:
 *      dir: full path of current item (file sym link. dir...)
 *      stat: info about current item
 *      typeflag: flag that states what type item is. all we want is FTW_F
 *  postcond: none
 *  return: 1 if command was found, 0 otherwise
 */

int compareCurrentBinary( const char *dir, const struct stat *info,
        const int typeflag ){

    unsigned long int commandLength;
    /* automatically return if they aren't the same length */
    if ( ( commandLength = strlen( commandSearched ) ) !=
            ( strlen( basename( (char*) dir ))))
        return 0;

    (void) info; /* bye bye warning */

    /* if we type is file, compare it to the min of the 2 length of string
     * to avoid memory errors ( maybe strncmp stops after one is null??)
     * euther way, is safe.
     * if result of strncmp is 0 - command found. return one so we know to
     * break out of loop and hold index (path) command is in. */
    if (typeflag == FTW_F )
        return ( strncmp( commandSearched, basename( (char*) dir ),
                commandLength ) == 0 ) ? 1 : 0;

    return 0;
}

/* take struct containg formatted command pass it to execl to execute
 * command
 * precond: input was able to be parsed into an available binary
 * args:
 *      command: command struct containing everything we need to run command
 *  return 0 for and child succeeded, error code otherwise
 */
int executeCommand( FormattedCommand *command ) {
    int rc, rc_wait;
    rc = fork();
    if (rc < 0 ){
        fprintf( stderr, "Fork failed. exiting...\n" );
        exit(EXIT_FAILURE);
    }else if ( rc == 0 ) /* child */
        execv( command->command, &command->commandAndArgs );
    else { /* parent */
        wait(&rc_wait);
        return WEXITSTATUS( rc_wait );
    }
    return -1; /* don't think we shhould get here */
}
