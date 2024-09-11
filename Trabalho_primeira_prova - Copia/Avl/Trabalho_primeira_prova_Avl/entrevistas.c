#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "entrevistas.h"

Arvore_entrevistas *criar_arvore_entrevistas()
{
    Arvore_entrevistas *a = (Arvore_entrevistas *)malloc(sizeof(Arvore_entrevistas));
    a->esq = NULL;
    a->dir = NULL;
    a->altura = 0;
    return a;
}

short maior_no(short a, short b)
{
    return (a > b) ? a : b;
}

short altura_do_no(Arvore_entrevistas *no)
{
    short altura;

    if (no == NULL)
    {
        altura = -1;
    }
    else
    {
        altura = no->altura;
    }

    return altura;
}

short fator_balanceamento(Arvore_entrevistas *no)
{
    short fb = 0;

    if (no != NULL)
    {
        fb = altura_do_no(no->esq) - altura_do_no(no->dir);
    }

    return fb;
}

Arvore_entrevistas *rotar_esquerda(Arvore_entrevistas *no)
{
    Arvore_entrevistas *aux, *aux1;

    aux = no->dir;
    aux1 = aux->esq;

    aux->esq = no;
    no->dir = aux1;

    no->altura = maior_no(altura_do_no(no->esq), altura_do_no(no->dir)) + 1;
    aux->altura = maior_no(altura_do_no(aux->esq), altura_do_no(aux->dir)) + 1;

    return aux;
}

Arvore_entrevistas *rotar_direita(Arvore_entrevistas *no)
{
    Arvore_entrevistas *aux, *aux1;

    aux = no->esq;
    aux1 = aux->dir;

    aux->dir = no;
    no->esq = aux1;

    no->altura = maior_no(altura_do_no(no->esq), altura_do_no(no->dir)) + 1;
    aux->altura = maior_no(altura_do_no(aux->esq), altura_do_no(aux->dir)) + 1;

    return aux;
}

Arvore_entrevistas *rotar_direita_esquerda(Arvore_entrevistas *no)
{
    no->dir = rotar_direita(no->dir);
    return rotar_esquerda(no);
}

Arvore_entrevistas *rotar_esquerda_direita(Arvore_entrevistas *no)
{
    no->esq = rotar_esquerda(no->esq);
    return rotar_direita(no);
}

Arvore_entrevistas *balencar_arvore(Arvore_entrevistas *raiz)
{
    short fb = fator_balanceamento(raiz);

    if (fb < -1 && fator_balanceamento(raiz->dir) <= 0)
    {
        raiz = rotar_esquerda(raiz);
    }
    else if (fb > 1 && fator_balanceamento(raiz->esq) >= 0)
    {
        raiz = rotar_direita(raiz);
    }
    else if (fb > 1 && fator_balanceamento(raiz->esq) < 0)
    {
        raiz = rotar_esquerda_direita(raiz);
    }
    else if (fb < -1 && fator_balanceamento(raiz->dir) > 0)
    {
        raiz = rotar_direita_esquerda(raiz);
    }
    return raiz;
}
void Ler_dados_de_insercao_entrevistas(Arvore_entrevistas *no)
{
    printf("Digite o titulo da entrevista: ");
    scanf(" %[^\n]", no->titulos);

    printf("Digite a data da entrevista: ");
    scanf(" %[^\n]", no->data);

    printf("Digite a duracao da entrevista: ");
    scanf("%d", &no->duracao);

    printf("Digite o nome do convidado: ");
    scanf(" %[^\n]", no->nome_convidado);

    printf("Digite a especialidade do convidado: ");
    scanf(" %[^\n]", no->especialidade_convidado);
}

Arvore_entrevistas *inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no)
{
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (strcmp(no->titulos, raiz->titulos) < 0)
        {
            if (raiz->esq == NULL)
            {
                raiz->esq = no;
            }
            else
            {
                raiz->esq = inserir_entrevistas(raiz->esq, no);
            }
        }
        else
        {
            if (raiz->dir == NULL)
            {
                raiz->dir = no;
            }
            else
            {
                raiz->dir = inserir_entrevistas(raiz->dir, no);
            }
        }
        // Atualizar a altura da raiz apenas se não for NULL
        raiz->altura = maior_no(altura_do_no(raiz->esq), altura_do_no(raiz->dir)) + 1;
        raiz = balencar_arvore(raiz);
    }
    return raiz;
}

