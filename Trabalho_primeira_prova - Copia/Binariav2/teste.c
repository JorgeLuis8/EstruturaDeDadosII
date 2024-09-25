//////////////////////////////////////// Numeros ordenados ////////////////////////////////////////

// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <windows.h>
// #include "notas.c"

// // Função para medir o tempo no Windows
// void iniciar_medicao(LARGE_INTEGER *inicio, LARGE_INTEGER *freq) {
//     QueryPerformanceFrequency(freq);
//     QueryPerformanceCounter(inicio);
// }

// long long finalizar_medicao(LARGE_INTEGER inicio, LARGE_INTEGER fim, LARGE_INTEGER freq) {
//     QueryPerformanceCounter(&fim);
//     return (fim.QuadPart - inicio.QuadPart) * 1000000000 / freq.QuadPart; // Converte para nanosegundos
// }

// // Função para desalocar a árvore de notas
// void liberar_arvore(arvore_notas *raiz) {
//     if (raiz == NULL) {
//         return;
//     }
//     liberar_arvore(raiz->esq);
//     liberar_arvore(raiz->dir);
//     free(raiz); // Libera o nó atual
// }

// // Função para buscar uma nota pelo código da disciplina


// int main() {
//     srand((unsigned)time(NULL)); // Inicializa o gerador de números aleatórios

//     LARGE_INTEGER inicio, fim, freq;
//     long long tempo_total_insercao = 0;
//     long long tempo_total_busca = 0;

//     int num_execucoes = 30;
//     int num_insercoes = 1000;

//     // Repetir o processo de inserção e busca 30 vezes
//     for (int j = 0; j < num_execucoes; j++) {
//         arvore_notas *raiz = NULL; // Reinicializa a árvore a cada iteração
//         long long tempo_insercao_atual = 0;

//         // Inserir 1000 elementos
//         for (int i = 0; i < num_insercoes; i++) {
//             arvore_notas *nova_nota = criar_nota();
//             nova_nota->codigo_disciplina = i; // Código em ordem crescente
//             snprintf(nova_nota->semestre_cursado, sizeof(nova_nota->semestre_cursado), "2023-2"); // Exemplo de semestre
//             nova_nota->nota_final = (float)(rand() % 101); // Nota aleatória de 0 a 100

//             iniciar_medicao(&inicio, &freq);
//             raiz = inserir_nota(raiz, nova_nota);
//             QueryPerformanceCounter(&fim);
//             tempo_insercao_atual += finalizar_medicao(inicio, fim, freq);
//         }

//         // Somar o tempo total de inserção ao total geral
//         tempo_total_insercao += tempo_insercao_atual;

//         // Buscar o mesmo elemento 30 vezes e medir o tempo
//         for (int i = 0; i < num_execucoes; i++) {
//             int codigo_busca = rand() % num_insercoes; // Código a ser buscado

//             iniciar_medicao(&inicio, &freq);
//             arvore_notas *resultado = buscar_notas(raiz, codigo_busca);
//             QueryPerformanceCounter(&fim);
//             tempo_total_busca += finalizar_medicao(inicio, fim, freq);
//         }

//         // Limpar a árvore ao final de cada iteração
//         liberar_arvore(raiz);
//     }

//     // Calcular a média de tempo de inserção e busca
//     long long media_tempo_insercao = tempo_total_insercao / num_execucoes;
//     long long media_tempo_busca = tempo_total_busca / num_execucoes;

//     // Mostrar a média de inserção e busca
//     printf("Tempo médio de inserção: %lld nanosegundos\n", media_tempo_insercao);
//     printf("Tempo médio de busca: %lld nanosegundos\n", media_tempo_busca);

//     return 0;
// }
//////////////////////////////////////// Numeros ordenados ////////////////////////////////////////



//////////////////////////////////////// Numeros decrecente ////////////////////////////////////////
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <windows.h>
// #include "notas.c"

