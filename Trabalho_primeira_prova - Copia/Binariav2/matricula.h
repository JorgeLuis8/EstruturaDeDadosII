#ifndef MATRICULA_H
#define MATRICULA_H

// Definição da estrutura da árvore de matrícula
typedef struct arvore_matricula {
    int codigo_disciplina;   // Código da disciplina
    struct arvore_matricula *esq;  // Ponteiro para o filho esquerdo
    struct arvore_matricula *dir;  // Ponteiro para o filho direito
} arvore_matricula;

// Funções para manipulação da árvore de matrícula

// Função para ler os dados de um nó de matrícula
void Ler_matricula(arvore_matricula *no);

// Função para inserir um nó na árvore de matrículas
arvore_matricula *inserir_matriculas(arvore_matricula *raiz, arvore_matricula *no);

// Função para imprimir todas as matrículas na árvore
void imprimir_matricula(arvore_matricula *raiz);

// Função para buscar uma matrícula na árvore pelo código da disciplina
arvore_matricula *buscar_matricula(arvore_matricula *raiz, int codigo_disciplina);

// Função para remover uma matrícula da árvore pelo código da disciplina
arvore_matricula *remover_matricula(arvore_matricula *raiz, int codigo_disciplina);

#endif // MATRICULA_H
