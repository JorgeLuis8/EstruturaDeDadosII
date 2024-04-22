#include "plataforma.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Plataforma *criar_plataforma()
{
    Plataforma *p = (Plataforma *)malloc(sizeof(Plataforma));
    p->arvPodcast = NULL;
    p->prox = NULL;
    return p;
}

void ler_dados_plataforma(Plataforma *p)
{
    char buffer[50];
    printf("Digite o nome da plataforma: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%[^\n]", p->nome);
}


