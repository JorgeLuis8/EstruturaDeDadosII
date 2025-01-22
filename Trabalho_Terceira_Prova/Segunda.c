#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#define MAX_CONFIGURATIONS 81
#define INF 1000000


typedef struct {
    int disks[4]; 
} Configuration;


void generateConfigurations(Configuration *configs) {
    int i, j;
    for (i = 0; i < MAX_CONFIGURATIONS; i++) {
        for (j = 0; j < 4; j++) {
            configs[i].disks[j] = (i / (int)pow(3, j)) % 3; 
        }
    }
}


void displayConfigurations(Configuration *configs) {
    int i, j;
    printf("\nTodas as configurações:\n");
    for (i = 0; i < MAX_CONFIGURATIONS; i++) {
        printf("No %d: ", i);
        for (j = 0; j < 4; j++) {
            printf("%d ", configs[i].disks[j] + 1); 
        }
        printf("\n");
    }
}

int isValidMove(Configuration a, Configuration b) {
    int diffCount = 0;
    int from = -1, to = -1, smallestDisk = -1;
    int i;
    int isValid = 1; 

    for (i = 0; i < 4 && isValid; i++) {
        if (a.disks[i] != b.disks[i]) {
            diffCount++;
            if (diffCount > 1) {
                isValid = 0; 
            } else {
                from = a.disks[i];
                to = b.disks[i];
                smallestDisk = i;
            }
        }
    }

    if (diffCount != 1) {
        isValid = 0; 
    }

    for (i = 0; i < smallestDisk && isValid; i++) {
        if (a.disks[i] == from || b.disks[i] == to) {
            isValid = 0; 
        }
    }

    return isValid;
}


void buildGraph(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], Configuration *configs) {
    int i, j;
    for (i = 0; i < MAX_CONFIGURATIONS; i++) {
        for (j = 0; j < MAX_CONFIGURATIONS; j++) {
            graph[i][j] = isValidMove(configs[i], configs[j]) ? 1 : INF;
        }
    }
}


void bellmanFord(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], int start, int end, Configuration *configs) {
 
    int dist[MAX_CONFIGURATIONS], prev[MAX_CONFIGURATIONS];
    int i, j, u, v; 
    int at; 


    for (i = 0; i < MAX_CONFIGURATIONS; i++) {
        dist[i] = INF; 
        prev[i] = -1;  
    }
    dist[start] = 0; 


    for (i = 0; i < MAX_CONFIGURATIONS - 1; i++) {
        for (u = 0; u < MAX_CONFIGURATIONS; u++) { 
            for (v = 0; v < MAX_CONFIGURATIONS; v++) { 
                if (graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v]; 
                    prev[v] = u; 
                }
            }
        }
    }

   
    printf("Menor caminho do início ao final: %d movimentos\n", dist[end]);
    printf("Caminho:\n");

    // Passo 4: Reconstrói o caminho do destino para a origem.
    int path[MAX_CONFIGURATIONS], pathIndex = 0;
    for (at = end; at != -1; at = prev[at]) {
        path[pathIndex++] = at; // Armazena os nós do caminho na ordem inversa.
    }

    // Passo 5: Exibe o caminho na ordem correta (do início ao fim).
    for (i = pathIndex - 1; i >= 0; i--) {
        printf("Configuracao %d: [", path[i]); // Exibe o índice da configuração.
        for (j = 0; j < 4; j++) {
            printf("%d", configs[path[i]].disks[j] + 1); // Exibe os discos ajustados para 1-indexado.
            if (j < 3) printf(", "); // Formata os separadores.
        }
        printf("]\n"); // Finaliza a exibição de uma configuração.
    }
}

#ifdef _WIN32
long long getNanoseconds() {
    LARGE_INTEGER frequency, start;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    return (start.QuadPart * 1000000000LL) / frequency.QuadPart;
}
#endif

int main() {
    Configuration configs[MAX_CONFIGURATIONS];
    int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS];
    int choice, start, end;

#ifdef _WIN32
    long long startTime, endTime;
#else
    struct timespec startTime, endTime;
#endif

    generateConfigurations(configs);
    buildGraph(graph, configs);

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Exibir todas as configuracoes\n");
        printf("2. Calcular o menor caminho entre duas configuracoes\n");
        printf("3. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayConfigurations(configs);
                break;
            case 2:
                printf("Digite a configuracao inicial (0 a 80): ");
                scanf("%d", &start);
                printf("Digite a configuracao final (0 a 80): ");
                scanf("%d", &end);

#ifdef _WIN32
                startTime = getNanoseconds();
                bellmanFord(graph, start, end, configs);
                endTime = getNanoseconds();
                printf("Tempo gasto: %lld nanosegundos\n", endTime - startTime);
#else
                clock_gettime(CLOCK_MONOTONIC, &startTime);
                bellmanFord(graph, start, end, configs);
                clock_gettime(CLOCK_MONOTONIC, &endTime);

                long seconds = endTime.tv_sec - startTime.tv_sec;
                long nanoseconds = endTime.tv_nsec - startTime.tv_nsec;
                if (nanoseconds < 0) {
                    seconds -= 1;
                    nanoseconds += 1000000000;
                }

                printf("Tempo gasto: %ld segundos e %ld nanosegundos\n", seconds, nanoseconds);
#endif
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (choice != 3);

    return 0;
}

