#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Curso23.h"

// Função para criar um novo nó de curso
arv_curso23 *criaNoCurso(int codigo, char *nome, int qtd_blocos, int num_semanas, arv_curso23 *esq, arv_curso23 *meio) {
    arv_curso23 *no = (arv_curso23*)malloc(sizeof(arv_curso23));
    no->info1 = (dados_curso23*)malloc(sizeof(dados_curso23));
    no->info1->codigo = codigo;
    strcpy(no->info1->nome, nome);
    no->info1->qtd_blocos = qtd_blocos;
    no->info1->num_semanas = num_semanas;
    no->num_info = 1;
    no->esq = esq;
    no->meio = meio;
    no->dir = NULL;
    no->info2 = NULL;
    no->disciplinas = NULL;  // Inicializa a lista de disciplinas como NULL
    return no;
}

// Função para adicionar um novo dado ao nó de curso
void adicionaNoCurso(arv_curso23 **raiz, int codigo, char *nome, int qtd_blocos, int num_semanas, arv_curso23 *filho) {
    (*raiz)->info2 = (dados_curso23*)malloc(sizeof(dados_curso23));
    if (codigo > (*raiz)->info1->codigo) {
        (*raiz)->info2->codigo = codigo;
        strcpy((*raiz)->info2->nome, nome);
        (*raiz)->info2->qtd_blocos = qtd_blocos;
        (*raiz)->info2->num_semanas = num_semanas;
        (*raiz)->dir = filho;
    } else {
        (*raiz)->info2->codigo = (*raiz)->info1->codigo;
        strcpy((*raiz)->info2->nome, (*raiz)->info1->nome);
        (*raiz)->info2->qtd_blocos = (*raiz)->info1->qtd_blocos;
        (*raiz)->info2->num_semanas = (*raiz)->info1->num_semanas;

        (*raiz)->info1->codigo = codigo;
        strcpy((*raiz)->info1->nome, nome);
        (*raiz)->info1->qtd_blocos = qtd_blocos;
        (*raiz)->info1->num_semanas = num_semanas;

        (*raiz)->dir = (*raiz)->meio;
        (*raiz)->meio = filho;
    }
    (*raiz)->num_info = 2;
}

// Função para quebrar um nó de curso
arv_curso23 *quebraNoCurso(arv_curso23 **raiz, arv_curso23 *filho, int codigo, char *nome, int qtd_blocos, int num_semanas, dados_curso23 *sobe) {
    arv_curso23 *maiorNo;
    maiorNo = NULL;

    if (codigo > (*raiz)->info2->codigo) {
        sobe->codigo = (*raiz)->info2->codigo;
        strcpy(sobe->nome, (*raiz)->info2->nome);
        sobe->qtd_blocos = (*raiz)->info2->qtd_blocos;
        sobe->num_semanas = (*raiz)->info2->num_semanas;

        maiorNo = criaNoCurso(codigo, nome, qtd_blocos, num_semanas, (*raiz)->dir, filho);
    } else if (codigo < (*raiz)->info1->codigo) {
        sobe->codigo = (*raiz)->info1->codigo;
        strcpy(sobe->nome, (*raiz)->info1->nome);
        sobe->qtd_blocos = (*raiz)->info1->qtd_blocos;
        sobe->num_semanas = (*raiz)->info1->num_semanas;

        maiorNo = criaNoCurso((*raiz)->info2->codigo, (*raiz)->info2->nome, (*raiz)->info2->qtd_blocos, (*raiz)->info2->num_semanas, (*raiz)->meio, (*raiz)->dir);
        
        (*raiz)->info1->codigo = codigo;
        strcpy((*raiz)->info1->nome, nome);
        (*raiz)->info1->qtd_blocos = qtd_blocos;
        (*raiz)->info1->num_semanas = num_semanas;
        (*raiz)->meio = filho;
    } else {
        sobe->codigo = codigo;
        strcpy(sobe->nome, nome);
        sobe->qtd_blocos = qtd_blocos;
        sobe->num_semanas = num_semanas;
        maiorNo = criaNoCurso((*raiz)->info2->codigo, (*raiz)->info2->nome, (*raiz)->info2->qtd_blocos, (*raiz)->info2->num_semanas, filho, (*raiz)->dir);
    }

    (*raiz)->num_info = 1;
    (*raiz)->info2 = NULL;
    (*raiz)->dir = NULL;
    return maiorNo;
}

