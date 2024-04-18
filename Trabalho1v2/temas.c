#include "temas.h"
#include "entrevistas.h"
#include <stdlib.h>
#include <stdio.h>

struct arvore_temas
{
    char tema[50];
    struct Arvore_entrevistas *entrevistas;
    struct arvore_temas *esq;
    struct arvore_temas *dir;
};

Arvore_temas *criar_arvore_temas()
{
    Arvore_temas *nova_arvore = (Arvore_temas *)malloc(sizeof(Arvore_temas));
    nova_arvore->esq = NULL;
    nova_arvore->dir = NULL;
    nova_arvore->entrevistas = NULL;
    return nova_arvore;
}

void lerDados(Arvore_temas *no)
{
    printf("Digite o tema: ");
    scanf("%s", no->tema);
}

Arvore_temas *inserir_temas(Arvore_temas *raiz, Arvore_temas *no,Arvore_entrevistas *entrevistas)
{
    if (raiz == NULL)
    {
        raiz = no;
        raiz->entrevistas = entrevistas;
    }
    else
    {
        if (strcmp(no->tema, raiz->tema) < 0)
        {
            raiz->esq = inserir_temas(raiz->esq, no,entrevistas);
        }
        else
        {
            raiz->dir = inserir_temas(raiz->dir, no,entrevistas);
        }
    }
    return raiz;
}

Arvore_temas *Busca_arv(Arvore_temas *raiz, char *tema)
{
    Arvore_temas *aux = NULL;
    if(raiz != NULL){
        if(strcmp(tema, raiz->tema) == 0){
            aux = raiz;
        }else if (strcmp(tema, raiz->tema) < 0){
            aux = Busca_arv(raiz->esq, tema);
    }   else{
            aux = Busca_arv(raiz->dir, tema);
        }
    }
    return aux;
}