void imprimir_dados(Arvore_entrevistas *raiz, int nivel)
{
    int i;
    if (raiz != NULL)
    {
        imprimir_dados(raiz->dir, nivel + 1);
        printf("\n\n");
        for (i = 0; i < nivel; i++)
        {
            printf("\t");
        }
        printf("%s\n", raiz->titulos);
        imprimir_dados(raiz->esq, nivel + 1);
    }
}

void imprimir_dados_entrevista(Arvore_entrevistas *raiz)
{
    if (raiz != NULL)
    {
        printf("Titulo: %s\n", raiz->titulos);
        printf("Data: %s\n", raiz->data);
        printf("Duracao: %d\n", raiz->duracao);
        printf("Nome do convidado: %s\n", raiz->nome_convidado);
        printf("Especialidade do convidado: %s\n", raiz->especialidade_convidado);
        imprimir_dados_entrevista(raiz->esq);
        imprimir_dados_entrevista(raiz->dir);
    }
}

void imprimir_titulos_entrevistas(Arvore_entrevistas *raiz)
{
    if (raiz != NULL)
    {
        printf("%s\n", raiz->titulos);
        imprimir_titulos_entrevistas(raiz->esq);
        imprimir_titulos_entrevistas(raiz->dir);
    }
}

Arvore_entrevistas *buscar_entrevistas(Arvore_entrevistas *raiz, char *titulo)
{
    Arvore_entrevistas *aux = NULL;
    if (raiz != NULL)
    {
        {
            if (strcmp(titulo, raiz->titulos) == 0)
            {
                aux = raiz;
            }
            else
            {
                if (strcmp(titulo, raiz->titulos) < 0)
                {
                    aux = buscar_entrevistas(raiz->esq, titulo);
                }
                else
                {
                    aux = buscar_entrevistas(raiz->dir, titulo);
                }
            }
        }
    }
    return aux;
}

Arvore_entrevistas *remover_entrevista(Arvore_entrevistas *raiz, char *nome)
{
    Arvore_entrevistas *resultado = NULL;
    if (raiz != NULL && raiz->titulos == NULL)
    {
        if (strcmp(nome, raiz->titulos) < 0)
        {
            raiz->esq = remover_entrevista(raiz->esq, nome);
        }
        else if (strcmp(nome, raiz->titulos) > 0)
        {
            raiz->dir = remover_entrevista(raiz->dir, nome);
        }
        else
        {
            if (raiz->esq == NULL)
            {
                Arvore_entrevistas *aux = raiz->dir;
                free(raiz);
                resultado = aux;
            }
            else if (raiz->dir == NULL)
            {
                Arvore_entrevistas *aux = raiz->esq;
                free(raiz);
                resultado = aux;
            }
            else
            {
                Arvore_entrevistas *aux = raiz->dir;
                while (aux->esq != NULL)
                {
                    aux = aux->esq;
                }
                strcpy(raiz->titulos, aux->titulos);
                raiz->dir = remover_entrevista(raiz->dir, aux->titulos);
            }
        }
    }
    raiz->altura = maior_no(altura_do_no(raiz->esq), altura_do_no(raiz->dir)) + 1;
    raiz = balencar_arvore(raiz);
    return resultado;
}

void mostrar_dados_entrevista(Arvore_entrevistas *entrevista)
{
    printf("Título: %s\n", entrevista->titulos);
    printf("Entrevistado: %s\n", entrevista->nome_convidado);
    printf("Data: %s\n", entrevista->data);
    printf("Especialidade do convidado: %s\n", entrevista->especialidade_convidado);
}
void imprimir_entrevistados(Arvore_entrevistas *entrevistas)
{
    if (entrevistas != NULL)
    {
        imprimir_entrevistados(entrevistas->esq);

        printf("- %s\n", entrevistas->nome_convidado);

        imprimir_entrevistados(entrevistas->dir);
    }
}
