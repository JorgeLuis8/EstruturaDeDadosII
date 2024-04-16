#include <stdio.h>
#include <stdlib.h>
#include "podcast.h"


struct nopodcast{
	char NomePod[100];
	char NomeEntr[100];
	struct nopodcast* Esq;
	struct nopodcast* Dir;
	struct raiztema* Temas;
};

struct raizpodcast{
	struct nopodcast *RaizPodcast;
};

NoPodcast *criar_arvore_podcast()
{
    NoPodcast *a = (NoPodcast *)malloc(sizeof(NoPodcast));
    a->Esq = NULL;
    a->Dir = NULL;
    return a;
}
