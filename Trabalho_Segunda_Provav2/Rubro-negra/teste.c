#include <stdio.h>
#include <stdlib.h>
#include "arv-ingles-bin.c"
#include "arv-portugues.c"
int main() {
    Arv_portugues *arvore = NULL;
    Arv_portugues *novoNo = cria_no_arv();
    strcpy(novoNo->dados.portugueseWord, "teste");
    novoNo->dados.unit = 1;
    arvore = inserir_no(arvore, novoNo);

    printf("Palavra inserida: %s, Unidade: %d\n", arvore->dados.portugueseWord, arvore->dados.unit);

    return 0;
}
