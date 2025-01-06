#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct listaEncadeadaUnidade
{
  char *nome_unidade;
  struct listaEncadeadaUnidade *prox;
} ListaEncadeadaUnidade;

typedef struct Inglesbin{
    ListaEncadeadaUnidade *unidades;
    char *englishWord;
    struct Inglesbin *rightChild,*leftChild;
} Inglesbin;

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



#endif // STRUCTS_H