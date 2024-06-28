#include <stdio.h>
#include <stdlib.h>
#include "Disciplina.h"




arv_curso *cria_no_curso()
{
    arv_curso *no = (arv_curso *)malloc(sizeof(arv_curso));
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
void ler_dados(arv_curso *no)
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
void trocaCor(arv_curso *raiz)
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
arv_curso *rotacionarEsquerda(arv_disciplina *A)
{
    arv_curso *aux = A->dir;
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

arv_curso *inserir_disciplina(arv_curso *raiz, arv_curso *no)
{
    raiz = inserir_rec(raiz, no); // Inserir e corrigir a árvore
    if (raiz != NULL)             // Garantir que a raiz seja sempre preta
        raiz->cor = BLACK;
    return raiz;
}

arv_disciplina *inserir_rec(arv_curso *raiz, arv_curso *no)
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

void imprimir_disciplinas(arv_curso *raiz)
{
    if (raiz != NULL)
    {
        imprimir_disciplinas(raiz->esq);
        printf("Codigo: %d\n", raiz->dados->codigo);
        printf("Nome: %s\n", raiz->dados->nome);
        printf("Quantidade de blocos: %d\n", raiz->dados->qtd_blocos);
        printf("Numero de semnas: %d\n", raiz->dados->num_semanas);
        printf("Cor: %d\n", raiz->cor);
        imprimir_disciplinas(raiz->dir);
    }
}

arv_curso *buscar_disciplina(arv_curso *raiz, int codigo)
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

arv_curso *move2EsqRED(arv_curso *H)
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

arv_curso *move2DirRED(arv_curso *H)
{
    trocaCor(H);
    if (H->esq != NULL && H->esq->esq != NULL && H->esq->esq->cor == RED)
    {
        H = rotacionarDireita(H);
        trocaCor(H);
    }
    return H;
}

arv_curso *removerMenor(arv_curso *H)
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

arv_curso *procuraMenor(arv_curso *atual)
{
    arv_curso *no1 = atual;
    arv_curso *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

arv_curso *remove_NO(arv_curso *H, int valor)
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

int remove_ArvLLRB(arv_curso **raiz, int codigo)
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