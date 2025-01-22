#include <stdio.h>  // Biblioteca padrão para entrada e saída (ex.: printf, scanf)
#include <stdlib.h> // Biblioteca para funções auxiliares (ex.: malloc, free)
#include <math.h>   // Biblioteca para cálculos matemáticos (ex.: pow)
#include <stdint.h> // Biblioteca para tipos de dados com tamanhos fixos

#ifdef _WIN32
#include <windows.h> // Inclui funções específicas do Windows, como medição de tempo
#else
#include <time.h> // Para medir tempo em sistemas Unix-like
#endif

#define MAX_CONFIGURATIONS 81 // Número total de configurações possíveis de 4 discos em 3 pinos (3^4 = 81)
#define INF 1000000           // Valor "infinito" usado para representar distâncias inicialmente desconhecidas

// Estrutura que representa uma configuração do problema
typedef struct
{
    int disks[4]; // Cada configuração armazena a posição dos 4 discos (valores de 0 a 2, representando os pinos)
} Configuration;

// Função para gerar todas as possíveis configurações
void generateConfigurations(Configuration *configs)
{
    int i, j; // Variáveis de controle para loops

    // Para cada uma das 81 configurações possíveis
    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        // Para cada disco, calcula sua posição (base 3) na configuração atual
        for (j = 0; j < 4; j++)
        {
            configs[i].disks[j] = (i / (int)pow(3, j)) % 3; // Converte o índice da configuração para base 3
        }
    }
}

// Função para exibir todas as configurações geradas
void displayConfigurations(Configuration *configs)
{
    int i, j; // Variáveis de controle para loops

    printf("\nTodas as configurações:\n");
    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {                         // Para cada configuração
        printf("No %d: ", i); // Exibe o índice da configuração
        for (j = 0; j < 4; j++)
        {                                           // Para cada disco na configuração atual
            printf("%d ", configs[i].disks[j] + 1); // Exibe a posição do disco (ajustada para 1-indexado)
        }
        printf("\n"); // Finaliza a linha da configuração
    }
}

// Função que verifica se é válido mover de uma configuração para outra
int isValidMove(Configuration a, Configuration b)
{
    int diffCount = 0;                         // Conta quantos discos mudaram de posição
    int from = -1, to = -1, smallestDisk = -1; // Variáveis para identificar o disco movido
    int isValid = 1;                           // Assume inicialmente que o movimento é válido
    int i;

    // Verifica as diferenças entre as configurações `a` e `b`
    for (i = 0; i < 4 && isValid; i++)
    {
        if (a.disks[i] != b.disks[i])
        {                // Se a posição do disco mudou
            diffCount++; // Incrementa o número de diferenças
            if (diffCount > 1)
            { // Se mais de um disco mudou, o movimento é inválido
                isValid = 0;
            }
            else
            {
                from = a.disks[i]; // Armazena de onde o disco foi retirado
                to = b.disks[i];   // Armazena para onde o disco foi movido
                smallestDisk = i;  // Armazena o índice do disco movido
            }
        }
    }

    // Verifica se exatamente um disco foi movido
    if (diffCount != 1)
    {
        isValid = 0;
    }

    // Verifica se há discos menores bloqueando o movimento
    for (i = 0; i < smallestDisk && isValid; i++)
    {
        if (a.disks[i] == from || b.disks[i] == to)
        {                // Discos menores estão no caminho?
            isValid = 0; // Movimento inválido se há bloqueio
        }
    }

    return isValid; // Retorna 1 (válido) ou 0 (inválido)
}

// Função que constrói o grafo de configurações
void buildGraph(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], Configuration *configs)
{
    int i, j;

    // Para cada par de configurações
    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        for (j = 0; j < MAX_CONFIGURATIONS; j++)
        {
            // Verifica se há um movimento válido entre `i` e `j`
            graph[i][j] = isValidMove(configs[i], configs[j]) ? 1 : INF; // Peso 1 se válido, INF caso contrário
        }
    }
}

