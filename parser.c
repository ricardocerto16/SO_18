#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <fildes.h>
#include "headers/struct.h"


int parser(char * filename, Array a){

	int fd;
	fd = open(filename,O_RDONLY);
	char cmd[128];
	char desc[512];
	int depends = 0;

	if (fd < 0) {
		perror("Erro a abrir o ficheiro");
		return 0;
	}

	



	fclose(fd);

}