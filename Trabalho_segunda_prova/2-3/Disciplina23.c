#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Disciplina23.h"

arv_23Disciplina *criaNo(int codigo, char *nome, int bloco, int carga_horaria, arv_23Disciplina *esq, arv_23Disciplina *meio) 
{
    arv_23Disciplina *no = (arv_23Disciplina*)malloc(sizeof(arv_23Disciplina)); 
    no->info1 = (dados_disciplina*)malloc(sizeof(dados_disciplina));
    no->info1->codigo = codigo;
    strcpy( no->info1->nome,nome);
    no->info1->bloco = bloco;
    no->info1->carga_horaria = carga_horaria;
    no->ninfos = 1;
    no->esq = esq;
    no->meio = meio;
    no->dir = NULL;
    no->info2 = NULL;
    return no;
}

arv_23Disciplina *criaNo_disciplina(int codigo, char *nome, int bloco, int carga_horaria, arv_23Disciplina *noEsq, arv_23Disciplina *noMeio) {
    arv_23Disciplina *no = (arv_23Disciplina*)malloc(sizeof(arv_23Disciplina));
    no->info1 = (dados_disciplina*)malloc(sizeof(dados_disciplina));
    no->info1->codigo = codigo;
    strcpy(no->info1->nome, nome);
    no->info1->bloco = bloco;
    no->info1->carga_horaria = carga_horaria;
    no->ninfos = 1;
    no->esq = noEsq;
    no->meio = noMeio;
    no->dir = NULL;
    no->info2 = NULL;
    return no;
}

void adicionaNo_disciplina(arv_23Disciplina **raiz, int codigo, char *nome, int bloco, int carga_horaria, arv_23Disciplina *filho) {
    (*raiz)->info2 = (dados_disciplina*)malloc(sizeof(dados_disciplina));
    if (codigo > (*raiz)->info1->codigo) {
        (*raiz)->info2->codigo = codigo;
        strcpy((*raiz)->info2->nome, nome);
        (*raiz)->info2->bloco = bloco;
        (*raiz)->info2->carga_horaria = carga_horaria;
        (*raiz)->dir = filho;
    } else {
        (*raiz)->info2->codigo = (*raiz)->info1->codigo;
        strcpy((*raiz)->info2->nome, (*raiz)->info1->nome);
        (*raiz)->info2->bloco = (*raiz)->info1->bloco;
        (*raiz)->info2->carga_horaria = (*raiz)->info1->carga_horaria;

        (*raiz)->info1->codigo = codigo;
        strcpy((*raiz)->info1->nome, nome);
        (*raiz)->info1->bloco = bloco;
        (*raiz)->info1->carga_horaria = carga_horaria;

        (*raiz)->dir = (*raiz)->meio;
        (*raiz)->meio = filho;
    }
    (*raiz)->ninfos = 2;
}

arv_23Disciplina *quebraNo_disciplina(arv_23Disciplina **raiz, arv_23Disciplina *filho, int codigo, char *nome, int bloco, int carga_horaria, dados_disciplina *sobe) {
    arv_23Disciplina *maiorNo;
    maiorNo = NULL;

    if (codigo > (*raiz)->info2->codigo) {
        sobe->codigo = (*raiz)->info2->codigo;
        strcpy(sobe->nome, (*raiz)->info2->nome);
        sobe->bloco = (*raiz)->info2->bloco;
        sobe->carga_horaria = (*raiz)->info2->carga_horaria;

        maiorNo = criaNo_disciplina(codigo, nome, bloco, carga_horaria, (*raiz)->dir, filho);
    } else if (codigo < (*raiz)->info1->codigo) {
        sobe->codigo = (*raiz)->info1->codigo;
        strcpy(sobe->nome, (*raiz)->info1->nome);
        sobe->bloco = (*raiz)->info1->bloco;
        sobe->carga_horaria = (*raiz)->info1->carga_horaria;

        maiorNo = criaNo_disciplina((*raiz)->info2->codigo, (*raiz)->info2->nome, (*raiz)->info2->bloco, (*raiz)->info2->carga_horaria, (*raiz)->meio, (*raiz)->dir);
        
        (*raiz)->info1->codigo = codigo;
        strcpy((*raiz)->info1->nome, nome);
        (*raiz)->info1->bloco = bloco;
        (*raiz)->info1->carga_horaria = carga_horaria;
        (*raiz)->meio = filho;
    } else {
        sobe->codigo = codigo;
        strcpy(sobe->nome, nome);
        sobe->bloco = bloco;
        sobe->carga_horaria = carga_horaria;
        maiorNo = criaNo_disciplina((*raiz)->info2->codigo, (*raiz)->info2->nome, (*raiz)->info2->bloco, (*raiz)->info2->carga_horaria, filho, (*raiz)->dir);
    }

    (*raiz)->ninfos = 1;
    (*raiz)->info2 = NULL;
    (*raiz)->dir = NULL; 
    return maiorNo;
}

int folha_disciplina(arv_23Disciplina *raiz) {
    return (raiz->esq == NULL);
}

