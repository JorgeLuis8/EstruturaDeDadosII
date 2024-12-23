#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define N 4      // Número de discos
#define PINOS 3  // Número de pinos
#define VERTICES 81  // 3^4 = 81 configurações para 4 discos e 3 pinos

// Função para converter um índice de configuração para um vetor
void indice_para_config(int indice, int config[]) {
    for (int i = 0; i < N; i++) {
        config[i] = (indice % PINOS) + 1;
        indice /= PINOS;
    }
}

// Função para converter um vetor de configuração para um índice
int config_para_indice(int config[]) {
    int indice = 0;
    for (int i = N - 1; i >= 0; i--) {
        indice = indice * PINOS + (config[i] - 1);
    }
    return indice;
}

// Verifica se um movimento entre duas configurações é válido
int movimento_valido(int origem[], int destino[]) {
    for (int i = 0; i < N; i++) {
        if (origem[i] != destino[i]) {
            for (int j = 0; j < i; j++) {
                if (origem[j] == origem[i]) {
                    return 0; // Movimento inválido (disco maior em cima)
                }
            }
            break;
        }
    }
    return 1;
}

// Constrói a matriz de adjacência do grafo
void construir_grafo(int grafo[VERTICES][VERTICES]) {
    int config_origem[N], config_destino[N];
    for (int i = 0; i < VERTICES; i++) {
        indice_para_config(i, config_origem);
        for (int j = 0; j < VERTICES; j++) {
            if (i == j) continue; // Evitar laços
            indice_para_config(j, config_destino);
            if (movimento_valido(config_origem, config_destino)) {
                grafo[i][j] = 1; // Existe uma aresta entre i e j
            } else {
                grafo[i][j] = 0;
            }
        }
    }
}

// Algoritmo de Dijkstra
void dijkstra(int grafo[VERTICES][VERTICES], int origem, int destino) {
    int dist[VERTICES], visitado[VERTICES], anterior[VERTICES];
    for (int i = 0; i < VERTICES; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
        anterior[i] = -1;
    }
    dist[origem] = 0;

    for (int i = 0; i < VERTICES; i++) {
        int u = -1;
        for (int j = 0; j < VERTICES; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (dist[u] == INT_MAX) break;
        visitado[u] = 1;

        for (int v = 0; v < VERTICES; v++) {
            if (grafo[u][v] && !visitado[v]) {
                int alt = dist[u] + grafo[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    anterior[v] = u;
                }
            }
        }
    }

    // Reconstrução do caminho
    printf("Menor caminho: ");
    int caminho[VERTICES], tamanho = 0;
    for (int v = destino; v != -1; v = anterior[v]) {
        caminho[tamanho++] = v;
    }
    for (int i = tamanho - 1; i >= 0; i--) {
        printf("%d ", caminho[i]);
    }
    printf("\nDistância mínima: %d\n", dist[destino]);
}

int main() {
    int grafo[VERTICES][VERTICES];
    int config_inicial[N], config_final[N];
    int origem, destino;

    // Configuração inicial (todos no pino 1)
    for (int i = 0; i < N; i++) config_inicial[i] = 1;
    origem = config_para_indice(config_inicial);

    // Configuração final (todos no pino 3)
    for (int i = 0; i < N; i++) config_final[i] = 3;
    destino = config_para_indice(config_final);

    // Construir o grafo
    construir_grafo(grafo);

    // Executar Dijkstra
    clock_t inicio = clock();
    dijkstra(grafo, origem, destino);
    clock_t fim = clock();

    // Tempo de execução
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto: %.4f segundos\n", tempo);

    return 0;
}
