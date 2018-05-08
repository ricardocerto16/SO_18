#include "headers/execute.h"


void limpaEspacos(char * t){
    int i, j=0;
    for(i=0;t[i]!='\0';i++){
        if(t[i]==' ' || t[i] == '\n');
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
	int tam = getUsed(a);
	char ** exec_args = (char**) malloc(tam*sizeof(char *));
	int fd[2];
	int n;
	char * buffer = (char *) malloc(2048 * sizeof(char));


	while(i < tam){
		//printf("%d - %d\n",i, tam);
		pipe(fd);
		f = fork();
		if (f == 0) {
			printf("Argumentos em execução\n");
			exec_args = argsexecution(exec_args,getComando(a,i));
			close(fd[0]);
			dup2(fd[1],1);
			close(fd[1]);
			i++;
			
			execvp(exec_args[0],exec_args);
			_exit(1);
		}
		else{
			 close(fd[1]);
			 wait(NULL);
			 int tama =0;
			 while((n = read(fd[0],buffer,2048)) > 0){
				//printf("bytes lidos %d\n", n);
				tama +=n;
			 }
			 buffer[tama-1]='\0';
			
			 //printf("Buffer %d -> %s\n",i, buffer);
			 insertArrayOutput(a,i,buffer);
	  		 //strcpy(buffer,"");
			 i++;
		}

	}


	return 0;
}

/*
int main(int argc, char *argv[]){

	int x;
	Array a = initArray(5);
	
	x = parser("teste2.nb",a);
	//printstruct(a);

	int r = execut(a);
	printstruct(a);

	return 1;
}*/