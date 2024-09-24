#ifndef CURSO_H
#define CURSO_H

#include "disciplinas.h" // Inclusão correta do cabeçalho
#include "Alunos.h"      // Verifique se o nome está correto (maiúsculas/minúsculas)

// Estrutura que representa um curso
typedef struct arvore_curso {
    int codigo;
    char nome[100];
    int periodo;
    short altura;
    arvore_disciplinas *raiz_disciplinas; // Tipo corrigido
    struct arvore_curso *esq;
    struct arvore_curso *dir;
} Arvore_curso;

// Função para criar um novo curso
Arvore_curso *criar_curso();

// Função para ler dados de um curso do usuário
void ler_dados_curso(Arvore_curso *curso);

// Função para inserir um curso na árvore
Arvore_curso *inserir_curso(Arvore_curso *raiz, Arvore_curso *no);

// Função para imprimir todos os cursos na árvore
void imprimir_cursos(Arvore_curso *raiz);

// Função para buscar um curso pelo código
Arvore_curso *buscar_curso(Arvore_curso *raiz, int codigo);

// Função para remover um curso da árvore pelo código
Arvore_curso *remover_curso(Arvore_curso *raiz, int codigo);

// Função para imprimir o histórico de um aluno
void imprimir_historico(Aluno *aluno, Arvore_curso *raiz_cursos);

#endif // CURSO_H
