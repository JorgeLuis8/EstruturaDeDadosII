#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv-portugues.c"

void menu() {
    printf("\nEscolha uma opção:\n");
    printf("1. Inserir Palavra\n");
    printf("2. Buscar Palavra\n");
    printf("3. Remover Palavra\n");
    printf("4. Imprimir Árvore\n");
    printf("5. Sair\n");
}

void imprimir_arvore(Arv_portugues *raiz, int nivel) {
    if (raiz != NULL) {
        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }
        printf("%s (Cor: %s)\n", raiz->dados.portugueseWord, raiz->cor == RED ? "Vermelha" : "Preta");
        imprimir_arvore(raiz->esq, nivel + 1);
        imprimir_arvore(raiz->dir, nivel + 1);
    }
}

int main() {
    Arv_portugues *raiz = NULL;
    int opcao;
    char palavra[100];
    int unidade;

    do {
        menu();
        printf("Digite a opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: // Inserir Palavra
            printf("Digite a palavra em português: ");
            scanf("%s", palavra);
            printf("Digite a unidade: ");
            scanf("%d", &unidade);

            Arv_portugues *novo_no = cria_no_arv();
            strcpy(novo_no->dados.portugueseWord, palavra);
            novo_no->dados.unit = unidade;

            raiz = inserir_no(raiz, novo_no);
            printf("Palavra inserida com sucesso.\n");
            break;

        case 2: // Buscar Palavra
            printf("Digite a palavra em português para buscar: ");
            scanf("%s", palavra);
            printf("Digite a unidade: ");
            scanf("%d", &unidade);

            Arv_portugues *resultado = buscar_palavra_portugues(raiz, palavra, unidade);
            if (resultado != NULL) {
                printf("Palavra encontrada: %s (Unidade: %d)\n", resultado->dados.portugueseWord, resultado->dados.unit);
            } else {
                printf("Palavra não encontrada.\n");
            }
            break;

        case 3: // Remover Palavra
            printf("Digite a palavra em português para remover: ");
            scanf("%s", palavra);
            printf("Digite a unidade: ");
            scanf("%d", &unidade);

            int sucesso = remove_ArvLLRB_arv(&raiz, palavra, unidade);
            if (sucesso) {
                printf("Palavra removida com sucesso.\n");
            } else {
                printf("Falha ao remover a palavra.\n");
            }
            break;

        case 4: // Imprimir Árvore
            printf("Árvore Red-Black:\n");
            imprimir_arvore(raiz, 0);
            break;

        case 5: // Sair
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }

    } while (opcao != 5);

    return 0;
}
