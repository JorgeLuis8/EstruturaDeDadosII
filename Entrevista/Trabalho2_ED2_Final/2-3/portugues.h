#ifndef arv23_H
#define arv23_H


#include "ingles.h"
typedef struct info {
    char *portugueseWord;
    Inglesbin *englishWord;
} NodeInfo;

typedef struct PortugueseTree{
    NodeInfo info1;
    NodeInfo info2;
    struct PortugueseTree *cent;
    struct PortugueseTree *right;
    struct PortugueseTree *left;
    int nInfos;
} PortugueseTree;

typedef struct Inglesbin Inglesbin;
PortugueseTree *FindWord(PortugueseTree **no, const char *palavraPortugues);
int insertPortugueseTerm(PortugueseTree **arvore, char *palavraPortugues, char *palavraIngles, int unidade);
void addEnglishTranslation(NodeInfo *info, const char *palavraIng, int unidade);

NodeInfo createInfo(char *palavra, char *palavraIngles, int unidade);
PortugueseTree *createNode(NodeInfo *informacao, PortugueseTree *filhoesq, PortugueseTree *filhocen);
PortugueseTree *updateNode23(PortugueseTree *no,  NodeInfo *informacao, PortugueseTree *filho);
PortugueseTree *splitNode(PortugueseTree **no, NodeInfo *informacao, NodeInfo *promove, PortugueseTree **filho);
int isNodeLeaf(PortugueseTree *no);
PortugueseTree *insertNode23(PortugueseTree **no, NodeInfo *informacao, NodeInfo *promove, PortugueseTree **pai);
int remove_unit_from_tree(Inglesbin **root, const char *englishWord, int unit);


void removeNodeInfo(NodeInfo *info);
void deallocateTree(PortugueseTree **no);
int remove_english_word_by_unit(PortugueseTree *raiz, const char *palavraIngles, int unidade, PortugueseTree **top);
void print_tree23(PortugueseTree *raiz);
void printWordsAtUnit(PortugueseTree *arvore, int unidade, int *unidadeImpressa);

void printPortugueseTranslation(PortugueseTree **raiz, const char *palavraPortugues);
void printTranslations(Inglesbin *node, int unidade, const char *palavraPortugues);

int remove_unit_from_tree(Inglesbin **root, const char *englishWord, int unit);

int removeNodeFrom23Tree(PortugueseTree **raiz, char *info, PortugueseTree *pai, PortugueseTree **origem, PortugueseTree **maior);
int Remove_word_from_portuguese_unit(PortugueseTree **rootNode, char *portugueseWord, int unit);


void printTranslationsInFormat(Inglesbin *node, int unidade, const char *palavraPortugues);
int deleteFrom23Tree(PortugueseTree **raiz, char *info, PortugueseTree *pai, PortugueseTree **origem, PortugueseTree **maior);

void printAllTranslations(PortugueseTree *rootNode, const char *portugueseWord);
#endif