// // Função para medir o tempo no Windows
// void iniciar_medicao(LARGE_INTEGER *inicio, LARGE_INTEGER *freq) {
//     QueryPerformanceFrequency(freq);
//     QueryPerformanceCounter(inicio);
// }

// long long finalizar_medicao(LARGE_INTEGER inicio, LARGE_INTEGER fim, LARGE_INTEGER freq) {
//     QueryPerformanceCounter(&fim);
//     return (fim.QuadPart - inicio.QuadPart) * 1000000000 / freq.QuadPart; // Converte para nanosegundos
// }

// // Função para desalocar a árvore de notas
// void liberar_arvore(arvore_notas *raiz) {
//     if (raiz == NULL) {
//         return;
//     }
//     liberar_arvore(raiz->esq);
//     liberar_arvore(raiz->dir);
//     free(raiz); // Libera o nó atual
// }

// // Função para buscar uma nota pelo código da disciplina
// arvore_notas* buscar_nota(arvore_notas *raiz, int codigo_disciplina) {
//     if (raiz == NULL || raiz->codigo_disciplina == codigo_disciplina) {
//         return raiz; // Encontrado ou árvore vazia
//     }
//     if (codigo_disciplina < raiz->codigo_disciplina) {
//         return buscar_nota(raiz->esq, codigo_disciplina); // Busca na subárvore esquerda
//     }
//     return buscar_nota(raiz->dir, codigo_disciplina); // Busca na subárvore direita
// }

// int main() {
//     srand((unsigned)time(NULL)); // Inicializa o gerador de números aleatórios

//     LARGE_INTEGER inicio, fim, freq;
//     long long tempo_total_insercao = 0;
//     long long tempo_total_busca = 0;

//     int num_execucoes = 30;
//     int num_insercoes = 1000;

//     // Repetir o processo de inserção e busca 30 vezes
//     for (int j = 0; j < num_execucoes; j++) {
//         arvore_notas *raiz = NULL; // Reinicializa a árvore a cada iteração
//         long long tempo_insercao_atual = 0;

//         // Inserir 1000 elementos do maior para o menor
//         for (int i = num_insercoes - 1; i >= 0; i--) {  // Inserção decrescente
//             arvore_notas *nova_nota = criar_nota();
//             nova_nota->codigo_disciplina = i; // Código em ordem decrescente
//             snprintf(nova_nota->semestre_cursado, sizeof(nova_nota->semestre_cursado), "2023-2"); // Exemplo de semestre
//             nova_nota->nota_final = (float)(rand() % 101); // Nota aleatória de 0 a 100

//             iniciar_medicao(&inicio, &freq);
//             raiz = inserir_nota(raiz, nova_nota);
//             QueryPerformanceCounter(&fim);
//             tempo_insercao_atual += finalizar_medicao(inicio, fim, freq);
//         }

//         // Somar o tempo total de inserção ao total geral
//         tempo_total_insercao += tempo_insercao_atual;

//         // Buscar o mesmo elemento 30 vezes e medir o tempo
//         for (int i = 0; i < num_execucoes; i++) {
//             int codigo_busca = rand() % num_insercoes; // Código a ser buscado

//             iniciar_medicao(&inicio, &freq);
//             arvore_notas *resultado = buscar_nota(raiz, codigo_busca);
//             QueryPerformanceCounter(&fim);
//             tempo_total_busca += finalizar_medicao(inicio, fim, freq);
//         }

//         // Limpar a árvore ao final de cada iteração
//         liberar_arvore(raiz);
//     }

//     // Calcular a média de tempo de inserção e busca
//     long long media_tempo_insercao = tempo_total_insercao / num_execucoes;
//     long long media_tempo_busca = tempo_total_busca / num_execucoes;

//     // Mostrar a média de inserção e busca
//     printf("Tempo médio de inserção: %lld nanosegundos\n", media_tempo_insercao);
//     printf("Tempo médio de busca: %lld nanosegundos\n", media_tempo_busca);

