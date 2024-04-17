#include "entrevistas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct arvore_entrevistas
{
    char titulos[50];
    char data[50];
    int duracao;
    char nome_convidado[50];
    char especialidade_convidado[50];
    struct arvore_entrevistas *esq;
    struct arvore_entrevistas *dir;
};

struct raiz_entrevistas
{
    struct arvore_entrevistas *raiz;
};

Arvore_entrevistas *criar_arvore_entrevistas()
{
    Arvore_entrevistas *a = (Arvore_entrevistas *)malloc(sizeof(Arvore_entrevistas));
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

Raiz_entrevistas *criar_raiz_entrevistas()
{
    Raiz_entrevistas *r = (Raiz_entrevistas *)malloc(sizeof(Raiz_entrevistas));
    r->raiz = NULL;
    return r;
}
// inserindo dados
void Ler_dados_de_insercao_entrevistas(Arvore_entrevistas *no)
{
    printf("Digite o titulo da entrevista: ");
    scanf("%s", no->titulos);
    printf("Digite a data da entrevista: ");
    scanf("%s", no->data);
    printf("Digite a duração da entrevista: ");
    scanf("%d", &no->duracao);
    printf("Digite o nome do convidado: ");
    scanf("%s", no->nome_convidado);
    printf("Digite a especialidade do convidado: ");
    scanf("%s", no->especialidade_convidado);
}

// Função para inserir entrevistas na árvore, usando a função de ler os dados de inserção
Arvore_entrevistas *inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no)
{

    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (strcmp(no->titulos, raiz->titulos) < 0)
            raiz->esq = inserir_entrevistas(raiz->esq, no);
        else if (strcmp(no->titulos, raiz->titulos) > 0)
            raiz->dir = inserir_entrevistas(raiz->dir, no);
    }
    return raiz;
}

void inserir_arvore(Raiz_entrevistas *arvore, Arvore_entrevistas *no)
{
    if (arvore->raiz == NULL)
    {
        arvore->raiz = no;
    }
    else
    {
        arvore->raiz = inserir_entrevistas(arvore->raiz, no);
    }
}

// Função para buscar entrevistas na árvore
Arvore_entrevistas *buscar_entrevistas(Arvore_entrevistas *raiz, char *titulo)
{
    Arvore_entrevistas *resultado = NULL;
    if (raiz != NULL)
    {
        if (strcmp(titulo, raiz->titulos) == 0)
        {
            resultado = raiz;
        }
        else if (strcmp(titulo, raiz->titulos) < 0)
        {
            resultado = buscar_entrevistas(raiz->esq, titulo);
        }
        else
        {
            resultado = buscar_entrevistas(raiz->dir, titulo);
        }
    }
    return resultado;
}

Raiz_entrevistas *arvore_busca(Raiz_entrevistas *raiz, char *titulo)
{
    Raiz_entrevistas *resultado = buscar_entrevistas(raiz->raiz, titulo);
    return resultado;
 
}
void imprimir_arvore_entrevistas(Arvore_entrevistas *raiz)
{
    if (raiz != NULL)
    {
        // Primeiro, imprima os valores na subárvore esquerda
        imprimir_arvore_entrevistas(raiz->esq);

        // Em seguida, imprima o valor na raiz atual
        printf("%s\n", raiz->titulos);

        // Por último, imprima os valores na subárvore direita
        imprimir_arvore_entrevistas(raiz->dir);
    }
}

void imprimir_melhor(Arvore_entrevistas *raiz, int nivel)
{
    if (raiz != NULL)
    {
        // Primeiro, imprima os valores na subárvore direita
        imprimir_melhor(raiz->dir, nivel + 1);

        // Em seguida, imprima o valor na raiz atual
        for (int i = 0; i < nivel; i++)
        {
            printf("\t");
        }
        printf("%s\n", raiz->titulos);

        // Por último, imprima os valores na subárvore esquerda
        imprimir_melhor(raiz->esq, nivel + 1);
    }
}

void imprimir_arvore(Raiz_entrevistas *raiz)
{
    if (raiz != NULL)
    {
        imprimir_melhor(raiz->raiz,0);
    }
}