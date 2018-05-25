#include "headers/writenfile.h"




int file_writen(char * filename, Array a){

	int fd, fd_out, n;
	char * desc = (char *) malloc(1024 * sizeof(char));
	char * com = (char *) malloc(1024 * sizeof(char));
	char * out = (char *) malloc(2048 * sizeof(char));
	int used = getUsed(a);
	
	fd = open(filename, O_TRUNC | O_WRONLY);
	//fd_out = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);

	if (fd < 0 ) {perror("Erro ao escrever output no ficheiro");}

	int i = 0;
	while(i < used){ 
		//printf("i: %d\nused: %d\n",i, used);
		//printf("exec ciclo\n");

		strcpy(desc, getDescricao(a,i));
		n = write(fd,desc,strlen(desc));
		if (n<0){perror("Erro write"); return 1;}
		

		strcpy(com, getComando(a,i));
		n = write(fd,com,strlen(com));
		

		strcpy(out,getOutput(a,i));


		if( (strcmp(out,"") != 0) ){
			n = write(fd,">>>",3);
			n = write(fd,"\n",1);
			n = write(fd,out,strlen(out));
			n = write(fd,"\n",1);
			n = write(fd,"<<<",3);
			n = write(fd,"\n",1);
		}

		i++;
	}

	close(fd);
	close(fd_out);

	return 0;
}



int main(int argc, char *argv[]){

	
	if (argc != 2) {return -1;}

	Array a = initArray(5);
	//printstruct(a);

	parser(argv[1],a);

	//printstruct(a);

	int r = execut(a);

	if (r > 0){ 	
		file_writen(argv[1],a);
	}

	printstruct(a);
	

	return 1;
}