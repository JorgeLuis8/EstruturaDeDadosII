#include "Curso23.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Curso23.h"

arv_curso23* cria_no23(dados_curso23* dados) {
    arv_curso23* novo_no = (arv_curso23*) malloc(sizeof(arv_curso23));
    if (novo_no) {
        novo_no->dados = NULL;
        novo_no->esq = NULL;
        novo_no->meio = NULL;
        novo_no->dir = NULL;
        novo_no->num_info = 0;
        novo_no->disciplinas = NULL;
    }
    return novo_no;
}

arv_curso23* insere_arv23(arv_curso23* raiz, dados_curso23* dados) {
    if (raiz == NULL) {
        return cria_no(dados);
    }

    if (raiz->num_info == 1) {
        if (dados->codigo < raiz->dados->codigo) {
            if (raiz->esq == NULL) {
                raiz->esq = cria_no(dados);
            } else {
                raiz->esq = insere_arv23(raiz->esq, dados);
            }
        } else {
            if (raiz->meio == NULL) {
                raiz->meio = cria_no(dados);
            } else {
                raiz->meio = insere_arv23(raiz->meio, dados);
            }
        }
        raiz->num_info++;
    } else {
        raiz = divide_no(raiz, dados);
    }
    return raiz;
}




