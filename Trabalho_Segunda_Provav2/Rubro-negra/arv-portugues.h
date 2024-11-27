#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#define BLACK 0
#define RED 1

#include "arv-ingles-bin.c"

// Estrutura para armazenar os dados de cada nó
typedef struct info {
    char portugueseWord[50];      // Palavra em português
    struct arv_ingles *englishTreeRoot; // Raiz da árvore binária para traduções em inglês
    int unit;                     // Unidade correspondente
} Info;

// Estrutura para a árvore rubro-negra
typedef struct arv_portugues {
    Info dados;
    struct arv_portugues *esq;    // Ponteiro para o filho esquerdo
    struct arv_portugues *dir;    // Ponteiro para o filho direito
    int cor;                      // Cor do nó (RED ou BLACK)
} Arv_portugues;

// Funções de criação e inserção
void ler_dados(Arv_portugues *no, struct arv_ingles *curso);
Arv_portugues *cria_no_arv();
Arv_portugues *inserir_no(Arv_portugues *raiz, Arv_portugues *no);
Arv_portugues *inserir_rec_arv(Arv_portugues *raiz, Arv_portugues *no);

// Funções de balanceamento e rotação
void trocaCor_arv(Arv_portugues *H);
Arv_portugues *rotacionarEsquerda_arv(Arv_portugues *A);
Arv_portugues *rotacionarDireita_arv(Arv_portugues *A);
Arv_portugues *balancear_arv(Arv_portugues *raiz);

// Funções de remoção
Arv_portugues *removerMenor_arv(Arv_portugues *H);
Arv_portugues *procuraMenor_arv(Arv_portugues *atual);
Arv_portugues *remove_NO_arv(Arv_portugues *H, Arv_portugues *no);
int remove_ArvLLRB_arv(Arv_portugues **raiz, char *palavra, int unidade);

// Função de busca
Arv_portugues *buscar_palavra_portugues(Arv_portugues *raiz, char *palavra, int unidade);

// Função de impressão
void imprimir_disciplinas(Arv_portugues *raiz);

// Funções auxiliares
Arv_portugues *move2EsqRED_arv(Arv_portugues *H);
Arv_portugues *move2DirRED_arv(Arv_portugues *H);

#endif // DISCIPLINA_H
