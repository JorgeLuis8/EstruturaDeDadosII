#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TAMANHO_TEXTO 1000000
#define NUM_TESTES 15

// Função para Cifra de César
void cifraCesar(char texto[], int chave) {
    int i;
    char letra;

    for (i = 0; texto[i] != '\0'; i++) {
        letra = texto[i];

        // Apenas cifrar letras
        if (isalpha(letra)) {
            // Caso seja letra maiúscula
            if (isupper(letra)) {
                letra = (letra - 'A' + chave) % 26 + 'A';
            }
            // Caso seja letra minúscula
            else if (islower(letra)) {
                letra = (letra - 'a' + chave) % 26 + 'a';
            }
        }

        texto[i] = letra;
    }
}

// Função para Cifra de Vigenère
void cifraVigenere(char texto[], char chave[]) {
    int i, j = 0;
    int lenChave = strlen(chave);
    char letra, letraChave;

    for (i = 0; texto[i] != '\0'; i++) {
        letra = texto[i];

        // Apenas cifrar letras
        if (isalpha(letra)) {
            letraChave = toupper(chave[j % lenChave]) - 'A';  // Normaliza a chave

            // Caso seja letra maiúscula
            if (isupper(letra)) {
                letra = (letra - 'A' + letraChave) % 26 + 'A';
            }
            // Caso seja letra minúscula
            else if (islower(letra)) {
                letra = (letra - 'a' + letraChave) % 26 + 'a';
            }

            j++; // Avança na chave apenas se for uma letra
        }

        texto[i] = letra;
    }
}

// Função para gerar texto de teste com 1 milhão de caracteres
void gerarTextoTeste(char texto[]) {
    const char *padrao = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";  // Padrão repetido
    int tamanhoPadrao = strlen(padrao);

    for (int i = 0; i < TAMANHO_TEXTO; i++) {
        texto[i] = padrao[i % tamanhoPadrao];  // Repetir o padrão
    }

    texto[TAMANHO_TEXTO] = '\0';  // Terminar o texto com caractere nulo
}

// Função para calcular a média de tempo de execução
double calcularMedia(double tempos[], int numTestes) {
    double soma = 0.0;
    for (int i = 0; i < numTestes; i++) {
        soma += tempos[i];
    }
    return soma / numTestes;
}

int main() {
    int opcao;
    char texto[TAMANHO_TEXTO + 1];  // Buffer de 1 milhão de caracteres + 1 para o '\0'
    char chave[100];
    int chaveCesar;
    double tempos[NUM_TESTES];
    clock_t inicio, fim;
    double tempoDecorrido;
    FILE *arquivo;

    // Gerar texto de teste com 1 milhão de caracteres
    gerarTextoTeste(texto);

    // Menu
    do {
        printf("\nEscolha uma opção de criptografia:\n");
        printf("1. Cifra de César\n");
        printf("2. Cifra de Vigenère\n");
        printf("3. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer de nova linha

        switch(opcao) {
            case 1:
                printf("Usando texto de teste com 1 milhão de caracteres.\n");

                printf("Digite a chave (deslocamento): ");
                scanf("%d", &chaveCesar);
                getchar();  // Limpar buffer de nova linha

                // Abrir arquivo para salvar tempos
                arquivo = fopen("tempos_cifra_cesar.txt", "w");
                if (arquivo == NULL) {
                    printf("Erro ao criar arquivo!\n");
                    return 1;
                }

                // Executar o teste 15 vezes para calcular a média
                for (int t = 0; t < NUM_TESTES; t++) {
                    gerarTextoTeste(texto);  // Regenerar o texto original para cada teste
                    inicio = clock();  // Início da medição de tempo

                    cifraCesar(texto, chaveCesar);

                    fim = clock();  // Fim da medição de tempo
                    tempoDecorrido = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                    tempos[t] = tempoDecorrido;

                    // Escrever tempo individual no arquivo
                    fprintf(arquivo, "Teste %d: %.6f segundos\n", t + 1, tempos[t]);
                }

                // Escrever a média no arquivo
                fprintf(arquivo, "\nTempo médio para Cifra de César: %.6f segundos\n", calcularMedia(tempos, NUM_TESTES));
                fclose(arquivo);

                printf("Tempos e média salvos em 'tempos_cifra_cesar.txt'.\n");
                break;

            case 2:
                printf("Usando texto de teste com 1 milhão de caracteres.\n");

                printf("Digite a chave (palavra-chave): ");
                fgets(chave, sizeof(chave), stdin);

                // Remove o newline da chave, se houver
                chave[strcspn(chave, "\n")] = '\0';

                // Abrir arquivo para salvar tempos
                arquivo = fopen("tempos_cifra_vigenere.txt", "w");
                if (arquivo == NULL) {
                    printf("Erro ao criar arquivo!\n");
                    return 1;
                }

                // Executar o teste 15 vezes para calcular a média
                for (int t = 0; t < NUM_TESTES; t++) {
                    gerarTextoTeste(texto);  // Regenerar o texto original para cada teste
                    inicio = clock();  // Início da medição de tempo

                    cifraVigenere(texto, chave);

                    fim = clock();  // Fim da medição de tempo
                    tempoDecorrido = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                    tempos[t] = tempoDecorrido;

                    // Escrever tempo individual no arquivo
                    fprintf(arquivo, "Teste %d: %.6f segundos\n", t + 1, tempos[t]);
                }

                // Escrever a média no arquivo
                fprintf(arquivo, "\nTempo médio para Cifra de Vigenère: %.6f segundos\n", calcularMedia(tempos, NUM_TESTES));
                fclose(arquivo);

                printf("Tempos e média salvos em 'tempos_cifra_vigenere.txt'.\n");
                break;

            case 3:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while(opcao != 3);

    return 0;
}