void bellmanFord(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], int start, int end, Configuration *configs)
{
    int dist[MAX_CONFIGURATIONS], prev[MAX_CONFIGURATIONS]; // Distâncias mínimas e predecessores
    int i, u, v, at;                                        // Variáveis para controle de loops e reconstrução do caminho

    // Inicializa as distâncias e predecessores
    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        dist[i] = INF; // Todas as distâncias começam como "infinito"
        prev[i] = -1;  // Predecessores começam como desconhecidos
    }
    dist[start] = 0; // A distância inicial para si mesmo é 0

    // Relaxa as arestas |V| - 1 vezes (V = número de vértices)
    // O que é relaxar uma aresta?
    // - Relaxar uma aresta é o processo de verificar se o custo de alcançar um vértice `v`
    //   passando por outro vértice `u` é menor do que o custo atualmente conhecido.
    // - Se o novo custo for menor, atualizamos:
    //   1. `dist[v]`: A distância mínima conhecida para o vértice `v`.
    //   2. `prev[v]`: O predecessor de `v`, indicando que o menor caminho para `v` passa por `u`.

    // Por que repetimos o processo |V| - 1 vezes?
    // - Em um grafo com `V` vértices, o menor caminho entre dois vértices em um grafo sem ciclos
    //   pode conter no máximo |V| - 1 arestas (comprimento máximo do caminho mais curto).
    // - Repetir o processo |V| - 1 vezes garante que todas as combinações de caminhos possíveis
    //   sejam verificadas e que as distâncias mínimas sejam encontradas para todos os vértices.

    for (i = 0; i < MAX_CONFIGURATIONS - 1; i++)
    {
        // Para cada vértice u (nó de origem)
        for (u = 0; u < MAX_CONFIGURATIONS; u++)
        {
            // Para cada vértice v (nó de destino)
            for (v = 0; v < MAX_CONFIGURATIONS; v++)
            {
                // Verifica se existe uma aresta entre u e v (peso diferente de INF)
                if (graph[u][v] != INF)
                {
                    // Verifica se o caminho atual para v, passando por u, é mais curto
                    // `dist[u]`: Distância mínima conhecida de `start` até u
                    // `graph[u][v]`: Peso da aresta entre u e v
                    // `dist[u] + graph[u][v]`: Custo total do caminho passando por u
                    if (dist[u] + graph[u][v] < dist[v])
                    {
                        // Atualiza a distância mínima para v
                        dist[v] = dist[u] + graph[u][v]; // Encontra um caminho mais curto para v

                        // Salva u como o predecessor de v
                        // Isso significa que o menor caminho para v passa por u
                        prev[v] = u;
                    }
                }
            }
        }
    }

    // Exibe o menor caminho e o número de movimentos
    printf("Menor caminho do início ao final: %d movimentos\n", dist[end]);

    // Reconstrói o caminho do nó final para o inicial usando os predecessores
    int path[MAX_CONFIGURATIONS], pathIndex = 0;
    for (at = end; at != -1; at = prev[at])
    {
        path[pathIndex++] = at; // Armazena o caminho reconstruído
    }

    // Exibe o caminho reconstruído na ordem correta (do início ao fim)
    for (i = pathIndex - 1; i >= 0; i--)
    {
        printf("Configuracao %d: [", path[i]);
        for (u = 0; u < 4; u++)
        {
            printf("%d", configs[path[i]].disks[u] + 1); // Exibe os discos ajustados para 1-indexado
            if (u < 3)
                printf(", ");
        }
        printf("]\n");
    }
}

#ifdef _WIN32
// Função para obter tempo em nanosegundos no Windows
long long getNanoseconds()
{
    LARGE_INTEGER frequency, start;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    return (start.QuadPart * 1000000000LL) / frequency.QuadPart;
}
#endif

int main()
{
    Configuration configs[MAX_CONFIGURATIONS];         // Todas as configurações
    int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS]; // Grafo de conexões
    int choice, start, end;                            // Controle do menu, configurações inicial e final

#ifdef _WIN32
    long long startTime, endTime; // Para medir tempo no Windows
#else
    struct timespec startTime, endTime; // Para medir tempo em Unix-like
#endif

    generateConfigurations(configs); // Gera as configurações possíveis
    buildGraph(graph, configs);      // Constrói o grafo de conexões

    do
    {
        printf("\n========== MENU ==========\n");
        printf("1. Exibir todas as configuracoes\n");
        printf("2. Calcular o menor caminho entre duas configuracoes\n");
        printf("3. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayConfigurations(configs); // Exibe todas as configurações
            break;
        case 2:
            printf("Digite a configuracao inicial (0 a 80): ");
            scanf("%d", &start); // Entrada inicial
            printf("Digite a configuracao final (0 a 80): ");
            scanf("%d", &end); // Entrada final

#ifdef _WIN32
            startTime = getNanoseconds();
            bellmanFord(graph, start, end, configs); // Calcula o menor caminho
            endTime = getNanoseconds();
            printf("Tempo gasto: %lld nanosegundos\n", endTime - startTime);
#else
            clock_gettime(CLOCK_MONOTONIC, &startTime);
            bellmanFord(graph, start, end, configs); // Calcula o menor caminho
            clock_gettime(CLOCK_MONOTONIC, &endTime);

            long seconds = endTime.tv_sec - startTime.tv_sec;
            long nanoseconds = endTime.tv_nsec - startTime.tv_nsec;
            if (nanoseconds < 0)
            {
                seconds -= 1;
                nanoseconds += 1000000000;
            }

            printf("Tempo gasto: %ld segundos e %ld nanosegundos\n", seconds, nanoseconds);
#endif
            break;
        case 3:
            printf("Saindo...\n"); // Encerra o programa
            break;
        default:
            printf("Opcao invalida!\n"); // Entrada inválida
        }
    } while (choice != 3); // Loop até o usuário escolher sair

    return 0; // Fim do programa
}

/*
    OBJETIVO DO CÓDIGO:
    Este programa resolve um problema semelhante à Torre de Hanói, gerando todas as possíveis configurações de discos
    em 3 torres, validando os movimentos permitidos e calculando o menor caminho (número de movimentos) entre duas configurações.

    FUNCIONALIDADES PRINCIPAIS:
    1. Gera todas as configurações possíveis para 4 discos distribuídos em 3 torres (81 combinações no total).
    2. Valida os movimentos entre as configurações, respeitando as regras:
       - Apenas um disco pode ser movido por vez.
       - Um disco só pode ser colocado em uma torre vazia ou sobre outro maior.
    3. Cria um grafo, onde:
       - Os vértices representam as configurações.
       - As arestas conectam configurações que possuem movimentos válidos entre elas.
    4. Usa o algoritmo de **Bellman-Ford** para calcular o menor caminho entre duas configurações fornecidas pelo usuário.
    5. Exibe o menor caminho em termos de número de movimentos e as configurações visitadas no trajeto.

    APLICAÇÕES:
    - Ensino de algoritmos de grafos e conceitos de busca de caminhos mínimos (Bellman-Ford).
    - Simulações e análise de problemas combinatórios semelhantes à Torre de Hanói.
*/

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
