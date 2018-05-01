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



void argsexecution(char *args[20], char * comando){
	int i = 0;
	char * string;

	string = strtok(comando," ");
	printf("String %s\n", string);

	while(string != NULL){
		args[i] = string;
		string = strtok(NULL, " ");
		printf("Arg%d -> %s \n",i,args[i]);
		i++;
	}
	args[i] = NULL;

}



int execut(Array a){

	int i = 0 , f, execution;
	int tam = a->used;
	Comando comaux;
	char * exec_args[20];
	char * coma;

	while(i < tam){
		f = fork();
		if (f == 0) {
			//strcpy(coma,a->cmd[i]->comando);
			//printf("Comando %s\n", coma);

			argsexecution(exec_args,a->cmd[i]->comando);
			execution = execvp(exec_args[0],exec_args);
			_exit(execution);
		}
		else{
			// ver como o pai vai buscar o output do filho e o guarda na estrutura
		}

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
	//res = insertArrayOutput(a,0,out);	
	res = insertArray(a,des11,cmds,0);
	//res = insertArrayOutput(a,1,cmds);
	


	char * exec_args[20];
	char coma[128] = "ls -l";

	//argsexecution(exec_args,coma);

	int r = execut(a);

	return 0;
}