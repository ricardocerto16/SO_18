#include "headers/writenfile.h"

int file_writen(char * filename, Array a){

	int fd, n, i = 0;
	char * desc = (char *) malloc(1024 * sizeof(char));
	char * com = (char *) malloc(1024 * sizeof(char));
	char * out = (char *) malloc(2048 * sizeof(char));
	int used = getUsed(a);
	
	fd = open(filename, O_TRUNC | O_WRONLY);

	if (fd < 0 ) 
		perror("Erro a abrir o ficheiro");

	while(i < used){ 
		strcpy(desc, getDescricao(a,i));
		strcat(desc,"\n");
		n = write(fd,desc,strlen(desc));
		if (n < 0) {
			perror("Erro write");
			return 1;
		}
	
		strcpy(com, getComando(a,i));
		n = write(fd,com,strlen(com));

		out = getOutput(a,i);

		//strcpy(out,getOutput(a,i));

		if(strcmp(out,"") != 0){
			n = write(fd,"\n>>>",4);
			n = write(fd,"\n",1);
			n = write(fd,out,strlen(out));
			n = write(fd,"<<<",3);
			n = write(fd,"\n",1);
		}
		i++;
	}

	close(fd);
	return 0;
}