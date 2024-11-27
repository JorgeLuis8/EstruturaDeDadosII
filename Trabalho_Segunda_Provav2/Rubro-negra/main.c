#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv-portugues.c"

void exibirMenu() {
    printf("\n=== Menu Árvores Rubro-Negra ===\n");
    printf("1. Inserir palavra\n");
    printf("2. Buscar palavra\n");
    printf("3. Remover palavra\n");
    printf("4. Exibir árvore (em ordem)\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}

void exibirArvore(Arv_portugues *raiz) {
    if (raiz != NULL) {
        exibirArvore(raiz->esq);
        printf("%s (%d) - Cor: %s\n", 
               raiz->dados.portugueseWord, 
               raiz->dados.unit, 
               raiz->cor == RED ? "Vermelho" : "Preto");
        exibirArvore(raiz->dir);
    }
}

int main() {
    Arv_portugues *raiz = NULL;
    int opcao;
    char palavra[50];
    int unidade;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                printf("Digite a palavra em português: ");
                scanf("%s", palavra);
                printf("Digite a unidade: ");
                scanf("%d", &unidade);

                Arv_portugues *novoNo = cria_no_arv();
                strcpy(novoNo->dados.portugueseWord, palavra);
                novoNo->dados.unit = unidade;

                raiz = inserir_no(raiz, novoNo);
                printf("Palavra inserida com sucesso!\n");
                break;
            }
            case 2: {
                printf("Digite a palavra em português para buscar: ");
                scanf("%s", palavra);
                printf("Digite a unidade: ");
                scanf("%d", &unidade);

                Arv_portugues *resultado = buscar_palavra_portugues(raiz, palavra, unidade);
                if (resultado) {
                    printf("Palavra encontrada: %s (%d)\n", resultado->dados.portugueseWord, resultado->dados.unit);
                } else {
                    printf("Palavra não encontrada.\n");
                }
                break;
            }
            case 3: {
                printf("Digite a palavra em português para remover: ");
                scanf("%s", palavra);
                printf("Digite a unidade: ");
                scanf("%d", &unidade);

                if (remove_ArvLLRB_arv(&raiz, palavra, unidade)) {
                    printf("Palavra removida com sucesso!\n");
                } else {
                    printf("Palavra não encontrada ou erro ao remover.\n");
                }
                break;
            }
            case 4: {
                printf("Árvore (em ordem):\n");
                exibirArvore(raiz);
                break;
            }
            case 5: {
                printf("Saindo...\n");
                break;
            }
            default: {
                printf("Opção inválida! Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 5);

    return 0;
}
