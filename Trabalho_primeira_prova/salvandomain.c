#include "entrevistas.c"
#include <stdlib.h>
#include <stdio.h>
 
void exibir_menu() {
    printf("\nMenu:\n");
    printf("1. Inserir entrevista\n");
    printf("2. Buscar entrevista\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
}
 
int main() {
    Arvore_entrevistas *raiz = NULL;
    int opcao;
    char titulo[50];
 
    do {
        exibir_menu();
        scanf("%d", &opcao);
 
        switch(opcao) {
            case 1:
                printf("\nInserir uma nova entrevista:\n");
                Arvore_entrevistas *nova_entrevista = criar_arvore_entrevistas();
                Ler_dados_de_insercao_entrevistas(nova_entrevista);
                raiz = inserir_entrevistas(raiz, nova_entrevista);
                printf("Entrevista inserida com sucesso!\n");
                break;
            case 2:
                printf("\nBuscar uma entrevista:\n");
                printf("Digite o titulo da entrevista: ");
                scanf("%s", titulo);
                Arvore_entrevistas *entrevista_encontrada = buscar_entrevistas(raiz, titulo);
                if (entrevista_encontrada != NULL) {
                    printf("Entrevista encontrada:\n");
                    printf("Titulo: %s\n", entrevista_encontrada->titulos);
                    printf("Data: %s\n", entrevista_encontrada->data);
                    printf("Duracao: %s\n", entrevista_encontrada->duracao);
                    printf("Nome do convidado: %s\n", entrevista_encontrada->nome_convidado);
                    printf("Especialidade do convidado: %s\n", entrevista_encontrada->especialidade_convidado);
                } else {
                    printf("Entrevista nao encontrada.\n");
                }
                break;
            case 3:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 3);
 
    return 0;
}