#ifndef ARVRB_H
#define ARVRB_H

typedef struct Info
{
  BinaryTreeNode *englishWordNode;
  char *portugueseWord;
} Info;

typedef struct PortuguesRB
{
  Info info;
  int color;
  struct PortuguesRB *left;
  struct PortuguesRB *right;
} PortuguesRB;

int insertPortugueseWord(PortuguesRB **arvore, char *palavraPortugues, char *palavraIngles, int unidade);

Info createInfo(char *palavra, char *palavraIngles, int unidade);

PortuguesRB *createNode(Info *informacao);
int getNodeColor(PortuguesRB *raiz);

void switch_node_color(PortuguesRB **raiz);

void rotate_right(PortuguesRB **raiz);

void left_rotate(PortuguesRB **raiz);

void balanceTree(PortuguesRB **raiz);

int insertRedBlackNode(PortuguesRB **raiz, Info *informacao);

int insertRedBlackTree(PortuguesRB **raiz, Info *informacao);

void shiftLeftRed(PortuguesRB **raiz);

void rotateRedRight(PortuguesRB **raiz);

void removeMinimum(PortuguesRB **raiz);

PortuguesRB *findMinimum(PortuguesRB *raiz);

int removeNodeFromRBTree(PortuguesRB **raiz, char *valor);

int removeRBTreeNode(PortuguesRB **raiz, char *valor);

PortuguesRB *SearchWordInTree(PortuguesRB **arvore, char *palavraPortugues);

void printWordsByUnit(PortuguesRB *arvore, int unidade);

void showPortugueseTranslation(PortuguesRB **raiz, char *palavraPortugues);

void printTranslations(BinaryTreeNode *node, int unidade, char *palavraPortugues);

void showRedBlackTree(PortuguesRB *raiz);


// void freeTree(PortuguesRB *no);

#endif