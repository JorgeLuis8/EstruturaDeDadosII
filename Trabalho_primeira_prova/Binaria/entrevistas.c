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

// inserindo dados
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

// Funcao para inserir entrevistas na arvore, usando a funcao de ler os dados de insercao
Arvore_entrevistas *inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no)
{
    // Se a raiz for nula, o no inserido sera a raiz
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        // Se o titulo do no inserido for menor que o titulo da raiz, o no sera inserido a esquerda
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
            // Se o titulo do no inserido for maior que o titulo da raiz, o no sera inserido a direita
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

// Funcao para buscar entrevistas na arvore
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

// Função para imprimir os nomes dos entrevistados de todas as entrevistas de um tema
// Função para imprimir os nomes dos entrevistados de todas as entrevistas de um tema
void imprimir_entrevistados(Arvore_entrevistas *entrevistas) {
    if (entrevistas != NULL) {
        // Imprimir os entrevistados da subárvore da esquerda
        imprimir_entrevistados(entrevistas->esq);
        
        // Imprimir o nome do entrevistado da entrevista atual
        printf("- %s\n", entrevistas->nome_convidado);
        
        // Imprimir os entrevistados da subárvore da direita
        imprimir_entrevistados(entrevistas->dir);
    }
}

