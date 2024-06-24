#include <stdio.h>
#include <stdlib.h>
#include "Disciplina.h"

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

    printf("Informe o nome da disciplina: ");
    scanf("%s", no->dados->nome);

    printf("Informe o bloco da disciplina: ");
    scanf("%d", &no->dados->bloco);

    printf("Informe a carga-horaria da disciplina: ");
    scanf("%d", &no->dados->carga_horaria);
}

arv_disciplina *inserir_disciplina(arv_disciplina *raiz, arv_disciplina *no)
{
    if (raiz == NULL)
    {
        return no;
    }
    if (no->dados->codigo < raiz->dados->codigo)
    {
        raiz->esq = inserir_disciplina(raiz->esq, no);
    }
    else
    {
        raiz->dir = inserir_disciplina(raiz->dir, no);
    }
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
        printf("Carga-Horaria: %d\n\n", raiz->dados->carga_horaria);
        imprimir_disciplinas(raiz->dir);
    }
}