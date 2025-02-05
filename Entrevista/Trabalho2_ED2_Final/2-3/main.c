#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "portugues.c"
#include "ingles.c"
#include "unidade.c"

// Função para limpar caracteres indesejados (espaços ou ';') de uma string
void clearCharacters(char *str)
{
    // Ponteiro para o final da string
    char *end = str + strlen(str) - 1;

    // Remove caracteres como ';' ou espaços do final da string
    while (end > str && (*end == ';' || isspace((unsigned char)*end)))
    {
        *end = '\0'; // Substitui o caractere por um terminador de string
        end--;       // Move o ponteiro para o caractere anterior
    }

    // Remove espaços do início da string
    while (*str && isspace((unsigned char)*str))
    {
        str++; // Avança o ponteiro até encontrar o primeiro caractere não espaço
    }
}

// Função para carregar dados de um arquivo e preenchê-los em uma árvore de termos em português
void loadFile(const char *nomeArquivo, PortugueseTree **arvore)
{
    // Abre o arquivo em modo leitura
    FILE *dataFile = fopen(nomeArquivo, "r");

    if (dataFile != NULL) // Verifica se o arquivo foi aberto com sucesso
    {
        char inputLine[256]; // Buffer para armazenar linhas lidas do arquivo
        int currentUnit = -1; // Unidade atual, inicialmente indefinida

        // Lê o arquivo linha por linha
        while (fgets(inputLine, sizeof(inputLine), dataFile))
        {
            inputLine[strcspn(inputLine, "\n")] = 0; // Remove o caractere de nova linha ('\n') da string

            // Identifica linhas que representam unidades (começam com '%')
            if (inputLine[0] == '%')
            {
                // Extrai o número da unidade e atualiza a variável currentUnit
                if (sscanf(inputLine, "%% Unidade %d", &currentUnit) != 1)
                {
                    currentUnit = -1; // Define unidade como inválida se a leitura falhar
                }
            }
            // Processa linhas com termos somente se a unidade atual for válida
            else if (currentUnit != -1)
            {
                char englishWord[50], portugueseTranslations[200]; // Buffers para palavras em inglês e traduções em português

                // Divide a linha em palavra em inglês e traduções em português
                if (sscanf(inputLine, "%[^:]: %[^\n]", englishWord, portugueseTranslations) == 2)
                {
                    clearCharacters(englishWord); // Limpa caracteres indesejados da palavra em inglês

                    // Divide as traduções em português separadas por vírgulas
                    char *currentPortugueseTranslation = strtok(portugueseTranslations, ",");
                    while (currentPortugueseTranslation != NULL) // Processa cada tradução
                    {
                        // Remove espaços iniciais da tradução
                        while (*currentPortugueseTranslation == ' ')
                        {
                            currentPortugueseTranslation++;
                        }

                        clearCharacters(currentPortugueseTranslation); // Limpa caracteres indesejados da tradução

                        // Insere o termo português na árvore
                        insertPortugueseTerm(arvore, currentPortugueseTranslation, englishWord, currentUnit);

                        // Avança para a próxima tradução
                        currentPortugueseTranslation = strtok(NULL, ",");
                    }
                }
            }
        }

        fclose(dataFile); // Fecha o arquivo após processar todas as linhas
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
    // Declara a raiz da árvore binária de termos em português
    PortugueseTree *rootNode = NULL;
    PortugueseTree *parentNode = NULL; // Declara o nó pai auxiliar para remoção

    char userInput[50]; // Buffer para entrada de palavras do usuário
    int unit; // Variável para armazenar o número da unidade
    int option; // Variável para armazenar a opção do menu

    // Carrega o arquivo de palavras e popula a árvore binária
    loadFile("C:\\Users\\jorge\\OneDrive\\Documentos\\GitHub\\EstruturaDeDadosII\\Entrevista\\Trabalho2_ED2_Final\\dicionario.txt", &rootNode);

    do
    {
        menu(); // Exibe o menu de opções para o usuário
        printf(">> "); 
        scanf("%d", &option); // Lê a opção escolhida pelo usuário

        switch (option) // Processa a opção escolhida
        {
        case 1: // Exibir palavras e suas traduções por unidade
            printf("\n---------------------------------------------------------------\n");
            printf("Informe a unidade para exibir as palavras e suas traducoes: ");
            scanf("%d", &unit); // Lê a unidade fornecida pelo usuário

            int hasUnitBeenPrinted = 0; // Variável para verificar se alguma palavra foi impressa
            printFormattedWordsByUnit(rootNode, unit, &hasUnitBeenPrinted); // Exibe as palavras da unidade

            if (!hasUnitBeenPrinted) // Caso nenhuma palavra tenha sido encontrada para a unidade
            {
                printf("Nenhuma palavra encontrada para a unidade %d.\n", unit);
            }
            printf("---------------------------------------------------------------\n");
            break;

        case 2: // Buscar traduções para uma palavra em português
            printf("\n---------------------------------------------------------------\n");
            printf("Digite a palavra em portugues para buscar as equivalentes em ingles: ");
            scanf(" %[^\n]", userInput); // Lê a palavra em português

            printAllTranslations(rootNode, userInput); // Exibe todas as traduções da palavra
            printf("---------------------------------------------------------------\n");
            break;

        case 3: // Remover uma palavra em inglês de uma unidade
            printf("\n---------------------------------------------------------------\n");
            printf("Digite a palavra em ingles para remover: ");
            scanf(" %[^\n]", userInput); // Lê a palavra em inglês
            printf("Informe a unidade associada: ");
            scanf("%d", &unit); // Lê a unidade fornecida pelo usuário

            // Remove a palavra em inglês da árvore na unidade especificada
            removeEnglishTranslation(&rootNode, userInput, unit, &parentNode);
            printf("\nPalavra '%s' removida com sucesso da unidade %d.\n", userInput, unit);
            printf("---------------------------------------------------------------\n");
            break;

        case 4: // Remover uma palavra em português de uma unidade
            printf("\n---------------------------------------------------------------\n");
            printf("Digite a palavra em portugues para remover: ");
            scanf(" %[^\n]", userInput); // Lê a palavra em português
            printf("Informe a unidade associada: ");
            scanf("%d", &unit); // Lê a unidade fornecida pelo usuário

            // Remove a palavra em português da árvore na unidade especificada
            if (Remove_word_from_portuguese_unit(&rootNode, userInput, unit))
            {
                printf("\nPalavra '%s' removida com sucesso da unidade %d.\n", userInput, unit);
            }
            else
            {
                printf("\nFalha ao remover a palavra '%s' da unidade %d.\n", userInput, unit);
            }
            printf("---------------------------------------------------------------\n");
            break;

        case 0: // Sair do programa
            printf("\n===============================================================\n");
            printf("Saindo do programa... Ate logo!\n");
            printf("===============================================================\n");
            break;

        default: // Caso o usuário insira uma opção inválida
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }
    } while (option != 0); // Continua no loop enquanto a opção não for 0 (sair)

    //deallocateTree(&rootNode); // Libera a memória da árvore antes de sair

    return 0; // Encerra o programa com sucesso
}
