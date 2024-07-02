#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Disciplina23.h"

arv_23Disciplina *cria_no23(arv_23Disciplina *raiz){
    arv_23Disciplina *no = (arv_23Disciplina*) malloc(sizeof(arv_23Disciplina));
    no->ninfos = 0;
    no->esq = NULL;
    no->meio = NULL;
    no->dir = NULL;
    return no;
}