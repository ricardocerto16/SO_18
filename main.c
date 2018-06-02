#include "headers/execute.h"
#include "headers/writenfile.h"


int main(int argc, char *argv[]){
	int i, r, f;
	Array a;

	if (argc < 2) return -1;

	for (i = 0 ; i < argc ; ++i) {

		f = fork();
		if (f == 0) {
			a = initArray(10);
			parser(argv[i],a);

			r = execut(a);

			if (r >= 0)	
				file_writen(argv[i],a);
			
			freeStruct(a);
		}
		else 
			wait(0);
	}
	return 0;
}