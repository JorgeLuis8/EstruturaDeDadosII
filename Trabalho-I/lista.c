#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista{
	char nomeP[100];
	struct lista *proximo;
	struct raizpodcast *podcast;
};
