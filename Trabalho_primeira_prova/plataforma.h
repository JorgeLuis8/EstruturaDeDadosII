#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include "podcast.h"
typedef struct plataforma{
    char nome[50];
    Arvore_podCast *arvPodcast;
    struct plataforma *prox;

}Plataforma;

#endif