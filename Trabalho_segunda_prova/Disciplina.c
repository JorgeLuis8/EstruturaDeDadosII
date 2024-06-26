#include <stdio.h>
#include <stdlib.h>
#include "Disciplina.h"

#define BLACK 0
#define RED 1

arv_disciplina *cria_no()
{
    arv_disciplina *no = (arv_disciplina *)malloc(sizeof(arv_disciplina));
    if (no != NULL)
    {
        no->dados = (dados_disciplina *)malloc(sizeof(dados_disciplina));
        no->cor = RED;
        no->esq = NULL;
        no->dir = NULL;
    }
    return no;
}

// Função para ler os dados da disciplina
void ler_dados(arv_disciplina *no)
{
    printf("Informe o codigo da disciplina: ");
    scanf("%d", &no->dados->codigo);

    // printf("Informe o nome da disciplina: ");
    // scanf("%s", no->dados->nome);

    // printf("Informe o bloco da disciplina: ");
    // scanf("%d", &no->dados->bloco);

    // printf("Informe a carga-horaria da disciplina: ");
    // scanf("%d", &no->dados->carga_horaria);
}

// Função para trocar a cor dos nós
void trocaCor(arv_disciplina *H)
{
    if (H != NULL)
    {
        H->cor = !H->cor;
        if (H->esq != NULL)
            H->esq->cor = !H->esq->cor;
        if (H->dir != NULL)
            H->dir->cor = !H->dir->cor;
    }
}

// Função para rotacionar um nó para a esquerda
arv_disciplina *rotacionarEsquerda(arv_disciplina *A)
{
    arv_disciplina *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

// Função para rotacionar um nó para a direita
arv_disciplina *rotacionarDireita(arv_disciplina *A)
{
    arv_disciplina *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

// Função para inserir uma disciplina na árvore
arv_disciplina *inserir_disciplina(arv_disciplina *raiz, arv_disciplina *no)
{
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (no->dados->codigo < raiz->dados->codigo)
            raiz->esq = inserir_disciplina(raiz->esq, no);
        else
            raiz->dir = inserir_disciplina(raiz->dir, no);

        // Verificações de correção de árvore vermelho-preta
        if (raiz->dir != NULL && raiz->dir->cor == RED)
            raiz = rotacionarEsquerda(raiz);
        if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->esq->esq != NULL && raiz->esq->esq->cor == RED)
            raiz = rotacionarDireita(raiz);
        if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->dir != NULL && raiz->dir->cor == RED)
            trocaCor(raiz);
    }
    return raiz;
}

// Função para imprimir as disciplinas
void imprimir_disciplinas(arv_disciplina *raiz)
{
    if (raiz != NULL)
    {
        imprimir_disciplinas(raiz->esq);
        printf("Codigo: %d\n", raiz->dados->codigo);
        printf("Nome: %s\n", raiz->dados->nome);
        printf("Bloco: %d\n", raiz->dados->bloco);
        printf("Carga-Horaria: %d\n", raiz->dados->carga_horaria);
        printf("Cor: %d\n", raiz->cor);
        imprimir_disciplinas(raiz->dir);
    }
}