// Função para verificar se o nó é folha
int folhaCurso(arv_curso23 *raiz) {
    return (raiz->esq == NULL);
}

// Função para inserir um curso na árvore 2-3
arv_curso23 *inserirCurso(arv_curso23 **raiz, int codigo, char *nome, int qtd_blocos, int num_semanas, arv_curso23 *pai, dados_curso23 *infoSobe) {
    arv_curso23 *maiorNo;
    if (*raiz == NULL) {
        *raiz = criaNoCurso(codigo, nome, qtd_blocos, num_semanas, NULL, NULL);
    } else {
        if (folhaCurso(*raiz)) {
            if ((*raiz)->num_info == 1) {
                adicionaNoCurso(raiz, codigo, nome, qtd_blocos, num_semanas, NULL);
                maiorNo = NULL;
            } else {
                maiorNo = quebraNoCurso(raiz, NULL, codigo, nome, qtd_blocos, num_semanas, infoSobe);

                if (pai == NULL) {
                    *raiz = criaNoCurso(infoSobe->codigo, infoSobe->nome, infoSobe->qtd_blocos, infoSobe->num_semanas, *raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        } else {
            if (codigo < (*raiz)->info1->codigo) {
                maiorNo = inserirCurso(&((*raiz)->esq), codigo, nome, qtd_blocos, num_semanas, *raiz, infoSobe);
            } else if (((*raiz)->num_info == 1) || (((*raiz)->num_info == 2) && codigo < (*raiz)->info2->codigo)) {
                maiorNo = inserirCurso(&((*raiz)->meio), codigo, nome, qtd_blocos, num_semanas, *raiz, infoSobe);
            } else {
                maiorNo = inserirCurso(&((*raiz)->dir), codigo, nome, qtd_blocos, num_semanas, *raiz, infoSobe);
            }

            if (maiorNo != NULL) {
                if ((*raiz)->num_info == 1) {
                    adicionaNoCurso(raiz, infoSobe->codigo, infoSobe->nome, infoSobe->qtd_blocos, infoSobe->num_semanas, maiorNo);
                    maiorNo = NULL;
                } else {
                    maiorNo = quebraNoCurso(raiz, maiorNo, infoSobe->codigo, infoSobe->nome, infoSobe->qtd_blocos, infoSobe->num_semanas, infoSobe);
                    if (pai == NULL) {
                        *raiz = criaNoCurso(infoSobe->codigo, infoSobe->nome, infoSobe->qtd_blocos, infoSobe->num_semanas, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}

// Função para imprimir a árvore 2-3 de cursos
void imprimirCurso(arv_curso23 *raiz) {
    if (raiz != NULL) {
        imprimirCurso(raiz->esq);
        printf("Info 1 codigo: %d\n", raiz->info1->codigo);
        printf("Info 1 nome: %s\n", raiz->info1->nome);
        printf("Info 1 qtd_blocos: %d\n", raiz->info1->qtd_blocos);
        printf("Info 1 num_semanas: %d\n", raiz->info1->num_semanas);
        imprimirCurso(raiz->meio);
        if (raiz->num_info == 2) {
            printf("Info 2 codigo: %d\n", raiz->info2->codigo);
            printf("Info 2 nome: %s\n", raiz->info2->nome);
            printf("Info 2 qtd_blocos: %d\n", raiz->info2->qtd_blocos);
            printf("Info 2 num_semanas: %d\n", raiz->info2->num_semanas);
            imprimirCurso(raiz->dir);
        }
    }
}
