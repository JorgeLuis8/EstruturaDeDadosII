#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

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
