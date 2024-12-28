#ifndef ARVBIN_H
#define ARVBIN_H

typedef struct EnglishBinaryTree
{
  char palavraIngles[50];
  int unidade;
  struct EnglishBinaryTree *esq;
  struct EnglishBinaryTree *dir;
} BinaryTreeNode;

typedef struct  PortuguesRB  PortuguesRB;
BinaryTreeNode *initializeBinaryTreeNode(char *palavraIngles, int unidade);

// Função para inserir uma palavra em inglês na arvore binaria de busca
BinaryTreeNode *insertEnglishWord(BinaryTreeNode *root, char *palavraIngles, int unidade);

void addEnglishTranslation(PortuguesRB *raiz, char *palavraIng, int unidade);

int isLeafNodes(BinaryTreeNode *raiz);

BinaryTreeNode *singleChildNode(BinaryTreeNode *raiz);

BinaryTreeNode *minimumChildNode(BinaryTreeNode *raiz);

void printBinaryTree(BinaryTreeNode *root);

int removeEnglishWord(BinaryTreeNode **raiz, char *palavra);
void FindEnglishTerm(PortuguesRB **raiz, char *palavraIngles, int unidade);

#endif