#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_CONFIGURATIONS 81
#define INF 1000000

// Representação de uma configuração
typedef struct {
    int disks[4]; // 4 discos, cada posição indica o pino (0, 1 ou 2)
} Configuration;

// Função para gerar todas as configurações possíveis
void generateConfigurations(Configuration *configs) {
    for (int i = 0; i < MAX_CONFIGURATIONS; i++) {
        for (int j = 0; j < 4; j++) {
            configs[i].disks[j] = (i / (int)pow(3, j)) % 3; // Calcula a base 3
        }
    }
}

// Verifica se um movimento entre duas configurações é válido
int isValidMove(Configuration a, Configuration b) {
    int diffCount = 0;  // Conta as diferenças entre as configurações
    int from = -1, to = -1;  // Torres de origem e destino do disco movido
    int smallestDisk = -1;  // Índice do menor disco que foi movido

    // Verificar diferenças entre as configurações
    for (int i = 0; i < 4; i++) {
        if (a.disks[i] != b.disks[i]) {
            diffCount++;
            if (diffCount > 1) return 0;  // Mais de um disco foi movido, inválido

            // Armazena o disco movido e sua origem/destino
            from = a.disks[i];
            to = b.disks[i];
            smallestDisk = i;  // Índice do menor disco que foi movido
        }
    }

    // Se nenhum disco foi movido ou mais de um disco foi movido, é inválido
    if (diffCount != 1) return 0;

    // Verificar as regras de empilhamento
    for (int i = 0; i < smallestDisk; i++) {
        // Se um disco menor está abaixo do disco movido na origem, movimento inválido
        if (a.disks[i] == from) return 0;
        // Se um disco menor está abaixo do disco movido no destino, movimento inválido
        if (b.disks[i] == to) return 0;
    }

    return 1;  // Movimento válido
}


// Constrói a matriz de adjacência do grafo
void buildGraph(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], Configuration *configs) {
    for (int i = 0; i < MAX_CONFIGURATIONS; i++) {
        for (int j = 0; j < MAX_CONFIGURATIONS; j++) {
            if (isValidMove(configs[i], configs[j])) {
                graph[i][j] = 1;  // Conexão válida
            } else {
                graph[i][j] = INF;  // Sem conexão
            }
        }
    }
}

void printAdjacencyMatrixCompact(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS]) {
    printf("Matriz de Adjacência (configurações conectadas):\n");
    for (int i = 0; i < MAX_CONFIGURATIONS; i++) {
        printf("Configuração %2d conecta-se a: ", i);
        int count = 0;
        for (int j = 0; j < MAX_CONFIGURATIONS; j++) {
            if (graph[i][j] == 1) {  // Mostra apenas conexões reais
                printf("%d ", j);
                count++;
            }
            if (count >= 10) {  // Limite de 10 conexões por linha para manter legibilidade
                printf("... ");
                break;
            }
        }
        printf("\n");
    }
}


// Implementação do Algoritmo de Dijkstra com caminho
void dijkstra(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], int start, int end, Configuration *configs) {
    int dist[MAX_CONFIGURATIONS], prev[MAX_CONFIGURATIONS], visited[MAX_CONFIGURATIONS] = {0};
    for (int i = 0; i < MAX_CONFIGURATIONS; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < MAX_CONFIGURATIONS; i++) {
        int minDist = INF, u = -1;
        for (int j = 0; j < MAX_CONFIGURATIONS; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < MAX_CONFIGURATIONS; v++) {
            if (graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    // Exibir caminho
    printf("Menor caminho do início ao final: %d movimentos\n", dist[end]);
    printf("Caminho:\n");

    int path[MAX_CONFIGURATIONS], pathIndex = 0;
    for (int at = end; at != -1; at = prev[at]) {
        path[pathIndex++] = at;
    }

    // Exibir as configurações no caminho
    for (int i = pathIndex - 1; i >= 0; i--) {
        printf("Configuração %d: [", path[i]);
        for (int j = 0; j < 4; j++) {
            printf("%d", configs[path[i]].disks[j]);
            if (j < 3) printf(", ");
        }
        printf("]\n");
    }
}

int main() {
    Configuration configs[MAX_CONFIGURATIONS];
    int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS];
    clock_t startTime, endTime;

    // Gerar configurações
    generateConfigurations(configs);

    // Construir o grafo
    buildGraph(graph, configs);

    // Exibir a matriz de adjacência
    //printAdjacencyMatrixCompact(graph);

    // Executar Dijkstra e calcular tempo
    startTime = clock();
    dijkstra(graph, 0, MAX_CONFIGURATIONS - 1, configs);
    endTime = clock();

    printf("Tempo gasto: %.2lf segundos\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

    return 0;
}
