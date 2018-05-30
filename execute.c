#include "headers/execute.h"


void limpaEspacos(char * t){
    int i, j=0;
    for(i=0;t[i]!='\0';i++){
        if(t[i]==' ' || t[i] == '\n');
        else { 
			t[j] = t[i]; 
        	j++;
		}
    }
    t[j]='\0';
}


char ** argsexecution(char **args, char * comando){
	int i = 0, p;
	char * string;

	string = strtok(comando," ");

	while(string != NULL){
		
		args[i] = string;
		string = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;

	args = args + 1;

	for(p=0; p < i-1; p++){
		limpaEspacos(args[p]);
	}

	return args;
}

// 0 -> leitura
// 1 -> escrita


int execut(Array a){

	int i = 0 , f;
	int tam = getUsed(a);
	char ** exec_args = (char**) malloc(tam*sizeof(char *));
	int fd[2];
	int n;
	char * buffer = (char *) malloc(2048 * sizeof(char));
	char * output = (char *) malloc(2048 * sizeof(char));
	int dependencia;
	int saida[2];
	int status, res;

	while(i < tam){
		pipe(fd);
		pipe(saida);
		dependencia = getDependencia(a,i);

		if( dependencia == 0) {
			f = fork();
			if (f == 0) {
				exec_args = argsexecution(exec_args,getComando(a,i));
				close(fd[0]);
				dup2(fd[1],1);
				close(fd[1]);
			
				execvp(exec_args[0],exec_args);
				_exit(1);
			}
			else {

				if (f < 0) { perror("Erro no fork"); return -1;}

			 	close(fd[1]);
				wait(&status);
			 	int tama =0;
				while((n = read(fd[0],buffer,2048)) > 0){
					tama +=n;
			 	}
				buffer[tama-1]='\0';
			
			 	insertArrayOutput(a,i,buffer);
	  		 	
			}
		}
		else if (dependencia > 0){
			
			if (i - dependencia < 0) { 
				perror("Dependencia Inválida"); 
				return -1;
			}

			f = fork();
			if(f == 0) {

				exec_args = argsexecution(exec_args,getComando(a,i));

				dup2(saida[0],0);
				close(saida[1]);
				close(saida[0]);

				close(fd[0]);
				dup2(fd[1],1);
				close(fd[1]);

				execvp(exec_args[0],exec_args);
				_exit(1);
			}
			else {

				if (f < 0) { 
					perror("Erro no fork"); 
					res = -1;
				}

				close(saida[0]);
				output = getOutput(a,(i - dependencia));
				write(saida[1],output,strlen(output)+1);
				close(saida[1]);

				wait(&status);
				close(fd[1]);

				int tama =0;
				while((n = read(fd[0],buffer,2048)) > 0)
					tama +=n;
			 	
				buffer[tama-1]='\0';

			 	insertArrayOutput(a,i,buffer);
			}
		  }
		 i++;

		 if (WIFEXITED(status))
				res = WEXITSTATUS(status);
	
		 else 
				return -1;
		}
	return res;
}

