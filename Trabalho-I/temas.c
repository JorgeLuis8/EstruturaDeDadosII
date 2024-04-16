#include <stdio.h>
#include <stdlib.h>
#include "temas.h"
#include "entrevistas.h"
struct notema{
	char Tema[100];
	struct notema* Esq;
	struct notema* Dir;
	struct raizEntrevista* entrevistas;
};

struct noraiz{
	struct notema* RaizTema;
};



