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
    struct dados_disciplina *dados;
    struct arv_23Disciplina *esq;
    struct arv_23Disciplina *meio;
    struct arv_23Disciplina *dir;
} arv_23Disciplina;

#endif