#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include "headers/struct.h"


int readlinha(int fd, char * buffer, int nbyte);


int parser(char * filename, Array a);

