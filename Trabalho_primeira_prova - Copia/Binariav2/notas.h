#ifndef NOTAS_H
#define NOTAS_H

// Definição da estrutura de nó da árvore de notas
typedef struct arvore_notas {
    int codigo_disciplina;  // Código da disciplina
    char semestre_cursado[10];   // Semestre cursado
    int nota_final;              // Nota final da disciplina
    struct arvore_notas *esq;    // Ponteiro para o nó à esquerda
    struct arvore_notas *dir;    // Ponteiro para o nó à direita
} arvore_notas;

// Funções
void Ler_notas(arvore_notas *no);  // Função para ler os dados de um nó
arvore_notas *inserir_nota(arvore_notas *raiz, arvore_notas *no);  // Corrigido
void imprimir_notas(arvore_notas *raiz);  // Função para imprimir as notas em ordem
arvore_notas *buscar_notas(arvore_notas *raiz, int codigo_disciplina);  // Função para buscar uma nota pelo código da disciplina
arvore_notas *remover_nota(arvore_notas *raiz, int codigo_disciplina);  // Função para remover uma nota pelo código da disciplina

#endif
