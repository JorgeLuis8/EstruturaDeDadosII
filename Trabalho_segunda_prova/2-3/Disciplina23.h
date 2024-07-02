#ifndef DISCIPLINA_H
#define DISCIPLINA_H
typedef struct dados_disciplina
{
    int codigo;
    char nome[100];
    int bloco;
    int carga_horaria;
} dados_disciplina;

typedef struct Arv_23Disciplina
{
    int ninfos;
    struct dados_disciplina *info1,*info2;
    struct Arv_23Disciplina *esq;
    struct Arv_23Disciplina *meio;
    struct Arv_23Disciplina *dir;
} arv_23Disciplina;

#endif