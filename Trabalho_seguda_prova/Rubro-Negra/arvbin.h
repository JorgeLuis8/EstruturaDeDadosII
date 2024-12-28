#ifndef ARVBIN_H
#define ARVBIN_H

typedef struct InglesBin
{
  char palavraIngles[50];
  int unidade;
  struct InglesBin *esq;
  struct InglesBin *dir;
} Inglesbin;
typedef struct  PortuguesRB  PortuguesRB;
Inglesbin *createNode(char *palavraIngles, int unidade);

// Função para inserir uma palavra em inglês na arvore binaria de busca
Inglesbin *insertpalavraIngles(Inglesbin *root, char *palavraIngles, int unidade);

void adicionarTraducaoEmIngles(PortuguesRB *raiz, char *palavraIng, int unidade);

int ehFolhas(Inglesbin *raiz);

Inglesbin *soUmFilho(Inglesbin *raiz);

Inglesbin *menorFilho(Inglesbin *raiz);

void printBinaryTree(Inglesbin *root);

int removerPalavraIngles(Inglesbin **raiz, char *palavra);
void BuscarPalavraIngles(PortuguesRB **raiz, char *palavraIngles, int unidade);

#endif