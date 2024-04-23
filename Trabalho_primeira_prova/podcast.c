#include "podcast.h"
#include "temas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct arvore_podCast
{
    char nome[50];
    char entrevistador[50];
    struct arvore_temas *raiz_temas;
    struct arvore_podCast *esq;
    struct arvore_podCast *dir;

};


Arvore_podCast* criar_arvore_podCast() {
    Arvore_podCast *a = (Arvore_podCast*) malloc(sizeof(Arvore_podCast));
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

void ler_dados_podcast(Arvore_podCast *no){
    printf("Digite o nome do podcast: ");
    scanf(" %[^\n]", no->nome);

    printf("Digite o nome do entrevistador: ");
    scanf(" %[^\n]", no->entrevistador);
}

Arvore_podCast *inserir_podcast(Arvore_podCast *raiz, Arvore_podCast *no)
{
    if (raiz == NULL)
    {
        raiz = no;
        raiz->raiz_temas = NULL;
    }
    else
    {
        if (strcmp(no->nome, raiz->nome) < 0)
        {
            raiz->esq = inserir_podcast(raiz->esq, no);
        }
        else
        {
            raiz->dir = inserir_podcast(raiz->dir, no);
        }
    }
    return raiz;
}

Arvore_podCast *Busca_arv_podcast(Arvore_podCast *raiz, char *nome)
{
    Arvore_podCast *aux = NULL;
    if (raiz != NULL)
    {
        if (strcmp(nome, raiz->nome) == 0)
        {
            aux = raiz;
        }
        else if (strcmp(nome, raiz->nome) < 0)
        {
            aux = Busca_arv_podcast(raiz->esq, nome);
        }
        else
        {
            aux = Busca_arv_podcast(raiz->dir, nome);
        }
    }
    return aux;
}


Arvore_podCast *remover_podcast (Arvore_podCast *raiz, char *nome) {
    Arvore_podCast *resultado = NULL;
    if (raiz != NULL && raiz->raiz_temas == NULL) {
        if (strcmp(nome, raiz->nome) < 0) {
            raiz->esq = remover_podcast(raiz->esq, nome);
        } else if (strcmp(nome, raiz->nome) > 0) {
            raiz->dir = remover_podcast(raiz->dir, nome);
        } else {
            if (raiz->esq == NULL) {
                Arvore_podCast *aux = raiz->dir;
                free(raiz);
                resultado = aux;
            } else if (raiz->dir == NULL) {
                Arvore_podCast *aux = raiz->esq;
                free(raiz);
                resultado = aux;
            } else {
                Arvore_podCast *aux = raiz->dir;
                while (aux->esq != NULL) {
                    aux = aux->esq;
                }
                strcpy(raiz->nome, aux->nome);
                raiz->dir = remover_podcast(raiz->dir, aux->nome);
            }
        }
    }
    return resultado;
}

