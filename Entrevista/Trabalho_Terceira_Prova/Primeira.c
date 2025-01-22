#include <stdio.h> // Biblioteca padrão para entrada e saída
#include <stdlib.h> // Biblioteca para funções úteis, como alocação de memória
#include <math.h> // Biblioteca para cálculos matemáticos (ex.: potência)
#include <windows.h> // Biblioteca específica do Windows (ex.: medição de tempo)
#include <time.h> // Biblioteca para manipulação de tempo

#define MAX_CONFIGURATIONS 81 // Total de configurações possíveis (3^4 = 81)
#define INF 1000000 // Valor que representa "infinito" no algoritmo de Dijkstra
// O infinito é usado para inicializar a distância de todos os nós, exceto o nó inicial, 
// já que no início do algoritmo não sabemos o caminho para esses nós. 
// Isso garante que qualquer distância calculada durante o algoritmo será menor que INF.

// Estrutura para representar uma configuração
typedef struct
{
    int disks[4]; // Cada configuração tem 4 discos, com posições de 0 a 2 (3 pinos)
} Configuration;

// Função para obter o tempo em nanosegundos
double getTime()
{
    LARGE_INTEGER frequency, start;
    QueryPerformanceFrequency(&frequency); // Obtém a frequência do contador de alta precisão
    QueryPerformanceCounter(&start); // Lê o valor atual do contador
    return (double)start.QuadPart / frequency.QuadPart * 1e9; // Converte para nanosegundos
}

// Função para gerar todas as 81 configurações possíveis
void generateConfigurations(Configuration *configs)
{
    int i, j; // Variáveis de loop

    // Itera por todas as configurações possíveis (0 a 80)
    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        // Para cada configuração, define o estado de cada disco (4 discos no total)
        for (j = 0; j < 4; j++)
        {
            // Determina a posição do disco `j` com base no número da configuração `i`
            configs[i].disks[j] = (i / (int)pow(3, j)) % 3; // Converte o número da configuração para base 3
        }
    }
}

// Função para exibir todas as configurações geradas
void displayConfigurations(Configuration *configs)
{
    int i, j; // Variáveis de loop

    printf("\nTodas as configurações:\n");
    for (i = 0; i < MAX_CONFIGURATIONS; i++) // Itera por todas as configurações
    {
        printf("No %d: ", i); // Exibe o número da configuração
        for (j = 0; j < 4; j++) // Itera pelos 4 discos
        {
            printf("%d ", configs[i].disks[j] + 1); // Exibe a posição de cada disco (ajustada para 1 a 3)
        }
        printf("\n"); // Nova linha após cada configuração
    }
}

// Função para verificar se uma configuração é um movimento válido de outra
int isValidMove(Configuration a, Configuration b)
{
    int diffCount = 0; // Contador para diferenças entre as configurações
    int from = -1, to = -1; // Armazena de onde e para onde o disco foi movido
    int smallestDisk = -1; // Índice do menor disco movido
    int isValid = 1; // Assume que o movimento é válido
    int i; // Variável de loop

    // Identifica discos que mudaram de posição
    for (i = 0; i < 4; i++)
    {
        if (a.disks[i] != b.disks[i]) // Se a posição do disco mudou
        {
            diffCount++; // Incrementa o número de diferenças

            if (diffCount > 1) // Se mais de um disco mudou, o movimento é inválido
            {
                isValid = 0;
            }
            else
            {
                from = a.disks[i]; // Armazena de onde o disco foi movido
                to = b.disks[i]; // Armazena para onde o disco foi movido
                smallestDisk = i; // Armazena o índice do menor disco movido
            }
        }
    }

    if (diffCount != 1) // Se nenhum ou mais de um disco foi movido
    {
        isValid = 0;
    }

    i = 0;
    while (i < smallestDisk && isValid) // Verifica se discos menores bloqueiam o movimento
    {
        if (a.disks[i] == from || b.disks[i] == to) // Se um disco menor está no caminho
        {
            isValid = 0;
        }
        i++;
    }

    return isValid; // Retorna se o movimento é válido ou não
}

// Função para construir o grafo representando todas as configurações e movimentos válidos
void buildGraph(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], Configuration *configs)
{
    int i, j; // Variáveis de loop

    // Inicializa o grafo com base nas configurações
    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        for (j = 0; j < MAX_CONFIGURATIONS; j++)
        {
            // Define o peso da aresta como 1 se o movimento for válido, caso contrário, infinito
            graph[i][j] = isValidMove(configs[i], configs[j]) ? 1 : INF;
        }
    }
}

