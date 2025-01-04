#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arv23.c"
#include "arvbin.c"
#include "unidade.c"

void clearCharacters(char *str)
{
    char *end = str + strlen(str) - 1;

    while (end > str && (*end == ';' || isspace((unsigned char)*end)))
    {
        *end = '\0';
        end--;
    }

    while (*str && isspace((unsigned char)*str))
    {
        str++;
    }
}

void carregarArquivo(const char *nomeArquivo, Portugues23 **arvore)
{
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo != NULL)
    {
        char linha[256];
        int unidadeAtual = -1; // Inicia com um valor inválido

        while (fgets(linha, sizeof(linha), arquivo))
        {
            linha[strcspn(linha, "\n")] = 0; // Remove o caractere de nova linha

            if (linha[0] == '%')
            {
                // Verifica a linha de unidade e extrai o número
                if (sscanf(linha, "%% Unidade %d", &unidadeAtual) != 1)
                {
                    unidadeAtual = -1; // Reseta para inválido
                }
            }
            else if (unidadeAtual != -1)
            {
                // Processa linhas de palavras e traduções
                char palavraIngles[50], traducoesPortugues[200];

                if (sscanf(linha, "%[^:]: %[^\n]", palavraIngles, traducoesPortugues) == 2)
                {
                    clearCharacters(palavraIngles); // Limpa caracteres indesejados

                    // Divide as traduções em português separadas por vírgula
                    char *traducaoPortugues = strtok(traducoesPortugues, ",");
                    while (traducaoPortugues != NULL)
                    {
                        while (*traducaoPortugues == ' ')
                        {
                            traducaoPortugues++; // Remove espaços no início
                        }

                        clearCharacters(traducaoPortugues); // Limpa caracteres indesejados
                        insertPortugueseTerm(arvore, traducaoPortugues, palavraIngles, unidadeAtual);

                        traducaoPortugues = strtok(NULL, ",");
                    }
                }
            }
        }

        fclose(arquivo);
    }
}


void menu()
{
    printf("\n===============================================================\n");
    printf("                         MENU DE OPCOES                       \n");
    printf("===============================================================\n");
    printf("[1] Exibir palavras e traducoes (por unidade)\n");
    printf("[2] Buscar traducoes de uma palavra em portugues\n");
    printf("[3] Remover palavra em ingles de uma unidade\n");
    printf("[4] Remover palavra em portugues de uma unidade\n");
    printf("[0] Sair\n");
    printf("===============================================================\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Portugues23 *raiz = NULL;
    Portugues23 *pai = NULL;

    char palavra[50];
    int unidade;
    int op;

    // Carrega o arquivo inicial
    carregarArquivo("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/text.txt", &raiz);

    // Loop do menu principal
    do
    {
        menu();
        printf(">> "); // Indicador de entrada
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\n---------------------------------------------------------------\n");
            printf("Informe a unidade para exibir as palavras e suas traducoes: ");
            scanf("%d", &unidade);

            int unidadeImpressa = 0;
            printFormattedWordsByUnit(raiz, unidade, &unidadeImpressa);

            if (!unidadeImpressa)
            {
                printf("Nenhuma palavra encontrada para a unidade %d.\n", unidade);
            }
            printf("---------------------------------------------------------------\n");
            break;

        case 2:
            printf("\n---------------------------------------------------------------\n");
            printf("Digite a palavra em portugues para buscar as equivalentes em ingles: ");
            scanf(" %[^\n]", palavra); // Lê uma linha inteira

            printAllTranslations(raiz, palavra);
            printf("---------------------------------------------------------------\n");
            break;

        case 3:
            printf("\n---------------------------------------------------------------\n");
            printf("Digite a palavra em ingles para remover: ");
            scanf(" %[^\n]", palavra);
            printf("Informe a unidade associada: ");
            scanf("%d", &unidade);

            removeEnglishTranslation(&raiz, palavra, unidade, &pai);

            printf("\nPalavra '%s' removida com sucesso da unidade %d.\n", palavra, unidade);
            printf("---------------------------------------------------------------\n");
            break;

        case 4:
            printf("\n---------------------------------------------------------------\n");
            printf("Digite a palavra em portugues para remover: ");
            scanf(" %[^\n]", palavra);
            printf("Informe a unidade associada: ");
            scanf("%d", &unidade);

            if (Remove_word_from_portuguese_unit(&raiz, palavra, unidade))
            {
                printf("\nPalavra '%s' removida com sucesso da unidade %d.\n", palavra, unidade);
            }
            else
            {
                printf("\nFalha ao remover a palavra '%s' da unidade %d.\n", palavra, unidade);
            }
            printf("---------------------------------------------------------------\n");
            break;

        case 0:
            printf("\n===============================================================\n");
            printf("Saindo do programa... Ate logo!\n");
            printf("===============================================================\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }
    } while (op != 0);

    deallocateTree(&raiz);

    return 0;
}
