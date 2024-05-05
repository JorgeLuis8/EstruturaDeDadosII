#include <stdio.h>
#include <stdlib.h>

void gerar_strings_alfabeticas_arquivo(int n, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        // Gerar a string: 'a' até 'z', adicionando 'a' + (índice % 26) e (índice / 26 + 1)
        char string[3];
        string[0] = 'a' + (i % 26);
        string[1] = '0' + (i / 26 + 1);
        string[2] = '\0'; // Terminador de string

        // Escrever a string no arquivo
        fprintf(arquivo, "%s\n", string);
    }

    fclose(arquivo);
}

int main() {
    int n = 10;
    const char *nome_arquivo = "strings.txt";
    gerar_strings_alfabeticas_arquivo(n, nome_arquivo);
    printf("Strings geradas e salvas no arquivo '%s'.\n", nome_arquivo);
    return 0;
}
