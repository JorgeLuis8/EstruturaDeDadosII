#include "plataforma.h"
#include <stdlib.h>


struct plataforma
{
    char nome[50];
    struct arvore_podCast *raiz_podcast;
    struct plataforma *prox;

};

Plataforma* criar_plataforma () {
    Plataforma *p = (Plataforma*) malloc(sizeof(Plataforma));
    p->raiz_podcast = NULL;
    p->prox = NULL;
    return p;
}





