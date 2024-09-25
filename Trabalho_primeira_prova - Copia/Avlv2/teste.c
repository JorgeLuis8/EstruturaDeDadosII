#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "notas.c"

// Funcao para medir o tempo no Windows
void iniciar_medicao(LARGE_INTEGER *inicio, LARGE_INTEGER *freq) {
    QueryPerformanceFrequency(freq);
    QueryPerformanceCounter(inicio);
}

long long finalizar_medicao(LARGE_INTEGER inicio, LARGE_INTEGER fim, LARGE_INTEGER freq) {
    QueryPerformanceCounter(&fim);
    return (fim.QuadPart - inicio.QuadPart) * 1000000000 / freq.QuadPart; // Converte para nanosegundos
}

// Funcao para desalocar a arvore de notas
void liberar_arvore(arvore_notas *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz); // Libera o no atual
}

// Caso para numeros ordenados
void caso_numeros_ordenados() {
    LARGE_INTEGER inicio, fim, freq;
    long long tempo_total_insercao = 0;
    long long tempo_total_busca = 0;

    int num_execucoes = 30;
    int num_insercoes = 1000;

    for (int j = 0; j < num_execucoes; j++) {
        arvore_notas *raiz = NULL; // Reinicializa a arvore a cada iteracao
        long long tempo_insercao_atual = 0;

        // Inserir 1000 elementos
        for (int i = 0; i < num_insercoes; i++) {
            arvore_notas *nova_nota = criar_nota();
            nova_nota->codigo_disciplina = i; // Codigo em ordem crescente
            snprintf(nova_nota->semestre_cursado, sizeof(nova_nota->semestre_cursado), "2023-2"); // Exemplo de semestre
            nova_nota->nota_final = (float)(rand() % 101); // Nota aleatoria de 0 a 100

            iniciar_medicao(&inicio, &freq);
            raiz = inserir_nota(raiz, nova_nota);
            tempo_insercao_atual += finalizar_medicao(inicio, fim, freq);
        }

        // Somar o tempo total de insercao ao total geral
        tempo_total_insercao += tempo_insercao_atual;

        // Buscar o mesmo elemento 30 vezes e medir o tempo
        for (int i = 0; i < num_execucoes; i++) {
            int codigo_busca = rand() % num_insercoes; // Codigo a ser buscado

            iniciar_medicao(&inicio, &freq);
            arvore_notas *resultado = buscar_notas(raiz, codigo_busca);
            tempo_total_busca += finalizar_medicao(inicio, fim, freq);
        }

        // Limpar a arvore ao final de cada iteracao
        liberar_arvore(raiz);
    }

    // Calcular a media de tempo de insercao e busca
    long long media_tempo_insercao = tempo_total_insercao / num_execucoes;
    long long media_tempo_busca = tempo_total_busca / num_execucoes;

    // Mostrar a media de insercao e busca
    printf("Numeros Ordenados:\n");
    printf("Tempo medio de insercao: %lld nanosegundos\n", media_tempo_insercao);
    printf("Tempo medio de busca: %lld nanosegundos\n\n", media_tempo_busca);
}

