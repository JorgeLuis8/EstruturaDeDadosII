#include <stdio.h>
#include <stdlib.h>
#include "matricula.h"


struct arvore_matricula;

arvore_matricula *criar_matricula()
{
    // Aloca memória para um novo nó da árvore de matrícula
    arvore_matricula *no = (arvore_matricula *)malloc(sizeof(arvore_matricula));
    
    // Inicializa os ponteiros esquerdo e direito como NULL
    no->esq = NULL;
    no->dir = NULL;

    // Retorna o novo nó criado
    return no;
}

arvore_matricula *inserir_matriculas(arvore_matricula *raiz, arvore_matricula *no) {
    if (raiz == NULL) {
        // Se a raiz é NULL, o novo nó se torna a raiz
        raiz = no;
    } else {
        // Comparação para decidir onde inserir o novo nó
        if (no->codigo_disciplina < raiz->codigo_disciplina) {
            // Inserir no subárvore esquerda
            raiz->esq = inserir_matriculas(raiz->esq, no);
        } else if (no->codigo_disciplina > raiz->codigo_disciplina) {
            // Inserir no subárvore direita
            raiz->dir = inserir_matriculas(raiz->dir, no);
        }
    }

    return raiz; // Retorna a raiz da árvore (ou subárvore)
}



void imprimir_matricula(arvore_matricula *raiz)
{
    if (raiz != NULL)
    {
        printf("Codigo da disciplina: %d\n", raiz->codigo_disciplina);

        imprimir_matricula(raiz->esq); 
        imprimir_matricula(raiz->dir); 
    }
}

arvore_matricula *buscar_matricula(arvore_matricula *raiz, int codigo_disciplina)
{
    arvore_matricula *aux = NULL; // Inicializa a variável auxiliar
    if (raiz != NULL) // Verifica se a raiz não é nula
    {
        if (codigo_disciplina == raiz->codigo_disciplina) // Encontrou o nó
        {
            aux = raiz; // Atribui o nó encontrado à variável auxiliar
        }
        else if (codigo_disciplina < raiz->codigo_disciplina) // Busca na subárvore esquerda
        {
            aux = buscar_matricula(raiz->esq, codigo_disciplina); 
        }
        else // Busca na subárvore direita
        {
            aux = buscar_matricula(raiz->dir, codigo_disciplina); 
        }
    }
    return aux; // Retorna o nó encontrado ou NULL
}


arvore_matricula *remover_matricula(arvore_matricula *raiz, int codigo_disciplina)
{
    if (raiz != NULL)
    {
        if (codigo_disciplina < raiz->codigo_disciplina)
        {
            raiz->esq = remover_matricula(raiz->esq, codigo_disciplina); 
        }
        else if (codigo_disciplina > raiz->codigo_disciplina)
        {
            raiz->dir = remover_matricula(raiz->dir, codigo_disciplina); 
        }
        else
        {
            // Caso 1: Nó a ser removido é uma folha
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);
                raiz = NULL;
            }
            // Caso 2: Nó a ser removido tem apenas o filho à direita
            else if (raiz->esq == NULL)
            {
                arvore_matricula *aux = raiz;
                raiz = raiz->dir;
                free(aux);
            }
            // Caso 3: Nó a ser removido tem apenas o filho à esquerda
            else if (raiz->dir == NULL)
            {
                arvore_matricula *aux = raiz;
                raiz = raiz->esq;
                free(aux);
            }
            // Caso 4: Nó a ser removido tem ambos os filhos
            else
            {
                arvore_matricula *aux = raiz->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir; // Encontra o maior da subárvore esquerda
                }
                raiz->codigo_disciplina = aux->codigo_disciplina; // Copia o valor
                raiz->esq = remover_matricula(raiz->esq, aux->codigo_disciplina); // Remove o nó
            }
        }
    }
    return raiz; // Retorna a nova raiz da árvore
}
