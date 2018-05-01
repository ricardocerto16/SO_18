#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "headers/struct.h"


struct comando {
	char * descricao;
	char * comando;
	char * output;
	int dependencia;
};


struct array{
	int size;
	int used;
	Comando * cmd;
};

Comando initComando(){
	Comando cmd = malloc(sizeof(struct comando));
	cmd -> dependencia = 0;
	cmd -> descricao = (char *)malloc(512 * sizeof(char));
	cmd -> comando = (char *)malloc(512 * sizeof(char));
	cmd -> output = (char *)malloc(1024 * sizeof(char));
	return cmd;
}

Array initArray(int size){
	Array a = malloc(sizeof(struct array));
	a -> size = size;
	a -> used = 0;
	a -> cmd = malloc(size * sizeof(Comando));
	//a -> cmd = initComando();
	//a -> cmd = malloc(size * sizeof(struct comando));

	return a;
}


// devolver o numero de valores usados?
// para facilitar a inserção
int insertArray(Array a, char * descricao, char * comando){
	if( a->used == a->size){
		a->cmd = realloc(a->cmd,2*(a->size)*sizeof(Comando));
		a->size = (a->size)*2;
	}
	Comando cmd = initComando();
	a->cmd[a->used] = cmd;
	strcpy(a->cmd[a->used]->descricao,descricao); 
	strcpy(a->cmd[a->used]->comando,comando);
	(a->used)++;
	return 1;  
}



int insertArrayOutput(Array a, int pos ,char * output){

	strcpy(a->cmd[pos]->output,output); 

	return 1;
}


void printstruct(Array a){

	int i;

	printf("Size : %d\n", a->size);
	printf("Used : %d\n", a->used);
	printf("-----------------------\n");

	for(i=0; i < a->used ; i++){

		printf("Nodo : %d \n", i);
		printf("Descricao: %s\n", a->cmd[i]->descricao);
		printf("Comando: %s\n", a->cmd[i]->comando);
		printf("Output: %s\n\n", a->cmd[i]->output);
	}

}

int main(int argc, char *argv[]){
	
	int res;
	Array a = initArray(5);
	char des[50] = "descricao";
	char des11[50] = "cmd 2";
	char cmds[50] = "ls -l";
	char out[50] = "make.c \n x.c";


	res = insertArray(a,des,cmds);
	res = insertArrayOutput(a,0,out);
	
	res = insertArray(a,des11,cmds);
	res = insertArrayOutput(a,1,cmds);
	
	printstruct(a);

	return 0;
}