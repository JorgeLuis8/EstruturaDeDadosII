#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO_TABELA1 101
#define TAMANHO_TABELA2 150
#define MAX_FUNCIONARIOS 1000

typedef struct {
    char matricula[7];
    char nome[50];
    char funcao[20];
    int salario;
    bool ocupado;
} Funcionario;

// Função para realizar a rotação à esquerda
void rotacao_esquerda(char *matricula) {
    char temp = matricula[0];
    for (int i = 0; i < 5; i++) {
        matricula[i] = matricula[i + 1];
    }
    matricula[5] = temp;
}

// Função de hashing personalizada: Rotação e Extração
int funcao_hashing_rotacao(char *matricula, int tamanho_tabela) {
    rotacao_esquerda(matricula);
    int d2 = matricula[1] - '0';
    int d4 = matricula[3] - '0';
    int d6 = matricula[5] - '0';
    return (d2 + d4 + d6) % tamanho_tabela;
}

// Função de hashing: Fold Shift
int funcao_hashing_fold_shift(char *matricula, int tamanho_tabela) {
    int grupo1 = (matricula[0] - '0') * 100 + (matricula[2] - '0') * 10 + (matricula[5] - '0');
    int grupo2 = (matricula[1] - '0') * 100 + (matricula[3] - '0') * 10 + (matricula[4] - '0');
    return (grupo1 + grupo2) % tamanho_tabela;
}

// Inserção com colisões tratadas por substituição
bool inserir(Funcionario *tabela, Funcionario funcionario, int tamanho_tabela, int (*hash_func)(char *, int), int *colisoes) {
    int indice = hash_func(funcionario.matricula, tamanho_tabela);
    int primeiro_digito = funcionario.matricula[0] - '0';

    for (int i = 0; i < tamanho_tabela; i++) {
        int posicao = (indice + i * primeiro_digito) % tamanho_tabela;

        if (!tabela[posicao].ocupado) {
            tabela[posicao] = funcionario;
            tabela[posicao].ocupado = true;
            return true;
        }

        (*colisoes)++;
    }

    // Substituir a primeira posição se todas as tentativas falharem
    tabela[0] = funcionario;
    tabela[0].ocupado = true;
    return false;
}

// Inicializar tabela
void inicializar_tabela(Funcionario *tabela, int tamanho_tabela) {
    for (int i = 0; i < tamanho_tabela; i++) {
        tabela[i].ocupado = false;
    }
}

// Função para gerar dados fictícios
void gerar_dados(Funcionario *dados, int total) {
    for (int i = 0; i < total; i++) {
        sprintf(dados[i].matricula, "%06d", rand() % 1000000);
        sprintf(dados[i].nome, "Funcionario_%d", i);
        sprintf(dados[i].funcao, "Funcao_%d", i % 4);
        dados[i].salario = 3000 + rand() % 20000;
        dados[i].ocupado = false;
    }
}

// Imprimir tabela hash
void imprimir_tabela_hash(Funcionario *tabela, int tamanho_tabela) {
    printf("+--------+------------+------------+-------------------+-------------+\n");
    printf("| Indice | Matricula  | Nome       | Funcao            | Salario     |\n");
    printf("+--------+------------+------------+-------------------+-------------+\n");
    for (int i = 0; i < tamanho_tabela; i++) {
        if (tabela[i].ocupado) {
            printf("| %6d | %-10s | %-10s | %-17s | %11d |\n",
                   i, tabela[i].matricula, tabela[i].nome,
                   tabela[i].funcao, tabela[i].salario);
        } else {
            printf("| %6d | %-10s | %-10s | %-17s | %-11s |\n",
                   i, "Vazio", "Vazio", "Vazio", "Vazio");
        }
    }
    printf("+--------+------------+------------+-------------------+-------------+\n");
}

// Função principal
int main() {
    Funcionario tabela1[TAMANHO_TABELA1], tabela2[TAMANHO_TABELA2];
    Funcionario dados[MAX_FUNCIONARIOS];
    int continuar = 1;

    gerar_dados(dados, MAX_FUNCIONARIOS);

    while (continuar) {
        int metodo, tamanho_tabela;
        int (*hash_func)(char *, int);

        printf("Escolha o método de hashing:\n");
        printf("1 - Rotacao e Extracao\n");
        printf("2 - Fold Shift\n");
        scanf("%d", &metodo);

        printf("Escolha o tamanho da tabela:\n");
        printf("1 - %d (Tabela 1)\n", TAMANHO_TABELA1);
        printf("2 - %d (Tabela 2)\n", TAMANHO_TABELA2);
        int opcao_tamanho;
        scanf("%d", &opcao_tamanho);

        if (opcao_tamanho == 1) {
            tamanho_tabela = TAMANHO_TABELA1;
            inicializar_tabela(tabela1, tamanho_tabela);
        } else {
            tamanho_tabela = TAMANHO_TABELA2;
            inicializar_tabela(tabela2, tamanho_tabela);
        }

        hash_func = (metodo == 1) ? funcao_hashing_rotacao : funcao_hashing_fold_shift;

        int colisoes = 0;

        for (int i = 0; i < MAX_FUNCIONARIOS; i++) {
            if (opcao_tamanho == 1) {
                inserir(tabela1, dados[i], tamanho_tabela, hash_func, &colisoes);
            } else {
                inserir(tabela2, dados[i], tamanho_tabela, hash_func, &colisoes);
            }
        }

        printf("\nTabela escolhida:\n");
        if (opcao_tamanho == 1) {
            imprimir_tabela_hash(tabela1, tamanho_tabela);
        } else {
            imprimir_tabela_hash(tabela2, tamanho_tabela);
        }

        printf("\nTotal de colisoes: %d\n", colisoes);

        printf("\nDeseja continuar? (1 - Sim, 0 - Nao): ");
        scanf("%d", &continuar);
    }

    printf("Programa encerrado.\n");
    return 0;
}
