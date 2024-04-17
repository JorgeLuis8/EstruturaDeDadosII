#include "temas.h"
#include "entrevistas.h"
#include <stdlib.h>
#include <stdio.h>

struct arvore_temas
{
    char tema[50];
    struct raiz_entrevistas *raiz;
    struct arvore_temas *esq;
    struct arvore_temas *dir;
};

struct raiz_temas
{
    struct arvore_temas *raiz;
};

Arvore_temas* criar_arvore_temas() {
    Arvore_temas *a = (Arvore_temas*) malloc(sizeof(Arvore_temas));
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

Arvore_temas* inserir_temas(Raiz_temas *raiz, Arvore_temas *no, Arvore_temas *novo) {
    // Se a raiz for nula, o nó inserido será a raiz
    if (raiz->raiz == NULL) {
        raiz->raiz = no;
        no->raiz = novo;
    } 
    else {
        // Se o título do nó inserido for menor que o título da raiz, o nó será inserido à esquerda
        if (strcmp(no->tema, raiz->raiz->tema) < 0) {
            if (raiz->raiz->esq == NULL) {
                raiz->raiz->esq = no;
            } else {
                raiz->raiz->esq = inserir_temas(raiz, raiz->raiz->esq, novo);
            }
        // Se o título do nó inserido for maior que o título da raiz, o nó será inserido à direita
        } else {
            if (raiz->raiz->dir == NULL) {
                raiz->raiz->dir = no;
            } else {
                raiz->raiz->dir = inserir_temas(raiz, raiz->raiz->dir, novo);
            }
        }
    }

    return no; // Retornar o nó inserido
}

Arvore_temas* buscar_temas(Raiz_temas *raiz, char *titulo) {
    Arvore_temas* resultado = NULL;
    if(raiz != NULL){ {
        if (strcmp(titulo, raiz->raiz->tema) == 0) {
            return raiz;
        } else {
            if (strcmp(titulo, raiz->raiz->tema) < 0) {
                resultado = buscar_temas(raiz->raiz->esq, titulo);
            } else {
                resultado = buscar_temas(raiz->raiz->dir, titulo);
                }
            }
        }
    }

    return resultado;
}