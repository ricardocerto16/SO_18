#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include "headers/struct.h"
#include "struct.c"



int readlinha(int fd, char * buffer, int nbyte){
	int i = 0;

	 while(i < nbyte-1 &&
         read(fd, buffer+i,1)>0 &&
         buffer[i] != '\n'){
         i++;
    }
    if(i>=nbyte)
           buffer[i] = 0;
    else
           buffer[i+1] = 0;

    return i;
}



int parser(char * filename, Array a){

	int fd, rd , n , x;
	char buffer[512];
	char str[512];
	char * token;
	fd = open(filename,O_RDONLY);
	char cmd[128] = "";
	char desc[512] = "";
	int depends = 0;

	if (fd < 0) {
		perror("Erro a abrir o ficheiro");
		return 0;
	}

	while((n = readlinha(fd,buffer,1000)) > 0) {
	
		//printf("Buffer: %s\n", buffer);
		
		if (buffer[0] == '$' && buffer[1] == '|'){
			strcpy(cmd,buffer);
			depends++;
		}
		else if(buffer[0] == '$'){
			strcpy(cmd,buffer);
			depends = 0;
			//printf("cmd %s\n", cmd);
		}
		else {
			strcpy(desc,buffer);
			//printf("desc %s\n", desc);
		}

		if( (strcmp(desc,"") !=0) && (strcmp(cmd,"") != 0)) {
			//printf("desc -> %s\n", desc);
			//printf("cmd -> %s\n", cmd);
		    insertArray(a,desc,cmd,depends);
			strcpy(desc,"");
			strcpy(cmd,"");
		}
	}


	close(fd);

}


int main(int argc, char *argv[]){
	
	int x;
	Array a = initArray(5);
	x = parser("teste1.nb",a);
	printstruct(a);

	return 0;
}