// Algoritmo de Dijkstra para encontrar o menor caminho entre duas configurações
void dijkstra(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], int start, int end, Configuration *configs)
{
    int dist[MAX_CONFIGURATIONS], prev[MAX_CONFIGURATIONS], visited[MAX_CONFIGURATIONS] = {0};
    int i, j, v, at;
    int loopControl = 1; // Controle do loop principal

    // Inicializa as distâncias como infinito e o nó anterior como -1
    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0; // Distância da configuração inicial para ela mesma é 0

    // Loop principal de Dijkstra
    i = 0;
    while (i < MAX_CONFIGURATIONS && loopControl)
    {
        int minDist = INF, u = -1;

        // Encontra o próximo nó com a menor distância
        for (j = 0; j < MAX_CONFIGURATIONS; j++)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) // Se nenhum nó não visitado foi encontrado, encerra
        {
            loopControl = 0;
        }
        else
        {
            visited[u] = 1; // Marca o nó como visitado

            // Atualiza as distâncias dos vizinhos
            for (v = 0; v < MAX_CONFIGURATIONS; v++)
            {
                if (graph[u][v] != INF && dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                    prev[v] = u; // Atualiza o nó anterior
                }
            }
        }
        i++;
    }

    // Exibe o menor caminho e sua distância
    printf("Menor caminho do início ao final: %d movimentos\n", dist[end]);
    printf("Caminho:\n");

    // Reconstrói o caminho
    int path[MAX_CONFIGURATIONS], pathIndex = 0;
    for (at = end; at != -1; at = prev[at])
    {
        path[pathIndex++] = at;
    }

    // Exibe o caminho reconstruído
    for (i = pathIndex - 1; i >= 0; i--)
    {
        printf("Configuracao %d: [", path[i]);
        for (j = 0; j < 4; j++)
        {
            printf("%d", configs[path[i]].disks[j] + 1);
            if (j < 3)
                printf(", ");
        }
        printf("]\n");
    }
}

// Função principal
int main()
{
    Configuration configs[MAX_CONFIGURATIONS]; // Array de configurações
    int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS]; // Matriz de adjacência do grafo
    int choice, start, end; // Opções e configurações inicial e final
    double startTime, endTime; // Para medir o tempo de execução

    generateConfigurations(configs); // Gera todas as configurações possíveis
    buildGraph(graph, configs); // Constrói o grafo com movimentos válidos

    // Menu interativo
    do
    {
        printf("\n========== MENU ==========\n");
        printf("1. Exibir todas as configuracoes\n");
        printf("2. Calcular o menor caminho entre duas configuracoes\n");
        printf("3. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice); // Lê a opção do usuário

        switch (choice)
        {
        case 1:
            displayConfigurations(configs); // Exibe todas as configurações
            break;
        case 2:
            printf("Digite a configuracao inicial (0 a 80): ");
            scanf("%d", &start); // Lê a configuração inicial
            printf("Digite a configuracao final (0 a 80): ");
            scanf("%d", &end); // Lê a configuração final

            startTime = getTime(); // Marca o tempo inicial
            dijkstra(graph, start, end, configs); // Executa o algoritmo de Dijkstra
            endTime = getTime(); // Marca o tempo final

            printf("Tempo gasto: %.2lf nanosegundos\n", endTime - startTime); // Exibe o tempo gasto
            break;
        case 3:
            printf("Saindo...\n"); // Finaliza o programa
            break;
        default:
            printf("Opcao invalida!\n"); // Opção inválida
        }
    } while (choice != 3); // Continua enquanto o usuário não escolher sair

    return 0; // Indica que o programa terminou com sucesso
}
/* 
    Por que usamos o algoritmo de Dijkstra?

    1. **Arestas com pesos positivos**:
       - Todas as arestas no grafo têm peso positivo (1 ou INF).
       - O Dijkstra é otimizado para encontrar o menor caminho em grafos com pesos positivos.
       - O Bellman-Ford é necessário apenas quando existem arestas com pesos negativos, o que não é o caso aqui.

    2. **Eficiência**:
       - O Dijkstra tem complexidade O(V + E * log(V)) quando implementado com uma fila de prioridade.
       - O Bellman-Ford, por outro lado, tem complexidade O(V * E), tornando-o mais lento em grafos densos como este.

    3. **Menor caminho com pesos uniformes**:
       - Como todas as arestas válidas têm peso 1, o Dijkstra consegue encontrar o menor número de movimentos de forma rápida e eficiente.

    Resumo:
    O algoritmo de Dijkstra é a melhor escolha para este problema porque é mais eficiente e adequado para grafos com arestas de peso positivo e uniforme.
*/


