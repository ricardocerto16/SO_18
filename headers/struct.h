#ifndef __STRUCH_H__
#define __STRUCH_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct array *Array;
typedef struct comando *Comando;


Array initArray(int size);


Comando initComando();


int insertArray(Array a, char * descricao, char * comando, int depends);


int insertArrayOutput(Array a, int pos ,char * output);


void printstruct(Array a);


int getUsed(Array a);


char * getComando(Array a, int i);


char * getDescricao(Array a, int i);


char * getOutput(Array a, int i);

#endif