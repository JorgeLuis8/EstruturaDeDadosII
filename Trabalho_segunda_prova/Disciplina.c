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

//     printf("Informe o nome da disciplina: ");
//     scanf("%s", no->dados->nome);

//     printf("Informe o bloco da disciplina: ");
//     scanf("%d", &no->dados->bloco);

//     printf("Informe a carga-horaria da disciplina: ");
//     scanf("%d", &no->dados->carga_horaria);
}

// Função para trocar a cor dos nós
void trocaCor(arv_disciplina *no)
{
    if (no != NULL)
    {
        no->cor = (no->cor == RED) ? BLACK : RED;
    }
}

// Função para rotacionar um nó para a direita
arv_disciplina *rotacionarDireita(arv_disciplina *no)
{
    arv_disciplina *aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    return aux;
}

// Função para rotacionar um nó para a esquerda
arv_disciplina *rotacionarEsquerda(arv_disciplina *no)
{
    arv_disciplina *aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    return aux;
}

arv_disciplina *balancear(arv_disciplina *raiz)
{
    // Caso 1: Filho da direita é vermelho
    if (raiz->dir != NULL && raiz->dir->cor == RED)
    {
        raiz = rotacionarEsquerda(raiz);
        trocaCor(raiz);
        trocaCor(raiz->esq);
    }

    // Caso 2: Filho da esquerda e neto esquerdo são vermelhos
    if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->esq->esq != NULL && raiz->esq->esq->cor == RED)
    {
        raiz = rotacionarDireita(raiz);
        trocaCor(raiz);
        trocaCor(raiz->dir);
    }

    // Caso 3: Ambos os filhos são vermelhos
    if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->dir != NULL && raiz->dir->cor == RED)
    {
        trocaCor(raiz);
        trocaCor(raiz->esq);
        trocaCor(raiz->dir);
    }

    return raiz;
}

// Função para inserir uma disciplina na árvore
arv_disciplina *inserir_disciplina(arv_disciplina *raiz, arv_disciplina *no)
{
    if (raiz == NULL)
    {
        raiz = no;
        raiz->cor = RED;
    }
    else
    {
        if (no->dados->codigo < raiz->dados->codigo)
        {
            raiz->esq = inserir_disciplina(raiz->esq, no);
        }
        else
        {
            raiz->dir = inserir_disciplina(raiz->dir, no);
        }
        raiz = balancear(raiz);
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