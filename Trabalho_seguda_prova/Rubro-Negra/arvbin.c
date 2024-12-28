#include "arvbin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvrb.h"
BinaryTreeNode *initializeBinaryTreeNode(char *palavraIngles, int unidade)
{
    BinaryTreeNode *novoNo = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    if (novoNo != NULL)
    {
        strcpy(novoNo->palavraIngles, palavraIngles);
        novoNo->unidade = unidade;
        novoNo->esq = novoNo->dir = NULL;
    }
    return novoNo;
}

// Função para inserir uma palavra em inglês na arvore binaria de busca
BinaryTreeNode *insertEnglishWord(BinaryTreeNode *root, char *palavraIngles, int unidade)
{
    BinaryTreeNode *result;
    if (root == NULL)
    {
        result = initializeBinaryTreeNode(palavraIngles, unidade);
    }
    else
    {
        if (strcmp(palavraIngles, root->palavraIngles) < 0)
        {
            root->esq = insertEnglishWord(root->esq, palavraIngles, unidade);
        }
        else if (strcmp(palavraIngles, root->palavraIngles) > 0)
        {
            root->dir = insertEnglishWord(root->dir, palavraIngles, unidade);
        }
        result = root;
    }
    return result;
}

void addEnglishTranslation(PortuguesRB *raiz, char *palavraIng, int unidade)
{
    raiz->info.palavraIngles = insertEnglishWord(raiz->info.palavraIngles, palavraIng, unidade);
}


void printBinaryTree(BinaryTreeNode *root)
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

int isLeafNodes(BinaryTreeNode *raiz)
{
    return (raiz->esq == NULL && raiz->dir == NULL);
}

BinaryTreeNode *singleChildNode(BinaryTreeNode *raiz)
{
    BinaryTreeNode *aux;
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

BinaryTreeNode *minimumChildNode(BinaryTreeNode *raiz)
{
    BinaryTreeNode *aux;
    aux = raiz;

    if (raiz)
    {
        if (raiz->esq)
            aux = minimumChildNode(raiz->esq);
    }

    return aux;
}

int removeEnglishWord(BinaryTreeNode **raiz, char *palavra)
{
    BinaryTreeNode *endFilho;
    int existe = 0;

    if (*raiz)
    {
        if (strcmp(palavra, (*raiz)->palavraIngles) == 0)
        {
            existe = 1;
            printf("removendo palavra: %s\n", palavra);
            BinaryTreeNode *aux = *raiz;
            if (isLeafNodes(*raiz))
            {
                free(aux);
                *raiz = NULL;
            }
            else if ((endFilho = singleChildNode(*raiz)) != NULL)
            {
                free(aux);
                *raiz = endFilho;
            }
            else
            {
                endFilho = minimumChildNode((*raiz)->dir);
                strcpy((*raiz)->palavraIngles, endFilho->palavraIngles);
                (*raiz)->unidade = endFilho->unidade;

                removeEnglishWord(&(*raiz)->dir, endFilho->palavraIngles);
            }
        }
        else if (strcmp(palavra, (*raiz)->palavraIngles) < 0)
        {
            existe = removeEnglishWord(&(*raiz)->esq, palavra);
        }
        else
        {
            existe = removeEnglishWord(&(*raiz)->dir, palavra);
        }
    }

    return existe;
}

void FindEnglishTerm(PortuguesRB **raiz, char *palavraIngles, int unidade)
{
    if (*raiz != NULL)
    {
        FindEnglishTerm(&(*raiz)->esq, palavraIngles, unidade);

        if ((*raiz)->info.palavraIngles != NULL && (*raiz)->info.palavraIngles->unidade == unidade)
            removeEnglishWord(&(*raiz)->info.palavraIngles, palavraIngles);
        FindEnglishTerm(&(*raiz)->dir, palavraIngles, unidade);
    }
}