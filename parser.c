#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
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
	char aux[512];
	fd = open(filename,O_RDONLY);
	char cmd[128] = "";
	char desc[512] = "";
	int depends = 0;
	char *dep[5];
	char num[20] = "";
	int i;
	char * string;

	if (fd < 0) {
		perror("Erro a abrir o ficheiro");
		return 0;
	}

	while((n = readlinha(fd,buffer,1000)) > 0) {
	

		// remover valores dependencia de um comando

		if (buffer[0] == '$' && buffer[1] == '|'){
			strcpy(cmd,buffer);
			depends = 1;
		}
		else if(buffer[0] == '$' && buffer[1] == ' '){
				strcpy(cmd,buffer);
				depends = 0;
		}
		else if(buffer[0] == '$'){
			i = 1;
			while(isdigit(buffer[i])){
				strcat(num,&buffer[i]);
				i++;
			}
			strcpy(cmd,buffer);
			depends = atoi(num);
			}
		else {
			strcpy(desc,buffer);
		}

		if( (strcmp(desc,"") !=0) && (strcmp(cmd,"") != 0)) {
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
