#include <stdio.h>
#include <stdlib.h>
#include "Disciplina.h"
#include "Curso.h"

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

void ler_dados(arv_disciplina *no, arv_curso *curso)
{
    printf("Informe o codigo da disciplina: ");
    scanf("%d", &no->dados->codigo);

    printf("Informe o nome da disciplina: ");
    scanf(" %99[^\n]", no->dados->nome);

    int bloco;
    do
    {
        printf("Informe o bloco da disciplina (deve ser menor que a quantidade de blocos do curso, que é %d): ", curso->dados->qtd_blocos);
        scanf("%d", &bloco);
        if (bloco >= curso->dados->qtd_blocos)
        {
            printf("Bloco inválido. Deve ser menor que a quantidade de blocos do curso.\n");
        }
    } while (bloco >= curso->dados->qtd_blocos);
    no->dados->bloco = bloco;

    int carga_horaria;
    do
    {
        printf("Informe a carga-horaria da disciplina (deve ser múltiplo de %d semanas): ", curso->dados->num_semanas);
        scanf("%d", &carga_horaria);
        if (carga_horaria % curso->dados->num_semanas != 0)
        {
            printf("Carga-horária inválida. Deve ser múltiplo de %d semanas.\n", curso->dados->num_semanas);
        }
    } while (carga_horaria % curso->dados->num_semanas != 0);
    no->dados->carga_horaria = carga_horaria;
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
    arv_disciplina *aux = NULL;
    if (raiz != NULL)
    {
        if (raiz->dados->codigo == codigo)
            aux = raiz;
        else if (raiz->dados->codigo < codigo)
            aux = buscar_disciplina(raiz->dir, codigo);
        else
            aux = buscar_disciplina(raiz->esq, codigo);
    }
    return aux;
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
    arv_disciplina *temp = H;

    if (H->esq == NULL)
    {
        free(H);
        temp = NULL;
    }
    else
    {
        if (H->esq->cor == BLACK && (H->esq->esq == NULL || H->esq->esq->cor == BLACK))
        {
            H = move2EsqRED(H);
        }

        H->esq = removerMenor(H->esq);
        H = balancear(H);
    }

    return temp;
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
    arv_disciplina *resultado = H; // Variável auxiliar para armazenar o resultado final

    if (H == NULL)
    {
        resultado = NULL;
    }
    else
    {
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
                resultado = NULL;
            }
            else
            {
                if (H->dir != NULL && H->dir->cor == BLACK && (H->dir->esq == NULL || H->dir->esq->cor == BLACK))
                    H = move2DirRED(H);

                if (valor == H->dados->codigo)
                {
                    arv_disciplina *x = procuraMenor(H->dir);
                    H->dados->codigo = x->dados->codigo;
                    H->dir = removerMenor(H->dir);
                }
                else if (H->dir != NULL)
                {
                    H->dir = remove_NO(H->dir, valor);
                }
            }
        }
    }

    if (resultado != NULL)
    {
        resultado = balancear(resultado);
    }

    return resultado;
}

int remove_ArvLLRB(arv_disciplina **raiz, int codigo)
{
    int aux = 0;
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

void imprimir_disciplinas_ordenadas(arv_disciplina *raiz)
{
    if (raiz != NULL)
    {
        imprimir_disciplinas_ordenadas(raiz->esq);
        printf("Código: %d, Nome: %s, Carga Horária: %d\n", raiz->dados->codigo, raiz->dados->nome, raiz->dados->carga_horaria);
        imprimir_disciplinas_ordenadas(raiz->dir);
    }
}