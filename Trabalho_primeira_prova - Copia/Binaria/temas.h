#ifndef TEMAS_H
#define TEMAS_H
#include "entrevistas.h"
typedef struct arvore_temas
{
    char tema[50];
    Arvore_entrevistas *entrevistas;
    struct arvore_temas *esq;
    struct arvore_temas *dir;
} Arvore_temas;


Arvore_temas *criar_arvore_temas();
Arvore_temas *inserir_temas(Arvore_temas *raiz, Arvore_temas *no);

// Arvore_temas *inserir_temas(Arvore_temas *raiz, Arvore_temas *no);
Arvore_temas *Busca_arv(Arvore_temas *raiz, char *tema);
void imprimir_entrevistas_tema(Arvore_temas *raiz, char *tema);

#endif