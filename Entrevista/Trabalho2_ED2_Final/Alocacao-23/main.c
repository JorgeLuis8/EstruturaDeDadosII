#include <stdio.h>
#include <stdlib.h>
#include "23.c"        // Inclui funções relacionadas à manipulação da árvore 2-3
#include "remocao.c"   // Inclui funções para remoção de nós ou gerenciamento de memória
#include "alocacao.c"  // Inclui funções para alocação de memória

#define MEMORY_SIZE (1024 * 1024) // Define o tamanho máximo da memória (1 MB)

// Função para exibir o menu de opções ao usuário
int menu() {
    int op;
    printf("\n1 - Alocar Nós");                // Opção para alocar nós
    printf("\n2 - Liberar Nós");               // Opção para liberar nós
    printf("\n3 - Exibir Nós (Endereços)");    // Opção para exibir endereços
    printf("\n4 - Exibir Nós Em Ordem");       // Opção para exibir a árvore em ordem
    printf("\n0 - Sair");                      // Opção para sair do programa
    printf("\nOpção escolhida: ");
    scanf("%d", &op);                          // Lê a opção do usuário
    while (getchar() != '\n');                 // Limpa o buffer do teclado
    return op;                                 // Retorna a opção escolhida
}

// Função principal do programa
int main() {
    TreeNode23 *treeRoot = NULL; // Inicializa a raiz da árvore como NULL

    int maximumMemorySize = MEMORY_SIZE; // Define o tamanho máximo da memória disponível

    printf("---------------------------------\n");
    printf("Alocacao de Memoria - Arvore 2-3\n"); // Título do programa
    printf("---------------------------------\n");

    // Exibe o tamanho máximo configurado para a memória
    printf("Tamanho máximo da memória configurado como %d blocos.\n", MEMORY_SIZE - 1);

    // Inicializa os blocos de memória e obtém o tamanho mínimo de um bloco
    int minimumMemoryBlock = initialize_memory_blocks(&treeRoot, maximumMemorySize);

    int op, node_count; // Variáveis para armazenar a opção do usuário e a quantidade de nós
    do {
        op = menu(); // Exibe o menu e lê a opção escolhida pelo usuário
        switch (op) {
            case 1: // Opção 1: Alocar nós
                do {
                    printf("\nQuantidade de nós a serem alocados: ");
                    scanf("%d", &node_count); // Lê a quantidade de nós a serem alocados
                    while (getchar() != '\n'); // Limpa o buffer do teclado

                    // Valida se a quantidade está dentro do intervalo permitido
                    if (node_count < minimumMemoryBlock || node_count > maximumMemorySize) {
                        printf("\nDigite um número entre %d e %d\n", minimumMemoryBlock, maximumMemorySize);
                    }
                } while (node_count < minimumMemoryBlock || node_count > maximumMemorySize);

                // Gerencia a alocação dos blocos de memória com o status "livre"
                manage_memory_block(&treeRoot, node_count, ALLOCATED_STATUS_FREE);
                break;

            case 2: // Opção 2: Liberar nós
                do {
                    printf("\nQuantidade de nós a serem liberados: ");
                    scanf("%d", &node_count); // Lê a quantidade de nós a serem liberados
                    while (getchar() != '\n'); // Limpa o buffer do teclado

                    // Valida se a quantidade está dentro do intervalo permitido
                    if (node_count < minimumMemoryBlock || node_count > maximumMemorySize) {
                        printf("\nDigite um número entre %d e %d\n", minimumMemoryBlock, maximumMemorySize);
                    }
                } while (node_count < minimumMemoryBlock || node_count > maximumMemorySize);

                // Gerencia a liberação dos blocos de memória com o status "ocupado"
                manage_memory_block(&treeRoot, node_count, STATUS_OCCUPIED);
                break;

            case 3: // Opção 3: Exibir endereços dos nós
                printf("\nExibindo Endereços\n");
                DisplayInfos(treeRoot); // Exibe as informações dos nós
                break;

            case 4: // Opção 4: Exibir a árvore em ordem
                printf("\nExibindo árvore\n");
                TreeNode23_print_in_order(treeRoot); // Exibe os nós da árvore em ordem
                break;

            case 0: // Opção 0: Sair do programa
                printf("\nFinalizando programa...\n");
                break;

            default: // Caso o usuário digite uma opção inválida
                printf("\nOpção inválida\n");
        }
    } while (op != 0); // Continua executando até o usuário escolher sair (opção 0)

    // Libera todos os nós e limpa a memória utilizada pela árvore
    TreeNode23_cleanup(&treeRoot);
    return 0; // Encerra o programa
}
