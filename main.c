#include "headers/execute.h"
#include "headers/writenfile.h"


int main(int argc, char *argv[]){
	int i, r;

	if (argc < 2) return -1;

	for (i = 1 ; i < argc ; i++) {
		Array a = initArray(10);
		parser(argv[i],a);

		r = execut(a);

	if (r >= 0)	
		file_writen(argv[i],a);

	freeStruct(a);
	}
	return 0;
}