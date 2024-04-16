#include <stdio.h>
#include <stdlib.h>
#include "temas.h"

struct notema{
	char Tema[100];
	struct notema* Esq;
	struct notema* Dir;
	struct raizEntrevista* entrevistas;
};

struct noraiz{
	struct notema* RaizTema;
};

NoTema* criaArvT(){
	NoEntrevista* Arv;
	NoEntrevista->Esq = NULL;
	NoEntrevista->Dir = NULL;
	arv* = (NoTema*) = malloc(sizeof(NoTema));
	return arv;
}
