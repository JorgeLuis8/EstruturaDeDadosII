#ifndef ALUNOS_H
#define ALUNOS_H
#include "notas.h"
#include "matricula.h"
//#include "ArvoreNotas.h"
//#include "ArvoreMatriculas.h"
typedef struct aluno
{
    int matricula;
    char nome[50];
    int codigo_curso;
    struct arvore_notas *raiz_notas;    // Caso queira implementar mais tarde
    struct arvore_matriculas *raiz_matriculas; // Caso queira implementar mais tarde
    struct aluno *prox;
} Aluno;

// Função para criar um novo aluno
Aluno *criar_aluno();

// Função para inserir um aluno na lista
Aluno *inserir_aluno(Aluno *aluno, Aluno *no);

// Função para remover um aluno pela matrícula
Aluno *remover_aluno(Aluno *aluno, int matricula);

// Função para buscar um aluno pela matrícula
Aluno *buscar_aluno(Aluno *aluno, int matricula);

// Função para imprimir todos os alunos
void imprimir_alunos(Aluno *aluno);

#endif