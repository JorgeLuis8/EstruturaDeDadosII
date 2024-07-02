#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Disciplina23.c"

int main() {
    arv_23Disciplina *raiz = NULL;
    dados_disciplina infoSobe;

    inserir_Disciplina(&raiz, 1, "Matematica", 1, 100, NULL, &infoSobe);
    inserir_Disciplina(&raiz, 2, "Fisica", 1, 100, NULL, &infoSobe);
    inserir_Disciplina(&raiz, 3, "Quimica", 1, 100, NULL, &infoSobe);
    inserir_Disciplina(&raiz, 4, "Biologia", 1, 100, NULL, &infoSobe);
    inserir_Disciplina(&raiz, 5, "Historia", 1, 100, NULL, &infoSobe);

    imprimir_Disciplina(raiz);

    return 0;
}
