#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados_disciplina {
    int codigo;          // Código da disciplina
    char nome[100];      // Nome da disciplina
    int bloco;           // Bloco da disciplina
    int carga_horaria;   // Carga horária da disciplina
} dados_disciplina;

typedef struct Arv_23Disciplina {
    int ninfos;
    dados_disciplina *info1, *info2;
    struct Arv_23Disciplina *esq, *meio, *dir;
} arv_23Disciplina;

// Função para criar um novo nó
arv_23Disciplina* criaNo_disciplina(int codigo, char *nome, int bloco, int carga_horaria, arv_23Disciplina *esq, arv_23Disciplina *meio) {
    arv_23Disciplina *novoNo = (arv_23Disciplina*)malloc(sizeof(arv_23Disciplina));
    novoNo->info1 = (dados_disciplina*)malloc(sizeof(dados_disciplina));
    novoNo->info1->codigo = codigo;
    strcpy(novoNo->info1->nome, nome);
    novoNo->info1->bloco = bloco;
    novoNo->info1->carga_horaria = carga_horaria;

    novoNo->info2 = NULL;
    novoNo->ninfos = 1;
    novoNo->esq = esq;
    novoNo->meio = meio;
    novoNo->dir = NULL;

    return novoNo;
}

// Função para quebrar um nó
arv_23Disciplina* quebraNo_disciplina(arv_23Disciplina **raiz, int codigo, char *nome, int bloco, int carga_horaria, arv_23Disciplina *filho) {
    arv_23Disciplina *maiorNo = NULL;

    dados_disciplina sobe;
    if (codigo > (*raiz)->info2->codigo) {
        sobe = *(*raiz)->info2;
        maiorNo = criaNo_disciplina(codigo, nome, bloco, carga_horaria, (*raiz)->dir, filho);
    } 
    else if (codigo < (*raiz)->info1->codigo) {
        sobe = *(*raiz)->info1;
        maiorNo = criaNo_disciplina((*raiz)->info2->codigo, (*raiz)->info2->nome, (*raiz)->info2->bloco, (*raiz)->info2->carga_horaria, (*raiz)->meio, (*raiz)->dir);

        (*raiz)->info1->codigo = codigo;
        strcpy((*raiz)->info1->nome, nome);
        (*raiz)->info1->bloco = bloco;
        (*raiz)->info1->carga_horaria = carga_horaria;
        (*raiz)->meio = filho;
    } 
    else {
        sobe.codigo = codigo;
        strcpy(sobe.nome, nome);
        sobe.bloco = bloco;
        sobe.carga_horaria = carga_horaria;
        maiorNo = criaNo_disciplina((*raiz)->info2->codigo, (*raiz)->info2->nome, (*raiz)->info2->bloco, (*raiz)->info2->carga_horaria, filho, (*raiz)->dir);
    }

    (*raiz)->ninfos = 1;
    (*raiz)->info2 = NULL;
    (*raiz)->dir = NULL; 

    return maiorNo;
}

// Função para inserir uma nova informação na árvore
arv_23Disciplina* insereRec(arv_23Disciplina *raiz, int codigo, char *nome, int bloco, int carga_horaria, dados_disciplina *sobe) {
    if (!raiz) {
        sobe->codigo = codigo;
        strcpy(sobe->nome, nome);
        sobe->bloco = bloco;
        sobe->carga_horaria = carga_horaria;
        return NULL;
    }

    arv_23Disciplina *novoNo;
    if (!raiz->esq) {
        if (raiz->ninfos == 1) {
            if (codigo < raiz->info1->codigo) {
                raiz->info2 = raiz->info1;
                raiz->info1 = sobe;
            } else {
                raiz->info2 = sobe;
            }
            raiz->ninfos = 2;
            return NULL;
        } else {
            return quebraNo_disciplina(&raiz, codigo, nome, bloco, carga_horaria, NULL);
        }
    }

    if (codigo < raiz->info1->codigo) {
        novoNo = insereRec(raiz->esq, codigo, nome, bloco, carga_horaria, sobe);
    } else if (raiz->ninfos == 1 || codigo < raiz->info2->codigo) {
        novoNo = insereRec(raiz->meio, codigo, nome, bloco, carga_horaria, sobe);
    } else {
        novoNo = insereRec(raiz->dir, codigo, nome, bloco, carga_horaria, sobe);
    }

    if (novoNo) {
        if (raiz->ninfos == 1) {
            if (codigo < raiz->info1->codigo) {
                raiz->info2 = raiz->info1;
                raiz->info1 = sobe;
                raiz->meio = novoNo;
            } else {
                raiz->info2 = sobe;
                raiz->dir = novoNo;
            }
            raiz->ninfos = 2;
            return NULL;
        } else {
            return quebraNo_disciplina(&raiz, sobe->codigo, sobe->nome, sobe->bloco, sobe->carga_horaria, novoNo);
        }
    }

    return NULL;
}

arv_23Disciplina* insere(arv_23Disciplina *raiz, int codigo, char *nome, int bloco, int carga_horaria) {
    dados_disciplina *sobe = (dados_disciplina*)malloc(sizeof(dados_disciplina));
    arv_23Disciplina *novoNo = insereRec(raiz, codigo, nome, bloco, carga_horaria, sobe);
    if (novoNo) {
        return criaNo_disciplina(sobe->codigo, sobe->nome, sobe->bloco, sobe->carga_horaria, raiz, novoNo);
    }
    return raiz;
}

// Função para imprimir a árvore (para fins de depuração)
void imprimeArvore(arv_23Disciplina *raiz) {
    if (raiz) {
        if (raiz->ninfos == 1) {
            printf("(%d, %s)", raiz->info1->codigo, raiz->info1->nome);
        } else {
            printf("(%d, %s), (%d, %s)", raiz->info1->codigo, raiz->info1->nome, raiz->info2->codigo, raiz->info2->nome);
        }
        if (raiz->esq || raiz->meio || raiz->dir) {
            printf(" [");
            imprimeArvore(raiz->esq);
            printf(", ");
            imprimeArvore(raiz->meio);
            if (raiz->dir) {
                printf(", ");
                imprimeArvore(raiz->dir);
            }
            printf("]");
        }
    }
}

int main() {
    arv_23Disciplina *raiz = NULL;

    raiz = insere(raiz, 20, "Algoritmos", 1, 60);
    raiz = insere(raiz, 10, "Estruturas de Dados", 2, 80);
    raiz = insere(raiz, 30, "Programação", 1, 100);
    raiz = insere(raiz, 40, "Matemática", 3, 70);
    raiz = insere(raiz, 50, "Física", 2, 60);
    raiz = insere(raiz, 25, "Química", 4, 90);

    printf("Árvore 2-3 de Disciplinas:\n");
    imprimeArvore(raiz);
    printf("\n");

    return 0;
}
