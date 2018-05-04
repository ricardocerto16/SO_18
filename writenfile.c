#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
//#include "headers/struct.h"
#include "struct.c"
//#include "headers/parser.h"
//#include "parser.c"







int file_writen(char * filename, Array a){

	int fd;
	int i = 0;
	int n;
	//char * buffer;
	char desc[512];
	char com[512];
	char out[1024];
	fd = open(filename, O_TRUNC | O_WRONLY);
	printf("size %d\n\n", a->used);


	while(i < a->used){ 
		
		printf("Desc| %s\n", a->cmd[i]->descricao);
		printf("Comando| %s\n", a->cmd[i]->comando);
		printf("Output| %s\n", a->cmd[i]->output);
		printf("---------------\n");

		strcpy(desc,a->cmd[i]->descricao);
		n = write(fd,desc,strlen(desc));
		if (n<0){perror("Erro write"); return 1;}
		n = write(fd,"\n",1);

		strcpy(com,a->cmd[i]->comando);
		n = write(fd,com,strlen(com));
		n = write(fd,"\n",1);

		n = write(fd,">>>",3);
		n = write(fd,"\n",1);
		strcpy(out,a->cmd[i]->output);
		n = write(fd,out,strlen(out));
		n = write(fd,"\n",1);
		n = write(fd,"<<<",3);
		n = write(fd,"\n",1);

		
		i++;
	}

	return 0;


}



int main(int argc, char *argv[]){

	int res;
	Array a = initArray(5);
	char des[50] = "descricao";
	char des11[50] = "cmd 2";
	char cmds[50] = "ls -l";
	char out[50] = "make.c \n x.c";

	res = insertArray(a,des,cmds,0);
	res = insertArrayOutput(a,0,out);	
	res = insertArray(a,des11,"ls",0);
	res = insertArrayOutput(a,1,cmds);
	


	char * exec_args[20];
	char coma[128] = "ls -l";

	//argsexecution(exec_args,coma);

	//int r = execut(a);
	//sleep(5);
	//printstruct(a);

	int fw = file_writen("example.nb",a);


	return 0;
}