#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct notema{
	char Tema[100];
	struct notema* Esq;
	struct notema* Dir;
	struct raizEntrevista* entrevistas;
};

struct noraiz{
	struct notema* RaizTema;
};
