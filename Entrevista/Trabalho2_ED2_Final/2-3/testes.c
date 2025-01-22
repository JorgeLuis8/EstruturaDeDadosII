#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Para QueryPerformanceCounter e QueryPerformanceFrequency
#include "portugues.c"
#include "ingles.c"
#include "unidade.c"

// Contadores globais para monitoramento de memoria
size_t totalMemoryAllocated = 0;
size_t totalMemoryFreed = 0;

// Funcoes para monitorar alocacao e liberacao de memoria
void *monitorMalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr != NULL)
    {
        totalMemoryAllocated += size;
    }
    return ptr;
}

void monitorFree(void *ptr, size_t size)
{
    if (ptr != NULL)
    {
        free(ptr);
        totalMemoryFreed += size;
    }
}

// Função createNode com monitoramento de memória
PortugueseTree *createNode(NodeInfo *nodeInfo, PortugueseTree *leftChild, PortugueseTree *middleChild)
{
    // Aloca memória usando a função monitorada
    PortugueseTree *no = (PortugueseTree *)monitorMalloc(sizeof(PortugueseTree));
    if (no == NULL)
    {
        printf("Erro: Falha na alocacao de memoria para o no.\n");
        exit(EXIT_FAILURE);
    }

    no->info1 = *nodeInfo;        // Copia as informações do nó principal (info1).
    no->info2.englishWord = NULL; // Inicializa a informação secundária como nula.
    no->info2.portugueseWord = NULL;
    no->left = leftChild;   // Define o filho esquerdo.
    no->cent = middleChild; // Define o filho central.
    no->right = NULL;       // Inicializa o filho direito como NULL.
    no->nInfos = 1;         // Define que o nó possui apenas uma informação inicialmente.

    printf("Memoria alocada para o no: %zu bytes\n", sizeof(PortugueseTree));
    printf("Memoria total alocada ate agora: %zu bytes\n", totalMemoryAllocated);

    return no; // Retorna o ponteiro para o novo nó criado.
}

// Funcao de desalocacao da arvore com monitoramento de memoria
void deallocateTree(PortugueseTree **node)
{
    if (*node != NULL)
    {
        // Desaloca recursivamente a subárvore esquerda.
        deallocateTree(&((*node)->left));

        // Desaloca recursivamente a subárvore central.
        deallocateTree(&((*node)->cent));

        // Se o nó possui duas informações, remove a segunda e desaloca a subárvore direita.
        if ((*node)->nInfos == 2)
        {
            removeNodeInfo(&((*node)->info2)); // Supondo que esta função também libera recursos internos
            deallocateTree(&((*node)->right));
        }

        // Remove a primeira informação e libera o nó atual.
        removeNodeInfo(&((*node)->info1));          // Supondo que esta função também libera recursos internos
        monitorFree(*node, sizeof(PortugueseTree)); // Usando monitorFree para rastrear a memória liberada

        // Define o ponteiro para nulo para evitar acessos inválidos.
        *node = NULL;
    }
}

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
        // Vetor de palavras para busca
    //   char *palavrasBuscar[] = {
    //     "areia", "aviacao", "bicicleta", "cachoeira", "carro", "cidade",
    //     "cometa", "computador", "constelacao", "chuva", "deserto", "estrela",
    //     "estrela-do-mar", "floresta", "galaxia", "lua", "mar", "montanha",
    //     "neve", "nuvem", "oceano", "planeta", "planicie", "rio", "sol",
    //     "submarino", "tempo", "terra", "universo", "vento", "vulcao"
    // };
    char *palavrasBuscar[] = {
        "vulcao", "vento", "universo", "terra", "tempo", "submarino",
        "sol", "rio", "planicie", "planeta", "oceano", "nuvem",
        "neve", "montanha", "mar", "lua", "galaxia", "floresta",
        "estrela-do-mar", "estrela", "deserto", "chuva", "constelacao",
        "computador", "cometa", "cidade", "carro", "cachoeira", "bicicleta", "areia"
    };

 
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

    // Relatorio de gerenciamento de memoria
    printf("\nGerenciamento de Memoria:\n");
    printf("Total de memoria alocada: %zu bytes\n", totalMemoryAllocated);
    printf("Total de memoria liberada: %zu bytes\n", totalMemoryFreed);

    if (totalMemoryAllocated == totalMemoryFreed)
    {
        printf("Memoria gerenciada corretamente. Nenhum vazamento detectado.\n");
    }
    else
    {
        printf("Atencao: Vazamento de memoria detectado! (%zu bytes nao liberados)\n",
               totalMemoryAllocated - totalMemoryFreed);
    }

    // Liberar memoria
    printf("\nLimpando memoria...\n");
    deallocateTree(&arvore);
    printf("Memoria liberada.\n");

    return 0;
}
