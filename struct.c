#include "headers/struct.h"


struct comando {
	char * descricao;
	char * comando;
	char * output;
	int dependencia;
};


struct array {
	int size;
	int used;
	Comando * cmd;
};

Comando initComando() {
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

	return a;
}



int insertArray(Array a, char * descricao, char * comando, int depends){
	if( a->used >= ((a->size)*0.7)){
		a->cmd = realloc(a->cmd,2*(a->size)*sizeof(Comando));
		a->size = (a->size)*2;
	}
	Comando cmd = initComando();
	a->cmd[a->used] = cmd;
	strcpy(a->cmd[a->used]->descricao,descricao); 
	strcpy(a->cmd[a->used]->comando,comando);
	a->cmd[a->used]->dependencia = depends;
	(a->used)++;
	return 0;  
}



int insertArrayOutput(Array a, int pos ,char * output){
	strcpy(a->cmd[pos]->output,output); 
	return 0;
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
		printf("Output: \n%s\n", a->cmd[i]->output);
		printf("Dependencia: %d\n", a->cmd[i]->dependencia);
		printf("-------------------------\n\n");
	}
}


int getDependencia(Array a, int i){
	return a->cmd[i]->dependencia;
}

int getUsed(Array a){
	int use = a -> used;
	return use;
}

char * getComando(Array a, int i){
	char* cmd = a->cmd[i]->comando;
	char* com = malloc((strlen(cmd) + 1) * sizeof(char));
	strcpy(com, a->cmd[i]->comando);
	return com;
}


char * getDescricao(Array a, int i){
	char* d = a->cmd[i]->descricao;
	char * des = malloc((strlen(d) + 1) * sizeof(char));
	strcpy(des,a->cmd[i]->descricao);
	return des;
}

char * getOutput(Array a, int i){
	char* o = a->cmd[i]->output;
	char * out = malloc((strlen(o) + 1) * sizeof(char));
	strcpy(out,a->cmd[i]->output);
	return out;
}

void freeStruct(Array a){

	int i = getUsed(a);
	int t = 0;

	while (a && t < i) {

		free(a->cmd[t]->descricao);
		free(a->cmd[t]->output);
		free(a->cmd[t]->comando);

		t++;
	}
	free(a);
}
