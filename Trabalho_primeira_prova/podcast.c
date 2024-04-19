#include "podcast.h"
#include <stdlib.h>
#include <stdio.h>

struct arvore_podCast
{
    char nome[50];
    char entrevistador[50];
    struct arvore_temas *raiz_temas;
    struct arvore_podCast *esq;
    struct arvore_podCast *dir;

};

struct raiz_podCast
{
    struct arvore_podCast *raiz;
};

Arvore_podCast* criar_arvore_podCast() {
    Arvore_podCast *a = (Arvore_podCast*) malloc(sizeof(Arvore_podCast));
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

