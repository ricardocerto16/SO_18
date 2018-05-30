#ifndef __EXECUTE_H__
#define __EXECUTE_H__


#include <stdio.h>
#include <sys/wait.h>
#include "struct.h"
#include "parser.h"



void limpaEspacos(char * t);


char ** argsexecution(char **args, char * comando);


int execut(Array a);

#endif