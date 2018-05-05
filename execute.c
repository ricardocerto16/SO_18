#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
//#include "headers/struct.h"
#include "struct.c"
//#include "headers/parser.h"
//#include "parser.c"

void limpaEspacos(char * t){
    int i, j=0;
    for(i=0;t[i]!='\0';i++){
        if(t[i]==' ');
        else { t[j] = t[i]; 
        	   j++;}
    }
    t[j]='\0';
}


char ** argsexecution(char **args, char * comando){
	int i = 0, p;
	char * string;

	string = strtok(comando," ");
	//printf("String %s\n", string);

	while(string != NULL){
		
		args[i] = string;
		string = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;

	args = args + 1;

	for(p=0; p < i-1; p++){
		limpaEspacos(args[p]);
		printf("Arg %d -> |%s| \n",p,args[p]);
	}

	return args;
}



int execut(Array a){

	int i = 0 , f;
	int tam = a->used;
	char ** exec_args = (char**) malloc(tam*sizeof(char *));
	int fd[2];
	int n;
	char * buffer = (char *) malloc(2048 * sizeof(char));


	while(i < tam){
		printf("%d - %d\n",i, tam);
		pipe(fd);
		f = fork();
		if (f == 0) {

			exec_args = argsexecution(exec_args,a->cmd[i]->comando);
			i++;
			close(fd[0]);
			dup2(fd[1],1);
			close(fd[1]);

			
			execvp(exec_args[0],exec_args);
			printf("%d\n", 33);
			_exit(1);
		}
		else{
			 close(fd[1]);
			 wait(NULL);
			 int tama =0;
			 while((n = read(fd[0],buffer,1024)) > 0){
				printf("bytes lidos %d\n", n);
				tama +=n;
			 }
			 buffer[tama-1]='\0';
			
			
			 insertArrayOutput(a,i,buffer);
	  		 //strcpy(buffer,"");
			 i++;
		}

	}


	return 0;
}


int main(int argc, char *argv[]){

	int res;
	Array a = initArray(5);
	char des[50] = "descricao";
	char des11[50] = "cmd 2";
	char cmds[50] = "$ pwd";
	char cmd1[50] = "$ ls -l";
	//char out[50] = "make.c \n x.c";

	res = insertArray(a,des,cmds,0);
	//res = insertArrayOutput(a,0,out);	
	res = insertArray(a,des11,cmd1,0);
	//res = insertArrayOutput(a,1,cmds);
	


	//char * exec_args[20];
	//char coma[128] = "$| ls -l";

	//argsexecution(exec_args,coma);

	int r = execut(a);
	printstruct(a);
	//limpaEspacos(coma);
	return 1;
}