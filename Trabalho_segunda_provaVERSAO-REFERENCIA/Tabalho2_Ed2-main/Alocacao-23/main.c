#include <stdio.h>
#include <stdlib.h>
#include "arv-23.c" // Supondo que contém as funções fornecidas

Memory *root = NULL; // Raiz da árvore
int flag = 0;

// Função para cadastrar nós na árvore
void cadastrarNos() {
    int start, end, status;
    printf("Cadastro de Nós:\n");
    printf("Informe o status do primeiro nó (1 para Livre, 0 para Ocupado): ");
    scanf("%d", &status);
    printf("Informe o início e o final do nó (em blocos): ");
    scanf("%d %d", &start, &end);

    Insert23(&root, NULL, NULL, start, end, status, &flag);

    while (1) {
        printf("Informe o final do próximo nó (ou -1 para terminar): ");
        scanf("%d", &end);
        if (end == -1) break;

        start = root->info2 ? root->info2->end + 1 : root->info1->end + 1;
        printf("Informe o status do nó atual (1 para Livre, 0 para Ocupado): ");
        scanf("%d", &status);
        Insert23(&root, NULL, NULL, start, end, status, &flag);
    }
}

// Função para alocar nós
void alocarNos() {
    int requiredSpace;
    printf("Informe a quantidade de blocos necessários: ");
    scanf("%d", &requiredSpace);

    Memory *found = SourceSpace(root, requiredSpace);
    if (found) {
        printf("Espaço encontrado: Começo: %d, Fim: %d\n",
               found->info1->start, found->info1->end);
        found->info1->status = OCCUPIED;
    } else {
        printf("Nenhum espaço disponível.\n");
    }
}

// Função para liberar nós
void liberarNos() {
    int start, end;
    printf("Informe o intervalo de blocos para liberar (começo e fim): ");
    scanf("%d %d", &start, &end);

    // Localizar e liberar nós
    Memory *current = root;
    while (current) {
        if (current->info1->start == start && current->info1->end == end) {
            current->info1->status = FREE;
            break;
        }
        if (current->info2 && current->info2->start == start && current->info2->end == end) {
            current->info2->status = FREE;
            break;
        }
        current = (start < current->info1->start) ? current->left : current->center;
    }
    printf("Blocos liberados.\n");
}

// Menu principal
int main() {
    int option;

    do {
        printf("\nGerenciador de Memória - Árvore 4-5\n");
        printf("1. Cadastrar Nós\n");
        printf("2. Alocar Nós\n");
        printf("3. Liberar Nós\n");
        printf("4. Exibir Nós\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
        case 1:
            cadastrarNos();
            break;
        case 2:
            alocarNos();
            break;
        case 3:
            liberarNos();
            break;
        case 4:
            DisplayInfos(root);
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (option != 0);

    return 0;
}
