#include "headers/parser.h"

int readlinha(int fd, char * buffer, int nbyte){
	int i = 0;
	char* p = buffer;


	while(i < nbyte && read(fd, p + i, 1 ) > 0)  {
		printf("i -> %s\n",p);
		if (p[i] == '\n'){
			buffer[i] = '\0';
			return i + 1;
		}

		if (p[i] == '\0') {
			return i + 1;
		}

		i++;
	}
	return i;
}



int parser(char * filename, Array a){

	int fd, n;
	char * buffer = (char *) malloc(512 * sizeof(char));;
	fd = open(filename,O_RDONLY);
	char * cmd = (char *) malloc(256 * sizeof(char));  
	char * desc = (char *) malloc(512 * sizeof(char));;
	int depends = 0;
	char * num = (char *) malloc(20 * sizeof(char));;
	int i;
	int descartar = 0;

	if (fd < 0) {
		perror("Erro a abrir o ficheiro");
		return 0;
	}

	while((n = readlinha(fd,buffer,1024)) > 0) {
		
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

			while (isdigit(buffer[i])) {
				strcat(num, &buffer[i]);
				i++;
			}
			strcpy(cmd,buffer);
			depends = atoi(num);
		}
		else {
			if ((strcmp(buffer,">>>") == 0))
				descartar = 1;
			
			else if ((strcmp(buffer,"<<<") == 0)) {
				descartar = 0;
				strcpy(buffer,"");
			}

			if (descartar == 0)
				strcpy(desc,buffer);
		}

		if( (strcmp(desc,"") !=0) && (strcmp(cmd,"") != 0)) {
		    insertArray(a,desc,cmd,depends);
			strcpy(desc,"");
			strcpy(cmd,"");
			free(buffer);
			buffer = (char *) malloc(512 * sizeof(char));;
		}
	}


	close(fd);
	return 0;
}

