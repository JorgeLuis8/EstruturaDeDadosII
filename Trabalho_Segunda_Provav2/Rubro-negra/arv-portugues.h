#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#define BLACK 0
#define RED 1
#include "arv-ingles-bin.c"

typedef struct info
{
    char portugueseWord[50];      // Palavra em português
    TreeNode *englishTreeRoot;    // Raiz da árvore binária para traduções em inglês
    int unit;                     // Unidade correspondente
} Info;

typedef struct arv_portugues
{
    Info dados;
    struct arv_portugues *esq;
    struct arv_portugues *dir;
    int cor;
} Arv_portugues;

// Funções de criação e inserção
void ler_dados(arv_disciplina *no, arv_curso *curso);
arv_disciplina *cria_no();
arv_disciplina *inserir_disciplina(arv_disciplina *raiz, arv_disciplina *no);
arv_disciplina *inserir_rec(arv_disciplina *raiz, arv_disciplina *no);

// Funções de balanceamento e rotação
void trocaCor(arv_disciplina *H);
arv_disciplina *rotacionarEsquerda(arv_disciplina *A);
arv_disciplina *rotacionarDireita(arv_disciplina *A);
arv_disciplina *balancear(arv_disciplina *raiz);


    // Funções de remoção
    arv_disciplina *removerMenor(arv_disciplina * H);
    arv_disciplina *procuraMenor(arv_disciplina * atual);
    arv_disciplina *remove_NO(arv_disciplina * H, int valor);
    int remove_ArvLLRB(arv_disciplina * *raiz, int codigo);

    // Função de busca
    arv_disciplina *buscar_disciplina(arv_disciplina * raiz, int codigo);

    // Função de impressão
    void imprimir_disciplinas(arv_disciplina * raiz);

    // Funções auxiliares
    arv_disciplina *move2EsqRED(arv_disciplina * H);
    arv_disciplina *move2DirRED(arv_disciplina * H);

#endif // DISCIPLINA_H