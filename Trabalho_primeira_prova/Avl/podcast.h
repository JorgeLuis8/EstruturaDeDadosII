#ifndef PODCAST_H
#define PODCAST_H


typedef struct arvore_podCast Arvore_podCast;

Arvore_podCast* criar_arvore_podCast();
void ler_dados_podcast(Arvore_podCast *no);

Arvore_podCast *inserir_podcast(Arvore_podCast *raiz, Arvore_podCast *no);
Arvore_podCast *Busca_arv_podcast(Arvore_podCast *raiz, char *nome);
Arvore_podCast *remover_podcast(Arvore_podCast *raiz, char *nome);
void imprimir_podcast_tema(Arvore_podCast *raiz, char *nome);
void imprimir_podcast(Arvore_podCast *raiz);

Arvore_podCast *balencar_arvore_podcast(Arvore_podCast *raiz);
Arvore_podCast *rotar_esquerda_direita_podcast(Arvore_podCast *no);
Arvore_podCast *rotar_direita_esquerda_podcast(Arvore_podCast *no);
Arvore_podCast *rotar_direita_podcast(Arvore_podCast *no);
Arvore_podCast *rotar_esquerda_podcast(Arvore_podCast *no);
short fator_balanceamento_podcast(Arvore_podCast *no);
short altura_do_no_podcast(Arvore_podCast *no);
short maior_no_podcast(short a, short b);



#endif 