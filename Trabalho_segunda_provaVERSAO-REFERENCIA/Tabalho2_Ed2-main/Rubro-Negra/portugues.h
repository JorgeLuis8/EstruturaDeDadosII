#ifndef PORTUGUES_H
#define PORTUGUES_H

#include "ingles.h"

// Definição da estrutura que irá armazenar a informação de uma palavra e suas traduções
typedef struct info {
    char *palavraPortugues;
    char *palavraIngles;
    int unidade;
} Info;

// Definição da estrutura do nó da árvore rubro-negra
typedef struct portuguesRB {
    Info info;
    int cor; // Cor do nó (1 = vermelho, 0 = preto)
    struct portuguesRB *esq, *dir; // Filhos esquerdo e direito
} PortuguesRB;

// Cores
#define RED 1
#define BLACK 0

// Funções para manipulação da árvore rubro-negra
Info criaInfo(char *palavra, char *palavraIngles, int unidade); // Cria a estrutura Info
PortuguesRB *criaNo(Info *informacao); // Cria um novo nó na árvore rubro-negra
int cor(PortuguesRB *raiz); // Retorna a cor de um nó (preto ou vermelho)
void troca_cor(PortuguesRB **raiz); // Troca a cor do nó e seus filhos
void rotacao_direita(PortuguesRB **raiz); // Realiza a rotação à direita
void rotacao_esquerda(PortuguesRB **raiz); // Realiza a rotação à esquerda
void balancear(PortuguesRB **raiz); // Balanceia a árvore rubro-negra após inserções
int inserirRB(PortuguesRB **raiz, Info *informacao); // Insere um nó na árvore rubro-negra
int inserirArvRB(PortuguesRB **raiz, Info *informacao); // Insere o nó e garante que a raiz seja preta
void moveEsqVermelha(PortuguesRB **raiz); // Move a cor vermelha para a esquerda
void moveDirVermelha(PortuguesRB **raiz); // Move a cor vermelha para a direita
void removeMenor(PortuguesRB **raiz); // Remove o menor nó da árvore
PortuguesRB *procuraMenor(PortuguesRB *raiz); // Busca o menor nó da árvore
int removerNoArvVP(PortuguesRB **raiz, char *valor); // Remove um nó com uma palavra portuguesa específica
void adicionarTraducaoEmIngles(PortuguesRB *raiz, char *palavraIng, int unidade); // Adiciona uma tradução em inglês
PortuguesRB *BuscarPalavra(PortuguesRB **arvore, char *palavraPortugues); // Busca uma palavra portuguesa na árvore

#endif // PORTUGUES_H
