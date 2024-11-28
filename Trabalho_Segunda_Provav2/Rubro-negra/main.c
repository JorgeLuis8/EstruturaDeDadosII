#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv-portugues.c"
#include "arv-ingles-bin.c"

// Função para carregar o arquivo com as palavras e traduções
void carregarArquivo(const char *nomeArquivo, Arv_portugues **arvore) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[256];
    int unidadeAtual = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0; // Remove quebra de linha

        if (linha[0] == '%') {
            sscanf(linha, "%% Unidade %d", &unidadeAtual);
        } else {
            char palavraPortugues[50];
            char traducoesIngles[200];

            if (sscanf(linha, "%[^:]: %[^\n]", palavraPortugues, traducoesIngles) == 2) {
                Arv_portugues *novoNo = cria_no_arv();
                strcpy(novoNo->dados.portugueseWord, palavraPortugues);
                novoNo->dados.unit = unidadeAtual;

                *arvore = inserir_no(*arvore, novoNo);

                char *traducao = strtok(traducoesIngles, ",;");
                while (traducao != NULL) {
                    while (*traducao == ' ') traducao++;
                    novoNo->dados.englishTreeRoot = insertEnglishWordEn(
                        novoNo->dados.englishTreeRoot, traducao, unidadeAtual);
                    traducao = strtok(NULL, ",;");
                }
            }
        }
    }

    fclose(arquivo);
}


// Função auxiliar para exibir palavras de uma unidade específica
void exibirPalavrasPorUnidade(Arv_portugues *arvore, int unidade) {
    if (arvore != NULL) {
        exibirPalavrasPorUnidade(arvore->esq, unidade);

        if (arvore->dados.unit == unidade) {
            printf("%s: ", arvore->dados.portugueseWord);
            int primeira = 1;
            imprimirTraducoesEn(arvore->dados.englishTreeRoot, arvore->dados.portugueseWord, &primeira);
            printf("\n");
        }

        exibirPalavrasPorUnidade(arvore->dir, unidade);
    }
}

// Função para verificar se há palavras para a unidade atual
void verificarUnidade(Arv_portugues *arvore, int unidade, int *temPalavras) {
    if (arvore != NULL) {
        if (arvore->dados.unit == unidade) {
            *temPalavras = 1;
        }
        verificarUnidade(arvore->esq, unidade, temPalavras);
        verificarUnidade(arvore->dir, unidade, temPalavras);
    }
}

// Função principal para exibir a árvore no formato do arquivo
void exibirArvoreFormatoArquivo(Arv_portugues *arvore) {
    int unidade = 1;
    while (1) {
        int temPalavras = 0;
        verificarUnidade(arvore, unidade, &temPalavras);

        if (!temPalavras) break;

        printf("%% Unidade %d\n", unidade);
        exibirPalavrasPorUnidade(arvore, unidade);
        unidade++;
    }
}

// // Função para exibir o menu de opções
// void exibirMenu() {
//     printf("\nEscolha uma opção:\n");
//     printf("1 - Imprimir traduções por unidade\n");
//     printf("2 - Imprimir uma unidade específica e suas traduções\n");
//     printf("3 - Imprimir traduções em inglês de uma palavra em português\n");
//     printf("4 - Remover uma palavra em inglês de uma unidade\n");
//     printf("5 - Remover uma palavra em português de uma unidade\n");
//     printf("6 - Sair\n");
//     printf("Digite sua opção: ");
// }

// int main() {
//     Arv_portugues *arvore = NULL;

//     int opcao = -1;
//     int unidade;
//     char palavraPortugues[50];
//     char palavraIngles[50];

//     // Carregar o arquivo de palavras
//     carregarArquivo("C:\\Users\\jorge\\OneDrive\\Documentos\\GitHub\\EstruturaDeDadosII\\Trabalho_Segunda_Provav2\\Rubro-negra\\vocabulario1.txt", &arvore);

//     // Loop principal do menu
//     while (opcao != 6) {
//         exibirMenu();
//         scanf("%d", &opcao);

//         switch (opcao) {
//             case 1:
//                 exibirArvoreFormatoArquivo(arvore);
//                 break;
//             case 2:
//                 printf("Digite a unidade: ");
//                 scanf("%d", &unidade);
//                 printf("%% Unidade %d\n", unidade);
//                 exibirPalavrasPorUnidade(arvore, unidade);
//                 break;
//             case 3:
//                 printf("Digite a palavra em português: ");
//                 scanf("%s", palavraPortugues);
//                 Arv_portugues *resultado = buscar_palavra_portugues(arvore, palavraPortugues, unidade);
//                 if (resultado != NULL) {
//                     printf("Traduções para '%s':\n", palavraPortugues);
//                     int primeira = 1;
//                     imprimirTraducoesEn(resultado->dados.englishTreeRoot, palavraPortugues, &primeira);
//                     printf("\n");
//                 } else {
//                     printf("Palavra não encontrada.\n");
//                 }
//                 break;
//             case 4:
//                 printf("Digite a palavra em inglês: ");
//                 scanf("%s", palavraIngles);
//                 printf("Digite a unidade: ");
//                 scanf("%d", &unidade);

//                 Arv_portugues *no = buscar_palavra_portugues(arvore, palavraIngles, unidade);
//                 if (no) {
//                     no->dados.englishTreeRoot = removeEnglishWordEn(no->dados.englishTreeRoot, palavraIngles, unidade);
//                     printf("Palavra '%s' removida com sucesso.\n", palavraIngles);
//                 } else {
//                     printf("Erro ao remover a palavra '%s'.\n", palavraIngles);
//                 }
//                 break;
//             case 5:
//                 printf("Digite a palavra em português para remover: ");
//                 scanf("%s", palavraPortugues);
//                 printf("Digite a unidade: ");
//                 scanf("%d", &unidade);

//                 if (remove_ArvLLRB_arv(&arvore, palavraPortugues, unidade)) {
//                     printf("Palavra '%s' removida com sucesso.\n", palavraPortugues);
//                 } else {
//                     printf("Erro ao remover a palavra '%s'.\n", palavraPortugues);
//                 }
//                 break;
//             case 6:
//                 printf("Saindo...\n");
//                 limparArvoreBinariaEn(&(arvore->dados.englishTreeRoot));
//                // limparArvore(&arvore);
//                 break;
//             default:
//                 printf("Opção inválida! Tente novamente.\n");
//                 break;
//         }
//     }

//     return 0;
// }


int main() {
    Arv_portugues *arvore = NULL;
    Arv_portugues *novoNo = cria_no_arv();
    if (novoNo == NULL) {
        printf("Erro ao criar nó.\n");
        return 1;
    }

    strcpy(novoNo->dados.portugueseWord, "teste");
    novoNo->dados.unit = 1;

    arvore = inserir_no(arvore, novoNo);

    if (arvore) {
        printf("Palavra inserida: %s, Unidade: %d\n", arvore->dados.portugueseWord, arvore->dados.unit);
    } else {
        printf("Erro ao inserir nó.\n");
    }

    return 0;
}
