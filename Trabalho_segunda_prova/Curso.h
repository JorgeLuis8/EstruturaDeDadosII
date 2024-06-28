#ifndef CURSO_H
#define CURSO_H
#include "Disciplina.h"

typedef struct dados_curso
{
    int codigo;
    char nome[100];
    int qtd_blocos;
    int num_semanas;
} dados_curso;

typedef struct arv_curso
{
    dados_curso *dados;
    int cor;
    struct arv_curso *esq;
    struct arv_curso *dir;
    struct arv_disciplina *disciplinas;
} arv_curso;

arv_curso *cria_no_curso();
void ler_dados_curso(arv_curso *no);
void imprimir_disciplinas_curso(arv_curso *raiz);
arv_curso *inserir_curso(arv_curso *raiz, arv_curso *no);
arv_curso *buscar_disciplina_curso(arv_curso *raiz, int codigo);
arv_curso *remove_NO_curso(arv_curso *H, int valor);
int remove_ArvLLRB_curso(arv_curso **raiz, int codigo);
arv_curso *inserir_rec_curso(arv_curso *raiz, arv_curso *no);
arv_curso *balancear_curso(arv_curso *raiz);

#endif /* CURSO_H */
