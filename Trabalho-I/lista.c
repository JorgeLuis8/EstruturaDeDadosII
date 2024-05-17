#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct lista{
	char nomeP[100];
	struct lista *proximo;
	struct raizpodcast *podcast;
};

void criaLista()
{
	return NULL;
}

void alocalista(Lista **l){
	*l = (Lista *) malloc(sizeof(Lista));
	if (*l != NULL){
		(*l)->proximo = NULL;
		(*l)->nomeP[0] = '\0';
		(*l)->podcast = NULL;
	}
}

void lerCampos(Lista *l){
	printf("Informe o nome do podcast: ");
	fgets(l->nomeP,100,stdin);
	l->nomeP[strcspn(l->nomeP,"\n")];
}
