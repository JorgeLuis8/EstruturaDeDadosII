#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "entrevistas.h"

Arvore_entrevistas *criar_arvore_entrevistas()
{
    Arvore_entrevistas *a = (Arvore_entrevistas *)malloc(sizeof(Arvore_entrevistas));
    a->esq = NULL;
    a->dir = NULL;
    return a;
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
    }

    return raiz;
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

Arvore_entrevistas *remover_entrevista(Arvore_entrevistas *raiz, char *titulo)
{
    if (raiz != NULL)
    {
        if (strcmp(titulo, raiz->titulos) < 0)
        {
            raiz->esq = remover_entrevista(raiz->esq, titulo);
        }
        else if (strcmp(titulo, raiz->titulos) > 0)
        {
            raiz->dir = remover_entrevista(raiz->dir, titulo);
        }
        else
        {
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);
                raiz = NULL;
            }
            else if (raiz->esq == NULL)
            {
                Arvore_entrevistas *aux = raiz;
                raiz = raiz->dir;
                free(aux);
            }
            else if (raiz->dir == NULL)
            {
                Arvore_entrevistas *aux = raiz;
                raiz = raiz->esq;
                free(aux);
            }
            else
            {
                Arvore_entrevistas *aux = raiz->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir;
                }
                strcpy(raiz->titulos, aux->titulos);
                raiz->esq = remover_entrevista(raiz->esq, aux->titulos);
            }
        }
    }
    return raiz;
}

void mostrar_dados_entrevista(Arvore_entrevistas* entrevista) {
    printf("Título: %s\n", entrevista->titulos);
    printf("Entrevistado: %s\n", entrevista->nome_convidado);
    printf("Data: %s\n", entrevista->data);
    printf("Especialidade do convidado: %s\n", entrevista->especialidade_convidado);
}


void imprimir_entrevistados(Arvore_entrevistas *entrevistas) {
    if (entrevistas != NULL) {

        imprimir_entrevistados(entrevistas->esq);
        
     
        printf("- %s\n", entrevistas->nome_convidado);
        
 
        imprimir_entrevistados(entrevistas->dir);
    }
}

