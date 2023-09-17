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
#include <string.h>
#include "partE_shell_common.h"
#include "partE_shell_get_input.h"
#include "partE_shell_commands.h"

/* mainfile for partE linux shell */


/*
 * TODO!!!!!!!
 * MEMORY THAT HAS BEEN ALLOCATED THAT HAS NOT YET BEEN FREED
 * PARSED INPUT AND ALL ITS STRINGS
 * DIR RETURNED IN FINDCOMMAND
 */


int main(){
    char *userInput, *x;
    ParsedInput *parsed;
    FormattedCommand *command;
    int i;

    parsed = NULL;
    if ( ! ( x = Malloc( 256, sizeof(char) )))
        exit(EXIT_FAILURE);
    while(1){
        userInput =  getInput();
        parsed = parseInput( userInput );
        x = (char*)findCommand( parsed->parsedInput[0] );
        if ( ! x ){
            fprintf( stderr, "command: %s not found \n", parsed->parsedInput[0] );
            continue;
        }

        parsed->parsedInput[parsed->length] = x;
        parsed->length++;
        command = formatParsedToCommand( parsed );
        i = executeCommand( command );
        (void) i;

    }
    return 0;

}
