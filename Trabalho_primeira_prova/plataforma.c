#include "plataforma.h"
#include "podcast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct plataforma
{
    char nome[50];
    struct arvore_podCast *raiz_podcast;
    struct plataforma *prox;
};

Plataforma *criar_plataforma()
{
    Plataforma *p = (Plataforma *)malloc(sizeof(Plataforma));
    p->raiz_podcast = NULL;
    p->prox = NULL;
    return p;
}

Plataforma *inserir_plataforma(Plataforma *plataforma, Plataforma *no)
{
    if (plataforma == NULL)
    {
        return no;
    }

    Plataforma *aux = plataforma;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    aux->prox = no;
    no->prox = NULL;

    return plataforma;
}

Plataforma *remover_plataforma(Plataforma *plataforma, char *nome)
{
    Plataforma *aux = plataforma;
    Plataforma *ant = NULL;

    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        return plataforma;
    }

    if (ant == NULL)
    {
        plataforma = aux->prox;
    }
    else
    {
        ant->prox = aux->prox;
    }

    free(aux);
    return plataforma;
}

Plataforma *buscar_plataforma(Plataforma *plataforma, char *nome)
{
    Plataforma *aux = plataforma;

    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        aux = aux->prox;
    }

    return aux;
}

void imprimir_plataforma(Plataforma *plataforma)
{
    Plataforma *aux = plataforma;

    while (aux != NULL)
    {
        printf("Nome: %s\n", aux->nome);
        aux = aux->prox;
    }
}

void imprimir_plataforma_podcast(Plataforma *plataforma)
{
    Plataforma *aux = plataforma;

    while (aux != NULL)
    {
        printf("Nome: %s\n", aux->nome);
        if (aux->raiz_podcast != NULL)
        {
            // imprimir_podcast(aux->raiz_podcast);
        }
        aux = aux->prox;
    }
}

void ler_dados_plataforma(Plataforma *plataforma)
{
    printf("Digite o nome da plataforma: ");
    scanf(" %[^\n]", plataforma->nome);
}