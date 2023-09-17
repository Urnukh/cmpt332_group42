/*
# Urnukh Tsogt
# URT633
# 11267557
#
# Mitchell Risling
# MJR810
# 11221612
#
# CMPT332
# a01-phase01
# 09:00, 19/09/2022
*/

/* functions that are used across multiple partE files */

#include "partE_shell_common.h"
#include "partE_shell_get_input.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * wrapper for Malloc. will called lots, so this cleans the code up
 * a little bit
 * preconds; variable to hold pointer is declared
 *  args:
 *          n: number of elements
 *          size: element size in bytes
 *  postcond: n * size bytes are allocated
 *  return: a pointer to the new memory
 */
void *Malloc( int n, int size ){
    void *pointer;
    if ( ! ( pointer =  malloc ( n * size ))){
        fprintf(stderr, "error allocating memory \n");
        return NULL;
    }
    return pointer;
}

void FreeParsedInput( ParsedInput *input ){

    /* for ( i = 0; i < input->length; i++ ) */
    /*     free(input->parsedInput[i] ); */
    free(input->parsedInput);
    free(input);
}
