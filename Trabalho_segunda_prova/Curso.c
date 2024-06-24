#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct Dados
{
    int codigo;
    int num_disciplina;
    int num_semanas;
}dados;

typedef struct Curso
{
    struct Dados *dados;
    int cor;
    struct Curso *raiz;
    struct Curso *esq,*dir;
}curso;


