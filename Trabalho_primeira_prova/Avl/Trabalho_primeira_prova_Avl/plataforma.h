#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include "podcast.h"

typedef struct plataforma Plataforma;

Plataforma *criar_plataforma();
void ler_dados_plataforma(Plataforma *no);
Plataforma *inserir_plataforma(Plataforma *raiz, Plataforma *no);
Plataforma *remover_plataforma(Plataforma *raiz, char *nome);
Plataforma *buscar_plataforma(Plataforma *raiz, char *nome);
void imprimir_plataforma(Plataforma *raiz);

#endif