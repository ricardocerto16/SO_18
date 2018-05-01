//#ifndef __STRUCT_H__
//#define __STRUCT_H__



#include <string.h>
#include <stdlib.h>



typedef struct array * Array;
typedef struct comando * Comando;


Array initArray(int size);


Comando initComando();


int insertArray(Array a, char * descricao, char * comando, int depends);


int insertArrayOutput(Array a, int pos ,char * output);


void printstruct(Array a);


//#endif