#include <stdio.h>
#include <stdlib.h>
#include "entrevistas.h"

int main() {
    Arvore_entrevistas *raiz = NULL; // Inicializa a raiz como NULL

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir nova entrevista\n");
        printf("2. Buscar entrevista por título\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nInserir nova entrevista:\n");
                Arvore_entrevistas *novaEntrevista = criar_arvore_entrevistas();
                Ler_dados_de_insercao_entrevistas(novaEntrevista);
                raiz = inserir_entrevistas(raiz, novaEntrevista);
                printf("Entrevista inserida com sucesso!\n");
                break;
            case 2:
                printf("\nBuscar entrevista por título:\n");
                char titulo[50];
                printf("Digite o título da entrevista a ser buscada: ");
                scanf("%s", titulo);
                Arvore_entrevistas *entrevistaEncontrada = buscar_entrevistas(raiz, titulo);
                if (entrevistaEncontrada != NULL) {
                    printf("Entrevista encontrada:\n");
                    printf("Título: %s\n", entrevistaEncontrada->titulos);
                    printf("Data: %s\n", entrevistaEncontrada->data);
                    printf("Duração: %d\n", entrevistaEncontrada->duracao);
                    printf("Nome do convidado: %s\n", entrevistaEncontrada->nome_convidado);
                    printf("Especialidade do convidado: %s\n", entrevistaEncontrada->especialidade_convidado);
                } else {
                    printf("Entrevista não encontrada.\n");
                }
                break;
            case 3:
                printf("\nEncerrando o programa.\n");
                break;
            default:
                printf("\nOpção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 3);

    // Libere a memória alocada para a árvore antes de encerrar o programa
    // Coloque aqui a lógica para liberar a memória

    return 0;
}

