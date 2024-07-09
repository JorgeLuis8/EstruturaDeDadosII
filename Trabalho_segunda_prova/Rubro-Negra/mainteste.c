#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Disciplina.C"
#include "Curso.C"

#define TOTAL_CODES 10000
#define NUM_SEARCHES 30
#define REPEAT_SEARCHES 10

void menu();

#ifdef _WIN32
#include <windows.h>

// Função para obter o tempo em alta resolução no Windows
void get_current_time(struct timespec *ts) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER currentTime;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&currentTime);
    ts->tv_sec = currentTime.QuadPart / frequency.QuadPart;
    ts->tv_nsec = (currentTime.QuadPart % frequency.QuadPart) * 1E9 / frequency.QuadPart;
}

#else
// Para sistemas POSIX, como Linux
#include <unistd.h>
#include <sys/time.h>

void get_current_time(struct timespec *ts) {
    clock_gettime(CLOCK_MONOTONIC, ts);
}
#endif

double get_elapsed_time(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) / 1E9;
}

// Função para gerar códigos de curso únicos e contar os passos e tempo
int generate_unique_codes(int *codes, int total, int *passos, double *tempo) {
    int generated = 0;
    bool is_unique;
    struct timespec start_time, end_time;

    *passos = 0;
    get_current_time(&start_time);

    while (generated < total) {
        int new_code = rand() % 10000 + 1; // Gerar código aleatório entre 1 e 10000
        int i;

        // Verificar se new_code já foi gerado
        is_unique = true;
        for (i = 0; i < generated; ++i) {
            (*passos)++;
            if (codes[i] == new_code) {
                is_unique = false;
                break;
            }
        }

        // Se único, adicionar ao array de códigos
        if (is_unique) {
            codes[generated] = new_code;
            generated++;
        }
    }

    get_current_time(&end_time);
    *tempo = get_elapsed_time(&start_time, &end_time);

    return generated; // Retornar o número de códigos gerados (deve ser igual a total)
}

// Função para buscar um curso na árvore e contar os passos e tempo gasto
double buscar_disciplina_curso_contador(arv_curso *raiz, int codigo, int *passos) {
    *passos = 0;
    struct timespec start_time, end_time;

    get_current_time(&start_time);

    arv_curso *atual = raiz;
    while (atual != NULL && atual->dados->codigo != codigo) {
        (*passos)++;
        if (codigo < atual->dados->codigo)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    get_current_time(&end_time);
    double tempo = get_elapsed_time(&start_time, &end_time);
    return tempo;
}

int main() {
    srand(time(NULL)); // Inicializar semente para números aleatórios

    arv_curso *raiz_curso = NULL;
    // int opcao;
    // int codigo_curso, bloco, carga_horaria;

    // Array para armazenar os códigos de curso gerados
    int unique_codes[TOTAL_CODES];
    int passos;
    double tempo;
    int i, j;

    // Gerar códigos únicos e contar passos e tempo
    int num_generated = generate_unique_codes(unique_codes, TOTAL_CODES, &passos, &tempo);
    if (num_generated != TOTAL_CODES) {
        printf("Erro ao gerar códigos de curso únicos.\n");
        return 1;
    }

    // Inserir cursos com códigos únicos na árvore
    for (i = 0; i < TOTAL_CODES; ++i) {
        arv_curso *novo_curso = cria_no_curso();
        if (novo_curso == NULL) {
            printf("Erro ao criar novo curso.\n");
            break;
        }

        novo_curso->dados->codigo = unique_codes[i]; // Atribuir código único ao curso

        raiz_curso = inserir_curso(raiz_curso, novo_curso);
    }

    // Permitir que o usuário escolha um código para buscar
    int codigo_busca;
    printf("Digite o código que deseja buscar: ");
    scanf("%d", &codigo_busca);

    // Realizar busca 30 vezes pelo mesmo código, repetindo 10 vezes cada
    double tempos_busca[NUM_SEARCHES][REPEAT_SEARCHES];
    int passos_busca[NUM_SEARCHES][REPEAT_SEARCHES];
    for (i = 0; i < NUM_SEARCHES; ++i) {
        printf("\nRepetição %d:\n", i + 1);
        for (j = 0; j < REPEAT_SEARCHES; ++j) {
            double tempo_busca = buscar_disciplina_curso_contador(raiz_curso, codigo_busca, &passos);
            tempos_busca[i][j] = tempo_busca;
            passos_busca[i][j] = passos;

            printf("Busca %d - Passos: %d, Tempo: %.9f segundos\n", j + 1, passos, tempo_busca);
        }
    }

    // Calcular média dos tempos e passos de busca para cada repetição
    double medias_tempos[NUM_SEARCHES];
    double medias_passos[NUM_SEARCHES];
    for (i = 0; i < NUM_SEARCHES; ++i) {
        double soma_tempos = 0.0;
        int soma_passos = 0;
        for (j = 0; j < REPEAT_SEARCHES; ++j) {
            soma_tempos += tempos_busca[i][j];
            soma_passos += passos_busca[i][j];
        }
        medias_tempos[i] = soma_tempos / REPEAT_SEARCHES;
        medias_passos[i] = (double)soma_passos / REPEAT_SEARCHES;
        printf("\nMédia do tempo gasto na repetição %d: %.9f segundos\n", i + 1, medias_tempos[i]);
        printf("Média de passos na repetição %d: %.2f passos\n", i + 1, medias_passos[i]);
    }

    // Calcular média geral dos tempos e passos de busca
    double soma_medias_tempos = 0.0;
    double soma_medias_passos = 0.0;
    for (i = 0; i < NUM_SEARCHES; ++i) {
        soma_medias_tempos += medias_tempos[i];
        soma_medias_passos += medias_passos[i];
    }
    double media_geral_tempo = soma_medias_tempos / NUM_SEARCHES;
    double media_geral_passos = soma_medias_passos / NUM_SEARCHES;

    printf("\nMédia geral do tempo gasto nas buscas: %.9f segundos\n", media_geral_tempo);
    printf("Média geral de passos nas buscas: %.2f passos\n", media_geral_passos);

    // Restante da lógica do programa guiado por menu
    // Exemplo: menu(), switch case, etc.

    return 0;
}
