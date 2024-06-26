#include <stdio.h>
#include <stdlib.h>
#include "Disciplina.c"

int main()
{
    arv_disciplina *raiz = NULL;
    int opcao;
    do
    {
        printf("1. Inserir disciplina\n");
        printf("2. Imprimir disciplinas\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            arv_disciplina *no = cria_no();
            ler_dados(no);
            raiz = inserir_disciplina(raiz, no);
            break;
        }
        case 2:
            imprimir_disciplinas(raiz);
            break;
        case 3:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 3);

    return 0;
}