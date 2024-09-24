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
    return (fim.QuadPart - inicio.QuadPart) * 1000000000 / freq.QuadPart;
}

int main() {
    arvore_notas *raiz = NULL;
    srand((unsigned)time(NULL)); // Inicializa o gerador de números aleatórios

    LARGE_INTEGER inicio, fim, freq;
    long long tempo_total_insercao = 0;
    long long tempo_total_busca = 0;

    // Inserir 30 elementos
    for (int i = 0; i < 30; i++) {
        arvore_notas *nova_nota = criar_nota();
        nova_nota->codigo_disciplina = rand() % 100; // Código aleatório de 0 a 99
        snprintf(nova_nota->semestre_cursado, sizeof(nova_nota->semestre_cursado), "2023-2"); // Exemplo de semestre
        nova_nota->nota_final = (float)(rand() % 101); // Nota aleatória de 0 a 100

        iniciar_medicao(&inicio, &freq);
        raiz = inserir_nota(raiz, nova_nota);
        tempo_total_insercao += finalizar_medicao(inicio, fim, freq);
    }

    // Medir tempo de busca
    for (int i = 0; i < 30; i++) {
        int codigo_busca = rand() % 100; // Código a ser buscado

        iniciar_medicao(&inicio, &freq);
        // Código de busca aqui
        // Exemplo: arvore_notas *resultado = buscar_nota(raiz, codigo_busca);
        tempo_total_busca += finalizar_medicao(inicio, fim, freq);
    }

    printf("Tempo total de inserção: %lld nanosegundos\n", tempo_total_insercao);
    printf("Tempo total de busca: %lld nanosegundos\n", tempo_total_busca);

    return 0;
}