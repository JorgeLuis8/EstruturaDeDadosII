#include "temas.c"
#include "entrevistas.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    Arvore_temas *raiz_temas = NULL;

    // Menu principal
    int escolha;
    char tema[50];

    do
    {
        printf("\n====== Menu ======\n");
        printf("1. Inserir tema\n");
        printf("2. Inserir entrevista\n");
        printf("3. Imprimir \n");
        printf("4. Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        getchar(); 

        switch (escolha)
        {
        case 1:
            // Inserir tema
            printf("Digite o tema: ");
            fgets(tema, sizeof(tema), stdin);
            tema[strcspn(tema, "\n")] = 0; // Remova o caractere de nova linha do final
            Arvore_temas *novo_tema = criar_arvore_temas();
            strcpy(novo_tema->tema, tema);
            raiz_temas = inserir_temas(raiz_temas, novo_tema);
            break;
        case 2:
            // Inserir entrevista
            printf("Digite o tema relacionado a entrevista: ");
            fgets(tema, sizeof(tema), stdin);
            tema[strcspn(tema, "\n")] = 0; // Remova o caractere de nova linha do final
            Arvore_temas *tema_encontrado = Busca_arv(raiz_temas, tema);
            if (tema_encontrado != NULL)
            {
                Arvore_entrevistas *nova_entrevista = criar_arvore_entrevistas();
                Ler_dados_de_insercao_entrevistas(nova_entrevista);
                tema_encontrado->entrevistas = inserir_entrevistas(tema_encontrado->entrevistas, nova_entrevista);
                printf("Entrevista relacionada ao tema '%s' adicionada com sucesso.\n", tema);
            }
            else
            {
                printf("Tema '%s' nao encontrado.\n", tema);
            }
            break;
        case 3:
        {
            printf("Informe o tema: ");
            fgets(tema, sizeof(tema), stdin);
            tema[strcspn(tema, "\n")] = 0; // Remova o caractere de nova linha do final
            if (raiz_temas != NULL)
            {
                imprimir_entrevistas_tema(raiz_temas, tema);
            }
            else
            {
                printf("A arvore de temas esta vazia.\n");
            }
            break;
        }
        case 4:
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Escolha invalida. Tente novamente.\n");
        }
    } while (escolha != 4);

    return 0;
}
