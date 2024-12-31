#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvbin.c"
#include "arvrb.c"
#include "unidade.c"
#include <ctype.h>

// Função para limpar caracteres indesejados
void clearCharacters(char *str)
{
    char *end;

    // Remove espaços e caracteres indesejados do final
    end = str + strlen(str) - 1;
    while (end > str && (isspace((unsigned char)*end) || *end == ';' || *end == ','))
    {
        *end = '\0';
        end--;
    }

    // Remove espaços do início
    char *start = str;
    while (*start && isspace((unsigned char)*start))
    {
        start++;
    }

    // Copia a string limpa para o início
    memmove(str, start, strlen(start) + 1);
}

void loadFile(const char *nomeArquivo, RedBlackTreePT **arvore)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[256];
    int unidadeAtual = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        // Remove o caractere de nova linha
        linha[strcspn(linha, "\n")] = 0;

        if (linha[0] == '%')
        {
            // Atualiza a unidade atual
            sscanf(linha, "%% Unidade %d", &unidadeAtual);
        }
        else
        {
            char palavraIngles[50], traducoesPortugues[200];

            // Separa a palavra em inglês e suas traduções em português
            if (sscanf(linha, "%[^:]: %[^\n]", palavraIngles, traducoesPortugues) == 2)
            {
                // Limpa a palavra em inglês
                clearCharacters(palavraIngles);

                // Divide as traduções em português
                char *traducaoPortugues = strtok(traducoesPortugues, ",;");
                while (traducaoPortugues != NULL)
                {
                    // Limpa cada tradução em português
                    clearCharacters(traducaoPortugues);

                    // Insere a palavra na árvore
                    insertPortugueseWord(arvore, traducaoPortugues, palavraIngles, unidadeAtual);

                    // Próxima tradução
                    traducaoPortugues = strtok(NULL, ",;");
                }
            }
        }
    }

    fclose(arquivo);
    printf("Arquivo '%s' carregado com sucesso!\n", nomeArquivo);
}


void exibirMenu() {
    printf("\n=================================================================\n");
    printf("                  SISTEMA DE GERENCIAMENTO DE PALAVRAS          \n");
    printf("=================================================================\n");
    printf("1 - Consultar palavras por unidade (Português e Inglês).\n");
    printf("2 - Buscar traduções em inglês para uma palavra em português.\n");
    printf("3 - Remover uma palavra em inglês de uma unidade específica.\n");
    printf("4 - Excluir uma palavra em português e suas traduções.\n");
    printf("5 - Exibir toda a estrutura da Árvore 2-3.\n");
    printf("6 - Mostrar a Árvore Binária de uma palavra em português.\n");
    printf("0 - Encerrar o programa.\n");
    printf("=================================================================\n");
    printf("Escolha uma opção: ");
}

int main() {
    RedBlackTreePT *rootNode = NULL;

    // Carregar os dados iniciais do arquivo
    loadFile("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/trabalhoEd2.txt", &rootNode);


    int opcao;
    char palavra[50];
    int unidade;
    int resultadoRemocao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n>>> Consultar palavras por unidade <<<\n");
                printf("Informe o número da unidade desejada: ");
                scanf("%d", &unidade);
                printf("\nResultado:\n");
                printWordsByUnit(rootNode, unidade);
                break;

            case 2:
                printf("\n>>> Buscar traduções em inglês <<<\n");
                printf("Digite uma palavra em português: ");
                scanf(" %[^]", palavra);
                printf("\nTraduções encontradas:\n");
                showPortugueseTranslation(&rootNode, palavra);
                break;

            case 3:
                printf("\n>>> Remover palavra em inglês de uma unidade <<<\n");
                printf("Digite a palavra em inglês: ");
                scanf("%s", palavra);
                printf("Informe a unidade: ");
                scanf("%d", &unidade);

                int totalRemovido = 0;
                removeWordByUnit(&rootNode, palavra, unidade, &totalRemovido, &rootNode);

                if (totalRemovido > 0) {
                    printf("\nPalavra '%s' removida com sucesso da unidade %d.\n", palavra, unidade);
                } else {
                    printf("\nA palavra '%s' não foi encontrada na unidade %d.\n", palavra, unidade);
                }
                break;

            case 4:
                printf("\n>>> Excluir palavra em português e traduções <<<\n");
                printf("Digite a palavra em português: ");
                scanf(" %[^]", palavra);

                resultadoRemocao = removeRBTreeNode(&rootNode, palavra);
                if (resultadoRemocao) {
                    printf("\nPalavra '%s' e suas traduções foram removidas com sucesso.\n", palavra);
                } else {
                    printf("\nA palavra '%s' não foi encontrada.\n", palavra);
                }
                break;

            case 5:
                printf("\n>>> Estrutura completa da Árvore 2-3 <<<\n");
                printf("\nÁrvore Atual:\n");
                showRedBlackTree(rootNode);
                break;

            case 6:
                printf("\n>>> Mostrar Árvore Binária de uma palavra <<<\n");
                printf("Digite a palavra em português: ");
                scanf("%s", palavra);
                printf("\nEstrutura da Árvore Binária:\n");
                exibir_arvorebianria_dada_palavra_portuguesa(rootNode, palavra);
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }

        printf("\n=================================================================\n");

    } while (opcao != 0);

    // Liberação de memória das árvores
    //freeTree(rootNode);

    return 0;
}
