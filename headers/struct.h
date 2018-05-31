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

int getDependencia(Array a, int i);

char * getComando(Array a, int i);

char * getDescricao(Array a, int i);

char * getOutput(Array a, int i);

<<<<<<< HEAD
char* getLast(Array a);
=======
>>>>>>> a381b4ea21622b472aa17f328ee68762a1aa7e41

void freeStruct(Array a);

#endif