// Caso para numeros decrescentes
void caso_numeros_decrescentes() {
    LARGE_INTEGER inicio, fim, freq;
    long long tempo_total_insercao = 0;
    long long tempo_total_busca = 0;

    int num_execucoes = 30;
    int num_insercoes = 1000;

    for (int j = 0; j < num_execucoes; j++) {
        arvore_notas *raiz = NULL; // Reinicializa a arvore a cada iteracao
        long long tempo_insercao_atual = 0;

        // Inserir 1000 elementos do maior para o menor
        for (int i = num_insercoes - 1; i >= 0; i--) {  // Insercao decrescente
            arvore_notas *nova_nota = criar_nota();
            nova_nota->codigo_disciplina = i; // Codigo em ordem decrescente
            snprintf(nova_nota->semestre_cursado, sizeof(nova_nota->semestre_cursado), "2023-2"); // Exemplo de semestre
            nova_nota->nota_final = (float)(rand() % 101); // Nota aleatoria de 0 a 100

            iniciar_medicao(&inicio, &freq);
            raiz = inserir_nota(raiz, nova_nota);
            tempo_insercao_atual += finalizar_medicao(inicio, fim, freq);
        }

        // Somar o tempo total de insercao ao total geral
        tempo_total_insercao += tempo_insercao_atual;

        // Buscar o mesmo elemento 30 vezes e medir o tempo
        for (int i = 0; i < num_execucoes; i++) {
            int codigo_busca = rand() % num_insercoes; // Codigo a ser buscado

            iniciar_medicao(&inicio, &freq);
            arvore_notas *resultado = buscar_notas(raiz, codigo_busca);
            tempo_total_busca += finalizar_medicao(inicio, fim, freq);
        }

        // Limpar a arvore ao final de cada iteracao
        liberar_arvore(raiz);
    }

    // Calcular a media de tempo de insercao e busca
    long long media_tempo_insercao = tempo_total_insercao / num_execucoes;
    long long media_tempo_busca = tempo_total_busca / num_execucoes;

    // Mostrar a media de insercao e busca
    printf("Numeros Decrescentes:\n");
    printf("Tempo medio de insercao: %lld nanosegundos\n", media_tempo_insercao);
    printf("Tempo medio de busca: %lld nanosegundos\n\n", media_tempo_busca);
}

// Caso para numeros aleatorios
void caso_numeros_aleatorios() {
    LARGE_INTEGER inicio, fim, freq;
    long long tempo_total_insercao = 0;
    long long tempo_total_busca = 0;

    int num_execucoes = 30;
    int num_insercoes = 1000;

    for (int j = 0; j < num_execucoes; j++) {
        arvore_notas *raiz = NULL; // Reinicializa a arvore a cada iteracao
        long long tempo_insercao_atual = 0;

        // Inserir 1000 elementos com codigos de disciplina aleatorios
        for (int i = 0; i < num_insercoes; i++) {  // Insercao aleatoria
            arvore_notas *nova_nota = criar_nota();
            nova_nota->codigo_disciplina = rand() % num_insercoes; // Codigo aleatorio
            snprintf(nova_nota->semestre_cursado, sizeof(nova_nota->semestre_cursado), "2023-2"); // Exemplo de semestre
            nova_nota->nota_final = (float)(rand() % 101); // Nota aleatoria de 0 a 100

            iniciar_medicao(&inicio, &freq);
            raiz = inserir_nota(raiz, nova_nota);
            tempo_insercao_atual += finalizar_medicao(inicio, fim, freq);
        }

        // Somar o tempo total de insercao ao total geral
        tempo_total_insercao += tempo_insercao_atual;

        // Buscar o mesmo elemento 30 vezes e medir o tempo
        for (int i = 0; i < num_execucoes; i++) {
            int codigo_busca = rand() % num_insercoes; // Codigo a ser buscado

            iniciar_medicao(&inicio, &freq);
            arvore_notas *resultado = buscar_notas(raiz, codigo_busca);
            tempo_total_busca += finalizar_medicao(inicio, fim, freq);
        }

        // Limpar a arvore ao final de cada iteracao
        liberar_arvore(raiz);
    }

    // Calcular a media de tempo de insercao e busca
    long long media_tempo_insercao = tempo_total_insercao / num_execucoes;
    long long media_tempo_busca = tempo_total_busca / num_execucoes;

    // Mostrar a media de insercao e busca
    printf("Numeros Aleatorios:\n");
    printf("Tempo medio de insercao: %lld nanosegundos\n", media_tempo_insercao);
    printf("Tempo medio de busca: %lld nanosegundos\n\n", media_tempo_busca);
}


// Funcao principal
int main() {
    int opcao;

    do {
        // Exibir o menu
        printf("Selecionar caso de teste:\n");
        printf("1 - Numeros Ordenados\n");
        printf("2 - Numeros Decrescentes\n");
        printf("3 - Numeros Aleatorios\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        // Executar a opcao escolhida
        switch (opcao) {
            case 1:
                caso_numeros_ordenados();
                break;
            case 2:
                caso_numeros_decrescentes();
                break;
            case 3:
                caso_numeros_aleatorios();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }while (opcao != 0);
}
