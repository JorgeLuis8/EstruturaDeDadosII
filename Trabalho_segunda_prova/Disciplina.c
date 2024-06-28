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

void ler_dados(arv_disciplina *no)
{
    printf("Informe o codigo da disciplina: ");
    scanf("%d", &no->dados->codigo);

    printf("Informe o nome da disciplina: ");
    scanf("%s", no->dados->nome);

    printf("Informe o bloco da disciplina: ");
    scanf("%d", &no->dados->bloco);

    printf("Informe a carga-horaria da disciplina: ");
    scanf("%d", &no->dados->carga_horaria);
}

void trocaCor(arv_disciplina *no)
{
    if (no != NULL)
    {
        no->cor = !no->cor;
        if (no->esq != NULL)
            no->esq->cor = !no->esq->cor;
        if (no->dir != NULL)
            no->dir->cor = !no->dir->cor;
    }
}

arv_disciplina *rotacionarEsquerda(arv_disciplina *A)
{
    arv_disciplina *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

arv_disciplina *rotacionarDireita(arv_disciplina *A)
{
    arv_disciplina *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

arv_disciplina *inserir_disciplina(arv_disciplina *raiz, arv_disciplina *no)
{
    raiz = inserir_rec(raiz, no);
    if (raiz != NULL)
        raiz->cor = BLACK;
    return raiz;
}

arv_disciplina *inserir_rec(arv_disciplina *raiz, arv_disciplina *no)
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
    }
    raiz = balancear(raiz);
    return raiz;
}

arv_disciplina *balancear(arv_disciplina *raiz)
{
    if (raiz->dir != NULL && raiz->dir->cor == RED)
        raiz = rotacionarEsquerda(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->esq->esq != NULL && raiz->esq->esq->cor == RED)
        raiz = rotacionarDireita(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->dir != NULL && raiz->dir->cor == RED)
        trocaCor(raiz);

    return raiz;
}

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

arv_disciplina *buscar_disciplina(arv_disciplina *raiz, int codigo)
{
    arv_disciplina *aux = NULL;
    if (raiz != NULL) {
        if (raiz->dados->codigo == codigo)
            aux = raiz;
        else if (raiz->dados->codigo < codigo)
            aux = buscar_disciplina(raiz->dir, codigo);
        else
            aux = buscar_disciplina(raiz->esq, codigo);
    }
    return aux;
}

arv_disciplina *move2EsqRED(arv_disciplina *no)
{
    trocaCor(no);
    if (no->dir != NULL && no->dir->esq != NULL && no->dir->esq->cor == RED)
    {
        no->dir = rotacionarDireita(no->dir);
        no = rotacionarEsquerda(no);
        trocaCor(no);
    }
    return no;
}

arv_disciplina *move2DirRED(arv_disciplina *no)
{
    trocaCor(no);
    if (no->esq != NULL && no->esq->esq != NULL && no->esq->esq->cor == RED)
    {
        no = rotacionarDireita(no);
        trocaCor(no);
    }
    return no;
}

arv_disciplina *removerMenor(arv_disciplina *no)
{
    if (no->esq == NULL)
    {
        free(no);
        return NULL;
    }
    if (no->esq->cor == BLACK && (no->esq->esq == NULL || no->esq->esq->cor == BLACK))
    {
        no = move2EsqRED(no);
    }
    no->esq = removerMenor(no->esq);
    return balancear(no);
}

arv_disciplina *procuraMenor(arv_disciplina *atual)
{
    arv_disciplina *no1 = atual;
    arv_disciplina *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

arv_disciplina *remove_NO(arv_disciplina *no, int valor)
{
    arv_disciplina *aux;
    if (no == NULL)
        aux = NULL;
    if (valor < no->dados->codigo)
    {
        if (no->esq != NULL && no->esq->cor == BLACK && (no->esq->esq == NULL || no->esq->esq->cor == BLACK))
            no = move2EsqRED(no);

        if (no->esq != NULL)
            no->esq = remove_NO(no->esq, valor);
    }
    else
    {
        if (no->esq != NULL && no->esq->cor == RED)
            no = rotacionarDireita(no);

        if (valor == no->dados->codigo && (no->dir == NULL))
        {
            free(no);
            aux = NULL;
        }

        if (no->dir != NULL && no->dir->cor == BLACK && (no->dir->esq == NULL || no->dir->esq->cor == BLACK))
            no = move2DirRED(no);

        if (valor == no->dados->codigo)
        {
            arv_disciplina *x = procuraMenor(no->dir);
            no->dados->codigo = x->dados->codigo;
            no->dir = removerMenor(no->dir);
        }
        else if (no->dir != NULL)
            no->dir = remove_NO(no->dir, valor);
    }
    return balancear(no);
}

int remove_ArvLLRB(arv_disciplina **raiz, int codigo)
{
    int aux=0;
    if (buscar_disciplina(*raiz, codigo))
    {
        *raiz = remove_NO(*raiz, codigo);
        if (*raiz != NULL)
        {
            (*raiz)->cor = BLACK;
        }
        aux = 1;
    }

    return aux;
}