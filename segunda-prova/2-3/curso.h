#ifndef CURSO_H
#define CURSO_H
#include "Disciplina.h"

//arvore 2-3

typedef struct dados_curso23
{
    int codigo;
    char nome[100];
    int qtd_blocos;
    int num_semanas;
} dados_curso23;

typedef struct Arv_curso23
{
    dados_curso23 *dados;
    struct arv_curso *esq;
    struct arv_curso *meio;
    struct arv_curso *dir;
    int num_info;
    arv_disciplina23 *disciplinas;
    
} arv_curso23;


#endif /* CURSO_H */