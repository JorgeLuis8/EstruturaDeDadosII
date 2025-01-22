#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Para QueryPerformanceCounter e QueryPerformanceFrequency
#include "portugues.c"
#include "ingles.c"
#include "unidade.c"

// Funcao para embaralhar as palavras (para ordem aleatoria)
void shuffle(char *array[], int n)
{
    srand((unsigned)time(NULL)); // Inicializar semente aleatoria
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Funcao para imprimir o caminho percorrido ate encontrar a palavra
void printPathToWord(PortugueseTree **root, const char *word)
{
    PortugueseTree *currentNode = *root;

    while (currentNode != NULL)
    {
        if (strcmp(word, currentNode->info1.portugueseWord) == 0)
        {
            printf("info1 -> ");
            break;
        }
        else if (currentNode->nInfos == 2 && strcmp(word, currentNode->info2.portugueseWord) == 0)
        {
            printf("info2 -> ");
            break;
        }

        if (strcmp(word, currentNode->info1.portugueseWord) < 0)
        {
            printf("left -> ");
            currentNode = currentNode->left;
        }
        else if (currentNode->nInfos == 1 || strcmp(word, currentNode->info2.portugueseWord) < 0)
        {
            printf("cent -> ");
            currentNode = currentNode->cent;
        }
        else
        {
            printf("right -> ");
            currentNode = currentNode->right;
        }
    }

    if (currentNode == NULL)
    {
        printf("NULL");
    }
}

int main()
{
    PortugueseTree *arvore = NULL;

    // Lista de palavras original
    char *palavras[] = {
        "carro", "automovel", "erro", "engano", "roda", "ventilador", "soprador",
        "teia", "conexao", "estrutura", "organizacao", "cadeado", "fruta",
        "memoria", "companheiro", "documento", "esfera", "fio", "dispositivo",
        "vidro", "escrivaninha", "cursor", "acordo", "estrela", "mar", "rio",
        "cachoeira", "tempo", "vento", "chuva"};
    int numPalavras = sizeof(palavras) / sizeof(palavras[0]);

    // Escolher a ordem
    printf("Escolha a ordem das palavras para busca:\n");
    printf("1 - Ordem alfabetica (A-Z)\n");
    printf("2 - Ordem decrescente (Z-A)\n");
    printf("3 - Ordem aleatoria\n");
    int escolha;
    scanf("%d", &escolha);

    // Ajustar a ordem com base na escolha
    if (escolha == 1)
    {
        printf("Ordem alfabetica (A-Z) selecionada.\n");
        qsort(palavras, numPalavras, sizeof(char *), (int (*)(const void *, const void *))strcmp);
    }
    else if (escolha == 2)
    {
        printf("Ordem decrescente (Z-A) selecionada.\n");
        qsort(palavras, numPalavras, sizeof(char *), (int (*)(const void *, const void *))strcmp);
        // Inverter a ordem para Z-A
        for (int i = 0; i < numPalavras / 2; i++)
        {
            char *temp = palavras[i];
            palavras[i] = palavras[numPalavras - i - 1];
            palavras[numPalavras - i - 1] = temp;
        }
    }
    else if (escolha == 3)
    {
        printf("Ordem aleatoria selecionada.\n");
        shuffle(palavras, numPalavras);
    }
    else
    {
        printf("Escolha invalida. Usando ordem original.\n");
    }

    // Inserir palavras na arvore 2-3
    printf("\nInserindo palavras na arvore 2-3...\n");
    for (int i = 0; i < numPalavras; i++)
    {
        insertPortugueseTerm(&arvore, palavras[i], "english_translation", i % 3 + 1);
    }
    printf("Palavras inseridas com sucesso.\n\n");

char *palavrasBuscar[] = {
    "areia", "aviacao", "bicicleta", "cachoeira", "carro", "cidade",
    "cometa", "computador", "constelacao", "chuva", "deserto", "estrela",
    "estrela-do-mar", "floresta", "galaxia", "lua", "mar", "montanha",
    "neve", "nuvem", "oceano", "planeta", "planicie", "rio", "sol",
    "submarino", "tempo", "terra", "universo", "vento", "vulcao"
};
// char *palavrasBuscar[] = {
//     "vulcao", "vento", "universo", "terra", "tempo", "submarino",
//     "sol", "rio", "planicie", "planeta", "oceano", "nuvem",
//     "neve", "montanha", "mar", "lua", "galaxia", "floresta",
//     "estrela-do-mar", "estrela", "deserto", "chuva", "constelacao",
//     "computador", "cometa", "cidade", "carro", "cachoeira", "bicicleta", "areia"
// };

// char *palavrasBuscar[] = {
//     "cachoeira", "planicie", "bicicleta", "universo", "lua", "vento",
//     "estrela", "mar", "cometa", "submarino", "chuva", "galaxia",
//     "computador", "planeta", "cidade", "constelacao", "montanha", "areia",
//     "vulcao", "tempo", "terra", "rio", "estrela-do-mar", "floresta",
//     "aviacao", "nuvem", "carro", "deserto", "neve", "oceano"
// };


    int numBuscar = sizeof(palavrasBuscar) / sizeof(palavrasBuscar[0]);

    // Realizando as buscas
    printf("Realizando buscas na ordem escolhida:\n\n");

    LARGE_INTEGER frequency, startTime, endTime;
    QueryPerformanceFrequency(&frequency); // Obtem a frequencia do contador de alta precisao
    double totalTime = 0;

    for (int i = 0; i < numBuscar; i++)
    {
        printf("Palavra: %s\n", palavrasBuscar[i]);
        QueryPerformanceCounter(&startTime);
        PortugueseTree *foundNode = FindWord(&arvore, palavrasBuscar[i]);

        printf("Caminho percorrido: ");
        printPathToWord(&arvore, palavrasBuscar[i]);
        if (foundNode != NULL)
        {
            printf("\nPalavra encontrada.\n");
        }
        else
        {
            printf("\nPalavra nao encontrada.\n");
        }

        QueryPerformanceCounter(&endTime);

        double elapsedTime = (double)(endTime.QuadPart - startTime.QuadPart) * 1e9 / frequency.QuadPart; // Em nanosegundos
        totalTime += elapsedTime;

        printf("Tempo de busca: %.2f ns\n\n", elapsedTime);
    }

    printf("Tempo total para buscar palavras: %.2f ns\n", totalTime);
    printf("Tempo medio por palavra: %.2f ns\n", totalTime / numBuscar);

    // Liberar memoria
    printf("\nLimpando memoria...\n");
    deallocateTree(&arvore);
    printf("Memoria liberada.\n");

    return 0;
}
