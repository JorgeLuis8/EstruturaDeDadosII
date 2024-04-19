#include "temas.h"
#include "entrevistas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct arvore_temas
{
    char tema[50];
    Arvore_entrevistas *entrevistas;
    struct arvore_temas *esq;
    struct arvore_temas *dir;
};

Arvore_temas *criar_arvore_temas()
{
    Arvore_temas *nova_arvore = (Arvore_temas *)malloc(sizeof(Arvore_temas));
    nova_arvore->esq = NULL;
    nova_arvore->dir = NULL;
    nova_arvore->entrevistas = NULL;
    return nova_arvore;
}

void lerDados(Arvore_temas *no)
{
    printf("Digite o tema: ");
    scanf("%s", no->tema);
}

Arvore_temas *inserir_temas(Arvore_temas *raiz, Arvore_temas *no)
{
    if (raiz == NULL)
    {
        raiz = no;
        // Inicializa a árvore de entrevistas associada ao nó inserido
        raiz->entrevistas = criar_arvore_entrevistas();
    }
    else
    {
        if (strcmp(no->tema, raiz->tema) < 0)
        {
            raiz->esq = inserir_temas(raiz->esq, no);
        }
        else if (strcmp(no->tema, raiz->tema) > 0)
        {
            raiz->dir = inserir_temas(raiz->dir, no);
        }
    }
    return raiz;
}



Arvore_temas *Busca_arv(Arvore_temas *raiz, char *tema)
{
    Arvore_temas *aux = NULL;
    if (raiz != NULL)
    {
        if (strcmp(tema, raiz->tema) == 0)
        {
            aux = raiz;
        }
        else if (strcmp(tema, raiz->tema) < 0)
        {
            aux = Busca_arv(raiz->esq, tema);
        }
        else
        {
            aux = Busca_arv(raiz->dir, tema);
        }
    }
    return aux;
}



// Função para imprimir as entrevistas de uma árvore de entrevistas
void imprimir_entrevistas_tema(Arvore_temas *raiz, char *tema) {
    // Busca o tema na árvore de temas
    Arvore_temas *tema_encontrado = Busca_arv(raiz, tema);

    if (tema_encontrado != NULL) {
        printf("Tema: %s\n", tema_encontrado->tema);
        // Verifica se há entrevistas associadas ao tema
        if (tema_encontrado->entrevistas != NULL) {
            // Imprime todas as entrevistas na árvore de entrevistas associada ao tema
            imprimir_dados_entrevista(tema_encontrado->entrevistas);
        } else {
            printf("Nao ha entrevistas cadastradas para este tema.\n");
        }
    } else {
        printf("Tema nao encontrado.\n");
    }
}


