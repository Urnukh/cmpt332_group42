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

#ifndef SHELL_COMMANDS_H_
#define SHELL_COMMANDS_H_

#include "partE_shell_get_input.h"
struct stat;
const char *findCommand( char *commandQuery);
int compareCurrentBinary( const char *dir, const struct stat *info,
                const int typeflag );
int executeCommand( FormattedCommand *command );


#endif
