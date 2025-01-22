#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAMANHO_TABELA1 101
#define TAMANHO_TABELA2 150
#define MAX_FUNCIONARIOS 1000

typedef struct {
    char Id[7];
    char userName[50];
    char functionName[20];
    int salary;
    bool isOccupied;
} Employee;

void rotate_left(char *matricula) {
    char temp = matricula[0];
    for (int i = 0; i < 5; i++) {
        matricula[i] = matricula[i + 1];
    }
    matricula[5] = temp;
}

int rotate_hash_function(char *matricula, int tamanho_tabela) {
    rotate_left(matricula);
    int d2 = matricula[1] - '0';
    int d4 = matricula[3] - '0';
    int d6 = matricula[5] - '0';
    return (d2 + d4 + d6) % tamanho_tabela;
}

int hash_fold_and_shift(char *matricula, int tamanho_tabela) {
    int grupo1 = (matricula[0] - '0') * 100 + (matricula[2] - '0') * 10 + (matricula[5] - '0');
    int grupo2 = (matricula[1] - '0') * 100 + (matricula[3] - '0') * 10 + (matricula[4] - '0');
    return (grupo1 + grupo2) % tamanho_tabela;
}

int handle_rotation_collision(int indice, int i, char *matricula, int tamanho_tabela) {
    int incremento = matricula[0] - '0'; 
    return (indice + i * incremento) % tamanho_tabela;
}

int handle_fold_shift_collision(int indice, int i, int tamanho_tabela) {
    int incremento = 7; 
    return (indice + i * incremento) % tamanho_tabela;
}

bool insertEmployee(Employee *tabela, Employee funcionario, int tamanho_tabela, int (*hash_func)(char *, int), int *colisoes, int metodo) {
    int indice = hash_func(funcionario.Id, tamanho_tabela);
    bool inserido = false;
    bool metodo_valido = (metodo == 1 || metodo == 2);
    int i = 0;

 
    if (!metodo_valido) {
        inserido = false;
    } else {
        while (i < tamanho_tabela && !inserido) {
            int posicao = 0;

   
            if (metodo == 1) { 
                posicao = handle_rotation_collision(indice, i, funcionario.Id, tamanho_tabela);
            } else if (metodo == 2) { 
                posicao = handle_fold_shift_collision(indice, i, tamanho_tabela);
            }

    
            if (!tabela[posicao].isOccupied) {
                tabela[posicao] = funcionario;
                tabela[posicao].isOccupied = true;
                inserido = true;
            } else {
                (*colisoes)++;
            }

            i++; 
        }

        if (!inserido) {
            tabela[0] = funcionario;
            tabela[0].isOccupied = true;
        }
    }

    return inserido;
}




void initialize_employee_table(Employee *tabela, int tamanho_tabela) {
    for (int i = 0; i < tamanho_tabela; i++) {
        tabela[i].isOccupied = false;
    }
}


void generate_employee_data(Employee *dados, int total) {
    for (int i = 0; i < total; i++) {
        sprintf(dados[i].Id, "%06d", rand() % 1000000);
        sprintf(dados[i].userName, "Funcionario_%d", i);
        sprintf(dados[i].functionName, "Funcao_%d", i % 4);
        dados[i].salary = 3000 + rand() % 20000;
        dados[i].isOccupied = false;
    }
}


void print_hash_table(Employee *tabela, int tamanho_tabela) {
    printf("+--------+------------+------------+-------------------+-------------+\n");
    printf("| Indice | Matricula  | Nome       | Funcao            | Salario     |\n");
    printf("+--------+------------+------------+-------------------+-------------+\n");
    for (int i = 0; i < tamanho_tabela; i++) {
        if (tabela[i].isOccupied) {
            printf("| %6d | %-10s | %-10s | %-17s | %11d |\n",
                   i, tabela[i].Id, tabela[i].userName,
                   tabela[i].functionName, tabela[i].salary);
        } else {
            printf("| %6d | %-10s | %-10s | %-17s | %-11s |\n",
                   i, "Vazio", "Vazio", "Vazio", "Vazio");
        }
    }
    printf("+--------+------------+------------+-------------------+-------------+\n");
}


int main() {
   Employee tabela1[TAMANHO_TABELA1], tabela2[TAMANHO_TABELA2];
    Employee dados[MAX_FUNCIONARIOS];
    int continuar = 1;

    generate_employee_data(dados, MAX_FUNCIONARIOS);

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
            initialize_employee_table(tabela1, tamanho_tabela);
        } else {
            tamanho_tabela = TAMANHO_TABELA2;
            initialize_employee_table(tabela2, tamanho_tabela);
        }

        hash_func = (metodo == 1) ? rotate_hash_function : hash_fold_and_shift;

        int colisoes = 0;

        for (int i = 0; i < MAX_FUNCIONARIOS; i++) {
            if (opcao_tamanho == 1) {
                insertEmployee(tabela1, dados[i], tamanho_tabela, hash_func, &colisoes, metodo);
            } else {
                insertEmployee(tabela2, dados[i], tamanho_tabela, hash_func, &colisoes, metodo);
            }
        }

        printf("\nTabela escolhida:\n");
        if (opcao_tamanho == 1) {
            print_hash_table(tabela1, tamanho_tabela);
        } else {
            print_hash_table(tabela2, tamanho_tabela);
        }

        printf("\nTotal de colisoes: %d\n", colisoes);

        printf("\nDeseja continuar? (1 - Sim, 0 - Nao): ");
        scanf("%d", &continuar);
    }

    printf("Programa encerrado.\n");
    return 0;
}

