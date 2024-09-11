#include "disciplinas.h"

struct arvore_curso {
    int codigo;
    char nome[50];
    int periodo;
    Arvore_disciplinas *raiz_disciplinas; 
    arvore_curso *esq;
    arvore_curso *dir;
};

typedef struct arvore_curso Arvore_curso;