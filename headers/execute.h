#ifndef __EXECUTE_H__
#define __EXECUTE_H__

//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
//#include <fcntl.h>
//#include <sys/types.h>
#include "struct.h"
#include "parser.h"



void limpaEspacos(char * t);


char ** argsexecution(char **args, char * comando);


int execut(Array a);

#endif