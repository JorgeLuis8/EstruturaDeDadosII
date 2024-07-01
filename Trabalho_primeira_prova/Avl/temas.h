#ifndef TEMAS_H
#define TEMAS_H
#include "entrevistas.h"
typedef struct arvore_temas
{
    char tema[50];
    Arvore_entrevistas *entrevistas;
    struct arvore_temas *esq;
    struct arvore_temas *dir;
    short altura;
} Arvore_temas;


Arvore_temas *criar_arvore_temas();
void lerDados(Arvore_temas *no);


Arvore_temas *inserir_temas(Arvore_temas *raiz, Arvore_temas *no);
Arvore_temas *Busca_arv(Arvore_temas *raiz, char *tema);
void imprimir_entrevistas_tema(Arvore_temas *raiz, char *tema);

Arvore_temas *balencar_arvore_temas(Arvore_temas *raiz);
Arvore_temas *rotar_esquerda_direita_temas(Arvore_temas *no);
Arvore_temas *rotar_direita_esquerda_temas(Arvore_temas *no);
Arvore_temas *rotar_direita_temas(Arvore_temas *no);
Arvore_temas *rotar_esquerda_temas(Arvore_temas *no);
short fator_balanceamento_temas(Arvore_temas *no);
short altura_do_no_temas(Arvore_temas*no);
short maior_no_temas(short a, short b);




#endif