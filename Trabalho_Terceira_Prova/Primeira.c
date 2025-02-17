#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#define MAX_CONFIGURATIONS 81
#define INF 1000000

typedef struct
{
    int disks[4];
} Configuration;

double getTime()
{
    LARGE_INTEGER frequency, start;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    return (double)start.QuadPart / frequency.QuadPart * 1e9;
}

void generateConfigurations(Configuration *configs)
{
    // Declara duas variáveis inteiras, i e j, que serão usadas nos loops.
    int i, j;

    // Loop externo: percorre todas as configurações possíveis, de 0 até MAX_CONFIGURATIONS - 1.
    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        // Loop interno: percorre cada um dos 4 discos (índices 0 a 3) da configuração atual.
        for (j = 0; j < 4; j++)
        {
            // Define o estado do disco 'j' na configuração 'i'.
            // Aqui, (int)pow(3, j) calcula 3 elevado à potência 'j'.
            // O índice 'i' é dividido por esse valor para isolar o dígito correspondente ao disco 'j'.
            // O operador '%' (módulo) é usado para extrair o valor do disco na base 3 (resto da divisão por 3).
            configs[i].disks[j] = (i / (int)pow(3, j)) % 3;
        }
    }
}


void displayConfigurations(Configuration *configs)
{
    int i, j;
    printf("\nTodas as configurações:\n");
    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        printf("No %d: ", i);
        for (j = 0; j < 4; j++)
        {
            printf("%d ", configs[i].disks[j] + 1);
        }
        printf("\n");
    }
}

int isValidMove(Configuration a, Configuration b)
{
    // Contador para saber quantos discos mudaram de posição.
    int diffCount = 0;

    // Variáveis para armazenar de onde veio e para onde foi o disco movido.
    int from = -1, to = -1;

    // Armazena o índice do menor disco (mais alto na torre) que foi movido.
    int smallestDisk = -1;

    // Assume que o movimento é válido até provar o contrário.
    int isValid = 1;

    // Variável para percorrer os discos.
    int i;

    // Passo 1: Identificar discos que mudaram de posição entre as configurações.
    for (i = 0; i < 4; i++)
    {
        // Verifica se o estado do disco `i` é diferente entre `a` e `b`.
        if (a.disks[i] != b.disks[i])
        {
            // Incrementa o número de diferenças encontradas.
            diffCount++;

            // Se mais de um disco mudou, o movimento é inválido.
            if (diffCount > 1)
            {
                isValid = 0;
            }
            else
            {
                // Armazena de onde veio (from) e para onde foi (to) o disco movido.
                from = a.disks[i];
                to = b.disks[i];

          
                smallestDisk = i;
            }
        }
    }

  
    if (diffCount != 1)
    {
        isValid = 0; 
    }

    i = 0;
    while (i < smallestDisk && isValid)
    {
     
        if (a.disks[i] == from || b.disks[i] == to)
        {
            isValid = 0; 
        }
        i++;
    }

    return isValid;
}


void buildGraph(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], Configuration *configs)
{

    int i, j;


    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        for (j = 0; j < MAX_CONFIGURATIONS; j++)
        {
          
            graph[i][j] = isValidMove(configs[i], configs[j]) ? 1 : INF;
        }
    }
}

void dijkstra(int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS], int start, int end, Configuration *configs)
{
    int dist[MAX_CONFIGURATIONS], prev[MAX_CONFIGURATIONS], visited[MAX_CONFIGURATIONS] = {0};
    int i, j, v, at;
    int loopControl = 1;

    for (i = 0; i < MAX_CONFIGURATIONS; i++)
    {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    i = 0;
    while (i < MAX_CONFIGURATIONS && loopControl)
    {
        int minDist = INF, u = -1;

        for (j = 0; j < MAX_CONFIGURATIONS; j++)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1)
        {
            loopControl = 0;
        }
        else
        {
            visited[u] = 1;

            for (v = 0; v < MAX_CONFIGURATIONS; v++)
            {
                if (graph[u][v] != INF && dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                    prev[v] = u;
                }
            }
        }
        i++;
    }

    printf("Menor caminho do início ao final: %d movimentos\n", dist[end]);
    printf("Caminho:\n");

    int path[MAX_CONFIGURATIONS], pathIndex = 0;

    for (at = end; at != -1; at = prev[at])
    {
        path[pathIndex++] = at;
    }

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

int main()
{
    Configuration configs[MAX_CONFIGURATIONS];
    int graph[MAX_CONFIGURATIONS][MAX_CONFIGURATIONS];
    int choice, start, end;
    double startTime, endTime;

    generateConfigurations(configs);
    buildGraph(graph, configs);

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
            displayConfigurations(configs);
            break;
        case 2:
            printf("Digite a configuracao inicial (0 a 80): ");
            scanf("%d", &start);
            printf("Digite a configuracao final (0 a 80): ");
            scanf("%d", &end);

            startTime = getTime();
            dijkstra(graph, start, end, configs);
            endTime = getTime();

            printf("Tempo gasto: %.2lf nanosegundos\n", endTime - startTime);
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
