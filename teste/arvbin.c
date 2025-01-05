#include "arvbin.h"
#include "lista_encadeada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Inglesbin *createNode(const char *palavraIngles, char *unidade)
{
    Inglesbin *novoNo = (Inglesbin *)malloc(sizeof(Inglesbin));
    if (novoNo != NULL)
    {
        novoNo->palavraIngles = (char *)malloc(strlen(palavraIngles) + 1);
        strcpy(novoNo->palavraIngles, palavraIngles);
        novoNo->unidades = NULL;
        inserir_lista_encadeada_unidade(&(novoNo->unidades), unidade);
        novoNo->esq = novoNo->dir = NULL;
    }
    return novoNo;
}

// Função para inserir uma palavra em ingles na arvore binaria de busca
int insertpalavraIngles(Inglesbin **root, NodeInfo *informacao)
{
    int result = 0;
    if ((*root) == NULL)
    {
        Inglesbin *new = createNode(informacao->englishWord->palavraIngles, informacao->englishWord->unidades->nome_unidade);
        *root = new;
        result = 1;
    }
    else if (strcmp(informacao->englishWord->palavraIngles, (*root)->palavraIngles) < 0)
        result = insertpalavraIngles(&(*root)->esq, informacao);
    else if (strcmp(informacao->englishWord->palavraIngles, (*root)->palavraIngles) > 0)
        result = insertpalavraIngles(&(*root)->dir, informacao);
    else
        result = inserir_lista_encadeada_unidade(&((*root)->unidades), informacao->englishWord->unidades->nome_unidade);
    
    return result;
}

void printBinaryTree(Inglesbin *root)
{
    if (root != NULL)
    {
        printBinaryTree(root->esq); // Percorre a árvore à esquerda
        // Imprime a tradução de ingles associada à palavra em portugues
        printf("Palavra em Ingles: %s \n", root->palavraIngles);
        show_lista_encadeada_unidade(root->unidades);
        printBinaryTree(root->dir); // Percorre a árvore à direita
    }
}

int eh_Folha(Inglesbin *raiz)
{
    return (raiz->esq == NULL && raiz->dir == NULL);
}

Inglesbin *soUmFilho(Inglesbin **raiz)
{
    Inglesbin *aux;
    aux = NULL;

    if ((*raiz)->dir == NULL)
    {
        aux = (*raiz)->esq;
    }
    else if ((*raiz)->esq == NULL)
    {
        aux = (*raiz)->dir;
    }

    return aux;
}

Inglesbin *getMinimumChild(Inglesbin *raiz)
{
    Inglesbin *aux;
    aux = raiz;

    if (raiz)
    {
        if (raiz->esq)
            aux = getMinimumChild(raiz->esq);
    }

    return aux;
}

int removerPalavraIngles(Inglesbin **raiz, const char *palavra)
{
    Inglesbin *endFilho = NULL;
    int existe = 0;

    if (*raiz)
    {
        if (strcmp(palavra, (*raiz)->palavraIngles) == 0)
        {
            Inglesbin *aux = *raiz;
            existe = 1;
            if (eh_Folha(*raiz))
            {
                free(aux);
                *raiz = NULL;
            }
            else if ((endFilho = soUmFilho(raiz)) != NULL)
            {
                free(aux);
                *raiz = endFilho;
            }
            else
            {
                endFilho = getMinimumChild((*raiz)->dir);
                strcpy((*raiz)->palavraIngles, endFilho->palavraIngles);
                (*raiz)->unidades = endFilho->unidades;

                removerPalavraIngles(&(*raiz)->dir, endFilho->palavraIngles);
            }
        }
        else if (strcmp(palavra, (*raiz)->palavraIngles) < 0)
        {
            existe = removerPalavraIngles(&(*raiz)->esq, palavra);
        }
        else
        {
            existe = removerPalavraIngles(&(*raiz)->dir, palavra);
        }
    }

    return existe;
}

void clear_binary_tree(Inglesbin *raiz)
{
    if (raiz)
    {
        clear_binary_tree(raiz->esq);
        clear_binary_tree(raiz->dir);
        free(raiz->palavraIngles);
        free(raiz);
    }
}