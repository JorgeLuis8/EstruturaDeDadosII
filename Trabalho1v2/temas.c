#include "temas.h"
#include "entrevistas.h"
#include <stdlib.h>
#include <stdio.h>

struct arvore_temas
{
    char tema[50];
    struct raiz_entrevistas *entrevistas;
    struct arvore_temas *esq;
    struct arvore_temas *dir;
};

struct raiz_temas
{
    struct arvore_temas *raiz;
};

Arvore_temas *criar_arvore_temas()
{
    Arvore_temas *a = (Arvore_temas *)malloc(sizeof(Arvore_temas));
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

Raiz_temas *criar_raiz_temas()
{
    Raiz_temas *r = (Raiz_temas *)malloc(sizeof(Raiz_temas));
    r->raiz = NULL;
    return r;
}

void Ler_dados_de_insercao_temas(Arvore_temas *no)
{
    printf("Digite o tema da entrevista: ");
    scanf("%s", no->tema);
}

Arvore_temas *inserir_temas(Arvore_temas *raiz, Arvore_temas *no)
{
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (strcmp(no->tema, raiz->tema) < 0)
            raiz->esq = inserir_temas(raiz->esq, no);
        else if (strcmp(no->tema, raiz->tema) > 0)
            raiz->dir = inserir_temas(raiz->dir, no);
    }
    printf("Tema: %s\n", raiz->tema);
    return raiz;
}

void inserir_arvore_temas(Raiz_temas *arvore, Arvore_temas *no)
{
    if (arvore->raiz == NULL)
    {
        arvore->raiz = no;
    }
    else
    {
        arvore->raiz = inserir_temas(arvore->raiz, no);
    }
}

Arvore_temas *buscar_temas(Arvore_temas *raiz, char *titulo)
{
    Arvore_entrevistas *resultado = NULL;
    if (raiz != NULL)
    {
        if (strcmp(titulo, raiz->tema) == 0)
        {
            resultado = raiz;
        }
        else if (strcmp(titulo, raiz->tema) < 0)
        {
            resultado = buscar_entrevistas(raiz->esq, titulo);
        }
        else
        {
            resultado = buscar_entrevistas(raiz->dir, titulo);
        }
    }
    return resultado;
}
