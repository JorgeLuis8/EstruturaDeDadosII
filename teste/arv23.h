#ifndef arv23_H
#define arv23_H

#include "structs.h"
#include "arvbin.h"
#include "lista_encadeada.h"

int inserirPalavraPortugues(PortugueseTree **arvore, char *palavraPortugues, char *palavraIngles, char *unidade);
NodeInfo criaInfo(char *palavra, char *palavraIngles, char *unidade);
PortugueseTree *createNode(const NodeInfo *informacao, PortugueseTree *filhoesq, PortugueseTree *filhocen);
void adicionaChave(PortugueseTree *no, const NodeInfo informacao, PortugueseTree *filho);
PortugueseTree *quebraNo(PortugueseTree **no, const NodeInfo *informacao, NodeInfo *promove, PortugueseTree *filho);
int isNodeLeaf(const PortugueseTree *no);
PortugueseTree *insertNode23(PortugueseTree **no, NodeInfo *informacao, NodeInfo *promove, PortugueseTree **pai);


void print_tree23(const PortugueseTree *raiz);
void imprimirPalavrasUnidade(PortugueseTree *arvore, char *unidade);
void imprimirTraducoes(Inglesbin *node, char *unidade, const char *palavraPortugues);
PortugueseTree *FindWord(PortugueseTree **no, const char *palavraPortugues);
void printPortugueseTranslation(PortugueseTree **raiz, const char *palavraPortugues);
void arvore23_exibir_pos(PortugueseTree *raiz);
void arvore23_exibir_pre(PortugueseTree *raiz);
void arvore23_exibir_ordem(PortugueseTree *raiz);


int rebalanceTree23(PortugueseTree **raiz, char *info, PortugueseTree **maior);
PortugueseTree *no23_juntar(PortugueseTree *filho1, NodeInfo info, PortugueseTree *maior, PortugueseTree **raiz);
int can_remove_node(PortugueseTree *raiz);
int removeNodeFrom23Tree(PortugueseTree **raiz, char *info, PortugueseTree *pai, PortugueseTree **origem, PortugueseTree **maior);
int deleteFrom23Tree(PortugueseTree **raiz, char *info, PortugueseTree *pai, PortugueseTree **origem, PortugueseTree **maior);
int nonLeafNodeDeletion(PortugueseTree **origem, PortugueseTree* raiz, NodeInfo *info, PortugueseTree *filho1, PortugueseTree *filho2, PortugueseTree **maior);
int removeNonLeafNodeFrom23Tree(PortugueseTree **origem, PortugueseTree* raiz, NodeInfo *info, PortugueseTree *filho1, PortugueseTree *filho2, PortugueseTree **maior);
int remove_node_from23_tree(PortugueseTree **raiz, char *info);

void deleteInfo2_3(NodeInfo *info);
void deallocateTree(PortugueseTree **no);

#endif