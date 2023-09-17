 /* Urnukh Tsogt
 URT633
 11267557

 Mitchell Risling
 MJR810
 11221612

 CMPT332
 a01-phase01
 09:00, 19/09/2022
 */

/* everything related to getting and validating input for part E */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partE_shell_common.h"
#include "partE_shell_get_input.h"


const int INPUT_BUFFSIZE = 256;
/*
 * get input from user and store it in a dynamic array until the user presses
 * the return key
 * precond: none
 * postcond: an array is created with space allocated. use input is stored here
 * return: nothing
 */
char *getInput(){
    int counter, buffSize;
    char *input, currentChar;
    buffSize = INPUT_BUFFSIZE;
    if ( ! ( input = (char*) Malloc( buffSize, sizeof(char) )))
        exit(EXIT_FAILURE);

    /*
     * main loop that will get all the user input one character at a time
     * updating the amount of memory for the input if it gets to the max
     */
    counter = 0;
    while(1){
        if ( counter % buffSize == 0 )
            if ( ! ( input = realloc( input, (counter / buffSize + 1 )\
                            * buffSize * sizeof(char) ))){
                fprintf(stderr, "error allocating memory for input\n");
                exit(EXIT_FAILURE);
            }

        currentChar = getchar();
        /* on newline append null char and break out of loop */
        if ( currentChar == '\n' ) {
            input[counter] = '\0';
            break;
        }
        /* if we get here put currentchar in input at index counter and
           increment */
        input[counter++] = currentChar;
    }
    return input;
}

/*
 * take char string and tokenize it into a array of strings
 * based on the white space in the argument
 * precond: input has been properly recieved and stored in a char array
 *  args:
 *      input: a string that has been entered on std in and stored in array
 * return: a new array of strings with tokenized based on input
 */
ParsedInput *parseInput( char *input ) {
    unsigned long int i;
    int count, spaceFlag, outputIndex;
    char *currentOutput, **output;
    ParsedInput *parsed;
    /* allocate 5 pointers in output to point to:
     *      command
     *      flags
     *      arguments
     */

    /* create enough space for 5 pointers. shouldnt need more than
     * that 99 % of the time i would think. */
    if ( ! ( output = (char**) Malloc( 5, sizeof(char) )))
        exit(EXIT_FAILURE);
    /*
     * initializer counters / flags to 0 and begin looping through input string
     * if we encounter a space set the flag, on the first space (count !=0 )
     * copy the last (counter) chars to newly allocated space currentOutput.
     *      we will also get here on string terminator, have an extra if
     *      to handle that by assigning current input char to end and moving
     *      null char to right one.
     *  will increment a counter everytime we dont hit a space so we know
     *  how many characters to copy into new string to add to output arr
     */
    outputIndex = spaceFlag = count = 0;
    for ( i = 0; i < strlen(input); i++ ) {
        if (input[i] == 124 ){
            printf("fuck\n");
        }
        if ( input[i] == 32 || input[i + 1] == 0 ){
            spaceFlag = 1; /* keep setting flag to one on each space */
            if ( count != 0 || i == 0  ){ /* here to else gets called once per
                                             space grp, i == 0 handles single
                                             vhar case */
                if ( ! ( currentOutput = Malloc( count + 2, sizeof(char) ) ))
                    exit(EXIT_FAILURE);

                strncpy( currentOutput, &input[i - count], count );
                currentOutput[count] = '\0';

                /* this is special case for encounter \0 instead of space */
                if ( input[i + 1] == 0 ){
                    currentOutput[count] = input[i];
                    currentOutput[count + 1] = '\0';
                }

                output[outputIndex] = currentOutput;
                outputIndex++;
                count = 0;
            }

        } else{
            spaceFlag = 0;
        } /* use dif if block so we dont miss first char after flag set =0 */
        if ( spaceFlag == 0 ) {
            count++;
        }
    }

    /* done with input. can be freed */
    free(input);

    /* have our separated string and its length. allocate and populate
     * ParsedInput struct with values */
    if ( ! ( parsed = (ParsedInput*) Malloc( 1, sizeof(ParsedInput) )))
        exit(EXIT_FAILURE);
    parsed->parsedInput = output;
    parsed->length = strlen(*output);
    return parsed;
}

/*
 * take string array and turn it into a struct that will
 * hold the commands in a format that will be easy to execute
 * precond: input has been successfuly parsed into string arr and cmd exists
 *  args:
 *      parsed: struct containing a string array and its length
 *  postcond: all mem used by parsed and its contents will be freed
 *  return a new struct that contains tha command, its args, whether
 *  its piped or redirected and the file descriptor its redirected to / from
 */
FormattedCommand *formatParsedToCommand( ParsedInput *parsed ) {
    FormattedCommand *formattedCommand;
    char *command;
    int  argsFlag;
    argsFlag = 1;
    if ( ! ( formattedCommand =
                (FormattedCommand*) Malloc( 1, sizeof(FormattedCommand) )))
        exit(EXIT_FAILURE);


    printf( "string: %s\n", parsed->parsedInput[0] );
    printf( "legbn %lu\n", strlen(parsed->parsedInput[0] ));
    if (! parsed->parsedInput[1]) argsFlag = 0;
    if ( argsFlag == 1 ){
        if ( ! ( command =
                    (char*) Malloc(
                        strlen(parsed->parsedInput[0]) +
                        strlen(parsed->parsedInput[1]) + 1,
                        sizeof(char) )))
            exit(EXIT_FAILURE);
    }else{
        if ( ! ( command =
                    (char*) Malloc(
                        strlen(parsed->parsedInput[0]) + 1,
                        sizeof(char) )))
            exit(EXIT_FAILURE);
    }


            FreeParsedInput( parsed ); /* done with this. free or sad */
        return formattedCommand;
    }
