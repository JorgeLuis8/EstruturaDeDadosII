#ifndef ARV_PORTUGUES_23_H
#define ARV_PORTUGUES_23_H

#include "arv_ingles-binaria.h"  // Inclui o cabeçalho da árvore binária para traduções em inglês

// Estrutura para armazenar as informações de cada palavra
typedef struct Info {
    char portugueseWord[50];      // Palavra em português
    TreeNode *englishTreeRoot;    // Raiz da árvore binária para traduções em inglês
    int unit;                     // Unidade correspondente
} Info;

// Estrutura do nó da árvore 2-3
typedef struct Tree23Node {
    Info info1;                   // Primeira informação
    Info info2;                   // Segunda informação (se houver)
    struct Tree23Node *left;      // Filho esquerdo
    struct Tree23Node *middle;    // Filho do meio
    struct Tree23Node *right;     // Filho direito
    struct Tree23Node *pai;       // Ponteiro para o nó pai
    int nInfos;                   // Número de chaves no nó (1 ou 2)
} Tree23Node;

// Funções para manipulação da árvore 2-3

// Funções de criação e inserção
Tree23Node* criarNodo23(Info info1, Info info2, int qtdDados, Tree23Node *pai, Tree23Node *left, Tree23Node *middle, Tree23Node *right);
void inserirValorArvore(Tree23Node **arvore, Info novoInfo);

// Funções de remoção e reconfiguração
void removerValorArvore(Tree23Node **arvore, const char *valor);
void removerValorNodo(Tree23Node **nodo, const char *valor);
Tree23Node** reconfigArvore(Tree23Node **remover, Tree23Node *irmao);
Tree23Node** unirPai(Tree23Node **remover, Tree23Node *irmao);
Tree23Node** unirFilho(Tree23Node **remover, Tree23Node *irmao);

// Funções de rotação
void rotacionarEsq(Tree23Node *remover, Tree23Node *irmao);
void rotacionarDir(Tree23Node *remover, Tree23Node *irmao);

// Funções de busca e utilitárias
Tree23Node** buscarValorArvore(Tree23Node **arvore, const char *valor, Tree23Node **irmao);
Tree23Node** trocarValoresArvore(Tree23Node **nodo, const char *valor, Tree23Node **irmao);
int ehFolha(Tree23Node *no);
int ehRaiz(Tree23Node *no);
int estaCheio(Tree23Node *no);
int estaNodo(Tree23Node *nodo, const char *valor);

// Funções de impressão e limpeza
void imprimirArvore(Tree23Node *arvore, int nivel);
void imprimirNodo(Tree23Node *no, int value, int nivel);
void limparArvore(Tree23Node **arvore);
void imprimirArvorePorUnidade(Tree23Node *arvore);
void imprimirPorDadaUnidadeTraducoes(Tree23Node *arvore, int unidade);

void removerPalavraIngles(Tree23Node** arvore, const char* palavraIngles, int unidade);

// Função para imprimir as palavras e traduções de uma unidade específica
void imprimirPorDadaUnidadeTraducoes(Tree23Node *arvore, int unidade);

// Função auxiliar para imprimir as informações de uma unidade formatadas, linha por linha
void imprimirInfoUnidadeFormatadaLinhaPorLinha(Tree23Node *arvore, int unidade);

// Função para imprimir as traduções da árvore binária de traduções, linha por linha
void imprimirTraducoesLinhaPorLinha(TreeNode *raiz);

#endif // ARV_PORTUGUES_23_H
