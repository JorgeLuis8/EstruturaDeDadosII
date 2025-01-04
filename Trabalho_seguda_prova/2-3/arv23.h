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
Portugues23 *BuscarPalavra(Portugues23 **no, const char *palavraPortugues);
int inserirPalavraPortugues(Portugues23 **arvore, char *palavraPortugues, char *palavraIngles, int unidade);
void adicionarTraducaoEmIngles(Info *info, const char *palavraIng, int unidade);

Info createInfo(char *palavra, char *palavraIngles, int unidade);
Portugues23 *criaNo(const Info *informacao, Portugues23 *filhoesq, Portugues23 *filhocen);
Portugues23 *adicionaChave(Portugues23 *no,  Info *informacao, Portugues23 *filho);
Portugues23 *quebraNo(Portugues23 **no, const Info *informacao, Info *promove, Portugues23 **filho);
int ehFolha(const Portugues23 *no);
Portugues23 *inserirArv23(Portugues23 **no, Info *informacao, Info *promove, Portugues23 **pai);


void freeInfo2_3(Info *info);
void freeTree(Portugues23 **no);
int remove_palavra_ingles_unidade(Portugues23 *raiz, const char *palavraIngles, int unidade, Portugues23 **top);
void exibir_tree23(const Portugues23 *raiz);
void imprimirPalavrasUnidade(Portugues23 *arvore, int unidade, int *unidadeImpressa);

void exibir_traducao_Portugues(Portugues23 **raiz, const char *palavraPortugues);
void imprimirTraducoes(Inglesbin *node, int unidade, const char *palavraPortugues);

void menorInfoDir(Portugues23 *Raiz, Portugues23 **no, Portugues23 **paiNo);
void maiorInfoEsq(Portugues23 *Raiz, Portugues23 **no, Portugues23 **paiNo);
int remover23(Portugues23 **Pai, Portugues23 **Raiz, char *valor);
int arvore23_remover2(Portugues23 **raiz, char *info, Portugues23 *pai, Portugues23 **origem, Portugues23 **maior);

void imprimirTraducoesNoFormato(Inglesbin *node, int unidade, const char *palavraPortugues);
int arvore23_remover1(Portugues23 **raiz, char *info, Portugues23 *pai, Portugues23 **origem, Portugues23 **maior);
#endif