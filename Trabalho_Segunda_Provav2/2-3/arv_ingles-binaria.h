#ifndef ARV_INGLES_BINARIA_H
#define ARV_INGLES_BINARIA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura para o nó da árvore binária de busca para palavras em inglês
typedef struct TreeNode {
    char englishWord[50];   // Palavra em inglês
    int unit;               // Unidade à qual a palavra pertence
    struct TreeNode *left;  // Subárvore esquerda
    struct TreeNode *right; // Subárvore direita
} TreeNode;

// Declarações das funções

// Função para criar um novo nó na árvore binária de busca
TreeNode* createNode(const char* word, int unit);

// Função para inserir uma palavra em inglês na árvore binária de busca
TreeNode* insertEnglishWord(TreeNode* root, const char* word, int unit);

// Função para buscar uma palavra em inglês na árvore binária de busca
TreeNode* searchEnglishWord(TreeNode* root, const char* word);

// Função para imprimir a árvore binária em ordem alfabética
void printBinaryTree(TreeNode* root);

TreeNode* removeEnglishWord(TreeNode* root, const char* word);
void imprimirTraducoes(TreeNode *node, const char *palavraPortugues, int *primeira);
#endif // ARV_INGLES_BINARIA_H