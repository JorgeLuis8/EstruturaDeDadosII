#ifndef ARV_INGLES_BIN_H
#define ARV_INGLES_BIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do tipo TreeNodeEn
typedef struct TreeNodeEn {
    char englishWord[50];
    int unit;
    struct TreeNodeEn* left;
    struct TreeNodeEn* right;
} TreeNodeEn;

// Declarações das funções
TreeNodeEn* createNodeEn(const char* word, int unit);
TreeNodeEn* insertEnglishWordEn(TreeNodeEn* root, const char* word, int unit);
TreeNodeEn* searchEnglishWordEn(TreeNodeEn* root, const char* word);
void printBinaryTreeEn(TreeNodeEn* root);
TreeNodeEn* removeEnglishWordEn(TreeNodeEn* root, const char* word, int unit);
void imprimirTraducoesEn(TreeNodeEn* node, const char* palavraPortugues, int* primeira);
void printTreeEn(TreeNodeEn* root);
void limparArvoreBinariaEn(TreeNodeEn** root);

#endif // ARV_INGLES_BIN_H
