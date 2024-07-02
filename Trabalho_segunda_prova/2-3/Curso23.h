#ifndef CURSO_H
#define CURSO_H
#include "Disciplina23.h"

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
    struct Arv_curso23 *esq;
    struct Arv_curso23 *meio;
    struct Arv_curso23 *dir;
    int num_info;
    arv_23Disciplina *disciplinas;
    
} arv_curso23;


#endif /* CURSO_H */