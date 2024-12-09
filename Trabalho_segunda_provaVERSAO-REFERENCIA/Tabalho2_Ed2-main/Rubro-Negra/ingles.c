#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingles.h"
#include "portugues.h"

Arv_ingles *createNode(char *palavraIngles, int unidade)
{
    Arv_ingles *novoNo = (Arv_ingles *)malloc(sizeof(Arv_ingles));
    if (novoNo != NULL)
    {
        strcpy(novoNo->palavraIngles, palavraIngles);
        novoNo->unidade = unidade;
        novoNo->esq = novoNo->dir = NULL;
    }
    return novoNo;
}

Arv_ingles *insertpalavraIngles(Arv_ingles *root, char *palavraIngles, int unidade)
{
    Arv_ingles *result;
    if (root == NULL)
    {
        result = createNode(palavraIngles, unidade);
    }
    else
    {
        if (strcmp(palavraIngles, root->palavraIngles) < 0)
        {
            root->esq = insertpalavraIngles(root->esq, palavraIngles, unidade);
        }
        else if (strcmp(palavraIngles, root->palavraIngles) > 0)
        {
            root->dir = insertpalavraIngles(root->dir, palavraIngles, unidade);
        }
        result = root;
    }
    return result;
}
int ehFolhas(Arv_ingles *raiz)
{
    return (raiz->esq == NULL && raiz->dir == NULL);
}

Arv_ingles *soUmFilho(Arv_ingles *raiz)
{
    Arv_ingles *aux;
    aux = NULL;

    if (raiz->dir == NULL)
    {
        aux = raiz->esq;
    }
    else if (raiz->esq == NULL)
    {
        aux = raiz->dir;
    }

    return aux;
}

Arv_ingles *menorFilho(Arv_ingles *raiz)
{
    Arv_ingles *aux;
    aux = raiz;

    if (raiz)
    {
        if (raiz->esq)
            aux = menorFilho(raiz->esq);
    }

    return aux;
}

int removerPalavraIngles(Arv_ingles **raiz, char *palavra) {
    if (*raiz == NULL) return 0; // Palavra não encontrada

    if (strcmp(palavra, (*raiz)->palavraIngles) < 0) {
        return removerPalavraIngles(&(*raiz)->esq, palavra);
    } else if (strcmp(palavra, (*raiz)->palavraIngles) > 0) {
        return removerPalavraIngles(&(*raiz)->dir, palavra);
    } else {
        // Palavra encontrada
        Arv_ingles *temp = *raiz;

        if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
            // Caso 1: Nó sem filhos
            *raiz = NULL;
        } else if ((*raiz)->esq == NULL) {
            // Caso 2: Apenas filho à direita
            *raiz = (*raiz)->dir;
        } else if ((*raiz)->dir == NULL) {
            // Caso 2: Apenas filho à esquerda
            *raiz = (*raiz)->esq;
        } else {
            // Caso 3: Nó com dois filhos
            Arv_ingles *menor = menorFilho((*raiz)->dir);
            strcpy((*raiz)->palavraIngles, menor->palavraIngles);
            (*raiz)->unidade = menor->unidade;
            removerPalavraIngles(&(*raiz)->dir, menor->palavraIngles);
        }

        free(temp); // Libera memória do nó removido
        return 1;   // Removido com sucesso
    }

    return 0; // Palavra não encontrada
}


void printBinaryTree(Arv_ingles *root)
{
    if (root != NULL)
    {
        printBinaryTree(root->esq); // Percorre a árvore à esquerda
        printf("\n");
        // Imprime a tradução de inglês associada à palavra em português
        printf("Palavra em Inglês: %s = Unidade: %d\n", root->palavraIngles, root->unidade);
        printBinaryTree(root->dir); // Percorre a árvore à direita
    }
}

