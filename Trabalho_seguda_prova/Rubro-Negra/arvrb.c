#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvbin.h"
#include "arvrb.h"
#define RED 1
#define BLACK 0

int insertPortugueseWord(PortuguesRB **arvore, char *palavraPortugues, char *palavraIngles, int unidade) {
    int inseriu = 0;

    // Busca a palavra na árvore
    PortuguesRB *noExistente = NULL;
    noExistente =  SearchWordInTree(arvore, palavraPortugues);

    if (noExistente != NULL) {
        addEnglishTranslation(noExistente, palavraIngles, unidade);
        inseriu = 1;
    } else {
        Info novoInfo = createInfo(palavraPortugues, palavraIngles, unidade);
        insertRedBlackTree(arvore, &novoInfo);
        inseriu = 1;
    }
    return inseriu;
}
Info createInfo(char *palavra, char *palavraIngles, int unidade)
{
    Info info;

    info.palavraPortugues = malloc(strlen(palavra) + 1);
    strcpy(info.palavraPortugues, palavra);

    info.palavraIngles = NULL;
    info.palavraIngles = insertEnglishWord(info.palavraIngles, palavraIngles, unidade);
    return info;
}

PortuguesRB *createNode(Info *informacao)
{
    PortuguesRB *novo = (PortuguesRB *)malloc(sizeof(PortuguesRB));
    novo->info = *informacao;
    novo->cor = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}
int getNodeColor(PortuguesRB *raiz)
{
    int cor;

    if (raiz == NULL)
        cor = BLACK;
    else
        cor = raiz->cor;

    return cor;
}

void switch_node_color(PortuguesRB **raiz)
{
    (*raiz)->cor = !(*raiz)->cor;
    if ((*raiz)->esq)
        (*raiz)->esq->cor = !(*raiz)->esq->cor;
    if ((*raiz)->dir)
        (*raiz)->dir->cor = !(*raiz)->dir->cor;
}

void rotate_right(PortuguesRB **raiz)
{
    PortuguesRB *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = RED;
    (*raiz) = aux;
}

void left_rotate(PortuguesRB **raiz)
{
    PortuguesRB *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = RED;
    (*raiz) = aux;
}

void balanceTree(PortuguesRB **raiz)
{
    if (*raiz)
    {
        if (getNodeColor((*raiz)->dir) == RED && getNodeColor((*raiz)->esq) == BLACK)
            left_rotate(raiz);
        if (getNodeColor((*raiz)->esq) == RED && getNodeColor((*raiz)->esq->esq) == RED)
            rotate_right(raiz);
        if (getNodeColor((*raiz)->esq) == RED && getNodeColor((*raiz)->dir) == RED)
            switch_node_color(raiz);
    }
}

int insertRedBlackNode(PortuguesRB **raiz, Info *informacao)
{

    int inseriu = 1;
    if (*raiz == NULL)
    {
        *raiz = createNode(informacao);
    }
    else
    {
        if (strcmp(informacao->palavraPortugues, (*raiz)->info.palavraPortugues) < 0)
        {
            inseriu = insertRedBlackNode(&(*raiz)->esq, informacao);
        }
        else
        {
            inseriu = insertRedBlackNode(&(*raiz)->dir, informacao);
        }
        balanceTree(&(*raiz));
    }

    return inseriu;
}

int insertRedBlackTree(PortuguesRB **raiz, Info *informacao)
{
    int inseriu = insertRedBlackNode(raiz, informacao);
    if (inseriu)
    {
        (*raiz)->cor = BLACK;
    }
    return inseriu;
}

void shiftLeftRed(PortuguesRB **raiz)
{
    switch_node_color(raiz);

    if ((*raiz)->dir && getNodeColor((*raiz)->dir->esq) == RED)
    {
        rotate_right(&(*raiz)->dir);
        left_rotate((raiz));
        switch_node_color(raiz);
    }
}

void rotateRedRight(PortuguesRB **raiz)
{
    switch_node_color(raiz);

    if ((*raiz)->esq && getNodeColor((*raiz)->esq->esq) == RED)
    {
        rotate_right(raiz);
        switch_node_color(raiz);
    }
}

void removeMinimum(PortuguesRB **raiz)
{
    if (!((*raiz)->esq))
    {
        free(*raiz);
        *raiz = NULL;
    }
    else
    {
        if (getNodeColor((*raiz)->esq) == BLACK && getNodeColor((*raiz)->esq->esq) == BLACK)
            shiftLeftRed(raiz);

        removeMinimum(&(*raiz)->esq);
        balanceTree(raiz);
    }
}

