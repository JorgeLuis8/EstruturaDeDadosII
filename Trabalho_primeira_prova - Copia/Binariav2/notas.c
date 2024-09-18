#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "notas.h"

struct arvore_notas;


arvore_notas *criar_nota()
{
    arvore_notas *no = (arvore_notas *)malloc(sizeof(arvore_notas));
    no->esq = NULL;
    no->dir = NULL;
    return no;
}
void Ler_notas(arvore_notas *no)
{
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &no->codigo_disciplina); // Corrigido

    printf("Digite o semestre cursado (ex: 2023.1): ");
    scanf("%s", no->semestre_cursado);  // Corrigido

    printf("Digite a nota final: ");
    scanf("%d", &no->nota_final);  // Corrigido
}


arvore_notas *inserir_nota(arvore_notas *raiz, arvore_notas *no)
{
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (no->codigo_disciplina < raiz->codigo_disciplina)
        {
            if (raiz->esq == NULL)
            {
                raiz->esq = no;
            }
            else
            {
                raiz->esq = inserir_nota(raiz->esq, no); // Corrigido
            }
        }
        else
        {
            if (raiz->dir == NULL)
            {
                raiz->dir = no;
            }
            else
            {
                raiz->dir = inserir_nota(raiz->dir, no); // Corrigido
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


