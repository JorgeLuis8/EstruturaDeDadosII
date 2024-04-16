#include <stdio.h>
#include <stdlib.h>
#include "entrevistas.c"

int main() {
    NoEntrevista *raiz = NULL; // Inicializa a raiz como NULL

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir nova entrevista\n");
        printf("2. Buscar entrevista por titulo\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nInserir nova entrevista:\n");
                NoEntrevista *novaEntrevista = criar_arvore_entrevistas();
                Ler_dados_de_insercao_entrevistas(novaEntrevista);
                raiz = inserir_entrevistas(raiz, novaEntrevista);
                printf("Entrevista inserida com sucesso!\n");
                break;
            case 2:
                printf("\nBuscar entrevista por titulo:\n");
                char titulo[50];
                printf("Digite o titulo da entrevista a ser buscada: ");
                scanf("%s", titulo);
                NoEntrevista *entrevistaEncontrada = buscar_entrevistas(raiz, titulo);
                if (entrevistaEncontrada != NULL) {
                    printf("Entrevista encontrada:\n");
                    struct arvore_entrevistas; // Forward declaration

                    printf("Titulo: %s\n", entrevistaEncontrada->titulos);
                    printf("Data: %s\n", entrevistaEncontrada->data);
                    printf("Duracao: %d\n", entrevistaEncontrada->duracao);
                    printf("Nome do convidado: %s\n", entrevistaEncontrada->nome_convidado);
                    printf("Especialidade do convidado: %s\n", entrevistaEncontrada->especialidade_convidado);
                } else {
                    printf("Entrevista nao encontrada.\n");
                }
                break;
            case 3:
                printf("\nEncerrando o programa.\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, escolha uma opcao valida.\n");
        }
    } while (opcao != 3);

    // Libere a mem�ria alocada para a �rvore antes de encerrar o programa
    // Coloque aqui a l�gica para liberar a mem�ria

    return 0;
}

