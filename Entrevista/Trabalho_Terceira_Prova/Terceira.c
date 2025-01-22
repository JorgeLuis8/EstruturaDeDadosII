#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_VERTICES 100
#define INF DBL_MAX

typedef struct {
    int v;         // Vértice de destino da aresta.
    double weight; // Peso da aresta (calculado como -log(reliability)).
} Edge;

typedef struct {
    Edge edges[MAX_VERTICES][MAX_VERTICES]; // Matriz de adjacência para armazenar arestas.
    int numVertices;                        // Número total de vértices no grafo.
    int numEdges;                           // Número total de arestas no grafo.
} Graph;

void initGraph(Graph *g, int numVertices) {
    g->numVertices = numVertices; // Configura o número de vértices.
    g->numEdges = 0;             // Inicializa o número de arestas como zero.

    // Configura todas as arestas como "infinito", exceto as diagonais (peso 0 para arestas reflexivas).
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

    // Define o peso como -log(reliability) para modelar confiabilidade no caminho.
    g->edges[u][v].v = v;
    g->edges[u][v].weight = -log(reliability);
    g->numEdges++; // Incrementa o número total de arestas.
}


void dijkstra(Graph *g, int start, int end, int *path, double *probability) {
    double dist[MAX_VERTICES];       // Distância mínima conhecida de cada vértice ao vértice inicial.
    int prev[MAX_VERTICES];          // Array para armazenar o predecessor de cada nó.
    int visited[MAX_VERTICES] = {0}; // Marca os nós já processados.
    int n = g->numVertices;          // Número de vértices no grafo.

    // Passo 1: Inicializa distâncias como infinito e predecessores como -1.
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0.0; // A distância do vértice inicial para ele mesmo é 0.

    // Passo 2: Executa o algoritmo de Dijkstra.
    for (int i = 0; i < n; i++) {
        double minDist = INF; // Menor distância encontrada para um vértice não visitado.
        int u = -1;

        // Encontra o próximo vértice não visitado com a menor distância.
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        // Se nenhum nó acessível for encontrado, encerra o loop.
        if (u == -1) break;

        visited[u] = 1; // Marca o vértice atual como visitado.

        // Atualiza as distâncias para os vizinhos do vértice atual.
        for (int v = 0; v < n; v++) {
            if (!visited[v] && g->edges[u][v].weight < INF) {
                double newDist = dist[u] + g->edges[u][v].weight;
                if (newDist < dist[v]) {
                    dist[v] = newDist; // Atualiza a menor distância para o vizinho.
                    prev[v] = u;       // Atualiza o predecessor do vizinho.
                }
            }
        }
    }

    // Passo 3: Reconstrói o caminho do destino ao início.
    int current = end;
    int pathIndex = 0;
    while (current != -1) { // Segue os predecessores até o início.
        path[pathIndex++] = current;
        current = prev[current];
    }

    // Inverte o caminho para exibir do início ao fim.
    for (int i = 0; i < pathIndex / 2; i++) {
        int temp = path[i];
        path[i] = path[pathIndex - 1 - i];
        path[pathIndex - 1 - i] = temp;
    }

    // Marca o fim do caminho com -1.
    path[pathIndex] = -1;

    // Passo 4: Calcula a probabilidade total como e^(-distância).
    *probability = exp(-dist[end]);
}



int main() {
    Graph g; // Declaração do grafo.
    int repeat = 1;

    while (repeat) {
        int n, m;

        printf("Digite o numero de vertices e arestas: ");
        if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m < 0 || n > MAX_VERTICES) {
            printf("Erro: Entrada invalida para vertices ou arestas.\n");
            continue;
        }

        initGraph(&g, n); // Inicializa o grafo com n vértices.

        printf("Digite as arestas no formato (u v r):\n");
        for (int i = 0; i < m; i++) {
            int u, v;
            double r;
            if (scanf("%d %d %lf", &u, &v, &r) != 3 || u < 0 || v < 0 || u >= n || v >= n || r <= 0 || r > 1) {
                printf("Erro: Entrada invalida para arestas.\n");
                i--; // Permite tentar novamente.
            } else {
                addEdge(&g, u, v, r); // Adiciona a aresta ao grafo.
            }
        }

        int start, end;
        printf("Digite os vertices de origem e destino: ");
        if (scanf("%d %d", &start, &end) != 2 || start < 0 || end < 0 || start >= n || end >= n) {
            printf("Erro: Entrada invalida para origem ou destino.\n");
            continue;
        }

        int path[MAX_VERTICES] = {-1};
        double probability;
        dijkstra(&g, start, end, path, &probability);

        printf("Caminho mais confiavel: ");
        for (int i = 0; path[i] != -1; i++) {
            printf("%d ", path[i]);
        }
        printf("\nProbabilidade de sucesso total: %.2lf%%\n", probability * 100);

        printf("Deseja calcular novamente? (1 - Sim / 0 - Nao): ");
        if (scanf("%d", &repeat) != 1) repeat = 0;
    }

    return 0;
}

