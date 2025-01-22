#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingles.c"
#include "portugues.c"
#include "unidade.c"
#include <ctype.h>

// Função para limpar caracteres indesejados de uma string
void clearCharacters(char *str)
{
    char *end; // Ponteiro para marcar o final da string

    // Posiciona o ponteiro 'end' no último caractere da string
    end = str + strlen(str) - 1;

    // Remove espaços em branco, ';' ou ',' do final da string
    while (end > str && (isspace((unsigned char)*end) || *end == ';' || *end == ','))
    {
        *end = '\0'; // Substitui o caractere indesejado por '\0'
        end--;       // Move o ponteiro para trás
    }

    // Ponteiro para o início da string
    char *start = str;

    // Remove espaços em branco do início da string
    while (*start && isspace((unsigned char)*start))
    {
        start++; // Move o ponteiro para o próximo caractere
    }

    // Move a parte limpa da string para o início, substituindo os espaços removidos
    memmove(str, start, strlen(start) + 1);
}

// Função para carregar dados de um arquivo e inserir em uma árvore vermelho-preta
void loadFile(const char *fileName, RedBlackTreePT **treeRef)
{
    // Abre o arquivo em modo leitura
    FILE *filePointer = fopen(fileName, "r");
    if (filePointer == NULL) // Verifica se o arquivo foi aberto com sucesso
    {
        perror("Erro ao abrir o arquivo"); // Exibe uma mensagem de erro
        return; // Retorna, já que o arquivo não pôde ser aberto
    }

    char inputLine[256]; // Buffer para armazenar linhas do arquivo
    int currentUnit = 0; // Unidade atual lida do arquivo

    // Lê o arquivo linha por linha
    while (fgets(inputLine, sizeof(inputLine), filePointer))
    {
        // Remove o caractere de nova linha ('\n') do final da string
        inputLine[strcspn(inputLine, "\n")] = 0;

        // Verifica se a linha começa com '%' (indica uma unidade)
        if (inputLine[0] == '%')
        {
            // Lê o número da unidade da linha
            sscanf(inputLine, "%% Unidade %d", &currentUnit);
        }
        else
        {
            char englishWord[50], portugueseTranslations[200]; // Buffers para palavras e traduções

            // Lê uma linha no formato "palavra: tradução1, tradução2, ..."
            if (sscanf(inputLine, "%[^:]: %[^\n]", englishWord, portugueseTranslations) == 2)
            {
                // Limpa caracteres indesejados da palavra em inglês
                clearCharacters(englishWord);

                // Divide as traduções em tokens, separadas por ',' ou ';'
                char *portugueseTranslationToken = strtok(portugueseTranslations, ",;");
                while (portugueseTranslationToken != NULL)
                {
                    // Limpa caracteres indesejados de cada tradução
                    clearCharacters(portugueseTranslationToken);

                    // Insere a tradução portuguesa na árvore
                    insertPortugueseWord(treeRef, portugueseTranslationToken, englishWord, currentUnit);

                    // Avança para o próximo token de tradução
                    portugueseTranslationToken = strtok(NULL, ",;");
                }
            }
        }
    }

    // Fecha o arquivo após o processamento
    fclose(filePointer);
}


void showMenu()
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

// Função principal do programa
int main()
{
    // Declaração do ponteiro para a raiz da árvore vermelho-preta
    RedBlackTreePT *rootNode = NULL;

    // Carrega o arquivo com palavras e traduções, inicializando a árvore
    loadFile("C:\\Users\\jorge\\OneDrive\\Documentos\\GitHub\\EstruturaDeDadosII\\dicionario.txt", &rootNode);

    int option;        // Variável para armazenar a opção escolhida pelo usuário
    char inputWord[50]; // Buffer para entrada de palavras
    int unitValue;      // Variável para armazenar o número da unidade

    // Loop principal do programa, executa até que a opção 0 (sair) seja escolhida
    do
    {
        // Exibe o menu de opções ao usuário
        showMenu();

        // Lê a opção escolhida pelo usuário
        scanf("%d", &option);

        // Executa diferentes ações com base na opção escolhida
        switch (option)
        {
        case 1: // Opção 1: Consultar palavras por unidade
            printf("\n>>> Consultar palavras por unidade <<<\n");
            printf("Informe o numero da unidade desejada: ");
            scanf("%d", &unitValue); // Lê o número da unidade
            printf("\nResultado:\n");
            printf("%% Unidade %d\n", unitValue);
            // Imprime as palavras associadas à unidade fornecida
            printWordsByUnit(rootNode, unitValue);
            break;

        case 2: // Opção 2: Buscar traduções em inglês
            printf("\n>>> Buscar traducoes em ingles <<<\n");
            printf("Digite uma palavra em portugues: ");
            // Lê uma palavra em português
            scanf(" %[^\n]", inputWord); 
            printf("\nTraducoes encontradas:\n");
            // Exibe as traduções da palavra em inglês
            showPortugueseTranslation(&rootNode, inputWord);
            break;

        case 3: // Opção 3: Remover palavra em inglês de uma unidade
            printf("\n>>> Remover palavra em ingles de uma unidade <<<\n");
            printf("Digite a palavra em ingles: ");
            // Lê a palavra em inglês
            scanf("%s", inputWord);
            printf("Informe a unidade: ");
            // Lê o número da unidade
            scanf("%d", &unitValue);

            int totalRemoved = 0; // Contador de palavras removidas
            // Remove a palavra da unidade especificada
            removeWordByUnit(&rootNode, inputWord, unitValue, &totalRemoved, &rootNode);

            // Verifica se a palavra foi removida com sucesso
            if (totalRemoved > 0)
            {
                printf("\nPalavra '%s' removida com sucesso da unidade %d.\n", inputWord, unitValue);
            }
            else
            {
                printf("\nA palavra '%s' nao foi encontrada na unidade %d.\n", inputWord, unitValue);
            }
            break;

        case 4: // Opção 4: Excluir palavra em português e suas traduções
            printf("\n>>> Excluir palavra em portugues e traducoes <<<\n");
            printf("Digite a palavra em portugues: ");
            // Lê a palavra em português
            scanf(" %[^\n]", inputWord); 

            printf("Digite a unidade à qual a palavra pertence: ");
            // Lê o número da unidade
            scanf("%d", &unitValue);

            // Remove a palavra e suas traduções associadas à unidade
            deleteWordFromTreeByUnit(&rootNode, inputWord, unitValue);

            break;

        case 0: // Opção 0: Encerrar o programa
            printf("\nEncerrando o programa...\n");
            break;

        default: // Opção inválida
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }

        // Exibe uma linha de separação após cada operação
        printf("\n=================================================================\n");

    } while (option != 0); // Continua o loop até que a opção seja 0

    // Retorna 0 para indicar que o programa foi executado com sucesso
    return 0;
}
