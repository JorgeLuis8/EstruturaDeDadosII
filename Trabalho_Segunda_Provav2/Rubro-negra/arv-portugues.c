#include <stdio.h>
#include <stdlib.h>
#include "arv-portugues.h"

#define BLACK 0
#define RED 1

Arv_portugues *cria_no_arv()
{
    Arv_portugues *no = (Arv_portugues *)malloc(sizeof(Arv_portugues));
    if (no != NULL)
    {
        no->cor = RED;
        no->esq = NULL;
        no->dir = NULL;
        no->dados.englishTreeRoot = NULL;
    }
    return no;
}

void trocaCor_arv(Arv_portugues *H)
{
    if (H != NULL)
    {
        H->cor = !H->cor;
        if (H->esq != NULL)
            H->esq->cor = !H->esq->cor;
        if (H->dir != NULL)
            H->dir->cor = H->dir->cor;
    }
}

Arv_portugues *rotacionarEsquerda_arv(Arv_portugues *A)
{
    Arv_portugues *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

Arv_portugues *rotacionarDireita_arv(Arv_portugues *A)
{
    Arv_portugues *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

Arv_portugues *inserir_no(Arv_portugues *raiz, Arv_portugues *no)
{
    raiz = inserir_rec_arv(raiz, no);
    if (raiz != NULL)
        raiz->cor = BLACK;
    return raiz;
    printf("Inseriu");
}

Arv_portugues *inserir_rec_arv(Arv_portugues *raiz, Arv_portugues *no)
{
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (strcmp(no->dados.portugueseWord, raiz->dados.portugueseWord) < 0)
            raiz->esq = inserir_rec_arv(raiz->esq, no);
        else
            raiz->dir = inserir_rec_arv(raiz->dir, no);
    }
    raiz = balancear_arv(raiz);
    return raiz;
}

Arv_portugues *balancear_arv(Arv_portugues *raiz)
{
    if (raiz->dir != NULL && raiz->dir->cor == RED)
        raiz = rotacionarEsquerda_arv(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->esq->esq != NULL && raiz->esq->esq->cor == RED)
        raiz = rotacionarDireita_arv(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->dir != NULL && raiz->dir->cor == RED)
        trocaCor_arv(raiz);

    return raiz;
}


Arv_portugues *buscar_palavra_portugues(Arv_portugues *raiz, char *portugues, int unidade) {
    Arv_portugues *resultado = NULL;
    if (raiz != NULL) {
        if (strcmp(portugues, raiz->dados.portugueseWord) == 0 && raiz->dados.unit == unidade) {
            resultado = raiz;
        } else if (strcmp(portugues, raiz->dados.portugueseWord) < 0) {
            resultado = buscar_palavra_portugues(raiz->esq, portugues, unidade);
        } else {
            resultado = buscar_palavra_portugues(raiz->dir, portugues, unidade);
        }
    }
    return resultado;
}

int remove_ArvLLRB_arv(Arv_portugues **raiz, char *palavra, int unidade) {
    int aux = 0;

    // Buscar o nó correspondente
    Arv_portugues *no = buscar_palavra_portugues(*raiz, palavra, unidade);
    if (no != NULL) {
        *raiz = remove_NO_arv(*raiz, no); // Passar o nó encontrado
        if (*raiz != NULL) {
            (*raiz)->cor = BLACK;
        }
        aux = 1; // Indicar sucesso
    }

    return aux; // Indicar se foi removido ou não
}


Arv_portugues *move2EsqRED_arv(Arv_portugues *H)
{
    trocaCor_arv(H);
    if (H->dir != NULL && H->dir->esq != NULL && H->dir->esq->cor == RED)
    {
        H->dir = rotacionarDireita_arv(H->dir);
        H = rotacionarEsquerda_arv(H);
        trocaCor_arv(H);
    }
    return H;
}

Arv_portugues *move2DirRED_arv(Arv_portugues *H)
{
    trocaCor_arv(H);
    if (H->esq != NULL && H->esq->esq != NULL && H->esq->esq->cor == RED)
    {
        H = rotacionarDireita_arv(H);
        trocaCor_arv(H);
    }
    return H;
}

Arv_portugues *removerMenor_arv(Arv_portugues *H)
{
    Arv_portugues *temp = H;

    if (H->esq == NULL)
    {
        free(H);
        temp = NULL;
    }
    else
    {
        if (H->esq->cor == BLACK && (H->esq->esq == NULL || H->esq->esq->cor == BLACK))
        {
            H = move2EsqRED_arv(H);
        }

        H->esq = removerMenor_arv(H->esq);
        H = balancear_arv(H);
    }

    return temp;
}

Arv_portugues *procuraMenor_arv(Arv_portugues *atual)
{
    Arv_portugues *no1 = atual;
    Arv_portugues *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}



Arv_portugues *remove_NO_arv(Arv_portugues *H, Arv_portugues *no) {
    if (H == NULL) {
        return NULL;
    }

    if (strcmp(no->dados.portugueseWord, H->dados.portugueseWord) < 0) {
        if (H->esq != NULL && H->esq->cor == BLACK && (H->esq->esq == NULL || H->esq->esq->cor == BLACK)) {
            H = move2EsqRED_arv(H);
        }
        H->esq = remove_NO_arv(H->esq, no);
    } else {
        if (H->esq != NULL && H->esq->cor == RED) {
            H = rotacionarDireita_arv(H);
        }
        if (strcmp(no->dados.portugueseWord, H->dados.portugueseWord) == 0 && H->dir == NULL) {
            free(H);
            return NULL;
        }
        if (H->dir != NULL && H->dir->cor == BLACK && (H->dir->esq == NULL || H->dir->esq->cor == BLACK)) {
            H = move2DirRED_arv(H);
        }
        if (strcmp(no->dados.portugueseWord, H->dados.portugueseWord) == 0) {
            Arv_portugues *x = procuraMenor_arv(H->dir);
            strcpy(H->dados.portugueseWord, x->dados.portugueseWord);
            H->dir = removerMenor_arv(H->dir);
        } else {
            H->dir = remove_NO_arv(H->dir, no);
        }
    }
    return balancear_arv(H);
}

// Função para verificar se existe palavras na unidade especificada
void verificarUnidade(Arv_portugues *arvore, int unidade, int *temPalavras) {
    if (arvore == NULL) {
        return;
    }

    // Verifica se a palavra da unidade corresponde
    if (arvore->dados.unit == unidade) {
        *temPalavras = 1;  // Encontrou palavras na unidade
    }

    // Percorre recursivamente as subárvores esquerda e direita
    verificarUnidade(arvore->esq, unidade, temPalavras);
    verificarUnidade(arvore->dir, unidade, temPalavras);
}
