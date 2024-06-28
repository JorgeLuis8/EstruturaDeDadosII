#include <stdio.h>
#include <stdlib.h>
#include "Curso.h"

#define BLACK 0
#define RED 1

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

void ler_dados_curso(arv_curso *no)
{
    printf("Informe o código do curso: ");
    scanf("%d", &no->dados->codigo);

    printf("Informe o nome do curso: ");
    scanf(" %99[^\n]", no->dados->nome); 

    printf("Informe a quantidade de blocos do curso: ");
    scanf("%d", &no->dados->qtd_blocos);

    printf("Informe o número de semanas para cada disciplina: ");
    scanf("%d", &no->dados->num_semanas);
}

void trocaCor_curso(arv_curso *H)
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

arv_curso *rotacionarEsquerda_curso(arv_curso *A)
{
    arv_curso *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

arv_curso *rotacionarDireita_curso(arv_curso *A)
{
    arv_curso *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

arv_curso *inserir_curso(arv_curso *raiz, arv_curso *no)
{
    raiz = inserir_rec_curso(raiz, no);
    if (raiz != NULL)
        raiz->cor = BLACK;
    return raiz;
}

void imprimir_cursos_por_blocos(arv_curso *raiz, int qtd_blocos)
{
    if (raiz == NULL)
        return;

    // Percorre a árvore em ordem
    imprimir_cursos_por_blocos(raiz->esq, qtd_blocos);

    // Imprime o curso se a quantidade de blocos for igual à informada
    if (raiz->dados->qtd_blocos == qtd_blocos)
    {
        printf("Código do Curso: %d\n", raiz->dados->codigo);
        printf("Nome do Curso: %s\n", raiz->dados->nome);
        printf("Quantidade de Blocos: %d\n", raiz->dados->qtd_blocos);
        printf("Número de Semanas: %d\n", raiz->dados->num_semanas);
        printf("------------------------\n");
    }

    imprimir_cursos_por_blocos(raiz->dir, qtd_blocos);
}

arv_curso *inserir_rec_curso(arv_curso *raiz, arv_curso *no)
{
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (no->dados->codigo < raiz->dados->codigo)
            raiz->esq = inserir_rec_curso(raiz->esq, no);
        else
            raiz->dir = inserir_rec_curso(raiz->dir, no);
    }
    raiz = balancear_curso(raiz);
    return raiz;
}

arv_curso *balancear_curso(arv_curso *raiz)
{
    if (raiz->dir != NULL && raiz->dir->cor == RED)
        raiz = rotacionarEsquerda_curso(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->esq->esq != NULL && raiz->esq->esq->cor == RED)
        raiz = rotacionarDireita_curso(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == RED && raiz->dir != NULL && raiz->dir->cor == RED)
        trocaCor_curso(raiz);

    return raiz;
}

arv_curso *buscar_disciplina_curso(arv_curso *raiz, int codigo)
{
    arv_curso *aux = NULL;
    if (raiz != NULL)
    {
        if (raiz->dados->codigo == codigo)
            aux = raiz;
        else if (raiz->dados->codigo < codigo)
            aux = buscar_disciplina_curso(raiz->dir, codigo);
        else
            aux = buscar_disciplina_curso(raiz->esq, codigo);
    }
    return aux;
}

arv_curso *move2EsqRED_curso(arv_curso *H)
{
    trocaCor_curso(H);
    if (H->dir != NULL && H->dir->esq != NULL && H->dir->esq->cor == RED)
    {
        H->dir = rotacionarDireita_curso(H->dir);
        H = rotacionarEsquerda_curso(H);
        trocaCor_curso(H);
    }
    return H;
}

arv_curso *move2DirRED_curso(arv_curso *H)
{
    trocaCor_curso(H);
    if (H->esq != NULL && H->esq->esq != NULL && H->esq->esq->cor == RED)
    {
        H = rotacionarDireita_curso(H);
        trocaCor_curso(H);
    }
    return H;
}

arv_curso *removerMenor_curso(arv_curso *H)
{
    arv_curso *temp = H;

    if (H->esq == NULL)
    {
        free(H);
        temp = NULL;
    }
    else
    {
        if (H->esq->cor == BLACK && (H->esq->esq == NULL || H->esq->esq->cor == BLACK))
        {
            H = move2EsqRED_curso(H);
        }

        H->esq = removerMenor_curso(H->esq);
        H = balancear_curso(H);
    }

    return temp;
}

arv_curso *procuraMenor_curso(arv_curso *atual)
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

arv_curso *remove_NO_curso(arv_curso *H, int valor)
{
    arv_curso *resultado = H; // Variável auxiliar para armazenar o resultado final

    if (H == NULL)
    {
        resultado = NULL;
    }
    else
    {
        if (valor < H->dados->codigo)
        {
            if (H->esq != NULL && H->esq->cor == BLACK && (H->esq->esq == NULL || H->esq->esq->cor == BLACK))
                H = move2EsqRED_curso(H);

            if (H->esq != NULL)
                H->esq = remove_NO_curso(H->esq, valor);
        }
        else
        {
            if (H->esq != NULL && H->esq->cor == RED)
                H = rotacionarDireita_curso(H);

            if (valor == H->dados->codigo && (H->dir == NULL))
            {
                free(H);
                resultado = NULL;
            }
            else
            {
                if (H->dir != NULL && H->dir->cor == BLACK && (H->dir->esq == NULL || H->dir->esq->cor == BLACK))
                    H = move2DirRED_curso(H);

                if (valor == H->dados->codigo)
                {
                    arv_curso *x = procuraMenor_curso(H->dir);
                    H->dados->codigo = x->dados->codigo;
                    H->dir = removerMenor_curso(H->dir);
                }
                else if (H->dir != NULL)
                {
                    H->dir = remove_NO_curso(H->dir, valor);
                }
            }
        }
    }

    if (resultado != NULL)
    {
        resultado = balancear_curso(resultado);
    }

    return resultado;
}

int remove_ArvLLRB_curso(arv_curso **raiz, int codigo)
{
    int aux = 0;
    if (buscar_disciplina_curso(*raiz, codigo))
    {
        *raiz = remove_NO_curso(*raiz, codigo);
        if (*raiz != NULL)
        {
            (*raiz)->cor = BLACK;
        }
        aux = 1;
    }
    return aux;
}