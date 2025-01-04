#ifndef ARVBIN_H
#define ARVBIN_H
#include "arv23.h"
#include "unidade.h"


typedef struct Inglesbin {
    char *palavraIngles;
    struct Inglesbin *dir, *esq;
    Unit *unidades; // Lista ligada de unidades
} Inglesbin;

typedef struct Portugues23 Portugues23;



Inglesbin* initializeNode(const char* word, int unit);

// Função para inserir uma palavra em inglês na arvore binaria de busca
Inglesbin* insertEnglishWord(Inglesbin* root, const char* word, int unit);

void insertTranslation(Portugues23 *no, const char *palavraPortugues, const char *palavraIngles, int unidade);

int isLeafNode(Inglesbin *raiz);

Inglesbin *getSingleChild(Inglesbin *raiz);

Inglesbin *getMinimumChild(Inglesbin *raiz);

void printBinaryTree(Inglesbin *root);

int removeEnglishWord(Inglesbin **raiz, const char *palavra, int unidade);
Inglesbin *findEnglishWord(Inglesbin *raiz, const char *palavraIngles);

void clear_binary_tree(Inglesbin *raiz);
void showEnglishTranslations(Inglesbin *raiz);
#endif