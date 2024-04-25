#include "temas.h"
#include "entrevistas.h"
#include "podcast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



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
    scanf(" %[^\n]", no->tema);
}


Arvore_temas *inserir_temas(Arvore_temas *raiz, Arvore_temas *no)
{
    if (raiz == NULL)
    {
        raiz = no;
        raiz->entrevistas = NULL;
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
    raiz->altura = maior_no_temas(altura_do_no_temas(raiz->esq), altura_do_no_temas(raiz->dir)) + 1;

    raiz = balencar_arvore_temas(raiz);

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


void imprimir_temas(Arvore_temas *raiz)
{
    if (raiz != NULL)
    {
        printf("Tema: %s\n", raiz->tema);
        imprimir_temas(raiz->esq);
        imprimir_temas(raiz->dir);
    }
}
// FunÃ§Ã£o para imprimir as entrevistas de uma Ã¡rvore de entrevistas
void imprimir_entrevistas_tema(Arvore_temas *raiz, char *tema) {
    // Busca o tema na Ã¡rvore de temas
    Arvore_temas *tema_encontrado = Busca_arv(raiz, tema);

    if (tema_encontrado != NULL) {
        // Verifica se hÃ¡ entrevistas associadas ao tema
        if (tema_encontrado->entrevistas != NULL) {
            imprimir_dados_entrevista(tema_encontrado->entrevistas);
        } else {
            printf("Nao ha entrevistas cadastradas para este tema.\n");
        }
    } else {
        printf("Tema nao encontrado.\n");
    }
}

Arvore_temas *remover_tema (Arvore_temas *raiz, char *tema) {
    Arvore_temas *resultado = NULL;
    if (raiz != NULL && raiz->entrevistas == NULL) {
        if (strcmp(tema, raiz->tema) < 0) {
            raiz->esq = remover_tema(raiz->esq, tema);
        } else if (strcmp(tema, raiz->tema) > 0) {
            raiz->dir = remover_tema(raiz->dir, tema);
        } else {
            if (raiz->esq == NULL) {
                Arvore_temas *aux = raiz->dir;
                free(raiz);
                resultado = aux;
            } else if (raiz->dir == NULL) {
                Arvore_temas *aux = raiz->esq;
                free(raiz);
                resultado = aux;
            } else {
                Arvore_temas *aux = raiz->dir;
                while (aux->esq != NULL) {
                    aux = aux->esq;
                }
                strcpy(raiz->tema, aux->tema);
                raiz->dir = remover_tema(raiz->dir, aux->tema);
            }
        }
    }
    raiz->altura = maior_no_temas(altura_do_no_temas(raiz->esq), altura_do_no_temas(raiz->dir)) + 1;
    raiz = balencar_arvore_temas(raiz);
    return resultado;
}

short maior_no_temas(short a, short b)
{
    return (a > b) ? a : b;
}

short altura_do_no_temas(Arvore_temas *no)
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

short fator_balanceamento_temas(Arvore_temas *no)
{
    short fb = 0;

    if (no != NULL)
    {
        fb = altura_do_no_temas(no->esq) - altura_do_no_temas(no->dir);
    }

    return fb;
}

Arvore_temas *rotar_esquerda_temas(Arvore_temas *no)
{
    Arvore_temas *aux, *aux1;

    aux = no->dir;
    aux1 = aux->esq;

    aux->esq = no;
    no->dir = aux1;

    no->altura = maior_no(altura_do_no_temas(no->esq), altura_do_no_temas(no->dir)) + 1;
    aux->altura = maior_no_temas(altura_do_no_temas(aux->esq), altura_do_no_temas(aux->dir)) + 1;

    return aux;
}

Arvore_temas *rotar_direita_temas(Arvore_temas *no)
{
    Arvore_temas *aux, *aux1;

    aux = no->esq;
    aux1 = aux->dir;

    aux->dir = no;
    no->esq = aux1;

    no->altura = maior_no_temas(altura_do_no_temas(no->esq), altura_do_no_temas(no->dir)) + 1;
    aux->altura = maior_no_temas(altura_do_no_temas(aux->esq), altura_do_no_temas(aux->dir)) + 1;

    return aux;
}

Arvore_temas *rotar_direita_esquerda_temas(Arvore_temas *no)
{
    no->dir = rotar_direita_temas(no->dir);
    return rotar_esquerda_temas(no);
}

Arvore_temas *rotar_esquerda_direita_temas(Arvore_temas *no)
{
    no->esq = rotar_esquerda_temas(no->esq);
    return rotar_direita_temas(no);
}

Arvore_temas *balencar_arvore_temas(Arvore_temas *raiz)
{
    short fb = fator_balanceamento_temas(raiz);

    if (fb < -1 && fator_balanceamento_temas(raiz->dir) <= 0)
    {
        raiz = rotar_esquerda_temas(raiz);
    }
    else if (fb > 1 && fator_balanceamento_temas(raiz->esq) >= 0)
    {
        raiz = rotar_direita_temas(raiz);
    }
    else if(fb > 1 && fator_balanceamento_temas(raiz->esq) < 0){
        raiz = rotar_esquerda_direita_temas(raiz);
    }
    else if(fb < -1 && fator_balanceamento_temas(raiz->dir) > 0){
        raiz = rotar_direita_esquerda_temas(raiz);
    }
    return raiz;
}