#include "portugues.c"
#include "ingles.c"
#include "ingles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inserirPalavraPortugues(Arv_portugues **arvore, char *palavraPortugues, char *palavraIngles, int unidade) {
    int inseriu = 0;

    // Busca a palavra na árvore
    Arv_portugues *noExistente = NULL;
    noExistente =  BuscarPalavra(arvore, palavraPortugues);

    if (noExistente != NULL) {
        printf("A palavra já existe. Adicionando tradução...\n");
        AdicionarTraducaoEN(noExistente, palavraIngles, unidade);
        inseriu = 1;
    } else {
        Info novoInfo = CriarInfo(palavraPortugues, palavraIngles, unidade);
        inserirArvRec(arvore, &novoInfo);
        inseriu = 1;
    }
    return inseriu;
}

void carregarArquivo(const char *nomeArquivo, Arv_portugues **arvore) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int unidadeAtual = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;  // Remover o \n no final da linha

        if (linha[0] == '%') {
            // Atualiza a unidade corretamente
            sscanf(linha, "%% Unidade %d", &unidadeAtual);
        } else {
            char palavraIngles[50], traducoesPortugues[200];
            sscanf(linha, "%[^:]: %[^;]", palavraIngles, traducoesPortugues);

            char *traducaoPortugues = strtok(traducoesPortugues, ",;");
            while (traducaoPortugues != NULL) {
                while (*traducaoPortugues == ' ') 
                    traducaoPortugues++;  // Ignorar espaços extras

                if (strlen(traducaoPortugues) > 0) {
                    inserirPalavraPortugues(arvore, traducaoPortugues, palavraIngles, unidadeAtual);
                }

                traducaoPortugues = strtok(NULL, ",;");    
            }
        }
    }

    fclose(arquivo);
    printf("Arquivo '%s' carregado com sucesso!\n", nomeArquivo);
}

// Função para imprimir palavras de uma unidade específica
void imprimirPalavrasPorUnidade(Arv_portugues *arvore, int unidade) {
    if (arvore == NULL) return;

    // Se a unidade da palavra for igual à unidade fornecida, imprime a tradução
    if (arvore->info.palavraIngles->unidade == unidade) {
        printf("%s: %s;\n", 
               arvore->info.palavraPortugues, arvore->info.palavraIngles->palavraIngles);
    }

    // Recursivamente imprime as palavras da subárvore esquerda e direita
    imprimirPalavrasPorUnidade(arvore->esq, unidade);
    imprimirPalavrasPorUnidade(arvore->dir, unidade);
}

// Função para imprimir todas as traduções em inglês de uma palavra em português
void imprimirTraducoesIngles(Arv_portugues *arvore, char *palavraPortugues) {
    if (arvore == NULL) return;

    // Se a palavra portuguesa da árvore for igual à palavra fornecida, imprime as traduções
    if (strcmp(arvore->info.palavraPortugues, palavraPortugues) == 0) {
        printf("Traduções em Inglês para '%s': %s\n", 
               arvore->info.palavraPortugues, arvore->info.palavraIngles->palavraIngles);
    }

    // Recursivamente busca nas subárvores esquerda e direita
    imprimirTraducoesIngles(arvore->esq, palavraPortugues);
    imprimirTraducoesIngles(arvore->dir, palavraPortugues);
}

// Função para remover uma palavra em português e sua tradução correspondente na mesma unidade
void removerPalavraPortuguesEIngles(Arv_portugues **arvore, char *palavraPortugues, int unidade) {
    if (*arvore == NULL) return;

    // Busca a palavra em português na árvore Rubro-Negra
    Arv_portugues *no = BuscarPalavra(arvore, palavraPortugues);

    if (no != NULL) {
        // Remove todas as palavras em inglês da árvore binária correspondente à unidade
        Inglesbin *raizIngles = no->info.palavraIngles;
        int traducaoRemovida = 0;

        if (raizIngles != NULL) {
            Inglesbin *temp = raizIngles;

            while (temp != NULL) {
                if (temp->unidade == unidade) {
                    removerPalavraIngles(&raizIngles, temp->palavraIngles);
                    traducaoRemovida = 1;
                    break;
                }
                temp = temp->dir; // Percorre para o próximo nó
            }
        }

        // Atualiza a árvore binária no nó
        no->info.palavraIngles = raizIngles;

        if (traducaoRemovida) {
            printf("A tradução na unidade %d foi removida.\n", unidade);

            // Se a árvore binária ficou vazia, remove o nó da árvore Rubro-Negra
            if (no->info.palavraIngles == NULL) {
                printf("A palavra '%s' não possui mais traduções e será removida da árvore principal.\n", palavraPortugues);
                RemoverNo(arvore, palavraPortugues);
            }
        } else {
            printf("Nenhuma tradução encontrada para a palavra '%s' na unidade %d.\n", palavraPortugues, unidade);
        }
    } else {
        printf("A palavra '%s' não foi encontrada na árvore.\n", palavraPortugues);
    }
}

int main() {
    Arv_portugues *arvore = NULL;
    int opcao, unidade;
    char palavraPortugues[50], palavraIngles[50];

    // Carregar o arquivo
    carregarArquivo("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/Trabalho_segunda_provaVERSAO-REFERENCIA/Tabalho2_Ed2-main/trabalhoEd2.txt", &arvore);

    while (1) {
        printf("\nMENU\n");
        printf("1. Imprimir palavras de uma unidade\n");
        printf("2. Imprimir traduções em inglês para uma palavra em português\n");
        printf("3. Remover palavra em inglês de todas as árvores\n");
        printf("4. Remover palavra em português e suas traduções\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Informe a unidade: ");
                while (1) {
                    scanf("%d", &unidade);

                    // Valida a unidade
                    if (unidade < 1) {
                        printf("Unidade inválida. Tente novamente: ");
                    } else {
                        break;
                    }
                }
                // Imprime as palavras da unidade fornecida
                printf("Palavras da unidade %d:\n", unidade);
                imprimirPalavrasPorUnidade(arvore, unidade);
                break;

            case 2:
                printf("Informe a palavra em português: ");
                scanf(" %[^\n]", palavraPortugues); // Lê a palavra com espaços
                printf("Traduções em inglês para '%s':\n", palavraPortugues);
                imprimirTraducoesIngles(arvore, palavraPortugues);
                break;

            case 3:
                printf("Informe a palavra em inglês: ");
                scanf(" %[^\n]", palavraIngles);
                printf("Informe a unidade: ");
                scanf("%d", &unidade);

                removerPalavraPortuguesEIngles (&arvore, palavraIngles, unidade);
                break;

            case 4:
                printf("Informe a palavra em português: ");
                scanf(" %[^\n]", palavraPortugues);
                printf("Informe a unidade: ");
                scanf("%d", &unidade);

                removerPalavraPortuguesEIngles(&arvore, palavraPortugues, unidade);
                break;

            case 5:
                printf("Saindo do programa...\n");
                exit(0);

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}