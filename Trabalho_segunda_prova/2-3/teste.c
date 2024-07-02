#include <stdio.h>
#include <stdlib.h>

typedef struct dados_disciplina {
    int valor;  // Ou qualquer outro dado que você queira armazenar
} dados_disciplina;

typedef struct Arv_23Disciplina {
    int ninfos;
    dados_disciplina *info1, *info2;
    struct Arv_23Disciplina *esq, *meio, *dir;
} arv_23Disciplina;

// Função para criar um novo nó
arv_23Disciplina* criaNo(dados_disciplina *info, arv_23Disciplina *esq, arv_23Disciplina *meio) {
    arv_23Disciplina *novoNo = (arv_23Disciplina*)malloc(sizeof(arv_23Disciplina));
    novoNo->ninfos = 1;
    novoNo->info1 = info;
    novoNo->info2 = NULL;
    novoNo->esq = esq;
    novoNo->meio = meio;
    novoNo->dir = NULL;
    return novoNo;
}

// Função auxiliar para inserir uma informação em um nó
void insereNo(arv_23Disciplina *no, dados_disciplina *info, arv_23Disciplina *dir) {
    if (info->valor < no->info1->valor) {
        no->info2 = no->info1;
        no->info1 = info;
        no->dir = no->meio;
        no->meio = dir;
    } else {
        no->info2 = info;
        no->dir = dir;
    }
    no->ninfos = 2;
}

// Função para quebrar um nó
arv_23Disciplina* split(arv_23Disciplina *raiz, dados_disciplina *info, dados_disciplina **infoMeio) {
    arv_23Disciplina *novoNo;

    if (info->valor < raiz->info1->valor) {
        *infoMeio = raiz->info1;
        novoNo = criaNo(raiz->info2, raiz->meio, raiz->dir);
        raiz->info1 = info;
    } else if (info->valor < raiz->info2->valor) {
        *infoMeio = info;
        novoNo = criaNo(raiz->info2, raiz->meio, raiz->dir);
    } else {
        *infoMeio = raiz->info2;
        novoNo = criaNo(info, raiz->meio, raiz->dir);
    }
    
    raiz->ninfos = 1;
    raiz->info2 = NULL;
    raiz->meio = novoNo->esq;
    raiz->dir = novoNo->meio;
    novoNo->esq = novoNo->meio;
    novoNo->meio = novoNo->dir;
    novoNo->dir = NULL;

    return novoNo;
}

// Função para inserir uma nova informação na árvore
arv_23Disciplina* insereRec(arv_23Disciplina *raiz, dados_disciplina *info, dados_disciplina **infoMeio) {
    if (!raiz) {
        *infoMeio = info;
        return NULL;
    }

    arv_23Disciplina *novoNo;
    if (!raiz->esq) {
        if (raiz->ninfos == 1) {
            insereNo(raiz, info, NULL);
            return NULL;
        } else {
            return split(raiz, info, infoMeio);
        }
    }

    if (info->valor < raiz->info1->valor) {
        novoNo = insereRec(raiz->esq, info, infoMeio);
    } else if (raiz->ninfos == 1 || info->valor < raiz->info2->valor) {
        novoNo = insereRec(raiz->meio, info, infoMeio);
    } else {
        novoNo = insereRec(raiz->dir, info, infoMeio);
    }

    if (novoNo) {
        if (raiz->ninfos == 1) {
            insereNo(raiz, *infoMeio, novoNo);
            return NULL;
        } else {
            return split(raiz, *infoMeio, infoMeio);
        }
    }

    return NULL;
}

arv_23Disciplina* insere(arv_23Disciplina *raiz, dados_disciplina *info) {
    dados_disciplina *infoMeio;
    arv_23Disciplina *novoNo = insereRec(raiz, info, &infoMeio);
    if (novoNo) {
        return criaNo(infoMeio, raiz, novoNo);
    }
    return raiz;
}

// Função para imprimir a árvore (para fins de depuração)
void imprimeArvore(arv_23Disciplina *raiz) {
    if (raiz) {
        if (raiz->ninfos == 1) {
            printf("(%d)", raiz->info1->valor);
        } else {
            printf("(%d, %d)", raiz->info1->valor, raiz->info2->valor);
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
    dados_disciplina infos[] = {{10}, {20}, {30}, {40}, {50}, {25}};
    
    for (int i = 0; i < 6; i++) {
        raiz = insere(raiz, &infos[i]);
    }

    imprimeArvore(raiz);
    printf("\n");

    return 0;
}
