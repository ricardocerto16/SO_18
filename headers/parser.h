#ifndef __PARSER_H__
#define __PARSER_H__

#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "struct.h"


int readlinha(int fd, char * buffer, int nbyte);

int parser(char * filename, Array a);

#endif