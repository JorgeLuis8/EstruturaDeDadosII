#include "podcast.h"
#include "temas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct arvore_podCast
{
    char nome[50];
    char entrevistador[50];
    short altura;
    struct arvore_temas *raiz_temas;
    struct arvore_podCast *esq;
    struct arvore_podCast *dir;
};

Arvore_podCast *criar_arvore_podCast()
{
    Arvore_podCast *a = (Arvore_podCast *)malloc(sizeof(Arvore_podCast));
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

void ler_dados_podcast(Arvore_podCast *no)
{
    printf("Digite o nome do podcast: ");
    scanf(" %[^\n]", no->nome);

    printf("Digite o nome do entrevistador: ");
    scanf(" %[^\n]", no->entrevistador);
}

Arvore_podCast *inserir_podcast(Arvore_podCast *raiz, Arvore_podCast *no)
{
    if (raiz == NULL)
    {
        raiz = no;
        raiz->raiz_temas = NULL;
    }
    else
    {
        if (strcmp(no->nome, raiz->nome) < 0)
        {
            raiz->esq = inserir_podcast(raiz->esq, no);
        }
        else
        {
            raiz->dir = inserir_podcast(raiz->dir, no);
        }
    }
    raiz->altura = maior_no_podcast(altura_do_no_podcast(raiz->esq), altura_do_no_podcast(raiz->dir)) + 1;
    raiz = balencar_arvore_podcast(raiz);
    return raiz;
}

Arvore_podCast *Busca_arv_podcast(Arvore_podCast *raiz, char *nome)
{
    Arvore_podCast *aux = NULL;
    if (raiz != NULL)
    {
        if (strcmp(nome, raiz->nome) == 0)
        {
            aux = raiz;
        }
        else if (strcmp(nome, raiz->nome) < 0)
        {
            aux = Busca_arv_podcast(raiz->esq, nome);
        }
        else
        {
            aux = Busca_arv_podcast(raiz->dir, nome);
        }
    }
    return aux;
}

Arvore_podCast *remover_podcast(Arvore_podCast *raiz, char *nome)
{
    Arvore_podCast *resultado = NULL;
    if (raiz != NULL && raiz->raiz_temas == NULL)
    {
        if (strcmp(nome, raiz->nome) < 0)
        {
            raiz->esq = remover_podcast(raiz->esq, nome);
        }
        else if (strcmp(nome, raiz->nome) > 0)
        {
            raiz->dir = remover_podcast(raiz->dir, nome);
        }
        else
        {
            if (raiz->esq == NULL)
            {
                Arvore_podCast *aux = raiz->dir;
                free(raiz);
                resultado = aux;
            }
            else if (raiz->dir == NULL)
            {
                Arvore_podCast *aux = raiz->esq;
                free(raiz);
                resultado = aux;
            }
            else
            {
                Arvore_podCast *aux = raiz->dir;
                while (aux->esq != NULL)
                {
                    aux = aux->esq;
                }
                strcpy(raiz->nome, aux->nome);
                raiz->dir = remover_podcast(raiz->dir, aux->nome);
            }
        }
    }
    raiz->altura = maior_no_podcast(altura_do_no_podcast(raiz->esq), altura_do_no_podcast(raiz->dir)) + 1;
    raiz = balencar_arvore_podcast(raiz);
    return resultado;
}

void imprimir_nomes_podcasts_em_ordem(Arvore_podCast *raiz)
{
    if (raiz != NULL)
    {
        imprimir_nomes_podcasts_em_ordem(raiz->esq);
        printf("%s\n", raiz->nome);
        imprimir_nomes_podcasts_em_ordem(raiz->dir);
    }
}

short maior_no_podcast(short a, short b)
{
    return (a > b) ? a : b;
}

short altura_do_no_podcast(Arvore_podCast *no)
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

short fator_balanceamento_podcast(Arvore_podCast *no)
{
    short fb = 0;

    if (no != NULL)
    {
        fb = altura_do_no_podcast(no->esq) - altura_do_no_podcast(no->dir);
    }

    return fb;
}

Arvore_podCast *rotar_esquerda_podcast(Arvore_podCast *no)
{
    Arvore_podCast *aux, *aux1;

    aux = no->dir;
    aux1 = aux->esq;

    aux->esq = no;
    no->dir = aux1;

    no->altura = maior_no_podcast(altura_do_no_podcast(no->esq), altura_do_no_podcast(no->dir)) + 1;
    aux->altura = maior_no_podcast(altura_do_no_podcast(aux->esq), altura_do_no_podcast(aux->dir)) + 1;

    return aux;
}

Arvore_podCast *rotar_direita_podcast(Arvore_podCast *no)
{
    Arvore_podCast *aux, *aux1;

    aux = no->esq;
    aux1 = aux->dir;

    aux->dir = no;
    no->esq = aux1;

    no->altura = maior_no_podcast(altura_do_no_podcast(no->esq), altura_do_no_podcast(no->dir)) + 1;
    aux->altura = maior_no_podcast(altura_do_no_podcast(aux->esq), altura_do_no_podcast(aux->dir)) + 1;

    return aux;
}

Arvore_podCast *rotar_direita_esquerda_podcast(Arvore_podCast *no)
{
    no->dir = rotar_direita_podcast(no->dir);
    return rotar_esquerda_podcast(no);
}

Arvore_podCast *rotar_esquerda_direita_podcast(Arvore_podCast *no)
{
    no->esq = rotar_esquerda_podcast(no->esq);
    return rotar_direita_podcast(no);
}

Arvore_podCast *balencar_arvore_podcast(Arvore_podCast *raiz)
{
    short fb = fator_balanceamento_podcast(raiz);

    if (fb < -1 && fator_balanceamento_podcast(raiz->dir) <= 0)
    {
        raiz = rotar_esquerda_podcast(raiz);
    }
    else if (fb > 1 && fator_balanceamento_podcast(raiz->esq) >= 0)
    {
        raiz = rotar_direita_podcast(raiz);
    }
    else if (fb > 1 && fator_balanceamento_podcast(raiz->esq) < 0)
    {
        raiz = rotar_esquerda_direita_podcast(raiz);
    }
    else if (fb < -1 && fator_balanceamento_podcast(raiz->dir) > 0)
    {
        raiz = rotar_direita_esquerda_podcast(raiz);
    }
    return raiz;
}