#ifndef ARVBIN_H
#define ARVBIN_H

#include "structs.h"

Inglesbin* createNode(const char* word, char *unidade);
int insertpalavraIngles(Inglesbin **root, NodeInfo *informacao);

void printBinaryTree(Inglesbin *root);

int eh_Folha(Inglesbin *raiz);
Inglesbin *soUmFilho(Inglesbin **raiz);
Inglesbin *getMinimumChild(Inglesbin *raiz);
int removerPalavraIngles(Inglesbin **raiz, const char *palavra);
void clear_binary_tree(Inglesbin *raiz);

#endif