/* Função: initGraph
   Propósito:
   - Inicializa o grafo, configurando todos os pesos entre os vértices como "infinito" (`INF`), exceto para loops (peso 0 para vértices conectados a si mesmos).
   
   Funcionamento:
   1. Recebe o grafo e o número de vértices.
   2. Itera pela matriz de adjacência (`edges`) para configurar os pesos:
      - Arestas inexistentes são marcadas como `INF`.
      - Loops (vértices conectados a si mesmos) recebem peso 0.
   3. Define o número de vértices no grafo (`numVertices`) e inicializa o contador de arestas (`numEdges`) como 0.
   
   Explicação para a entrevista:
   - Essa função é essencial para garantir que o grafo esteja corretamente inicializado antes de ser usado.
   - `INF` é usado para representar arestas inexistentes, garantindo que o algoritmo de Dijkstra ignore caminhos inválidos.
*/

/* Função: addEdge
   Propósito:
   - Adiciona uma aresta direcionada entre dois vértices com um peso correspondente à confiabilidade.
   
   Funcionamento:
   1. Verifica se a confiabilidade está no intervalo válido (0, 1].
      - Valores fora desse intervalo são tratados como erro.
   2. Calcula o peso da aresta como `-log(reliability)`.
      - Essa transformação permite usar Dijkstra, que funciona com somas, para resolver o problema de confiabilidade (multiplicativa).
   3. Atualiza a matriz de adjacência com o peso calculado e incrementa o contador de arestas (`numEdges`).

   Explicação para a entrevista:
   - Transformar confiabilidades em `-log(reliability)` converte multiplicações em somas, facilitando o uso do algoritmo de Dijkstra.
   - A validação dos valores de confiabilidade evita erros lógicos no grafo.
*/

/* Função: dijkstra
   Propósito:
   - Calcula o caminho mais confiável entre dois vértices em um grafo ponderado, usando o algoritmo de Dijkstra.
   - Retorna o caminho e a probabilidade total de sucesso.

   Funcionamento:
   1. **Inicialização:**
      - Todas as distâncias (`dist`) são configuradas como infinito (`INF`), exceto o vértice inicial (`start`), que tem distância 0.
      - O vetor `prev` armazena os predecessores de cada vértice no menor caminho.
      - O vetor `visited` rastreia os vértices já processados.
   
   2. **Execução do algoritmo:**
      - Em cada iteração, encontra o vértice com a menor distância que ainda não foi processado.
      - Para cada vizinho desse vértice:
        - Calcula a nova distância acumulada considerando o peso da aresta.
        - Se a nova distância for menor que a atual registrada, atualiza a distância e o predecessor.
      - Repete até que todos os vértices sejam processados ou não haja mais caminhos acessíveis.

   3. **Reconstrução do caminho:**
      - Usa o vetor `prev` para rastrear o caminho do vértice final (`end`) até o inicial (`start`).
      - O caminho é construído de trás para frente e depois invertido para exibição.

   4. **Cálculo da probabilidade:**
      - A probabilidade total do caminho é calculada como `exp(-dist[end])`.
      - Isso reverte a transformação logarítmica para retornar à confiabilidade original.

   Explicação para a entrevista:
   - Dijkstra é usado porque o grafo possui apenas pesos positivos, e ele é mais eficiente que Bellman-Ford neste caso.
   - O uso de `-log(reliability)` converte confiabilidades multiplicativas em somas, compatíveis com Dijkstra.
   - A reconstrução do caminho com `prev` permite exibir não apenas o custo, mas também o trajeto completo.
   - A probabilidade total, calculada no final, é intuitiva e responde diretamente ao problema proposto.
*/

/* Função: main
   Propósito:
   - Controla o fluxo principal do programa, permitindo ao usuário interagir com as funcionalidades do grafo.

   Funcionamento:
   1. Lê o número de vértices e arestas do grafo.
   2. Inicializa o grafo usando `initGraph`.
   3. Lê as arestas (vértices de origem, destino e confiabilidade) e as adiciona ao grafo com `addEdge`.
   4. Solicita os vértices de origem e destino para calcular o caminho mais confiável:
      - Chama `dijkstra` para encontrar o caminho e a probabilidade.
      - Exibe o caminho e a probabilidade no formato decimal e percentual.
   5. Oferece ao usuário a opção de executar novamente ou encerrar o programa.

   Explicação para a entrevista:
   - O `main` integra todas as funcionalidades do programa e facilita a interação do usuário.
   - Cada etapa é cuidadosamente validada para evitar entradas inválidas (número de vértices, arestas, confiabilidade, etc.).
   - O programa foi projetado para ser reutilizável, permitindo que o usuário insira diferentes grafos e execute cálculos várias vezes.
*/