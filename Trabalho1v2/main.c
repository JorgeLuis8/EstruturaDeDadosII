#include "entrevistas.c"
#include "temas.c"
#include <stdio.h>
#include <stdlib.h>

// Função para exibir o menu
void exibir_menu()
{
    printf("\n===== Menu =====\n");
    printf("1. Inserir nova entrevista\n");
    printf("2. Buscar entrevista por titulo\n");
    printf("3. Imprimir melhor entrevista\n");
    printf("4. Inserir novo tema\n");
    printf("5. Buscar tema\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Raiz_entrevistas *raiz = criar_raiz_entrevistas();
    Arvore_entrevistas *novo_no = NULL;

    Raiz_temas *raiz_temas = criar_raiz_temas();
    Arvore_temas *novo_tema = NULL;
    int opcao;
    char titulo[50];

    do
    {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // Criar um novo no e ler os dados da entrevista
            novo_no = criar_arvore_entrevistas();
            Ler_dados_de_insercao_entrevistas(novo_no);
            // Inserir a nova entrevista na arvore
            inserir_arvore(raiz, novo_no);

            printf("Entrevista inserida com sucesso!\n");
            break;
        case 2:
            printf("Digite o titulo da entrevista a ser buscada: ");
            scanf("%s", titulo);
            // Buscar a entrevista na arvore
            novo_no = arvore_busca(raiz, titulo);
            if (novo_no != NULL)
            {
                printf("Entrevista encontrada:\n");
                printf("raiz: %s\n", raiz->raiz->titulos);
                printf("Titulo: %s\n", novo_no->titulos);
                printf("Data: %s\n", novo_no->data);
                printf("Duracao: %d\n", novo_no->duracao);
                printf("Nome do convidado: %s\n", novo_no->nome_convidado);
                printf("Especialidade do convidado: %s\n", novo_no->especialidade_convidado);
            }
            else
            {
                printf("Entrevista nao encontrada.\n");
            }
            break;
        case 3:
            imprimir_arvore(raiz);
            break;
        case 4:
            novo_tema = criar_arvore_temas();
            Ler_dados_de_insercao_temas(novo_tema);
            inserir_arvore_temas(raiz_temas, novo_tema);
            break;
        case 5:
            printf("Digite o tema a ser buscado: ");
            scanf("%s", titulo);
            printf("Raiz: %s\n", raiz_temas->raiz->tema);
            novo_tema = buscar_temas(raiz_temas->raiz, titulo);
            if (novo_tema != NULL)
            {
                printf("Tema encontrado: %s\n", novo_tema->tema);
            }
            else
            {
                printf("Tema não encontrado.\n");
            }
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao);

    return 0;
}
