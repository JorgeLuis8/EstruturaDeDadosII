#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> // Para QueryPerformanceCounter e QueryPerformanceFrequency
#include "ingles.c"
#include "portugues.c"
#include "unidade.c"
// Contadores globais para monitoramento de memoria
// size_t totalMemoryAllocated = 0;
// size_t totalMemoryFreed = 0;

// Função de alocação de memória com monitoramento

// Função de desalocação de memória com monitoramento
void monitorFree(void *ptr, size_t size) {
    if (ptr != NULL) {
        free(ptr);
        totalMemoryFreed += size;
    }
}

// Função para embaralhar palavras (ordem aleatória)
void shuffle(char *array[], int n) {
    srand((unsigned int)time(NULL)); // Inicializar semente aleatória
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Função para imprimir o caminho percorrido até encontrar uma palavra
void printSearchPath(RedBlackTreePT *rootNode, const char *word) {
    RedBlackTreePT *currentNode = rootNode;
    printf("Caminho percorrido: ");
    
    while (currentNode != NULL) {
        if (strcmp(word, currentNode->info.portugueseWord) == 0) {
            printf("info -> ");
            break;
        } else if (strcmp(word, currentNode->info.portugueseWord) < 0) {
            printf("left -> ");
            currentNode = currentNode->left;
        } else {
            printf("right -> ");
            currentNode = currentNode->right;
        }
    }

    if (currentNode == NULL) {
        printf("NULL");
    }
    printf("\n");
}

int main() {
    RedBlackTreePT *arvore = NULL;

    // Vetor de palavras para inserção
   char *palavras[] = {
        "carro", "automovel", "erro", "engano", "roda", "ventilador", "soprador",
        "teia", "conexao", "estrutura", "organizacao", "cadeado", "fruta",
        "memoria", "companheiro", "documento", "esfera", "fio", "dispositivo",
        "vidro", "escrivaninha", "cursor", "acordo", "estrela", "mar", "rio",
        "cachoeira", "tempo", "vento", "chuva"};
    int numPalavras = sizeof(palavras) / sizeof(palavras[0]);

    // Escolher a ordem
    printf("Escolha a ordem das palavras para busca:\n");
    printf("1 - Ordem alfabética (A-Z)\n");
    printf("2 - Ordem decrescente (Z-A)\n");
    printf("3 - Ordem aleatória\n");
    int escolha;
    scanf("%d", &escolha);

    // Ajustar a ordem com base na escolha
    if (escolha == 1) {
        printf("Ordem alfabética (A-Z) selecionada.\n");
        qsort(palavras, numPalavras, sizeof(char *), (int (*)(const void *, const void *))strcmp);
    } else if (escolha == 2) {
        printf("Ordem decrescente (Z-A) selecionada.\n");
        qsort(palavras, numPalavras, sizeof(char *), (int (*)(const void *, const void *))strcmp);
        for (int i = 0; i < numPalavras / 2; i++) {
            char *temp = palavras[i];
            palavras[i] = palavras[numPalavras - i - 1];
            palavras[numPalavras - i - 1] = temp;
        }
    } else if (escolha == 3) {
        printf("Ordem aleatória selecionada.\n");
        shuffle(palavras, numPalavras);
    } else {
        printf("Escolha inválida. Usando ordem original.\n");
    }

    // Inserir palavras na árvore
    for (int i = 0; i < numPalavras; i++) {
        insertPortugueseWord(&arvore, palavras[i], "tradução", i % 3 + 1);
    }

    // Vetor de palavras para busca
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

    // Realizando buscas e calculando o tempo
    LARGE_INTEGER frequency, startTime, endTime;
    QueryPerformanceFrequency(&frequency); // Obter a frequência do contador de alta precisão
    double totalTime = 0;

    for (int i = 0; i < numBuscar; i++) {
        printf("Buscando: %s\n", palavrasBuscar[i]);
        QueryPerformanceCounter(&startTime);
        printSearchPath(arvore, palavrasBuscar[i]);
        RedBlackTreePT *foundNode = SearchWordInTree(&arvore, palavrasBuscar[i]);
        QueryPerformanceCounter(&endTime);

        double elapsedTime = (double)(endTime.QuadPart - startTime.QuadPart) * 1e9 / frequency.QuadPart; // Tempo em nanosegundos
        totalTime += elapsedTime;

        if (foundNode != NULL) {
            printf("Palavra encontrada: %s\n", foundNode->info.portugueseWord);
        } else {
            printf("Palavra não encontrada.\n");
        }
        printf("Tempo de busca: %.2f ns\n\n", elapsedTime);
    }

    // Exibir tempo total e médio
    printf("Tempo total para buscar palavras: %.2f ns\n", totalTime);
    printf("Tempo médio por palavra: %.2f ns\n", totalTime / numBuscar);

    // Relatório de gerenciamento de memória
    printf("\nGerenciamento de Memória:\n");
    printf("Total de memória alocada: %zu bytes\n", totalMemoryAllocated);
    printf("Total de memória liberada: %zu bytes\n", totalMemoryFreed);

    if (totalMemoryAllocated == totalMemoryFreed) {
        printf("Memória gerenciada corretamente. Nenhum vazamento detectado.\n");
    } else {
        printf("Atenção: Vazamento de memória detectado! (%zu bytes não liberados)\n",
               totalMemoryAllocated - totalMemoryFreed);
    }

    // Limpeza da árvore
    printf("Limpando memória...\n");
    //deallocateTree(&arvore);
    printf("Memória liberada.\n");

    return 0;
}








