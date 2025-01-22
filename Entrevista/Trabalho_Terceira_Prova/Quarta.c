#include <stdio.h>      // Biblioteca para entrada e saída padrão.
#include <stdlib.h>     // Biblioteca para geração de números aleatórios e alocação de memória.
#include <string.h>     // Biblioteca para manipulação de strings.
#include <stdbool.h>    // Biblioteca para trabalhar com tipos booleanos (true/false).

#define TAMANHO_TABELA1 101      // Tamanho da primeira tabela hash.
#define TAMANHO_TABELA2 150      // Tamanho da segunda tabela hash.
#define MAX_FUNCIONARIOS 1000    // Número máximo de funcionários que podem ser gerados.

// Estrutura que representa um funcionário.
typedef struct {
    char Id[7];           // Matrícula do funcionário (6 caracteres + '\0').
    char userName[50];    // Nome do funcionário.
    char functionName[20];// Função desempenhada pelo funcionário.
    int salary;           // Salário do funcionário.
    bool isOccupied;      // Indica se a posição da tabela está ocupada.
} Employee;

// Função: rotate_left
// Realiza uma rotação à esquerda nos caracteres de uma matrícula.
// O primeiro caractere é movido para o final, e os demais são deslocados uma posição à esquerda.
void rotate_left(char *matricula) {
    char temp = matricula[0];       // Armazena o primeiro caractere.
    for (int i = 0; i < 5; i++) {   // Desloca os caracteres para a esquerda.
        matricula[i] = matricula[i + 1];
    }
    matricula[5] = temp;            // Insere o caractere inicial na última posição.
}

// Função: rotate_hash_function
// Calcula o índice hash de uma matrícula usando rotação e extração de dígitos.
// Rotaciona a matrícula, extrai os dígitos 2, 4 e 6, soma os valores e aplica módulo.
int rotate_hash_function(char *matricula, int tamanho_tabela) {
    rotate_left(matricula);                     // Rotaciona os caracteres da matrícula.
    int d2 = matricula[1] - '0';                // Extrai o 2º dígito como número.
    int d4 = matricula[3] - '0';                // Extrai o 4º dígito como número.
    int d6 = matricula[5] - '0';                // Extrai o 6º dígito como número.
    return (d2 + d4 + d6) % tamanho_tabela;     // Calcula o índice hash.
}

// Função: hash_fold_and_shift
// Calcula o índice hash dividindo os dígitos da matrícula em dois grupos e somando-os.
// Aplica módulo do resultado para obter o índice.
int hash_fold_and_shift(char *matricula, int tamanho_tabela) {
    int grupo1 = (matricula[0] - '0') * 100 + (matricula[2] - '0') * 10 + (matricula[5] - '0'); // Grupo 1: Dígitos 0, 2 e 5.
    int grupo2 = (matricula[1] - '0') * 100 + (matricula[3] - '0') * 10 + (matricula[4] - '0'); // Grupo 2: Dígitos 1, 3 e 4.
    return (grupo1 + grupo2) % tamanho_tabela;  // Soma os dois grupos e aplica módulo.
}

// Função: handle_rotation_collision
// Resolve colisões no método de hash baseado em rotação.
// Usa o 1º dígito da matrícula como incremento para calcular o novo índice.
int handle_rotation_collision(int indice, int i, char *matricula, int tamanho_tabela) {
    int incremento = matricula[0] - '0';        // Incremento baseado no 1º dígito.
    return (indice + i * incremento) % tamanho_tabela; // Calcula novo índice.
}

// Função: handle_fold_shift_collision
// Resolve colisões no método Fold and Shift.
// Usa um incremento fixo (número primo) para calcular o novo índice.
int handle_fold_shift_collision(int indice, int i, int tamanho_tabela) {
    int incremento = 7;                        // Incremento fixo (primo).
    return (indice + i * incremento) % tamanho_tabela; // Calcula novo índice.
}

// Função: insertEmployee
// Insere um funcionário na tabela hash, resolvendo colisões quando necessário.
bool insertEmployee(Employee *tabela, Employee funcionario, int tamanho_tabela, int (*hash_func)(char *, int), int *colisoes, int metodo) {
    int indice = hash_func(funcionario.Id, tamanho_tabela); // Índice inicial.
    bool inserido = false;                                 // Indica se foi inserido.
    int i = 0;                                             // Contador de tentativas.

    while (i < tamanho_tabela && !inserido) {              // Tenta inserir enquanto houver espaço.
        int posicao = 0;

        // Define a estratégia de resolução de colisão.
        if (metodo == 1) { 
            posicao = handle_rotation_collision(indice, i, funcionario.Id, tamanho_tabela);
        } else if (metodo == 2) { 
            posicao = handle_fold_shift_collision(indice, i, tamanho_tabela);
        }

        // Verifica se a posição está livre.
        if (!tabela[posicao].isOccupied) {
            tabela[posicao] = funcionario;                 // Insere o funcionário.
            tabela[posicao].isOccupied = true;             // Marca posição como ocupada.
            inserido = true;                               // Marca como inserido.
        } else {
            (*colisoes)++;                                 // Incrementa contador de colisões.
        }

        i++;                                               // Próxima tentativa.
    }

    return inserido;                                       // Retorna se foi inserido.
}

