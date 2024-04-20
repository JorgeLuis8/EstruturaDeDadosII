#ifndef PODCAST_H
#define PODCAST_H


typedef struct arvore_podCast Arvore_podCast;

Arvore_podCast* criar_arvore_podCast();
void ler_dados_podcast(Arvore_podCast *no);
Arvore_podCast *inserir_podcast(Arvore_podCast *raiz, Arvore_podCast *no);
Arvore_podCast *Busca_arv_podcast(Arvore_podCast *raiz, char *nome);
Arvore_podCast *remover_podcast(Arvore_podCast *raiz, char *nome);
void imprimir_podcast_tema(Arvore_podCast *raiz, char *nome);
#endif 
