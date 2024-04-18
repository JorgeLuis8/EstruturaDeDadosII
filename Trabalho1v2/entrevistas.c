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

Arvore_entrevistas *buscar_entrevistas(Arvore_entrevistas * raiz,char *titulo){
    Arvore_entrevistas *aux = NULL;

    if(raiz != NULL){
        if(strcmp(titulo, raiz->titulos) == 0){
            aux = raiz;
        }else if(strcmp(titulo, raiz->titulos) < 0){
            aux = buscar_entrevistas(raiz->esq, titulo);
        }else{
            aux = buscar_entrevistas(raiz->dir, titulo);
        }
    }
    return aux;
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

