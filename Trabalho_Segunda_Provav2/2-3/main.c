#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_portugues-23.c"
#include "arv_ingles-binaria.c"

void carregarArquivo(const char *nomeArquivo, Tree23Node **arvore) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int unidadeAtual = 0; // Variável para armazenar a unidade atual

    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remove a quebra de linha ao final
        linha[strcspn(linha, "\n")] = 0;

        // Verifica se é uma linha de unidade
        if (linha[0] == '%') {
            sscanf(linha, "%% Unidade %d", &unidadeAtual);
        } else {
            // Processar linha com palavra em inglês e traduções em português
            char palavraIngles[50];
            char traducoesPortugues[200];

            if (sscanf(linha, "%[^:]: %[^\n]", palavraIngles, traducoesPortugues) == 2) {
                // Processar cada tradução em português
                char *traducaoPortugues = strtok(traducoesPortugues, ",;");
                while (traducaoPortugues != NULL) {
                    // Remove espaços em branco no início da tradução
                    while (*traducaoPortugues == ' ') traducaoPortugues++;

                    // Cria um novo Info para a tradução em português
                    Info novoInfo = criarInfo(traducaoPortugues, unidadeAtual);

                    // Adiciona a palavra em inglês na árvore binária associada
                    adicionarTraducao(&novoInfo, palavraIngles, unidadeAtual);

                    // Insere o Info (com a árvore binária preenchida) na árvore 2-3
                    inserirValorArvore(arvore, novoInfo);

                    // Próxima tradução
                    traducaoPortugues = strtok(NULL, ",;");
                }
            }
        }
    }

    fclose(arquivo);
}



// Função para exibir os valores do arquivo
void exibirArvore23(Tree23Node *arvore) {
    if (arvore) {
        // Exibe subárvore à esquerda
        exibirArvore23(arvore->left);

        // Exibe o primeiro Info
        printf("Palavra em Português: %s (Unidade: %d)\n", arvore->info1.portugueseWord, arvore->info1.unit);
        printf("Traduções em Inglês:\n");
        printBinaryTree(arvore->info1.englishTreeRoot); // Imprime a árvore binária associada

        // Exibe o segundo Info, se existir
        if (arvore->nInfos == 2) {
            printf("Palavra em Português: %s (Unidade: %d)\n", arvore->info2.portugueseWord, arvore->info2.unit);
            printf("Traduções em Inglês:\n");
            printBinaryTree(arvore->info2.englishTreeRoot); // Imprime a árvore binária associada
        }

        // Exibe subárvores do meio e à direita
        exibirArvore23(arvore->middle);
        if (arvore->nInfos == 2) {
            exibirArvore23(arvore->right);
        }
    }
}


int main() {
    Tree23Node *arvore23 = NULL;

    // Carregar o arquivo de palavras
    carregarArquivo("C:/Users/PurooLight/Documents/GitHub/EstruturaDeDadosII-GRUPO/Trabalho_Segunda_Provav2/2-3/vocabulario.txt", &arvore23);

    // Exibir os valores da árvore 2-3
    printf("Árvore 2-3 carregada:\n");
    exibirArvore23(arvore23);

    return 0;
}




