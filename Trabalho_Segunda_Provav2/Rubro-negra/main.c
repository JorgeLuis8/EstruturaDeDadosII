#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv-portugues.c"
#include "arv-ingles-bin.c"

// Função para carregar o arquivo com as palavras e traduções
void carregarArquivo(const char *nomeArquivo, Arv_portugues *arvore)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];

    int unidadeAtual = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        linha[strcspn(linha, "\n")] = 0;

        if (linha[0] == '%')
        {
            // Atualiza a unidade corretamente
            sscanf(linha, "%% Unidade %d", &unidadeAtual);
        }
        else
        {
            char palavraIngles[50], traducoesPortugues[200];
            sscanf(linha, "%[^:]: %[^;]", palavraIngles, traducoesPortugues);
            printf("Lendo: Palavra Inglês = '%s', Traduções: '%s'\n", palavraIngles, traducoesPortugues);
            
            char *traducaoPortugues = strtok(traducoesPortugues, ",;");
            while(traducaoPortugues != NULL)
            {
                while (*traducaoPortugues == ' ') 
                    traducaoPortugues++;

                Arv_portugues *novo_no = cria_no_arv();
                novo_no->dados.unit = unidadeAtual;
                strcpy(novo_no->dados.portugueseWord, traducaoPortugues);
                novo_no->dados.englishTreeRoot = NULL;
                arvore = inserir_no(arvore, novo_no);  // Correção

                printf("Cria no");

                // Info novoInfo = criaInfo(traducaoPortugues, palavraIngles, unidadeAtual);
                // inserirArvRB(arvore, &novoInfo);
                traducaoPortugues = strtok(NULL, ",;");    
            }
            
        }
    }

    fclose(arquivo);
    printf("Arquivo '%s' carregado com sucesso!\n", nomeArquivo);
}



// Função auxiliar para exibir palavras de uma unidade específica
void exibirPalavrasPorUnidade(Arv_portugues *arvore, int unidade) {
    if (arvore != NULL) {
        exibirPalavrasPorUnidade(arvore->esq, unidade);

        if (arvore->dados.unit == unidade) {
            printf("%s: ", arvore->dados.portugueseWord);
            int primeira = 1;
            imprimirTraducoes(arvore->dados.englishTreeRoot, arvore->dados.portugueseWord, &primeira);
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
    Arv_portugues *arvore = NULL;

    int opcao = -1;
    int unidade;
    char palavraPortugues[50];
    char palavraIngles[50];

    // Carregar o arquivo de palavras
    carregarArquivo("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/Trabalho_Segunda_Provav2/Rubro-negra/vocabulario1.txt", arvore);

    // Loop principal do menu
    while (opcao != 6) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirArvoreFormatoArquivo(arvore);
                break;
            case 2:
                printf("Digite a unidade: ");
                scanf("%d", &unidade);
                printf("%% Unidade %d\n", unidade);
                exibirPalavrasPorUnidade(arvore, unidade);
                break;
            case 3:
                printf("Digite a palavra em português: ");
                scanf("%s", palavraPortugues);
                Arv_portugues *resultado = buscar_palavra_portugues(arvore, palavraPortugues, unidade);
                if (resultado != NULL) {
                    printf("Traduções para '%s':\n", palavraPortugues);
                    int primeira = 1;
                    imprimirTraducoes(resultado->dados.englishTreeRoot, palavraPortugues, &primeira);
                    printf("\n");
                } else {
                    printf("Palavra não encontrada.\n");
                }
                break;
            case 4:
                printf("Digite a palavra em inglês: ");
                scanf("%s", palavraIngles);
                printf("Digite a unidade: ");
                scanf("%d", &unidade);

                Arv_portugues *no = buscar_palavra_portugues(arvore, palavraIngles, unidade);
                if (no) {
                    no->dados.englishTreeRoot = removeEnglishWord(no->dados.englishTreeRoot, palavraIngles, unidade);
                    printf("Palavra '%s' removida com sucesso.\n", palavraIngles);
                } else {
                    printf("Erro ao remover a palavra '%s'.\n", palavraIngles);
                }
                break;
            case 5:
                printf("Digite a palavra em português para remover: ");
                scanf("%s", palavraPortugues);
                printf("Digite a unidade: ");
                scanf("%d", &unidade);

                if (remove_ArvLLRB_arv(&arvore, palavraPortugues, unidade)) {
                    printf("Palavra '%s' removida com sucesso.\n", palavraPortugues);
                } else {
                    printf("Erro ao remover a palavra '%s'.\n", palavraPortugues);
                }
                break;
            case 6:
                printf("Saindo...\n");
                limparArvoreBinaria(&(arvore->dados.englishTreeRoot));
               // limparArvore(&arvore);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}