/* Função: rotate_left
   Propósito:
   - Realiza uma rotação à esquerda nos caracteres de uma matrícula, movendo o primeiro caractere para o final.

   Funcionamento:
   1. O primeiro caractere é armazenado em uma variável temporária.
   2. Todos os caracteres são deslocados uma posição para a esquerda.
   3. O caractere armazenado temporariamente é colocado na última posição.

   Explicação:
   - Essa função é usada para modificar a estrutura da matrícula e garantir maior dispersão dos valores ao aplicar uma função de hash. */

/* Função: rotate_hash_function
   Propósito:
   - Calcula o índice hash de uma matrícula utilizando o método de rotação e extração.

   Funcionamento:
   1. A matrícula passa por uma rotação à esquerda (chamando `rotate_left`).
   2. Os dígitos 2, 4 e 6 da matrícula são extraídos.
   3. A soma dos valores desses dígitos é calculada.
   4. O índice hash final é obtido como o resto da divisão dessa soma pelo tamanho da tabela.

   Explicação:
   - Este método combina diferentes dígitos da matrícula, reduzindo a probabilidade de colisões para matrículas similares. */

/* Função: hash_fold_and_shift
   Propósito:
   - Calcula o índice hash de uma matrícula utilizando a técnica de divisão em grupos e soma.

   Funcionamento:
   1. Divide a matrícula em dois grupos de dígitos:
      - Grupo 1: Dígitos 0, 2 e 5.
      - Grupo 2: Dígitos 1, 3 e 4.
   2. Cada grupo é convertido para um número inteiro.
   3. Soma os valores dos dois grupos.
   4. O índice hash final é obtido como o resto da divisão dessa soma pelo tamanho da tabela.

   Explicação:
   - Este método utiliza mais informações da matrícula (dois grupos) para calcular o índice hash, melhorando a dispersão. */

/* Função: handle_rotation_collision
   Propósito:
   - Resolve colisões para o método de hash baseado em rotação, utilizando incrementos dependentes da matrícula.

   Funcionamento:
   1. Calcula um incremento baseado no primeiro dígito da matrícula.
   2. Ajusta a posição do índice hash adicionando o incremento multiplicado pelo número de tentativas (i).
   3. Retorna o novo índice ajustado.

   Explicação:
   - A dependência do incremento no primeiro dígito da matrícula reduz a chance de ciclos repetitivos durante a resolução de colisões. */

/* Função: handle_fold_shift_collision
   Propósito:
   - Resolve colisões para o método de hash baseado em Fold Shift, utilizando um incremento fixo.

   Funcionamento:
   1. Define um incremento fixo (neste caso, 7).
   2. Ajusta a posição do índice hash adicionando o incremento multiplicado pelo número de tentativas (i).
   3. Retorna o novo índice ajustado.

   Explicação:
   - Um incremento fixo é simples de implementar e evita ciclos, funcionando bem para tabelas com tamanhos primos. */

/* Função: insertEmployee
   Propósito:
   - Insere um funcionário na tabela hash, resolvendo colisões quando necessário.

   Funcionamento:
   1. Calcula o índice inicial usando a função de hash escolhida.
   2. Tenta inserir o funcionário na posição calculada.
   3. Se houver colisão:
      - Calcula uma nova posição usando o método de resolução de colisões escolhido.
      - Incrementa o contador de colisões.
   4. Continua até encontrar uma posição vazia ou percorrer toda a tabela.

   Explicação:
   - Combina hashing e métodos de resolução de colisões para garantir que todos os funcionários possam ser inseridos na tabela. */

/* Função: initialize_employee_table
   Propósito:
   - Inicializa a tabela de funcionários, marcando todas as posições como vazias.

   Funcionamento:
   1. Itera por todas as posições da tabela.
   2. Define o campo `isOccupied` como falso para cada posição.

   Explicação:
   - Garante que a tabela hash esteja pronta para receber os funcionários, sem valores residuais. */

/* Função: generate_employee_data
   Propósito:
   - Gera dados fictícios para os funcionários, incluindo matrícula, nome, função e salário.

   Funcionamento:
   1. Para cada funcionário:
      - Gera uma matrícula aleatória de 6 dígitos.
      - Cria um nome no formato "Funcionario_X".
      - Atribui uma função no formato "Funcao_Y" (cíclico entre 4 funções).
      - Gera um salário aleatório entre 3000 e 23000.

   Explicação:
   - Essa função simula dados reais, permitindo testar a funcionalidade da tabela hash com diferentes entradas. */

/* Função: print_hash_table
   Propósito:
   - Exibe a tabela hash em formato tabular, mostrando os funcionários armazenados.

   Funcionamento:
   1. Percorre todas as posições da tabela.
   2. Para cada posição:
      - Se estiver ocupada, exibe os dados do funcionário.
      - Caso contrário, exibe "Vazio".

   Explicação:
   - Facilita a análise visual da distribuição de funcionários na tabela hash, ajudando a identificar colisões e padrões de dispersão. */
