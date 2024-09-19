#ifndef DISCIPLINAS_H
#define DISCIPLINAS_H
typedef struct Arvore_disciplinas {
    int codigo;
    char nome[50];
    int carga_horaria;
    int periodo;
    struct Arvore_disciplinas *esq;
    struct Arvore_disciplinas *dir;
}arvore_disciplinas;

arvore_disciplinas *criar_disciplina();
arvore_disciplinas *inserir_disciplina(arvore_disciplinas *raiz, arvore_disciplinas *no);
arvore_disciplinas *buscar_disciplina(arvore_disciplinas *raiz, int codigo);
arvore_disciplinas *remover_disciplina(arvore_disciplinas *raiz, int codigo);
void imprimir_disciplinas(arvore_disciplinas *raiz);
void imprimir_disciplinas_periodo(arvore_disciplinas *raiz, int periodo);
#endif // DISCIPLINAS_H