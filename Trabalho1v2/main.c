#include "entrevistas.c"
#include <stdio.h>
#include <stdlib.h>

// Função para exibir o menu
void exibir_menu() {
    printf("\n===== Menu =====\n");
    printf("1. Inserir nova entrevista\n");
    printf("2. Buscar entrevista por titulo\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Raiz_entrevistas *raiz = NULL;
    Arvore_entrevistas *novo_no = NULL;
    int opcao;
    char titulo[50];

    do {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Criar um novo no e ler os dados da entrevista
                novo_no = criar_arvore_entrevistas();
                Ler_dados_de_insercao_entrevistas(novo_no);
                // Inserir a nova entrevista na arvore
                raiz = inserir_entrevistas(raiz, novo_no);
                printf("Entrevista inserida com sucesso!\n");
                break;
            case 2:
                printf("Digite o titulo da entrevista a ser buscada: ");
                scanf("%s", titulo);
                // Buscar a entrevista na arvore
                novo_no = buscar_entrevistas(raiz, titulo);
                if (novo_no != NULL) {
                    printf("Entrevista encontrada:\n");
                    printf("Titulo: %s\n", novo_no->titulos);
                    printf("Data: %s\n", novo_no->data);
                    printf("Duracao: %d\n", novo_no->duracao);
                    printf("Nome do convidado: %s\n", novo_no->nome_convidado);
                    printf("Especialidade do convidado: %s\n", novo_no->especialidade_convidado);
                } else {
                    printf("Entrevista nao encontrada.\n");
                }
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
