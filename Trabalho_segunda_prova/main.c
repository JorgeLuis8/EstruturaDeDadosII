#include <stdio.h>
#include <stdlib.h>
#include "Disciplina.c"

int main()
{
    arv_disciplina *raiz = NULL;
    int opcao;

    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir disciplina\n");
        printf("2. Imprimir disciplinas\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            arv_disciplina *novo_no = cria_no();
            if (novo_no == NULL)
            {
                printf("Erro ao criar novo no!\n");
                break;
            }
            ler_dados(novo_no);
            raiz = inserir_disciplina(raiz, novo_no);
            break;
        }
        case 2:
            printf("\nDisciplinas inseridas:\n");
            imprimir_disciplinas(raiz);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 3);


    return 0;
}