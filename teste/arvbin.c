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
        novoNo->englishWord = (char *)malloc(strlen(palavraIngles) + 1);
        strcpy(novoNo->englishWord, palavraIngles);
        novoNo->unidades = NULL;
        inserir_lista_encadeada_unidade(&(novoNo->unidades), unidade);
        novoNo->leftChild = novoNo->rightChild = NULL;
    }
    return novoNo;
}

// Função para inserir uma palavra em ingles na arvore binaria de busca
int insertpalavraIngles(Inglesbin **root, NodeInfo *informacao)
{
    int result = 0;
    if ((*root) == NULL)
    {
        Inglesbin *new = createNode(informacao->englishWord->englishWord, informacao->englishWord->unidades->nome_unidade);
        *root = new;
        result = 1;
    }
    else if (strcmp(informacao->englishWord->englishWord, (*root)->englishWord) < 0)
        result = insertpalavraIngles(&(*root)->leftChild, informacao);
    else if (strcmp(informacao->englishWord->englishWord, (*root)->englishWord) > 0)
        result = insertpalavraIngles(&(*root)->rightChild, informacao);
    else
        result = inserir_lista_encadeada_unidade(&((*root)->unidades), informacao->englishWord->unidades->nome_unidade);
    
    return result;
}

void printBinaryTree(Inglesbin *root)
{
    if (root != NULL)
    {
        printBinaryTree(root->leftChild); // Percorre a árvore à esquerda
        // Imprime a tradução de ingles associada à palavra em portugues
        printf("Palavra em Ingles: %s \n", root->englishWord);
        show_lista_encadeada_unidade(root->unidades);
        printBinaryTree(root->rightChild); // Percorre a árvore à direita
    }
}

int eh_Folha(Inglesbin *raiz)
{
    return (raiz->leftChild == NULL && raiz->rightChild == NULL);
}

Inglesbin *soUmFilho(Inglesbin **raiz)
{
    Inglesbin *aux;
    aux = NULL;

    if ((*raiz)->rightChild == NULL)
    {
        aux = (*raiz)->leftChild;
    }
    else if ((*raiz)->leftChild == NULL)
    {
        aux = (*raiz)->rightChild;
    }

    return aux;
}

Inglesbin *getMinimumChild(Inglesbin *raiz)
{
    Inglesbin *aux;
    aux = raiz;

    if (raiz)
    {
        if (raiz->leftChild)
            aux = getMinimumChild(raiz->leftChild);
    }

    return aux;
}

int removerPalavraIngles(Inglesbin **raiz, const char *palavra)
{
    Inglesbin *endFilho = NULL;
    int existe = 0;

    if (*raiz)
    {
        if (strcmp(palavra, (*raiz)->englishWord) == 0)
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
                endFilho = getMinimumChild((*raiz)->rightChild);
                strcpy((*raiz)->englishWord, endFilho->englishWord);
                (*raiz)->unidades = endFilho->unidades;

                removerPalavraIngles(&(*raiz)->rightChild, endFilho->englishWord);
            }
        }
        else if (strcmp(palavra, (*raiz)->englishWord) < 0)
        {
            existe = removerPalavraIngles(&(*raiz)->leftChild, palavra);
        }
        else
        {
            existe = removerPalavraIngles(&(*raiz)->rightChild, palavra);
        }
    }

    return existe;
}

void clear_binary_tree(Inglesbin *raiz)
{
    if (raiz)
    {
        clear_binary_tree(raiz->leftChild);
        clear_binary_tree(raiz->rightChild);
        free(raiz->englishWord);
        free(raiz);
    }
}