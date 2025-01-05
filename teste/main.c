#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv23.c"
#include "arvbin.c"
#include "remocao.c"
#include "lista_encadeada.c"

void imprimirArvore23(Portugues23 *raiz, int nivel)
{
    if (raiz == NULL)
        return; // Caso base: nó vazio

    // Indentação para representar o nível atual da árvore
    for (int i = 0; i < nivel; i++)
    {
        printf("    ");
    }

    // Imprime as informações do nó, verificando valores nulos
    printf("[");
    if (raiz->nInfos >= 1 && raiz->info1.portugueseWord != NULL)
    {
        printf(" %s ", raiz->info1.portugueseWord);
    }
    if (raiz->nInfos == 2 && raiz->info2.portugueseWord != NULL)
    {
        printf("| %s ", raiz->info2.portugueseWord);
    }
    printf("]\n");

    // Recursivamente imprime os filhos, com indentação ajustada
    if (raiz->left != NULL)
    {
        imprimirArvore23(raiz->left, nivel + 1); // Filho à esquerda
    }
    if (raiz->cent != NULL)
    {
        imprimirArvore23(raiz->cent, nivel + 1); // Filho central
    }
    if (raiz->right != NULL)
    {
        imprimirArvore23(raiz->right, nivel + 1); // Filho à direita
    }
}

void loadFile(const char *nomeArquivo, Portugues23 **arvore)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo != NULL)
    {
        char linha[256];

        char unidadeAtual[50];

        while (fgets(linha, sizeof(linha), arquivo))
        {

            if (linha[0] == '%')
            {
                // Atualiza a unidade corretamente
                sscanf(linha, "%% Unidade %[^\n]", unidadeAtual);
            }
            else
            {
                char palavraIngles[50], traducoesPortugues[200];
                sscanf(linha, "%[^:]: %[^;]", palavraIngles, traducoesPortugues);
                printf("Inserindo palavra em ingles: %s na unidade: %s\n", palavraIngles, unidadeAtual);
                char *traducaoPortugues = strtok(traducoesPortugues, ",;");
                while (traducaoPortugues != NULL)
                {
                    while (*traducaoPortugues == ' ')
                        traducaoPortugues++;

                    inserirPalavraPortugues(arvore, traducaoPortugues, palavraIngles, unidadeAtual);
                    traducaoPortugues = strtok(NULL, ",;");
                }
            }
        }

        fclose(arquivo);
        printf("Arquivo '%s' carregado com sucesso!\n", nomeArquivo);
    }
}

void menu()
{
    printf("\n------------------------------------------------------------------------------------------------- \n");
    printf("\nMenu de opcoes:\n");
    printf("1 - Informar uma unidade e imprimir todas as palavras em portugues e as equivalentes em ingles.\n");
    printf("2 - Informar uma palavra em portugues e imprimir todas as palavras em ingles equivalentes.\n");
    printf("3 - Informar uma palavra em ingles e a unidade, remove-la da arvore binaria e da arvore 2-3.\n");
    printf("4 - Informar uma palavra em portugues e a unidade, remove-la da arvore binaria e da arvore 2-3.\n");
    printf("5 - Imprimir a arvore completa\n");
    printf("6 - Imprimir a arvore 2-3 pre-ordem, em ordem e pos-ordem\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: \n");
    printf("\n------------------------------------------------------------------------------------------------- \n");
}

int main()
{
    Portugues23 *raiz = NULL;
    Portugues23 *pai = NULL;

    char palavra[50];
    char unidade[50];
    int removido;
    loadFile("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/trabalhoEd2.txt", &raiz);
    int op, res;

    do
    {
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\n--------------------------------------------------------------- \n");
            printf("Insira a unidade que deseja imprimir as palavras: ");
            while (getchar() != '\n')
                ; // Limpa o buffer antes de ler a entrada
            fgets(unidade, sizeof(unidade), stdin);

            // Remove o caractere de nova linha, se presente
            unidade[strcspn(unidade, "\n")] = '\0';

            imprimirPalavrasUnidade(raiz, unidade);
            printf("\n--------------------------------------------------------------- \n");
            break;

        case 2:
            printf("\n--------------------------------------------------------------- \n");
            printf("Insira a palavra em portugues que deseja imprimir as palavras em ingles: ");
            scanf("%s", palavra);
            exibir_traducao_Portugues(&raiz, palavra);
            printf("\n--------------------------------------------------------------- \n");
            break;
        case 3:
            printf("\n--------------------------------------------------------------- \n");
            printf("Insira a palavra em ingles que deseja remover: ");
            scanf("%s", palavra);
            printf("Insira a unidade da palavra que deseja remover: ");
            scanf("%s", unidade);
            removido = Remove_palavra_ingles_unidade(&raiz, palavra, unidade);
            if (removido)
                printf("A palavra %s foi removida com sucesso!\n\n", palavra);
            printf("\n--------------------------------------------------------------- \n");
            break;
        case 4:
            printf("\n--------------------------------------------------------------- \n");
            printf("Insira a palavra em portugues que deseja remover: ");
            while (getchar() != '\n')
                ; // Limpa o buffer antes de ler a entrada
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = '\0'; // Remove o caractere de nova linha

            printf("Insira a unidade da palavra que deseja remover: ");
            fgets(unidade, sizeof(unidade), stdin);
            unidade[strcspn(unidade, "\n")] = '\0'; // Remove o caractere de nova linha

            removido = Remove_palavra_portugues_unidade(&raiz, palavra, unidade);
            if (removido)
                printf("A palavra %s foi removida com sucesso!\n\n", palavra);
            printf("\n--------------------------------------------------------------- \n");
            break;

        case 5:
            printf("\n--------------------------------------------------------------- \n");
            printf("\nArvore 2-3 e binaria:\n");
            exibir_tree23(raiz);
            printf("\n--------------------------------------------------------------- \n");
            break;
        case 6:
            printf("\n--------------------------------------------------------------- \n");
            printf("\nArvore 2-3 pre-ordem:\n");
            arvore23_exibir_pre(raiz);
            printf("\n\nArvore 2-3 em ordem:\n");
            arvore23_exibir_ordem(raiz);
            printf("\n\nArvore 2-3 pos-ordem:\n");
            arvore23_exibir_pos(raiz);
            printf("\n--------------------------------------------------------------- \n");
            break;
        case 0:
            printf("\n--------------------------------------------------------------- \n");
            printf("Saindo do programa...\n");
            printf("\n--------------------------------------------------------------- \n");
            break;
        default:
            printf("Insira um valor valido. \n");
            break;
        }
    } while (op != 0);

    // freeTree(&raiz);

    return 0;
}