arv_23Disciplina *inserir_Disciplina(arv_23Disciplina **raiz, int codigo, char *nome, int bloco, int carga_horaria, arv_23Disciplina *pai, dados_disciplina *infoSobe) {
    arv_23Disciplina *maiorNo;
    if (*raiz == NULL) {
        *raiz = criaNo_disciplina(codigo, nome, bloco, carga_horaria, NULL, NULL);
    } else {
        if (folha_disciplina(*raiz)) {
            if ((*raiz)->ninfos == 1) {
                adicionaNo_disciplina(raiz, codigo, nome, bloco, carga_horaria, NULL);
                maiorNo = NULL;
            } else {
                maiorNo = quebraNo_disciplina(raiz, NULL, codigo, nome, bloco, carga_horaria, infoSobe);

                if (pai == NULL) {
                    *raiz = criaNo_disciplina(infoSobe->codigo, infoSobe->nome, infoSobe->bloco, infoSobe->carga_horaria, *raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        } else {
            if (codigo < (*raiz)->info1->codigo) {
                maiorNo = inserir_Disciplina(&((*raiz)->esq), codigo, nome, bloco, carga_horaria, *raiz, infoSobe);
            } else if (((*raiz)->ninfos == 1) || (((*raiz)->ninfos == 2) && codigo < (*raiz)->info2->codigo)) {
                maiorNo = inserir_Disciplina(&((*raiz)->meio), codigo, nome, bloco, carga_horaria, *raiz, infoSobe);
            } else {
                maiorNo = inserir_Disciplina(&((*raiz)->dir), codigo, nome, bloco, carga_horaria, *raiz, infoSobe);
            }

            if (maiorNo != NULL) {
                if ((*raiz)->ninfos == 1) {
                    adicionaNo_disciplina(raiz, infoSobe->codigo, infoSobe->nome, infoSobe->bloco, infoSobe->carga_horaria, maiorNo);
                    maiorNo = NULL;
                } else {
                    maiorNo = quebraNo_disciplina(raiz, maiorNo, infoSobe->codigo, infoSobe->nome, infoSobe->bloco, infoSobe->carga_horaria, infoSobe);
                    if (pai == NULL) {
                        *raiz = criaNo_disciplina(infoSobe->codigo, infoSobe->nome, infoSobe->bloco, infoSobe->carga_horaria, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}

void imprimir_Disciplina(arv_23Disciplina *raiz) {
    if (raiz != NULL) {
        imprimir_Disciplina(raiz->esq);
        printf("Info 1 codigo: %d\n", raiz->info1->codigo);
        printf("Info 1 nome: %s\n", raiz->info1->nome);
        printf("Info 1 bloco: %d\n", raiz->info1->bloco);
        printf("Info 1 carga horaria: %d\n", raiz->info1->carga_horaria);
        imprimir_Disciplina(raiz->meio);
        if (raiz->ninfos == 2) {
            printf("Info 2 codigo: %d\n", raiz->info2->codigo);
            printf("Info 2 nome: %s\n", raiz->info2->nome);
            printf("Info 2 bloco: %d\n", raiz->info2->bloco);
            printf("Info 2 carga horaria: %d\n", raiz->info2->carga_horaria);
            imprimir_Disciplina(raiz->dir);
        }
    }
}

arv_23Disciplina *buscarDisciplina(arv_23Disciplina *raiz, int codigo) {
    arv_23Disciplina *disciplina;
    if (raiz == NULL) {
        disciplina = NULL;
    } else {
        if (raiz->info1->codigo == codigo) {
            disciplina = raiz;
        } else if (raiz->ninfos == 2 && raiz->info2->codigo == codigo) {
            disciplina = raiz;
        } else if (codigo < raiz->info1->codigo) {
            disciplina = buscarDisciplina(raiz->esq, codigo);
        } else if (raiz->ninfos == 2 && codigo < raiz->info2->codigo) {
            disciplina = buscarDisciplina(raiz->meio, codigo);
        } else {
            disciplina = buscarDisciplina(raiz->dir, codigo);
        }
    }
    return disciplina;
}

void imprimirDisciplinasBloco (arv_23Disciplina *raiz, int bloco) {
    if (raiz != NULL) {
        imprimirDisciplinasBloco(raiz->esq, bloco);
        if (raiz->info1->bloco == bloco) {
            printf("Info 1 codigo: %d\n", raiz->info1->codigo);
            printf("Info 1 nome: %s\n", raiz->info1->nome);
            printf("Info 1 bloco: %d\n", raiz->info1->bloco);
            printf("Info 1 carga horaria: %d\n", raiz->info1->carga_horaria);
        }
        imprimirDisciplinasBloco(raiz->meio, bloco);
        if (raiz->ninfos == 2) {
            if (raiz->info2->bloco == bloco) {
                printf("Info 2 codigo: %d\n", raiz->info2->codigo);
                printf("Info 2 nome: %s\n", raiz->info2->nome);
                printf("Info 2 bloco: %d\n", raiz->info2->bloco);
                printf("Info 2 carga horaria: %d\n", raiz->info2->carga_horaria);
            }
            imprimirDisciplinasBloco(raiz->dir, bloco);
        }
    }
}