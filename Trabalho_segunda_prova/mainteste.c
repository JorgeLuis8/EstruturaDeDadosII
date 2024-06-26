#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct ArvoreDisciplina
{
    int chave;
    struct ArvoreDisciplina *esquerda;
    struct ArvoreDisciplina *direita;
    int cor; // RED ou BLACK
} arv_disciplina;

void trocaCor(arv_disciplina *no)
{
    if (no != NULL)
    {
        no->cor = (no->cor == RED) ? BLACK : RED;
    }
}

int main()
{
    arv_disciplina *no = (arv_disciplina *)malloc(sizeof(arv_disciplina));
    if (no == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }

    no->chave = 10;
    no->esquerda = NULL;
    no->direita = NULL;
    no->cor = RED;

    printf("Cor antes da troca: %d\n", no->cor); // Deve imprimir 0 (RED)
    trocaCor(no);
    printf("Cor depois da troca: %d\n", no->cor); // Deve imprimir 1 (BLACK)

    trocaCor(no);
    printf("Cor depois da segunda troca: %d\n", no->cor); // Deve imprimir 0 (RED)

    free(no);
    return 0;
}