// Função: initialize_employee_table
// Inicializa a tabela hash, marcando todas as posições como vazias.
void initialize_employee_table(Employee *tabela, int tamanho_tabela) {
    for (int i = 0; i < tamanho_tabela; i++) {
        tabela[i].isOccupied = false;                      // Marca como vazio.
    }
}

// Função: generate_employee_data
// Gera dados fictícios de funcionários para preencher a tabela hash.
void generate_employee_data(Employee *dados, int total) {
    for (int i = 0; i < total; i++) {
        sprintf(dados[i].Id, "%06d", rand() % 1000000);    // Gera matrícula aleatória (6 dígitos).
        sprintf(dados[i].userName, "Funcionario_%d", i);   // Gera nome.
        sprintf(dados[i].functionName, "Funcao_%d", i % 4);// Gera função cíclica.
        dados[i].salary = 3000 + rand() % 20000;           // Gera salário entre 3000 e 23000.
        dados[i].isOccupied = false;                      // Marca como não ocupado inicialmente.
    }
}

// Função: print_hash_table
// Imprime a tabela hash no console em formato tabular.
void print_hash_table(Employee *tabela, int tamanho_tabela) {
    printf("+--------+------------+------------+-------------------+-------------+\n");
    printf("| Indice | Matricula  | Nome       | Funcao            | Salario     |\n");
    printf("+--------+------------+------------+-------------------+-------------+\n");
    for (int i = 0; i < tamanho_tabela; i++) {
        if (tabela[i].isOccupied) {                       // Se posição está ocupada.
            printf("| %6d | %-10s | %-10s | %-17s | %11d |\n",
                   i, tabela[i].Id, tabela[i].userName,
                   tabela[i].functionName, tabela[i].salary);
        } else {
            printf("| %6d | %-10s | %-10s | %-17s | %-11s |\n",
                   i, "Vazio", "Vazio", "Vazio", "Vazio"); // Posição vazia.
        }
    }
    printf("+--------+------------+------------+-------------------+-------------+\n");
}

// Função principal: main
// Controla o fluxo principal do programa.
int main() {
    Employee tabela1[TAMANHO_TABELA1], tabela2[TAMANHO_TABELA2]; // Duas tabelas hash.
    Employee dados[MAX_FUNCIONARIOS];                           // Dados de funcionários.
    int continuar = 1;                                          // Controle de repetição.

    generate_employee_data(dados, MAX_FUNCIONARIOS);            // Gera dados fictícios.

    while (continuar) {
        int metodo, tamanho_tabela;
        int (*hash_func)(char *, int); // Ponteiro para a função hash.

        // Escolha do método de hashing.
        printf("Escolha o método de hashing:\n");
        printf("1 - Rotacao e Extracao\n");
        printf("2 - Fold Shift\n");
        scanf("%d", &metodo);

        // Escolha do tamanho da tabela.
        printf("Escolha o tamanho da tabela:\n");
        printf("1 - %d (Tabela 1)\n", TAMANHO_TABELA1);
        printf("2 - %d (Tabela 2)\n", TAMANHO_TABELA2);
        int opcao_tamanho;
        scanf("%d", &opcao_tamanho);

        if (opcao_tamanho == 1) {
            tamanho_tabela = TAMANHO_TABELA1;
            initialize_employee_table(tabela1, tamanho_tabela); // Inicializa tabela 1.
        } else {
            tamanho_tabela = TAMANHO_TABELA2;
            initialize_employee_table(tabela2, tamanho_tabela); // Inicializa tabela 2.
        }

        hash_func = (metodo == 1) ? rotate_hash_function : hash_fold_and_shift; // Define função hash.

        int colisoes = 0; // Contador de colisões.

        // Insere funcionários na tabela hash.
        for (int i = 0; i < MAX_FUNCIONARIOS; i++) {
            if (opcao_tamanho == 1) {
                insertEmployee(tabela1, dados[i], tamanho_tabela, hash_func, &colisoes, metodo);
            } else {
                insertEmployee(tabela2, dados[i], tamanho_tabela, hash_func, &colisoes, metodo);
            }
        }

        // Imprime a tabela hash selecionada.
        printf("\nTabela escolhida:\n");
        if (opcao_tamanho == 1) {
            print_hash_table(tabela1, tamanho_tabela);
        } else {
            print_hash_table(tabela2, tamanho_tabela);
        }

        printf("\nTotal de colisoes: %d\n", colisoes);

        // Pergunta se o usuário deseja continuar.
        printf("\nDeseja continuar? (1 - Sim, 0 - Nao): ");
        scanf("%d", &continuar);
    }

    printf("Programa encerrado.\n");
    return 0;
}
