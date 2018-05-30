#include "headers/execute.h"
#include "headers/writenfile.h"


int main(int argc, char *argv[]){
	if (argc != 2) {return -1;}

	Array a = initArray(5);

	parser(argv[1],a);

	int r = execut(a);

	if (r >= 0){ 	
		file_writen(argv[1],a);
	}

	printstruct(a);
	freeStruct(a);
	return 0;
}