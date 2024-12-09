#ifndef INGLESBIN_H
#define INGLESBIN_H


// Definição da estrutura para armazenar palavras em inglês em uma árvore binária de busca
typedef struct inglesbin {
    char palavraIngles[100]; // Palavra em inglês
    int unidade;             // Unidade associada à tradução
    struct inglesbin *esq;   // Subárvore esquerda
    struct inglesbin *dir;   // Subárvore direita
} Arv_ingles;

// Funções para manipulação da árvore binária de busca de palavras em inglês
Arv_ingles *createNode(char *palavraIngles, int unidade); // Cria um novo nó para a árvore binária
Arv_ingles *insertpalavraIngles(Arv_ingles *root, char *palavraIngles, int unidade); // Insere uma palavra em inglês na árvore binária
void printBinaryTree(Arv_ingles *root); // Imprime a árvore binária de palavras em inglês


// Funções para remoção de palavras em inglês
int ehFolhas(Arv_ingles *raiz); // Verifica se o nó é uma folha
Arv_ingles *soUmFilho(Arv_ingles *raiz); // Retorna o único filho de um nó (se existir)
Arv_ingles *menorFilho(Arv_ingles *raiz); // Encontra o menor filho (subárvore à esquerda)
int removerPalavraIngles(Arv_ingles **raiz, char *palavra); // Remove uma palavra em inglês da árvore binária

// Função para buscar e remover uma tradução em inglês associada à unidade
// Busca e remove uma tradução em inglês de uma palavra portuguesa

#endif // INGLESBIN_H
