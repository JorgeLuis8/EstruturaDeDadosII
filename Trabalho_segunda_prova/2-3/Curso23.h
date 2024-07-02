#ifndef CURSO_H
#define CURSO_H

#include "Disciplina23.h"

// Estrutura para armazenar os dados do curso
typedef struct dados_curso23 {
    int codigo;
    char nome[100];
    int qtd_blocos;
    int num_semanas;
} dados_curso23;

// Estrutura da árvore 2-3 para cursos
typedef struct Arv_curso23 {
    dados_curso23 *info1;
    dados_curso23 *info2;
    struct Arv_curso23 *esq;
    struct Arv_curso23 *meio;
    struct Arv_curso23 *dir;
    int num_info;
    arv_23Disciplina *disciplinas;  // Lista de disciplinas associadas ao curso
} arv_curso23;

#endif /* CURSO_H */
