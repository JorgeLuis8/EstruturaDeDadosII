#include "portugues.c"
#include "ingles.c"
#include "ingles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inserirPalavraPortugues(Arv_portugues **arvore, char *palavraPortugues, char *palavraIngles, int unidade)
{
    Arv_portugues *noExistente = BuscarPalavra(arvore, palavraPortugues);

    if (noExistente != NULL)
    {
        // Verifica se já existe a mesma tradução na mesma unidade
        Arv_ingles *traducao = noExistente->info.palavraIngles;
        while (traducao != NULL)
        {
            if (strcmp(traducao->palavraIngles, palavraIngles) == 0 && traducao->unidade == unidade)
            {
                printf("A tradução '%s' para '%s' já existe na unidade %d. Ignorando.\n",
                       palavraIngles, palavraPortugues, unidade);
                return 0; // Já existe, não insere novamente
            }
            traducao = traducao->dir;
        }

        // Adiciona nova tradução na lista
        AdicionarTraducaoEN(noExistente, palavraIngles, unidade);
        return 1;
    }
    else
    {
        // Cria nova entrada para a palavra
        Info novoInfo = CriarInfo(palavraPortugues, palavraIngles, unidade);
        inserirArvRec(arvore, &novoInfo);
        return 1;
    }
}

void carregarArquivo(const char *nomeArquivo, Arv_portugues **arvore)
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
        linha[strcspn(linha, "\n")] = 0; // Remover o \n no final da linha

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
            while (traducaoPortugues != NULL)
            {
                while (*traducaoPortugues == ' ')
                    traducaoPortugues++; // Ignorar espaços extras

                if (strlen(traducaoPortugues) > 0)
                {
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
void imprimirPalavrasPorUnidade(Arv_portugues *arvore, int unidade)
{
    if (arvore == NULL)
        return;

    // Percorre a lista de traduções e imprime todas as palavras e traduções para a unidade
    Arv_ingles *traducao = arvore->info.palavraIngles;
    while (traducao != NULL)
    {
        if (traducao->unidade == unidade)
        {
            printf("%s: %s;\n", arvore->info.palavraPortugues, traducao->palavraIngles);
        }
        traducao = traducao->dir; // Avança para a próxima tradução
    }

    // Recursivamente percorre as subárvores
    imprimirPalavrasPorUnidade(arvore->esq, unidade);
    imprimirPalavrasPorUnidade(arvore->dir, unidade);
}

// Função para imprimir todas as traduções em inglês de uma palavra em português
void imprimirTraducoesIngles(Arv_portugues *arvore, char *palavraPortugues)
{
    if (arvore == NULL)
        return;

    // Se a palavra portuguesa da árvore for igual à palavra fornecida, imprime as traduções
    if (strcmp(arvore->info.palavraPortugues, palavraPortugues) == 0)
    {
        printf("Traduções em Inglês para '%s': %s\n",
               arvore->info.palavraPortugues, arvore->info.palavraIngles->palavraIngles);
    }

    // Recursivamente busca nas subárvores esquerda e direita
    imprimirTraducoesIngles(arvore->esq, palavraPortugues);
    imprimirTraducoesIngles(arvore->dir, palavraPortugues);
}

// Função para remover uma palavra em inglês e atualizar as árvores
void removerPalavraInglesEArvore(Arv_portugues **arvore, char *palavraIngles, int unidade)
{
    if (*arvore != NULL)
    {

        // Remoção na subárvore esquerda
        removerPalavraInglesEArvore(&(*arvore)->esq, palavraIngles, unidade);

        if (*arvore != NULL && (*arvore)->info.palavraIngles != NULL)
        {
            Arv_ingles *raizIngles = (*arvore)->info.palavraIngles;
            int removida = 0;

            // Percorre a árvore binária de traduções e remove a palavra correspondente à unidade
            Arv_ingles *temp = raizIngles;
            while (temp != NULL)
            {
                if (strcmp(temp->palavraIngles, palavraIngles) == 0 && temp->unidade == unidade)
                {
                    removida = removerPalavraIngles(&(*arvore)->info.palavraIngles, palavraIngles);
                    printf("Debug: A palavra '%s' na unidade %d foi removida.\n", palavraIngles, unidade);
                    break;
                }
                temp = temp->dir; // Avança para o próximo nó
            }

            // Verifica se a árvore binária ficou vazia após a remoção
            if (removida && (*arvore)->info.palavraIngles == NULL)
            {
                printf("Debug: A palavra '%s' era a única tradução. Removendo nó correspondente na árvore principal.\n", palavraIngles);
                RemoverNo(arvore, (*arvore)->info.palavraPortugues);
            }
        }
        if (*arvore != NULL)
        {
            removerPalavraInglesEArvore(&(*arvore)->dir, palavraIngles, unidade);
        }
    }
}

void removerPalavraPortuguesEUnidade(Arv_portugues **arvore, char *palavraPortugues, int unidade)
{
    if (*arvore == NULL)
        return;

    // Localiza o nó correspondente à palavra em português
    Arv_portugues *no = BuscarPalavra(arvore, palavraPortugues);

    if (no != NULL)
    {
        // Remove as traduções associadas à unidade fornecida
        Arv_ingles *raizIngles = no->info.palavraIngles;
        int traducaoRemovida = 0;

        if (raizIngles != NULL)
        {
            Arv_ingles *temp = raizIngles;

            while (temp != NULL)
            {
                if (temp->unidade == unidade)
                {
                    traducaoRemovida = removerPalavraIngles(&raizIngles, temp->palavraIngles);
                    break;
                }
                temp = temp->dir; // Avança para a próxima tradução
            }
        }

        // Atualiza a árvore binária no nó
        no->info.palavraIngles = raizIngles;

        if (traducaoRemovida)
        {
            printf("A tradução na unidade %d foi removida.\n", unidade);

            // Se a árvore binária ficou vazia, remove o nó da árvore Rubro-Negra
            if (no->info.palavraIngles == NULL)
            {
                printf("A palavra '%s' não possui mais traduções e será removida da árvore principal.\n", palavraPortugues);
                RemoverNo(arvore, palavraPortugues);
            }
        }
        else
        {
            printf("Nenhuma tradução encontrada para a palavra '%s' na unidade %d.\n", palavraPortugues, unidade);
        }
    }
    else
    {
        printf("A palavra '%s' não foi encontrada na árvore.\n", palavraPortugues);
    }
}

int main()
{
    Arv_portugues *arvore = NULL;
    int opcao, unidade;
    char palavraPortugues[50], palavraIngles[50];

    // Carregar o arquivo
    carregarArquivo("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/Trabalho_segunda_provaVERSAO-REFERENCIA/Tabalho2_Ed2-main/trabalhoEd2.txt", &arvore);

    while (1)
    {
        printf("\nMENU\n");
        printf("1. Exibir palavras associadas a uma unidade\n");
        printf("2. Exibir traducoes em ingles para uma palavra em portugues\n");
        printf("3. Remover palavra em ingles e atualizacoes associadas\n");
        printf("4. Remover palavra em portugues e traducoes associadas\n");
        printf("5. Sair do programa\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Informe a unidade: ");
            while (1)
            {
                scanf("%d", &unidade);

                // Valida a unidade
                if (unidade < 1)
                {
                    printf("Unidade invalida. Tente novamente: ");
                }
                else
                {
                    break;
                }
            }
            // Imprime as palavras da unidade fornecida
            printf("Palavras da unidade %d:\n", unidade);
            imprimirPalavrasPorUnidade(arvore, unidade);
            break;

        case 2:
            printf("Informe a palavra em portugues: ");
            scanf(" %[^\n]", palavraPortugues); // Lê a palavra com espaços
            printf("Traducoes em ingles para '%s':\n", palavraPortugues);
            imprimirTraducoesIngles(arvore, palavraPortugues);
            break;

        case 3:
            printf("Informe a palavra em ingles: ");
            scanf(" %[^\n]", palavraIngles);
            printf("Informe a unidade: ");
            scanf("%d", &unidade);

            removerPalavraInglesEArvore(&arvore, palavraIngles, unidade);
            break;

        case 4:
            printf("Informe a palavra em portugues: ");
            scanf(" %[^\n]", palavraPortugues);
            printf("Informe a unidade: ");
            scanf("%d", &unidade);

            removerPalavraPortuguesEUnidade(&arvore, palavraPortugues, unidade);
            break;

        case 5:
            printf("Saindo do programa...\n");
            exit(0);

        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