// Struct Configuration
// Estrutura que armazena o estado de 4 discos em um array `disks[4]`.
// Cada valor no array representa a torre onde o disco está:
// - 0: Primeira torre
// - 1: Segunda torre
// - 2: Terceira torre

// Função generateConfigurations
// Gera todas as 81 configurações possíveis (3^4) de discos em 3 torres.
// - Para cada configuração `i`, calcula a posição de cada disco (0 a 3):
//   1. `pow(3, j)`: Obtém o peso da base 3 para o disco `j`.
//   2. `(i / pow(3, j)) % 3`: Determina a torre para o disco `j`.
// - Resultado: O array `configs` contém todas as configurações possíveis.

// Função displayConfigurations
// Exibe todas as 81 configurações geradas no formato:
// "No X: disco1 disco2 disco3 disco4".
// - Itera pelo array `configs` e imprime o estado de cada disco, ajustando para 1-indexado.

// Função isValidMove
// Verifica se é válido mover de uma configuração `a` para outra `b`:
// 1. Apenas um disco pode ser movido.
// 2. O disco movido deve ser o menor disponível na torre original.
// 3. Nenhum disco pode ser colocado sobre outro menor em outra torre.
// Retorna:
// - 1: Movimento válido.
// - 0: Movimento inválido.

// Função buildGraph
// Constrói a matriz de adjacência `graph`, onde:
// - `graph[i][j] = 1`: Movimento válido entre as configurações `i` e `j`.
// - `graph[i][j] = INF`: Movimento inválido (representa caminho impossível).
// - Usa `isValidMove` para determinar a validade dos movimentos.

// Função bellmanFord
// Implementa o algoritmo de Bellman-Ford para encontrar o menor caminho no grafo.
// Entrada:
// - `graph`: Matriz de adjacência com os pesos das arestas.
// - `start`: Índice da configuração inicial.
// - `end`: Índice da configuração final.
// Passo a passo:
// 1. Inicializa as distâncias (`dist`) como `INF`, exceto o ponto inicial (`dist[start] = 0`).
// 2. Relaxa as arestas repetidamente (até `MAX_CONFIGURATIONS - 1` vezes):
//    - Para cada aresta `(u, v)`, atualiza `dist[v]` se passar por `u` resultar em um caminho mais curto.
//    - Registra o predecessor (`prev`) de cada vértice para reconstruir o caminho.
// 3. Reconstrói o caminho do destino (`end`) ao início (`start`) usando o vetor `prev`.
// 4. Exibe o menor caminho e as configurações no trajeto.

// Função getNanoseconds
// Retorna o tempo atual em nanosegundos (apenas para Windows).
// - Usa `QueryPerformanceFrequency` e `QueryPerformanceCounter` para medir intervalos de tempo com alta precisão.

// Função main
// Controla o fluxo do programa com um menu interativo.
// 1. Exibe todas as configurações geradas (chama `displayConfigurations`).
// 2. Calcula o menor caminho entre duas configurações (chama `bellmanFord`):
//    - Lê as configurações inicial e final fornecidas pelo usuário.
//    - Mede o tempo de execução do algoritmo e exibe o resultado.
// 3. Encerra o programa.

// Por que usar Dijkstra em vez de Bellman-Ford neste caso?
// - O grafo contém apenas arestas com pesos positivos (todas as distâncias são 1 ou INF).
// - O algoritmo de Dijkstra é mais eficiente do que Bellman-Ford para este tipo de grafo porque:
//   1. Dijkstra usa uma abordagem de "ganância" (greedy), escolhendo sempre o menor caminho no momento, 
//      enquanto Bellman-Ford relaxa todas as arestas repetidamente, tornando-o mais lento.
//   2. O custo de Dijkstra com uma implementação eficiente (usando uma fila de prioridade) é \(O(V + E \log V)\),
//      enquanto Bellman-Ford tem um custo de \(O(V \times E)\), onde \(V\) é o número de vértices e \(E\), o número de arestas.
// - Como o grafo deste problema é denso (muitos vértices e arestas), Dijkstra se torna mais eficiente em termos de tempo de execução.
// - No entanto, Dijkstra não funciona corretamente com arestas de peso negativo, enquanto Bellman-Ford pode lidar com essas situações.
// - Como sabemos que as arestas do grafo são todas positivas, Dijkstra é a melhor escolha para este caso.
