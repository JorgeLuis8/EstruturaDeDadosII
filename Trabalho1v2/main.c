#include "entrevistas.c"
#include "temas.c"
#include <stdio.h>
#include <stdlib.h>

void exibirMenu()
{
    printf("\n--- MENU ---\n");
    printf("1. Inserir Tema\n");
    printf("2. Inserir Entrevista\n");
    printf("3. Buscar Entrevista\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Arvore_temas *raiz_temas = NULL;
    Arvore_entrevistas *raiz_entrevistas = NULL;
    int opcao;

    do
    {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            {
                Arvore_temas *novo_tema = criar_arvore_temas();
                lerDados(novo_tema);
                raiz_temas = inserir_temas(raiz_temas, novo_tema, raiz_entrevistas);
                printf("Tema inserido com sucesso!\n");
                break;
            }
        case 2:
            {
                char tema[50];
                printf("Digite o tema relacionado a entrevista: ");
                scanf("%s", tema);
                Arvore_temas *tema_encontrado = Busca_arv(raiz_temas, tema);
                if (tema_encontrado != NULL)
                {
                    Arvore_entrevistas *nova_entrevista = (Arvore_entrevistas *)malloc(sizeof(Arvore_entrevistas));
                    Ler_dados_de_insercao_entrevistas(nova_entrevista);
                    tema_encontrado->entrevistas = inserir_entrevistas(tema_encontrado->entrevistas, nova_entrevista);
                    printf("Entrevista relacionada ao tema '%s' inserida com sucesso!\n", tema);
                }
                else
                {
                    printf("Tema nao encontrado.\n");
                }
                break;
            }
        case 3:
            {
                char titulo[50];
                printf("Digite o titulo da entrevista que deseja buscar: ");
                scanf("%s", titulo);
                Arvore_entrevistas *entrevista_encontrada = buscar_entrevistas(raiz_entrevistas, titulo);
                if (entrevista_encontrada != NULL)
                {
                    printf("Entrevista encontrada:\n");
                    printf("Titulo: %s\n", entrevista_encontrada->titulos);
                    printf("Data: %s\n", entrevista_encontrada->data);
                    printf("Duracao: %d\n", entrevista_encontrada->duracao);
                    printf("Nome do convidado: %s\n", entrevista_encontrada->nome_convidado);
                    printf("Especialidade do convidado: %s\n", entrevista_encontrada->especialidade_convidado);
                }
                else
                {
                    printf("Entrevista nao encontrada.\n");
                }
                break;
            }
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 4);

    return 0;
}