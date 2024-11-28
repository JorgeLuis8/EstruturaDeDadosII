#ifndef ARV_PORTUGUES_H
#define ARV_PORTUGUES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv-ingles-bin.h" // Inclui a árvore binária para as traduções em inglês

#define BLACK 0
#define RED 1

// Estrutura Info para armazenar informações de palavras em português
typedef struct Info {
    char portugueseWord[50]; // Palavra em português
    int unit;                // Unidade
    TreeNode* englishTreeRoot; // Raiz da árvore binária de traduções em inglês
} Info;

// Estrutura para o nó da árvore vermelho-preta
typedef struct Arv_portugues {
    Info dados;                  // Dados armazenados no nó
    int cor;                     // Cor do nó: RED ou BLACK
    struct Arv_portugues* esq;   // Subárvore esquerda
    struct Arv_portugues* dir;   // Subárvore direita
} Arv_portugues;

// Funções para manipulação da árvore vermelho-preta

// Cria um novo nó na árvore
Arv_portugues* cria_no_arv();

// Troca a cor de um nó e de seus filhos
void trocaCor_arv(Arv_portugues* H);

// Rotaciona a subárvore à esquerda
Arv_portugues* rotacionarEsquerda_arv(Arv_portugues* A);

// Rotaciona a subárvore à direita
Arv_portugues* rotacionarDireita_arv(Arv_portugues* A);

// Insere um novo nó na árvore
Arv_portugues* inserir_no(Arv_portugues* raiz, Arv_portugues* no);

// Função auxiliar para inserção recursiva
Arv_portugues* inserir_rec_arv(Arv_portugues* raiz, Arv_portugues* no);

// Balanceia a árvore após inserção ou remoção
Arv_portugues* balancear_arv(Arv_portugues* raiz);

// Busca uma palavra em português na árvore
Arv_portugues* buscar_palavra_portugues(Arv_portugues* raiz, char* portugues, int unidade);

// Remove uma palavra da árvore vermelho-preta
int remove_ArvLLRB_arv(Arv_portugues** raiz, char* palavra, int unidade);

// Move a subárvore esquerda se for RED
Arv_portugues* move2EsqRED_arv(Arv_portugues* H);

// Move a subárvore direita se for RED
Arv_portugues* move2DirRED_arv(Arv_portugues* H);

// Remove o menor nó da subárvore
Arv_portugues* removerMenor_arv(Arv_portugues* H);

// Procura o menor nó na subárvore
Arv_portugues* procuraMenor_arv(Arv_portugues* atual);

// Remove um nó específico da árvore
Arv_portugues* remove_NO_arv(Arv_portugues* H, Arv_portugues* no);

#endif // ARV_PORTUGUES_H