PortuguesRB *findMinimum(PortuguesRB *raiz)
{
    PortuguesRB *menor;
    menor = raiz;

    if (raiz)
        if (raiz->esq)
            menor = findMinimum(raiz->esq);

    return menor;
}

int removeNodeFromRBTree(PortuguesRB **raiz, char *valor)
{
    int existe = 0;

    if (*raiz)
    {
        if (strcmp(valor, (*raiz)->info.palavraPortugues) < 0)
        {
            if ((*raiz)->esq && getNodeColor((*raiz)->esq) == BLACK && getNodeColor((*raiz)->esq->esq) == BLACK)
                shiftLeftRed(raiz);

            existe = removeNodeFromRBTree(&(*raiz)->esq, valor);
        }
        else
        {
            if (getNodeColor((*raiz)->esq) == RED)
                rotate_right(raiz);

            if (strcmp(valor, (*raiz)->info.palavraPortugues) == 0 && (*raiz)->dir == NULL)
            {
                free(*raiz);
                *raiz = NULL;

                existe = 1;
            }else{
                if ((*raiz)->dir && getNodeColor((*raiz)->dir) == BLACK && getNodeColor((*raiz)->dir->esq) == BLACK)
                rotateRedRight(raiz);

                if (strcmp(valor, (*raiz)->info.palavraPortugues) == 0)
                {
                    PortuguesRB *aux;
                    aux = findMinimum((*raiz)->dir);
                    (*raiz)->info = aux->info;
                    removeMinimum(&(*raiz)->dir);

                    existe = 1;
                }
                else
                {
                    existe = removeNodeFromRBTree(&(*raiz)->dir, valor);
                }
            }
        }
    }
    balanceTree(raiz);
    return existe;
}

int removeRBTreeNode(PortuguesRB **raiz, char *valor)
{
    int removeu = removeNodeFromRBTree(raiz, valor);
    if (removeu)
    {
        (*raiz)->cor = BLACK;
    }
    return removeu;
}


PortuguesRB *SearchWordInTree(PortuguesRB **arvore, char *palavraPortugues)
{
    PortuguesRB *atual = NULL;

    if (*arvore != NULL)
    {
        if (strcmp(palavraPortugues, (*arvore)->info.palavraPortugues) == 0)
        {
            atual = *arvore;
        }
        else if (strcmp(palavraPortugues, (*arvore)->info.palavraPortugues) < 0)
        {
            atual = SearchWordInTree(&(*arvore)->esq, palavraPortugues);
        }
        else
        {
            atual = SearchWordInTree(&(*arvore)->dir, palavraPortugues);
        }
    }
    return atual;
}


void printWordsByUnit(PortuguesRB *arvore, int unidade)
{
    if (arvore)
    {
        printWordsByUnit(arvore->esq, unidade);
        printTranslations(arvore->info.palavraIngles, unidade, arvore->info.palavraPortugues);
        printWordsByUnit(arvore->dir, unidade);
    }
}

void printTranslations(BinaryTreeNode *node, int unidade, char *palavraPortugues)
{
    if (node)
    {
        if (node->unidade == unidade)
        {
            printf("Palavra em Português: %s\n", palavraPortugues);
            printf("Palavra em inglês: %s\n", node->palavraIngles);
        }
        printTranslations(node->esq, unidade, palavraPortugues);
        printTranslations(node->dir, unidade, palavraPortugues);
    }
}

void showPortugueseTranslation(PortuguesRB **raiz, char *palavraPortugues)
{
    PortuguesRB *resultado = NULL;
    if (raiz != NULL)
    {
        resultado = SearchWordInTree(raiz, palavraPortugues);
        if (resultado)
        {
            printf("Traduções em inglês para a palavra '%s':\n", palavraPortugues);

            if (strcmp(palavraPortugues, resultado->info.palavraPortugues) == 0)
            {
                printBinaryTree(resultado->info.palavraIngles);
            }

        }
    }
}

void showRedBlackTree(PortuguesRB *raiz)
{
    if (raiz)
    {
        showRedBlackTree(raiz->esq);
        printf("Cor - %d\n", raiz->cor);
        printf("Palavra em Português - %s\n", raiz->info.palavraPortugues);
        printBinaryTree(raiz->info.palavraIngles);
        printf("\n");
        showRedBlackTree(raiz->dir);
    }
}