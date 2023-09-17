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

/* header file for shell_get_input.c */

#ifndef SHELL_GET_INPUT_H_
#define SHELL_GET_INPUT_H_

typedef struct {
    char **parsedInput;
    int length;
}ParsedInput;

typedef struct {
    char *command;
    char *commandAndArgs;
    char *numberOfPipes;
    int redirectedFlag;
    char *redirectFile;
}FormattedCommand;


char *getInput();
ParsedInput *parseInput( char *input );
FormattedCommand *formatParsedToCommand( ParsedInput *parsed );


#endif
