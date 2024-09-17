#include "disciplinas.h"
#include <stdio.h>
#include <stdlib.h>


arvore_disciplinas *criar_disciplina()
{
    arvore_disciplinas *disciplina = (arvore_disciplinas *)malloc(sizeof(arvore_disciplinas));
    if (disciplina == NULL)
    {
        printf("Erro ao alocar memória para a disciplina\n");
        exit(1);
    }
    disciplina->esq = NULL;
    disciplina->dir = NULL;
    return disciplina;
}

arvore_disciplinas *inserir_disciplina(arvore_disciplinas *raiz, arvore_disciplinas *no)
{
    if (buscar_disciplina(raiz, no->codigo) != NULL)
    {
        /* code */
        printf("Disciplina ja cadastrada\n");
    }
    else{
    
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (no->codigo < raiz->codigo)
        {
            raiz->esq = inserir_disciplina(raiz->esq, no);
        }
        else
        {
            raiz->dir = inserir_disciplina(raiz->dir, no);
        }
    }
    }
    return raiz;
}

arvore_disciplinas *buscar_disciplina(arvore_disciplinas *raiz, int codigo)
{
    arvore_disciplinas *aux = NULL;
    if (raiz != NULL)
    {
        if (codigo == raiz->codigo)
        {
            aux = raiz;
        }
        else
        {
            if (codigo < raiz->codigo)
            {
                aux = buscar_disciplina(raiz->esq, codigo);
            }
            else
            {
                aux = buscar_disciplina(raiz->dir, codigo);
            }
        }
    }
    return aux;
}

arvore_disciplinas *remover_disciplina(arvore_disciplinas *raiz, int codigo)
{
    if (raiz != NULL)
    {
        if (codigo < raiz->codigo)
        {
            raiz->esq = remover_disciplina(raiz->esq, codigo);
        }
        else if (codigo > raiz->codigo)
        {
            raiz->dir = remover_disciplina(raiz->dir, codigo);
        }
        else
        {
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);
                raiz = NULL;
            }
            else if (raiz->esq == NULL)
            {
                arvore_disciplinas *aux = raiz;
                raiz = raiz->dir;
                free(aux);
            }
            else if (raiz->dir == NULL)
            {
                arvore_disciplinas *aux = raiz;
                raiz = raiz->esq;
                free(aux);
            }
            else
            {
                arvore_disciplinas *aux = raiz->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir;
                }
                raiz->codigo = aux->codigo;
                raiz->esq = remover_disciplina(raiz->esq, aux->codigo);
            }
        }
    }
    return raiz;
}

void imprimir_disciplinas(arvore_disciplinas *raiz)
{
    if (raiz != NULL)
    {
        imprimir_disciplinas(raiz->esq);
        printf("Codigo: %d\n", raiz->codigo);
        printf("Nome: %s\n", raiz->nome);
        printf("\n");
        imprimir_disciplinas(raiz->dir);
    }
}

void liberar_disciplinas(arvore_disciplinas *raiz)
{
    if (raiz != NULL)
    {
        liberar_disciplinas(raiz->esq);
        liberar_disciplinas(raiz->dir);
        free(raiz);
    }
}