//     return 0;
// }

//////////////////////////////////////// Numeros decrecente ////////////////////////////////////////

//////////////////////////////////////// Numeros aleatorios ////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "notas.c"

// Função para medir o tempo no Windows
void iniciar_medicao(LARGE_INTEGER *inicio, LARGE_INTEGER *freq) {
    QueryPerformanceFrequency(freq);
    QueryPerformanceCounter(inicio);
}

long long finalizar_medicao(LARGE_INTEGER inicio, LARGE_INTEGER fim, LARGE_INTEGER freq) {
    QueryPerformanceCounter(&fim);
    return (fim.QuadPart - inicio.QuadPart) * 1000000000 / freq.QuadPart; // Converte para nanosegundos
}

// Função para desalocar a árvore de notas
void liberar_arvore(arvore_notas *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz); // Libera o nó atual
}

// Função para buscar uma nota pelo código da disciplina
arvore_notas* buscar_nota(arvore_notas *raiz, int codigo_disciplina) {
    if (raiz == NULL || raiz->codigo_disciplina == codigo_disciplina) {
        return raiz; // Encontrado ou árvore vazia
    }
    if (codigo_disciplina < raiz->codigo_disciplina) {
        return buscar_nota(raiz->esq, codigo_disciplina); // Busca na subárvore esquerda
    }
    return buscar_nota(raiz->dir, codigo_disciplina); // Busca na subárvore direita
}

int main() {
    srand((unsigned)time(NULL)); // Inicializa o gerador de números aleatórios

    LARGE_INTEGER inicio, fim, freq;
    long long tempo_total_insercao = 0;
    long long tempo_total_busca = 0;

    int num_execucoes = 30;
    int num_insercoes = 1000;

    // Repetir o processo de inserção e busca 30 vezes
    for (int j = 0; j < num_execucoes; j++) {
        arvore_notas *raiz = NULL; // Reinicializa a árvore a cada iteração
        long long tempo_insercao_atual = 0;

        // Inserir 1000 elementos com códigos de disciplina aleatórios
        for (int i = 0; i < num_insercoes; i++) {  // Inserção aleatória
            arvore_notas *nova_nota = criar_nota();
            nova_nota->codigo_disciplina = rand() % num_insercoes; // Código aleatório
            snprintf(nova_nota->semestre_cursado, sizeof(nova_nota->semestre_cursado), "2023-2"); // Exemplo de semestre
            nova_nota->nota_final = (float)(rand() % 101); // Nota aleatória de 0 a 100

            iniciar_medicao(&inicio, &freq);
            raiz = inserir_nota(raiz, nova_nota);
            QueryPerformanceCounter(&fim);
            tempo_insercao_atual += finalizar_medicao(inicio, fim, freq);
        }

        // Somar o tempo total de inserção ao total geral
        tempo_total_insercao += tempo_insercao_atual;

        // Buscar o mesmo elemento 30 vezes e medir o tempo
        for (int i = 0; i < num_execucoes; i++) {
            int codigo_busca = rand() % num_insercoes; // Código a ser buscado

            iniciar_medicao(&inicio, &freq);
            arvore_notas *resultado = buscar_nota(raiz, codigo_busca);
            QueryPerformanceCounter(&fim);
            tempo_total_busca += finalizar_medicao(inicio, fim, freq);
        }

        // Limpar a árvore ao final de cada iteração
        liberar_arvore(raiz);
    }

    // Calcular a média de tempo de inserção e busca
    long long media_tempo_insercao = tempo_total_insercao / num_execucoes;
    long long media_tempo_busca = tempo_total_busca / num_execucoes;

    // Mostrar a média de inserção e busca
    printf("Tempo médio de inserção: %lld nanosegundos\n", media_tempo_insercao);
    printf("Tempo médio de busca: %lld nanosegundos\n", media_tempo_busca);

    return 0;
}
//////////////////////////////////////// Numeros aleatorios ////////////////////////////////////////