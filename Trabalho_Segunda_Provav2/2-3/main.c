#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_portugues-23.c"
#include "arv_ingles-binaria.c"

// Função para carregar o arquivo com as palavras e traduções
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

// Função auxiliar para exibir palavras de uma unidade específica
void exibirPalavrasPorUnidade(Tree23Node *arvore, int unidade) {
    if (arvore) {
        // Percorre a subárvore esquerda
        exibirPalavrasPorUnidade(arvore->left, unidade);

        // Verifica e exibe palavras da unidade na info1
        if (arvore->info1.unit == unidade) {
            printf("%s:", arvore->info1.portugueseWord); // Exibe palavra em português
            printBinaryTree(arvore->info1.englishTreeRoot); // Exibe traduções associadas
        }

        // Verifica e exibe palavras da unidade na info2 (se existir)
        if (arvore->nInfos == 2 && arvore->info2.unit == unidade) {
            printf("%s:", arvore->info2.portugueseWord); // Exibe palavra em português
            printBinaryTree(arvore->info2.englishTreeRoot); // Exibe traduções associadas
        }

        // Percorre as subárvores do meio e direita
        exibirPalavrasPorUnidade(arvore->middle, unidade);
        if (arvore->nInfos == 2) {
            exibirPalavrasPorUnidade(arvore->right, unidade);
        }
    }
}

// Função principal para exibir a árvore no formato do arquivo
void exibirArvoreFormatoArquivo(Tree23Node *arvore) {
    int unidade = 1;
    while (1) {
        // Verifica se há palavras para a unidade atual
        int temPalavras = 0;

        // Percorre a árvore para verificar se há palavras nessa unidade
        void verificarUnidade(Tree23Node *no) {
            if (no) {
                if (no->info1.unit == unidade || (no->nInfos == 2 && no->info2.unit == unidade)) {
                    temPalavras = 1;
                }
                verificarUnidade(no->left);
                verificarUnidade(no->middle);
                if (no->nInfos == 2) verificarUnidade(no->right);
            }
        }
        verificarUnidade(arvore);

        // Se não houver mais palavras para exibir, interrompe o loop
        if (!temPalavras) break;

        // Exibe o cabeçalho da unidade
        printf("%% Unidade %d\n", unidade);

        // Exibe as palavras da unidade atual
        exibirPalavrasPorUnidade(arvore, unidade);

        // Passa para a próxima unidade
        unidade++;
    }
}


int main() {
    Tree23Node *arvore23 = NULL;

    // Carregar o arquivo de palavras
    carregarArquivo("C:/Users/PurooLight/Documents/GitHub/EstruturaDeDadosII-GRUPO/Trabalho_Segunda_Provav2/2-3/vocabulario.txt", &arvore23);

    // Exibir os valores da árvore 2-3
    printf("Árvore 2-3 carregada:\n");
    exibirArvoreFormatoArquivo(arvore23);

    return 0;
}
