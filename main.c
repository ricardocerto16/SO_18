#include "headers/execute.h"
#include "headers/writenfile.h"


int main(int argc, char *argv[]){
	int i, r;
	Array a;
	char* res = "EXECUÇÃO BEM SUCEDIDA DO FICHEIRO ";

	if (argc < 2) return -1;

	for (i = 1 ; i < argc ; i++) {
		a = initArray(10);
		parser(argv[i],a);

		r = execut(a);

		if (r >= 0)	{
			file_writen(argv[i],a);
			printf("FICHEIRO ESCRITO COM SUCESSO -> %s\n", argv[i]);
		}
		else 
			printf("FALHA NA EXECUÇÃO DO FICHEIRO -> %s\n", argv[i]);
	}
	freeStruct(a);
	return 0;
}