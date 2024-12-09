#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portugues_arv.c"
#include "ingles_arv.c"
// #include "arvbin.h"

int inserirPalavraPortugues(Arv_pt **arvore, char *palavraPortugues, char *palavraIngles, int unidade) {
    Info promove;
    Arv_pt *pai = NULL;
    int inseriu;

    // Busca a palavra na árvore
    Arv_pt *noExistente = NULL;
    noExistente =  BuscarNoPorPalavra(arvore, palavraPortugues);

    if (noExistente != NULL) {
        AdicionarTraducaoNo(noExistente, palavraPortugues, palavraIngles, unidade);
        inseriu = 1;
    } else {
        Info novoInfo = CriarInfo(palavraPortugues, palavraIngles, unidade);
        InserirInfoArvore23(arvore, &novoInfo, &promove, &pai);
        inseriu = 0;
    }
    return inseriu;
}

void carregarArquivo(const char *nomeArquivo, Arv_pt **arvore)
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
            
            char *traducaoPortugues = strtok(traducoesPortugues, ",;");
            while(traducaoPortugues != NULL)
            {
                while (*traducaoPortugues == ' ') 
                    traducaoPortugues++;

                inserirPalavraPortugues(arvore, traducaoPortugues, palavraIngles, unidadeAtual);
                traducaoPortugues = strtok(NULL, ",;");    
            }
            
        }
    }

    fclose(arquivo);
}



void menu(Arv_pt *raiz)
{
    int opcao;
    do
    {
        printf("\nMenu de Opções:\n");
        printf("1. Informar uma unidade e listar palavras em português e suas traduções\n");
        printf("2. Informar uma palavra em português e listar traduções em inglês\n");
        printf("3. Informar uma palavra em inglês e a unidade para removê-la\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
                {
                    int unidade;
                    printf("Informe o número da unidade: ");
                    scanf("%d", &unidade);
                    printf("\nPalavras da unidade %d:\n", unidade);
                    ImprimirPorUnidade(raiz, unidade);
                    printf("\n");
                }
                break;

            case 2:
                {
                    char palavraPortugues[100];
                    printf("Informe a palavra em português: ");
                    scanf(" %[^\n]s", palavraPortugues); // Lê a linha inteira, incluindo espaços
                    printf("\nTraduções em inglês para '%s':\n", palavraPortugues);
                    ExibirTraducoesPortugues(&raiz, palavraPortugues);
                }
                break;

            case 3:
                {
                    char palavraIngles[100];
                    int unidade;
                    printf("Informe a palavra em inglês: ");
                    scanf(" %[^\n]s", palavraIngles); // Lê a linha inteira
                    printf("Informe a unidade: ");
                    scanf("%d", &unidade);
                    printf("\nRemovendo a palavra '%s' da unidade %d...\n", palavraIngles, unidade);
                    RemoverPalavraInglesDaUnidade(&raiz, palavraIngles, unidade);
                }
                break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}




int main() {
    Arv_pt *raiz = NULL;

    // Carregar o arquivo com palavras e traduções
    carregarArquivo("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/Trabalho_segunda_provaVERSAO-REFERENCIA/Tabalho2_Ed2-main/trabalhoEd2.txt", &raiz);

    printf("\nÁrvore carregada com sucesso!\n");

    // Chamar o menu interativo
    menu(raiz);

    // Liberar memória alocada para a árvore
    LiberarArvore23(raiz);

    return 0;
}
