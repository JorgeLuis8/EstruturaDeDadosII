#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv23.h" // Certifique-se de que este arquivo define Arv_pt e Info

// Estrutura da árvore binária
typedef struct Arv_en {
    char palavraIngles[50];
    struct Arv_en *dir, *esq;
    int unidade;
} Arv_en;

// Funções da árvore binária
Arv_en *createNode(const char *palavraIngles, int unidade);
Arv_en *insertpalavraIngles(Arv_en *root, const char *palavraIngles, int unidade);
void printBinaryTree(Arv_en *root);
int ehFolhas(Arv_en *raiz);
Arv_en *soUmFilho(Arv_en *raiz);
Arv_en *menorFilho(Arv_en *raiz);
int removerPalavraIngles(Arv_en **raiz, char *palavra);


#endif // ARVORE_BINARIA_H
