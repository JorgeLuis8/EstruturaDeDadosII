#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temas.h"
#include "entrevistas.h"
struct notema{
	char Tema[100];
	struct notema* Esq;
	struct notema* Dir;
	struct raizEntrevista* entrevistas;
};

struct noraiz{
	struct notema* RaizTema;
};

NoTema *cria_arvore_tema(){
	NoTema *a = (NoTema*)malloc(sizeof(NoTema));
	a->Esq = NULL;
	a->Dir = NULL;
	return a;
}

void ler_dados(NoTema *no){
	printf("Digite o tema: ");
	fgets(no->Tema, sizeof(no->Tema), stdin);
}

