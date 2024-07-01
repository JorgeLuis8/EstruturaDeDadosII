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

    // printf("Informe o nome da disciplina: ");
    // scanf("%s", no->dados->nome);

    // printf("Informe o bloco da disciplina: ");
    // scanf("%d", &no->dados->bloco);

    // printf("Informe a carga-horaria da disciplina: ");
    // scanf("%d", &no->dados->carga_horaria);
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

#include <stdio.h>
#include "curso.h"

// Função para imprimir os dados do curso
void imprimir_disciplinas_curso(arv_curso *raiz)
{
    if (raiz != NULL)
    {
        imprimir_disciplinas_curso(raiz->esq); // Percorre a subárvore esquerda
        printf("Código: %d\n", raiz->dados->codigo);
        printf("Nome: %s\n", raiz->dados->nome);
        printf("Quantidade de blocos: %d\n", raiz->dados->qtd_blocos);
        printf("Número de semanas: %d\n", raiz->dados->num_semanas);
        printf("Cor: %s\n", raiz->cor == RED ? "Vermelho" : "Preto");
        imprimir_disciplinas_curso(raiz->dir); // Percorre a subárvore direita
    }
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