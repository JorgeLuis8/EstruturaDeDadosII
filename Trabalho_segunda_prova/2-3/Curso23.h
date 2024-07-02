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
    dados_curso23 *info1,info2;
    struct Arv_curso23 *esq;
    struct Arv_curso23 *meio;
    struct Arv_curso23 *dir;
    int num_info;
    arv_23Disciplina *disciplinas;
    
} arv_curso23;

arv_curso23* cria_no23(dados_curso23* dados);
arv_curso23* insere_arv23(arv_curso23* raiz, dados_curso23* dados);




#endif /* CURSO_H */