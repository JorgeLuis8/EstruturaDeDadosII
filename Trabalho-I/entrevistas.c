#include "entrevistas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// struct da arvore de entrevistas
struct noentrevista
{
    char titulos[50];
    char data[50];
    int duracao;
    char nome_convidado[50];
    char especialidade_convidado[50];
    struct noentrevista *esq;
    struct noentrevista *dir;
};
// struct da raiz da arvore de entrevistas
struct raizentrevista
{
    struct noentrevista *raiz;
};
/*criando a arvore de entrevistas, onde a memoria é alocada e depois é atribuido NULL para os ponteiros de esquerda e direita e depois é retornada a arvore alocada*/
NoEntrevista *criar_arvore_entrevistas()
{
    NoEntrevista *a = (NoEntrevista *)malloc(sizeof(NoEntrevista));
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

/*Função simples parar ler os dados da entrevista*/
void Ler_dados_de_insercao_entrevistas(NoEntrevista *no)
{
    printf("Digite o titulo da entrevista: ");
    scanf("%s", no->titulos);
    printf("Digite a data da entrevista: ");
    scanf("%s", no->data);
    printf("Digite a duracao da entrevista: ");
    scanf("%d", &no->duracao);
    printf("Digite o nome do convidado: ");
    scanf("%s", no->nome_convidado);
    printf("Digite a especialidade do convidado: ");
    scanf("%s", no->especialidade_convidado);
}

/* Funcao de insercao das entrevista, onde a raiz e o no sao passados de parametro e logo depois
é verificado se a raiz é nula, se sim insere o no diretamente na raiz,se nao verfica a esquerda em ordem alfabetica, e depois a direita. */
NoEntrevista *inserir_entrevistas(NoEntrevista *raiz, NoEntrevista *no)
{
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if ((strcmp(no->titulos, raiz->titulos) < 0))
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

/* Funcao de busca, onde e passada a arvore e o titulo logo apos é feita a busca na raiz,se nao vai para a esquerda e se nao estiver na esquerda ele vai para a direira e se nao encontrar retorna NULL  */
NoEntrevista *buscar_entrevistas(NoEntrevista *raiz, char *titulo)
{
    NoEntrevista *resultado = NULL;

    if (raiz != NULL)
    {
        if (strcmp(titulo, raiz->titulos) == 0)
        {
            resultado = raiz;
        }
        else
        {
            if (strcmp(titulo, raiz->titulos) < 0)
            {
                resultado = buscar_entrevistas(raiz->esq, titulo);
            }
            else if (strcmp(titulo, raiz->titulos) > 0)
            {
                resultado = buscar_entrevistas(raiz->dir, titulo);
            }
        }
    }

    return resultado;
}
