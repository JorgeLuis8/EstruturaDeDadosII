#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrevistas.c"

int main() {
    Arvore_entrevistas *arvore = NULL;
    int opcao;
    char titulo[100];

    do {
        printf("\nMenu:\n");
        printf("1. Inserir nova entrevista\n");
        printf("2. Remover entrevista\n");
        printf("3. Buscar entrevista\n");
        printf("4. Listar todas as entrevistas\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Inserir nova entrevista:\n");
                Arvore_entrevistas *nova_entrevista = criar_arvore_entrevistas();
                Ler_dados_de_insercao_entrevistas(nova_entrevista);
                arvore = inserir_entrevistas(arvore, nova_entrevista);
                break;
            case 2:
                printf("Digite o título da entrevista a ser removida: ");
                scanf(" %[^\n]", titulo);
                arvore = remover_entrevista(arvore, titulo);
                break;
            case 3:
                printf("Digite o título da entrevista a ser buscada: ");
                scanf(" %[^\n]", titulo);
                Arvore_entrevistas *entrevista_encontrada = buscar_entrevistas(arvore, titulo);
                if (entrevista_encontrada != NULL) {
                    printf("Entrevista encontrada:\n");
                    mostrar_dados_entrevista(entrevista_encontrada);
                } else {
                    printf("Entrevista não encontrada.\n");
                }
                break;
            case 4:
                printf("Lista de todas as entrevistas:\n");
                imprimir_dados(arvore,0);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Por favor, escolha uma opcao valida.\n");
        }
    } while (opcao != 5);

    return 0;
}
