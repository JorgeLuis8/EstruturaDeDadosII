#include <stdio.h>
#include <stdlib.h>
#include "entrevistas.h"

struct noentrevista{
	char TituloEnt[100];
	int Data[4];
	float Duracao;
	char NomeEntrevistado [100];
	char EspecialidadeEntrevistado[100];
	struct noentrevista* Esq;
	struct noentrevista* Dir;
};

struct raizentrevista{
	struct noentrevista* RaizEntrevista;
};
void alocaArv(NoEntrevista** no){
	*no = (NoEntrevista*)malloc(sizeof(NoEntrevista));
	if(*no){
		(*no)->Esq = NULL;
		(*no)->Dir = NULL;

	}

}