// Struct Configuration
// Estrutura que representa uma configuração do problema.
// O array `disks[4]` armazena o estado dos 4 discos, onde:
// - Cada posição do array representa um disco (0 a 3).
// - O valor na posição indica em qual torre o disco está (0, 1 ou 2).

// Função getTime()
// Retorna o tempo atual em nanosegundos.
// - `QueryPerformanceFrequency`: Obtém a frequência do contador de alta precisão.
// - `QueryPerformanceCounter`: Lê o valor atual do contador.
// - Divide o valor lido pela frequência para obter o tempo decorrido em segundos e converte para nanosegundos.
// Usada para medir o desempenho e o tempo de execução de algoritmos.


// Função generateConfigurations(Configuration *configs)
// Gera todas as configurações possíveis de discos e as armazena no array `configs`.
// - Para cada configuração `i` (0 a 80):
//   1. Para cada disco (0 a 3), calcula sua posição usando `(i / pow(3, j)) % 3`.
//      - `pow(3, j)`: Obtém o peso da base 3 para o disco `j`.
//      - `(i / pow(3, j))`: Isola o dígito correspondente ao disco `j` na representação na base 3.
//      - `% 3`: Obtém o valor do dígito (0, 1 ou 2), que representa a torre do disco.
// - Resultado: Cada configuração representa uma distribuição válida de discos em 3 torres.


// Função displayConfigurations(Configuration *configs)
// Imprime todas as 81 configurações armazenadas no array `configs`.
// - Para cada configuração:
//   1. Imprime o número da configuração (`i`).
//   2. Itera pelos 4 discos e imprime o estado de cada disco, adicionando 1 para exibir como (1, 2, 3).


// Função isValidMove(Configuration a, Configuration b)
// Verifica se é possível mover de uma configuração `a` para outra `b` respeitando as regras do jogo.
// Passo a passo:
// 1. Calcula quantos discos mudaram de posição entre `a` e `b`.
//    - Se mais de um disco mudou, o movimento é inválido (`diffCount > 1`).
// 2. Identifica de onde (from) e para onde (to) o disco foi movido.
// 3. Verifica se o disco movido é o menor disponível na torre original (não pode haver outro disco menor bloqueando).
// 4. Verifica se o disco movido não foi colocado em uma torre acima de outro disco menor.
// Retorna:
// - `1` (válido) se as regras forem seguidas.
// - `0` (inválido) caso contrário.


// Função buildGraph(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], Configuration *configs)
// Constrói a matriz de adjacência do grafo representando todas as configurações possíveis.
// - Para cada par de configurações `(i, j)`:
//   1. Verifica se é possível mover de `i` para `j` usando `isValidMove`.
//   2. Se for válido, define `graph[i][j] = 1`.
//   3. Caso contrário, define `graph[i][j] = INF` (representando caminho impossível).
// Resultado: Um grafo onde os vértices são as configurações e as arestas representam movimentos válidos.


// Função dijkstra(...)
// Implementa o algoritmo de Dijkstra para encontrar o menor caminho entre duas configurações.
// Entrada:
// - `graph`: Matriz de adjacência com os pesos das arestas (1 para movimentos válidos, `INF` para inválidos).
// - `start`: Índice da configuração inicial.
// - `end`: Índice da configuração final.
// Passo a passo:
// 1. Inicializa as distâncias (`dist`) de todos os vértices como `INF`, exceto o inicial (`dist[start] = 0`).
// 2. Cria um vetor de visitados para rastrear os vértices já processados.
// 3. Iterativamente:
//    - Escolhe o vértice `u` não visitado com a menor distância (`dist[u]`).
//    - Marca `u` como visitado.
//    - Atualiza as distâncias dos vizinhos de `u`:
//      - Se `dist[u] + graph[u][v] < dist[v]`, atualiza `dist[v]` e define `prev[v] = u`.
// 4. Reconstrói o menor caminho do final (`end`) ao início (`start`) usando o vetor de predecessores (`prev`).
// 5. Imprime o menor caminho e a sequência de configurações no trajeto.
// Por que usar `INF`?
// - Indica caminhos impossíveis e evita que sejam considerados no cálculo do menor caminho.


// Função main()
// Controla o fluxo do programa com um menu interativo.
// Opções:
// 1. Exibe todas as configurações possíveis (usando `displayConfigurations`).
// 2. Calcula o menor caminho entre duas configurações (usando `dijkstra`):
//    - Lê as configurações inicial e final do usuário.
//    - Mede o tempo de execução para calcular o menor caminho.
// 3. Encerra o programa.
