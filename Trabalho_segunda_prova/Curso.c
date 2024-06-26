#include <stdio.h>
#include <stdlib.h>
#include "Disciplina.h"

#define RED 0
#define BLACK 1

typedef struct Dados
{
    int codigo;
    char nome[50];
    int qtd_blocos;
    int num_semanas;
}dados_curso;

typedef struct Curso
{
    arv_disciplina * disciplinas;
    struct Dados *dados;
    int cor;
    struct Curso *esq,*dir;
}curso;


curso *cria_no()
{
    curso *no = (curso *)malloc(sizeof(curso));
    if (no != NULL)
    {
        no->dados = (dados_curso *)malloc(sizeof(dados_curso));
        no->cor = RED;
        no->esq = NULL;
        no->dir = NULL;
        no->disciplinas = NULL;
    }
    return no;
}

// Função para ler os dados da disciplina
void ler_dados(curso *no)
{
    printf("Informe o codigo do curso: ");
    scanf("%d", &no->dados->codigo);

    printf("Informe o nome do curso: ");
    scanf("%s", no->dados->nome);

    printf("Informe a quantidade de blocos do curso: ");
    scanf("%d", &no->dados->qtd_blocos);

    printf("Informe o numero de semanas para cada disciplina: ");
    scanf("%d", &no->dados->num_semanas);
}

// Função para trocar a cor dos nós
void trocaCor(curso *raiz)
{
    if (raiz != NULL)
    {
        raiz->cor = !raiz->cor;
        if (raiz->esq != NULL)
            raiz->esq->cor = !raiz->esq->cor;
        if (raiz->dir != NULL)
            raiz->dir->cor = !raiz->dir->cor;
    }
}

// Função para rotacionar um nó para a esquerda
arv_disciplina *rotacionarEsquerda(arv_disciplina *A)
{
    arv_disciplina *aux = A->dir;
    A->dir = aux->esq;
    aux->esq = A;
    aux->cor = A->cor;
    A->cor = RED;
    return aux;
}

// Função para rotacionar um nó para a direita
arv_disciplina *rotacionarDireita(arv_disciplina *A)
{
    arv_disciplina *aux = A->esq;
    A->esq = aux->dir;
    aux->dir = A;
    aux->cor = A->cor;
    A->cor = RED;
    return aux;
}

curso *inserir_disciplina(curso *raiz, curso *no)
{
    raiz = inserir_rec(raiz, no); // Inserir e corrigir a árvore
    if (raiz != NULL)             // Garantir que a raiz seja sempre preta
        raiz->cor = BLACK;
    return raiz;
}

arv_disciplina *inserir_rec(curso *raiz, curso *no)
{
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (no->dados->codigo < raiz->dados->codigo)
            raiz->esq = inserir_rec(raiz->esq, no);
        else
            raiz->dir = inserir_rec(raiz->dir, no);

        if (raiz->dir != NULL && raiz->dir->cor == RED)
            raiz = rotacionarEsquerda(raiz);
        if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->esq->esq != NULL && raiz->esq->esq->cor == RED)
            raiz = rotacionarDireita(raiz);
        if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->dir != NULL && raiz->dir->cor == RED)
            trocaCor(raiz);
    }
    return raiz;
}

