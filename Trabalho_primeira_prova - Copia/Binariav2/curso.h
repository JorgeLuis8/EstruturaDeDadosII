#ifndef CURSO_H
#define CURSO_H

// Estrutura que representa um curso
typedef struct arvore_curso {
    int codigo;
    char nome[100];
    int periodo;
    struct raiz_disciplinas *raiz_disciplinas;
   
    
    struct arvore_curso *esq;
    struct arvore_curso *dir;
} Arvore_curso;

// Função para criar um novo curso
Arvore_curso *criar_curso();

// Função para ler dados de um curso do usuário
void ler_dados_curso(Arvore_curso *curso);

// Função para inserir um curso na árvore
Arvore_curso *inserir_curso(Arvore_curso *curso, Arvore_curso *no);

// Função para imprimir todos os cursos na árvore
void imprimir_cursos(Arvore_curso *curso);

// Função para buscar um curso pelo código
Arvore_curso *buscar_curso(Arvore_curso *curso, int codigo);

// Função para remover um curso da árvore pelo código
Arvore_curso *remover_curso(Arvore_curso *curso, int codigo);

#endif // CURSO_H
