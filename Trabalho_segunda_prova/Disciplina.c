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
    if (raiz == NULL)
        return NULL;

    if (raiz->dados->codigo == codigo)
        return raiz;

    if (codigo < raiz->dados->codigo)
        return buscar_disciplina(raiz->esq, codigo);
    else
        return buscar_disciplina(raiz->dir, codigo);
}

arv_disciplina *move2EsqRED(arv_disciplina *H)
{
    trocaCor(H);
    if (H->dir != NULL && H->dir->esq != NULL && H->dir->esq->cor == RED)
    {
        H->dir = rotacionarDireita(H->dir);
        H = rotacionarEsquerda(H);
        trocaCor(H);
    }
    return H;
}

arv_disciplina *move2DirRED(arv_disciplina *H)
{
    trocaCor(H);
    if (H->esq != NULL && H->esq->esq != NULL && H->esq->esq->cor == RED)
    {
        H = rotacionarDireita(H);
        trocaCor(H);
    }
    return H;
}

arv_disciplina *removerMenor(arv_disciplina *H)
{
    if (H->esq == NULL)
    {
        free(H);
        return NULL;
    }
    if (H->esq->cor == BLACK && (H->esq->esq == NULL || H->esq->esq->cor == BLACK))
    {
        H = move2EsqRED(H);
    }
    H->esq = removerMenor(H->esq);
    return balancear(H);
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

arv_disciplina *remove_NO(arv_disciplina *H, int valor)
{
    if (H == NULL)
        return NULL;

    if (valor < H->dados->codigo)
    {
        if (H->esq != NULL && H->esq->cor == BLACK && (H->esq->esq == NULL || H->esq->esq->cor == BLACK))
            H = move2EsqRED(H);

        if (H->esq != NULL)
            H->esq = remove_NO(H->esq, valor);
    }
    else
    {
        if (H->esq != NULL && H->esq->cor == RED)
            H = rotacionarDireita(H);

        if (valor == H->dados->codigo && (H->dir == NULL))
        {
            free(H);
            return NULL;
        }

        if (H->dir != NULL && H->dir->cor == BLACK && (H->dir->esq == NULL || H->dir->esq->cor == BLACK))
            H = move2DirRED(H);

        if (valor == H->dados->codigo)
        {
            arv_disciplina *x = procuraMenor(H->dir);
            H->dados->codigo = x->dados->codigo;
            H->dir = removerMenor(H->dir);
        }
        else if (H->dir != NULL)
            H->dir = remove_NO(H->dir, valor);
    }
    return balancear(H);
}

int remove_ArvLLRB(arv_disciplina **raiz, int codigo)
{
    if (buscar_disciplina(*raiz, codigo))
    {
        *raiz = remove_NO(*raiz, codigo);
        if (*raiz != NULL)
        {
            (*raiz)->cor = BLACK;
        }
        return 1;
    }
    return 0;
}