#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "notas.h"

struct arvore_notas;

void Ler_notas(arvore_notas *no)
{
    printf("Digite o codigo da disciplina: ");
    scanf(" %d", &no->codigo_disciplina);

    printf("Digite o semestre cursado: ");
    scanf(" %s", no->semestre_cursado);

    printf("Digite a nota final: ");
    scanf("%d", &no->nota_final);

}
arvore_notas *inserir_entrevistas(arvore_notas *raiz, arvore_notas *no)
{
    // Se a raiz for nula, o nó inserido será a raiz
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        // Se o código da disciplina do nó inserido for menor que o da raiz, o nó será inserido à esquerda
        if (no->codigo_disciplina < raiz->codigo_disciplina)
        {
            if (raiz->esq == NULL)
            {
                raiz->esq = no;
            }
            else
            {
                raiz->esq = inserir_entrevistas(raiz->esq, no);
            }
        }
        // Se o código da disciplina do nó inserido for maior que o da raiz, o nó será inserido à direita
        else
        {
            if (raiz->dir == NULL)
            {
                raiz->dir = no;
            }
            else
            {
                raiz->dir = inserir_entrevistas(raiz->dir, no);
            }
        }
    }

    return raiz;
}


void imprimir_notas(arvore_notas *raiz)
{
    if (raiz != NULL)
    {
        printf("Codigo da disciplina: %d\n", raiz->codigo_disciplina);
        printf("Semestre cursado: %s\n", raiz->semestre_cursado);
        printf("Nota Final: %d\n", raiz->nota_final);
        imprimir_notas(raiz->esq);
        imprimir_notas(raiz->dir);
    }
}


arvore_notas *buscar_notas(arvore_notas *raiz, int codigo_disciplina)
{
    arvore_notas *aux = NULL;
    if (raiz != NULL)
    {
        {
            if (codigo_disciplina == raiz->codigo_disciplina)
            {
                aux = raiz;
            }
            else
            {
                if (codigo_disciplina < raiz->codigo_disciplina)
                {
                    aux = buscar_notas(raiz->esq, codigo_disciplina);
                }
                else
                {
                    aux = buscar_notas(raiz->dir, codigo_disciplina);
                }
            }
        }
    }
    return aux;
}


arvore_notas *remover_nota(arvore_notas *raiz, int codigo_disciplina)
{
    if (raiz != NULL)
    {
        if (codigo_disciplina < raiz->codigo_disciplina)
        {
            raiz->esq = remover_nota(raiz->esq, codigo_disciplina);
        }
        else if (codigo_disciplina > raiz->codigo_disciplina)
        {
            raiz->dir = remover_nota(raiz->dir, codigo_disciplina);
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
                arvore_notas *aux = raiz;
                raiz = raiz->dir;
                free(aux);
            }
            else if (raiz->dir == NULL)
            {
                arvore_notas *aux = raiz;
                raiz = raiz->esq;
                free(aux);
            }
            else
            {
                arvore_notas *aux = raiz->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir;
                }
                raiz->codigo_disciplina = aux->codigo_disciplina;
                raiz->esq = remover_nota(raiz->esq, aux->codigo_disciplina);
            }
        }
    }
    return raiz;
}


