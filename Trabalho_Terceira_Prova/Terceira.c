#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_VERTICES 100
#define INF DBL_MAX

typedef struct {
    int v;
    double weight;
} Edge;

typedef struct {
    Edge edges[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
    int numEdges;
} Graph;

void initGraph(Graph *g, int numVertices) {
    g->numVertices = numVertices;
    g->numEdges = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->edges[i][j].weight = (i == j) ? 0.0 : INF;
        }
    }
}

void addEdge(Graph *g, int u, int v, double reliability) {
    if (reliability <= 0 || reliability > 1) {
        printf("Erro: Confiabilidade deve estar no intervalo (0, 1].\n");
        exit(1);
    }
    g->edges[u][v].v = v;
    g->edges[u][v].weight = -log(reliability);
    g->numEdges++;
}

void dijkstra(Graph *g, int start, int end, int *path, double *probability) {
    double dist[MAX_VERTICES];
    int prev[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    int n = g->numVertices;

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0.0;

    for (int i = 0; i < n; i++) {
        double minDist = INF;
        int u = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && g->edges[u][v].weight < INF) {
                double newDist = dist[u] + g->edges[u][v].weight;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                }
            }
        }
    }

    int current = end, pathIndex = 0;
    while (current != -1) {
        path[pathIndex++] = current;
        current = prev[current];
    }

    *probability = exp(-dist[end]);

    for (int i = 0; i < pathIndex / 2; i++) {
        int temp = path[i];
        path[i] = path[pathIndex - 1 - i];
        path[pathIndex - 1 - i] = temp;
    }

    path[pathIndex] = -1;
}

void runTests() {
    Graph g;
    initGraph(&g, 5);

    addEdge(&g, 0, 1, 0.9);
    addEdge(&g, 1, 2, 0.8);
    addEdge(&g, 0, 3, 0.7);
    addEdge(&g, 3, 4, 0.6);
    addEdge(&g, 4, 2, 0.9);

    printf("Teste 1: Grafo Básico\n");
    int path[MAX_VERTICES];
    double probability;
    dijkstra(&g, 0, 2, path, &probability);
    printf("Caminho mais confiável: ");
    for (int i = 0; path[i] != -1; i++) {
        printf("%d ", path[i]);
    }
    printf("\nProbabilidade: %.2lf%%\n\n", probability * 100);

    printf("Teste 2: Sem Caminho Possível\n");
    Graph g2;
    initGraph(&g2, 3);
    addEdge(&g2, 0, 1, 0.5);
    dijkstra(&g2, 0, 2, path, &probability);
    if (probability > 0) {
        printf("Caminho encontrado erroneamente.\n");
    } else {
        printf("Nenhum caminho encontrado, como esperado.\n\n");
    }

    printf("Teste 3: Caminho Direto e Indireto\n");
    Graph g3;
    initGraph(&g3, 4);
    addEdge(&g3, 0, 1, 0.9);
    addEdge(&g3, 1, 2, 0.8);
    addEdge(&g3, 0, 2, 0.95);
    dijkstra(&g3, 0, 2, path, &probability);
    printf("Caminho mais confiável: ");
    for (int i = 0; path[i] != -1; i++) {
        printf("%d ", path[i]);
    }
    printf("\nProbabilidade: %.2lf%%\n\n", probability * 100);
}

int main() {
    printf("Executando testes automatizados...\n\n");
    runTests();

    printf("Modo interativo:\n");
    Graph g;
    int repeat = 1;

    while (repeat == 1) {
        int n, m, erro = 0;
        printf("Digite o numero de vertices e arestas: ");
        if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m < 0 || n > MAX_VERTICES) {
            printf("Erro: Entrada invalida.\n");
            continue;
        }

        initGraph(&g, n);
        printf("Digite as arestas (u v r):\n");
        for (int i = 0; i < m; i++) {
            int u, v;
            double r;
            if (scanf("%d %d %lf", &u, &v, &r) != 3 || u < 0 || v < 0 || u >= n || v >= n) {
                printf("Erro na entrada de arestas.\n");
                erro = 1;
                break;
            }
            addEdge(&g, u, v, r);
        }

        if (!erro) {
            int start, end;
            printf("Digite os vertices de origem e destino: ");
            if (scanf("%d %d", &start, &end) != 2 || start < 0 || end < 0 || start >= n || end >= n) {
                printf("Erro na entrada de origem/destino.\n");
                continue;
            }

            int path[MAX_VERTICES];
            double probability;
            dijkstra(&g, start, end, path, &probability);

            printf("Caminho mais confiável: ");
            for (int i = 0; path[i] != -1; i++) {
                printf("%d ", path[i]);
            }
            printf("\nProbabilidade de sucesso total: %.2lf%%\n", probability * 100);
        }

        printf("Deseja tentar novamente? (1 - Sim / 0 - Não): ");
        scanf("%d", &repeat);
    }

    return 0;
}
