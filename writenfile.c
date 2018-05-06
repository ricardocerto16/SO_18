#include "headers/writenfile.h"




int file_writen(char * filename, Array a){

	int fd;
	int i = 0;
	int n;
	//char * buffer;
	char desc[512];
	char com[512];
	char out[1024];
	fd = open(filename, O_TRUNC | O_WRONLY);
	int used = getUsed(a);


	while(i < used){ 
		
		printf("Desc| %s\n", getDescricao(a,i));
		printf("Comando| %s\n", getComando(a,i));
		printf("Output| %s\n", getOutput(a,i));
		printf("---------------\n");

		strcpy(desc,getDescricao(a,i));
		n = write(fd,desc,strlen(desc));
		if (n<0){perror("Erro write"); return 1;}
		n = write(fd,"\n",1);

		strcpy(com,getComando(a,i));
		n = write(fd,com,strlen(com));
		n = write(fd,"\n",1);

		n = write(fd,">>>",3);
		n = write(fd,"\n",1);
		strcpy(out,getOutput(a,i));
		n = write(fd,out,strlen(out));
		n = write(fd,"\n",1);
		n = write(fd,"<<<",3);
		n = write(fd,"\n",1);

		
		i++;
	}

	return 0;


}



int main(int argc, char *argv[]){

	//int res;
	Array a = initArray(5);
	//printstruct(a);

	parser("1.nb",a);

	//printstruct(a);

	int r = execut(a);
	printstruct(a);

	//file_writen("teste2.nb",a);
	



	return 1;
}