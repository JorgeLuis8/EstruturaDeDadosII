#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arv23.c"
#include "arvbin.c"
#include "unidade.c"
#include <windows.h> // Para QueryPerformanceCounter e QueryPerformanceFrequency

// Função para limpar caracteres indesejados
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

// Função para carregar o arquivo de dados
void loadFile(const char *nomeArquivo, PortugueseTree **arvore)
{
    FILE *dataFile = fopen(nomeArquivo, "r");

    if (dataFile != NULL)
    {
        char inputLine[256];
        int currentUnit = -1; // Inicia com um valor inválido

        while (fgets(inputLine, sizeof(inputLine), dataFile))
        {
            inputLine[strcspn(inputLine, "\n")] = 0; // Remove o caractere de nova linha

            if (inputLine[0] == '%')
            {
                // Verifica a linha de unidade e extrai o número
                if (sscanf(inputLine, "%% Unidade %d", &currentUnit) != 1)
                {
                    currentUnit = -1; // Reseta para inválido
                }
            }
            else if (currentUnit != -1)
            {
                // Processa linhas de palavras e traduções
                char englishWord[50], portugueseTranslations[200];

                if (sscanf(inputLine, "%[^:]: %[^\n]", englishWord, portugueseTranslations) == 2)
                {
                    clearCharacters(englishWord); // Limpa caracteres indesejados

                    // Divide as traduções em português separadas por vírgula
                    char *currentPortugueseTranslation = strtok(portugueseTranslations, ",");
                    while (currentPortugueseTranslation != NULL)
                    {
                        while (*currentPortugueseTranslation == ' ')
                        {
                            currentPortugueseTranslation++; // Remove espaços no início
                        }

                        clearCharacters(currentPortugueseTranslation); // Limpa caracteres indesejados
                        insertPortugueseTerm(arvore, currentPortugueseTranslation, englishWord, currentUnit);

                        currentPortugueseTranslation = strtok(NULL, ",");
                    }
                }
            }
        }

        fclose(dataFile);
    }
}

// Função para encontrar uma palavra e exibir o caminho
void printPathAndFindWord(PortugueseTree **tree, const char *word)
{
    PortugueseTree *currentNode = *tree;
    int found = 0;
    char caminho[1024] = ""; // String para armazenar o caminho

    while (currentNode != NULL && !found)
    {
        if (strcmp(word, currentNode->info1.portugueseWord) == 0)
        {
            found = 1;
        }
        else if (currentNode->nInfos == 2 && strcmp(word, currentNode->info2.portugueseWord) == 0)
        {
            found = 1;
        }
        else
        {
            if (strcmp(word, currentNode->info1.portugueseWord) < 0)
            {
                strcat(caminho, "Esquerda -> ");
                currentNode = currentNode->left;
            }
            else if (currentNode->nInfos == 1 || strcmp(word, currentNode->info2.portugueseWord) < 0)
            {
                strcat(caminho, "Centro -> ");
                currentNode = currentNode->cent;
            }
            else
            {
                strcat(caminho, "Direita -> ");
                currentNode = currentNode->right;
            }
        }
    }

    if (found)
    {
        // Remover a última " -> " do caminho
        if (strlen(caminho) > 0)
            caminho[strlen(caminho) - 4] = '\0';

        printf("Palavra encontrada.\n");
        printf("Caminho percorrido: %s\n", caminho);
    }
    else
    {
        strcat(caminho, "NULL"); // Adiciona "NULL" ao final do caminho
        printf("Palavra nao encontrada.\n");
        printf("Caminho percorrido: %s\n", caminho);
    }
}

// Função principal
int main()
{
    PortugueseTree *arvore = NULL;

    // Carregar dados do arquivo
    const char *nomeArquivo = "C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/text.txt"; // Altere para o nome real do arquivo
    loadFile(nomeArquivo, &arvore);

    // Lista de palavras para busca
    const char *palavras[] = {
        "carro", "automovel", "erro", "engano", "roda", "ventilador", "soprador",
        "teia", "conexao", "estrutura", "organizacao", "cadeado", "fruta",
        "memoria", "companheiro", "documento", "esfera", "fio", "dispositivo",
        "vidro", "escrivaninha", "cursor", "acordo", "estrela", "mar", "rio",
        "cachoeira", "tempo", "vento", "chuva"};

    int numPalavras = sizeof(palavras) / sizeof(palavras[0]);

    printf("Realizando buscas por %d palavras\n\n", numPalavras);

    LARGE_INTEGER frequency, startTime, endTime;
    QueryPerformanceFrequency(&frequency); // Obtém a frequência do contador de alta precisão

    double totalTime = 0;

    // Buscar cada palavra e medir o tempo em nanosegundos
    for (int i = 0; i < numPalavras; i++)
    {
        printf("Palavra: %s\n", palavras[i]);

        QueryPerformanceCounter(&startTime);
        printPathAndFindWord(&arvore, palavras[i]);
        QueryPerformanceCounter(&endTime);

        double elapsedTime = (double)(endTime.QuadPart - startTime.QuadPart) * 1e9 / frequency.QuadPart; // Em nanosegundos
        totalTime += elapsedTime;

        printf("Tempo de busca: %.2f ns\n\n", elapsedTime); // Exibir o tempo em nanosegundos
    }

    printf("Tempo total para buscar %d palavras: %.2f ns\n", numPalavras, totalTime);
    printf("Tempo medio por palavra: %.2f ns\n", totalTime / numPalavras);

    // Liberar memória
    deallocateTree(&arvore);

    return 0;
}
