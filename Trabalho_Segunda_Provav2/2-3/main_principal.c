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

// Função para verificar se há palavras para a unidade atual
void verificarUnidade(Tree23Node *no, int unidade, int *temPalavras) {
    if (no) {
        if (no->info1.unit == unidade || (no->nInfos == 2 && no->info2.unit == unidade)) {
            *temPalavras = 1;
        }
        verificarUnidade(no->left, unidade, temPalavras);
        verificarUnidade(no->middle, unidade, temPalavras);
        if (no->nInfos == 2) verificarUnidade(no->right, unidade, temPalavras);
    }
}

// Função principal para exibir a árvore no formato do arquivo
void exibirArvoreFormatoArquivo(Tree23Node *arvore) {
    int unidade = 1;
    while (1) {
        // Verifica se há palavras para a unidade atual
        int temPalavras = 0;

        // Percorre a árvore para verificar se há palavras nessa unidade
        verificarUnidade(arvore, unidade, &temPalavras);

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

// Função para exibir o menu de opções
void exibirMenu() {
    printf("\nEscolha uma opção:\n");
    printf("1 - Imprimir traduções por unidade\n");
    printf("2 - Imprimir uma unidade específica e suas traduções\n");
    printf("3 - Imprimir traduções em inglês de uma palavra em português\n");
    printf("4 - Remover uma palavra em inglês de uma unidade\n");
    printf("5 - Remover uma palavra em português de uma unidade\n");
    printf("6 - Sair\n");
    printf("Digite sua opção: ");
}

int main() {
    Tree23Node *arvore = NULL;
    TreeNode *arvoreIngles = NULL;

    int opcao = -1;
    int unidade;
    char palavraPortugues[50];
    char palavraIngles[50];

    // Carregar o arquivo de palavras
    carregarArquivo("C:/Users/jorge/OneDrive/Documentos/GitHub/ED2-JOB2/Trabalho_Segunda_Provav2/2-3/vocabulario.txt", &arvore);

    // Loop principal do menu
    while (opcao != 6) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // (i) Imprimir todas as palavras em português e traduções por unidade
                imprimirArvorePorUnidade(arvore);
                break;
            case 2:
                // (ii) Informar uma unidade específica e imprimir palavras e traduções
                printf("Digite a unidade: ");
                scanf("%d", &unidade);
                imprimirPorDadaUnidadeTraducoes(arvore, unidade);
                break;
            case 3:
                // (iii) Imprimir traduções em inglês de uma palavra em português
                printf("Digite a palavra em português: ");
                scanf("%s", palavraPortugues);
                imprimirTraducoesEmIngles(arvore, palavraPortugues);
                break;
            case 4:
                printf("Digite a palavra em inglês: ");
                scanf("%s", palavraIngles);
                printf("Digite a unidade: ");
                scanf("%d", &unidade);
                removerPalavraIngles(&arvore, palavraIngles, unidade);
                break;
            case 5:
                // (v) Remover uma palavra em português de uma unidade específica
                printf("Digite a palavra em português para remover: ");
                printf("Digite a palavra em português para remover: ");
                scanf("%s", palavraPortugues);
                printf("Digite a unidade: ");
                scanf("%d", &unidade);

                removerPalavraPortugues(&arvore, palavraPortugues, unidade);
                
                break;
            case 6:
                // Finalizar o programa
                limparArvore(&arvore);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
