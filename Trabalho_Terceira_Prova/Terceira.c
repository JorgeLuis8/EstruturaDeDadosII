#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 100

typedef struct {
    int destino;
    double confiabilidade;
} Aresta;

typedef struct {
    Aresta arestas[MAX];
    int tamanho;
} ListaAdjacencia;

ListaAdjacencia grafo[MAX];
int num_vertices; // Numero de vertices no grafo

void adicionarAresta(int origem, int destino, double confiabilidade) {
    grafo[origem].arestas[grafo[origem].tamanho].destino = destino;
    grafo[origem].arestas[grafo[origem].tamanho].confiabilidade = confiabilidade;
    grafo[origem].tamanho++;
}

double dijkstra(int inicio, int fim) {
    double confiabilidades[MAX];
    int visitado[MAX] = {0};
    for (int i = 0; i < num_vertices; i++) {
        confiabilidades[i] = 0.0;
    }
    confiabilidades[inicio] = 1.0;

    for (int i = 0; i < num_vertices; i++) {
        double max_confiabilidade = 0.0;
        int atual = -1;

        for (int j = 0; j < num_vertices; j++) {
            if (!visitado[j] && confiabilidades[j] > max_confiabilidade) {
                max_confiabilidade = confiabilidades[j];
                atual = j;
            }
        }

        if (atual == -1) break;
        visitado[atual] = 1;

        for (int j = 0; j < grafo[atual].tamanho; j++) {
            int vizinho = grafo[atual].arestas[j].destino;
            double confiabilidade = grafo[atual].arestas[j].confiabilidade;

            if (!visitado[vizinho] && confiabilidades[atual] * confiabilidade > confiabilidades[vizinho]) {
                confiabilidades[vizinho] = confiabilidades[atual] * confiabilidade;
            }
        }
    }

    return confiabilidades[fim];
}

int main() {
    num_vertices = 5; // Numero de vertices
    adicionarAresta(0, 1, 0.9);
    adicionarAresta(0, 2, 0.5);
    adicionarAresta(1, 3, 0.7);
    adicionarAresta(2, 3, 0.8);
    adicionarAresta(3, 4, 0.6);

    int inicio = 0, fim = 4;
    double confiabilidade = dijkstra(inicio, fim);

    if (confiabilidade > 0) {
        printf("A confiabilidade maxima entre %d e %d e: %.6f\n", inicio, fim, confiabilidade);
    } else {
        printf("Nao ha caminho entre %d e %d.\n", inicio, fim);
    }

    return 0;
}
