#ifndef arv23_H
#define arv23_H


#include "arvbin.h"
typedef struct info {
    char *palavraPortugues;
    Inglesbin *palavraIngles;
} Info;

typedef struct Portugues23{
    Info info1;
    Info info2;
    struct Portugues23 *cent;
    struct Portugues23 *dir;
    struct Portugues23 *esq;
    int nInfos;
} Portugues23;

typedef struct Inglesbin Inglesbin;
Portugues23 *FindWord(Portugues23 **no, const char *palavraPortugues);
int insertPortugueseTerm(Portugues23 **arvore, char *palavraPortugues, char *palavraIngles, int unidade);
void addEnglishTranslation(Info *info, const char *palavraIng, int unidade);

Info createInfo(char *palavra, char *palavraIngles, int unidade);
Portugues23 *createNode(const Info *informacao, Portugues23 *filhoesq, Portugues23 *filhocen);
Portugues23 *updateNode23(Portugues23 *no,  Info *informacao, Portugues23 *filho);
Portugues23 *splitNode(Portugues23 **no, const Info *informacao, Info *promove, Portugues23 **filho);
int ehFolha(const Portugues23 *no);
Portugues23 *inserirArv23(Portugues23 **no, Info *informacao, Info *promove, Portugues23 **pai);


void deleteInfo2_3(Info *info);
void deallocateTree(Portugues23 **no);
int remove_palavra_ingles_unidade(Portugues23 *raiz, const char *palavraIngles, int unidade, Portugues23 **top);
void print_tree23(const Portugues23 *raiz);
void printWordsAtUnit(Portugues23 *arvore, int unidade, int *unidadeImpressa);

void printPortugueseTranslation(Portugues23 **raiz, const char *palavraPortugues);
void printTranslations(Inglesbin *node, int unidade, const char *palavraPortugues);

void menorInfoDir(Portugues23 *Raiz, Portugues23 **no, Portugues23 **paiNo);
void maiorInfoEsq(Portugues23 *Raiz, Portugues23 **no, Portugues23 **paiNo);
int remover23(Portugues23 **Pai, Portugues23 **Raiz, char *valor);
int removeNodeFrom23Tree(Portugues23 **raiz, char *info, Portugues23 *pai, Portugues23 **origem, Portugues23 **maior);

void printTranslationsInFormat(Inglesbin *node, int unidade, const char *palavraPortugues);
int deleteFrom23Tree(Portugues23 **raiz, char *info, Portugues23 *pai, Portugues23 **origem, Portugues23 **maior);
#endif