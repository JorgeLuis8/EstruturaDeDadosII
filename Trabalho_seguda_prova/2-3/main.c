#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arv23.c"
#include "arvbin.c"
#include "unidade.c"

void clearCharacters(char *str)
{
    char *end = str + strlen(str) - 1;

    while (end > str && (*end == ';' || isspace((unsigned char)*end)))
    {
        *end = '\0';
        end--;
    }

    while (*str && isspace((unsigned char)*str))
    {
        str++;
    }
}

void carregarArquivo(const char *nomeArquivo, Portugues23 **arvore)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int unidadeAtual = -1; // Inicia com um valor inválido

    while (fgets(linha, sizeof(linha), arquivo))
    {
        linha[strcspn(linha, "\n")] = 0; // Remove o caractere de nova linha

        if (linha[0] == '%')
        {
            // Verifica a linha de unidade e extrai o número
            if (sscanf(linha, "%% Unidade %d", &unidadeAtual) == 1)
            {
                printf("Carregando Unidade: %d\n", unidadeAtual);
            }
            else
            {
                printf("Erro ao interpretar a unidade na linha: %s\n", linha);
                unidadeAtual = -1; // Reseta para inválido
            }
        }
        else if (unidadeAtual != -1)
        {
            // Processa linhas de palavras e traduções
            char palavraIngles[50], traducoesPortugues[200];

            if (sscanf(linha, "%[^:]: %[^\n]", palavraIngles, traducoesPortugues) == 2)
            {
                clearCharacters(palavraIngles); // Limpa caracteres indesejados

                // Divide as traduções em português separadas por vírgula
                char *traducaoPortugues = strtok(traducoesPortugues, ",");
                while (traducaoPortugues != NULL)
                {
                    while (*traducaoPortugues == ' ')
                    {
                        traducaoPortugues++; // Remove espaços no início
                    }

                    clearCharacters(traducaoPortugues); // Limpa caracteres indesejados
                    inserirPalavraPortugues(arvore, traducaoPortugues, palavraIngles, unidadeAtual);

                    traducaoPortugues = strtok(NULL, ",");
                }
            }
            else
            {
                printf("Erro ao interpretar a linha: %s\n", linha);
            }
        }
    }

    fclose(arquivo);
}

void imprimirUnidadesExistentes(Portugues23 *raiz, int *unidades, int *numUnidades)
{
    if (raiz)
    {
        // Verifica as unidades da primeira informação
        Inglesbin *ingles = raiz->info1.palavraIngles;
        while (ingles)
        {
            Unidade *unidadeAtual = ingles->unidades;
            while (unidadeAtual)
            {
                int existe = 0;
                for (int i = 0; i < *numUnidades; i++)
                {
                    if (unidades[i] == unidadeAtual->unidade)
                    {
                        existe = 1;
                        break;
                    }
                }
                if (!existe)
                {
                    unidades[*numUnidades] = unidadeAtual->unidade;
                    (*numUnidades)++;
                }
                unidadeAtual = unidadeAtual->prox;
            }
            ingles = ingles->esq ? ingles->esq : ingles->dir;
        }

        // Percorre a subárvore central
        imprimirUnidadesExistentes(raiz->cent, unidades, numUnidades);

        // Verifica as unidades da segunda informação
        if (raiz->nInfos == 2)
        {
            ingles = raiz->info2.palavraIngles;
            while (ingles)
            {
                Unidade *unidadeAtual = ingles->unidades;
                while (unidadeAtual)
                {
                    int existe = 0;
                    for (int i = 0; i < *numUnidades; i++)
                    {
                        if (unidades[i] == unidadeAtual->unidade)
                        {
                            existe = 1;
                            break;
                        }
                    }
                    if (!existe)
                    {
                        unidades[*numUnidades] = unidadeAtual->unidade;
                        (*numUnidades)++;
                    }
                    unidadeAtual = unidadeAtual->prox;
                }
                ingles = ingles->esq ? ingles->esq : ingles->dir;
            }
        }

        // Percorre a subárvore direita
        if (raiz->nInfos == 2)
        {
            imprimirUnidadesExistentes(raiz->dir, unidades, numUnidades);
        }
    }
}
void imprimirPalavrasPortuguesPorUnidade(Portugues23 *arvore, int unidade, int *unidadeImpressa)
{
    if (arvore)
    {
        // Percorre a subárvore esquerda
        imprimirPalavrasPortuguesPorUnidade(arvore->esq, unidade, unidadeImpressa);

        // Verifica se a palavra em português está associada à unidade e imprime
        if (arvore->info1.palavraIngles != NULL)
        {
            Inglesbin *ingles = arvore->info1.palavraIngles;
            while (ingles)
            {
                if (buscar_unidade(ingles->unidades, unidade))
                {
                    if (!(*unidadeImpressa))
                    {
                        printf("%% Unidade %d\n", unidade);
                        *unidadeImpressa = 1;
                    }
                    printf("- %s\n", arvore->info1.palavraPortugues);
                    break; // Palavra em português já encontrada para esta unidade
                }
                ingles = ingles->esq ? ingles->esq : ingles->dir;
            }
        }

        // Percorre a subárvore central
        imprimirPalavrasPortuguesPorUnidade(arvore->cent, unidade, unidadeImpressa);

        // Se houver um segundo elemento, verifica também
        if (arvore->nInfos == 2 && arvore->info2.palavraIngles != NULL)
        {
            Inglesbin *ingles = arvore->info2.palavraIngles;
            while (ingles)
            {
                if (buscar_unidade(ingles->unidades, unidade))
                {
                    if (!(*unidadeImpressa))
                    {
                        printf("%% Unidade %d\n", unidade);
                        *unidadeImpressa = 1;
                    }
                    printf("- %s\n", arvore->info2.palavraPortugues);
                    break; // Palavra em português já encontrada para esta unidade
                }
                ingles = ingles->esq ? ingles->esq : ingles->dir;
            }
        }

        // Percorre a subárvore direita
        if (arvore->nInfos == 2)
        {
            imprimirPalavrasPortuguesPorUnidade(arvore->dir, unidade, unidadeImpressa);
        }
    }
}
void imprimirPalavrasInglesPorUnidade(Portugues23 *arvore, int unidade, int *unidadeImpressa)
{
    if (arvore)
    {
        // Percorre a subárvore esquerda
        imprimirPalavrasInglesPorUnidade(arvore->esq, unidade, unidadeImpressa);

        // Verifica as palavras em inglês associadas ao primeiro elemento do nó
        if (arvore->info1.palavraIngles != NULL)
        {
            Inglesbin *ingles = arvore->info1.palavraIngles;
            while (ingles)
            {
                if (buscar_unidade(ingles->unidades, unidade))
                {
                    if (!(*unidadeImpressa))
                    {
                        printf("%% Unidade %d\n", unidade);
                        *unidadeImpressa = 1;
                    }
                    printf("- %s\n", ingles->palavraIngles);
                }
                ingles = ingles->esq ? ingles->esq : ingles->dir;
            }
        }

        // Percorre a subárvore central
        imprimirPalavrasInglesPorUnidade(arvore->cent, unidade, unidadeImpressa);

        // Verifica as palavras em inglês associadas ao segundo elemento do nó, se existir
        if (arvore->nInfos == 2 && arvore->info2.palavraIngles != NULL)
        {
            Inglesbin *ingles = arvore->info2.palavraIngles;
            while (ingles)
            {
                if (buscar_unidade(ingles->unidades, unidade))
                {
                    if (!(*unidadeImpressa))
                    {
                        printf("%% Unidade %d\n", unidade);
                        *unidadeImpressa = 1;
                    }
                    printf("- %s\n", ingles->palavraIngles);
                }
                ingles = ingles->esq ? ingles->esq : ingles->dir;
            }
        }

        // Percorre a subárvore direita
        if (arvore->nInfos == 2)
        {
            imprimirPalavrasInglesPorUnidade(arvore->dir, unidade, unidadeImpressa);
        }
    }
}
// void testeAutomatizadoRemocao(Portugues23 **raiz, Portugues23 **pai)
// {
//     char *palavrasIngles[] = {
//         "Bus", "Bike", "Bug", "Bus", "Bug", "Network", "System", "Coller"};
//     int numPalavras = sizeof(palavrasIngles) / sizeof(palavrasIngles[0]);

//     // Lista de unidades que existem na árvore
//     int unidades[100] = {0};
//     int numUnidades = 0;
//     imprimirUnidadesExistentes(*raiz, unidades, &numUnidades);

//     printf("\n### Iniciando Teste Automático ###\n");

//     // Percorre cada palavra em inglês e tenta removê-la de todas as unidades
//     for (int i = 0; i < numPalavras; i++)
//     {
//         printf("\nRemovendo a palavra '%s' de todas as unidades...\n", palavrasIngles[i]);

//         for (int j = 0; j < numUnidades; j++)
//         {
//             int unidade = unidades[j];

//             printf("Tentando remover '%s' da unidade %d...\n", palavrasIngles[i], unidade);
//             removerTraducaoIngles(raiz, palavrasIngles[i], unidade, pai);
//         }
//     }

//     printf("\n### Teste Automático Concluído ###\n");

//     // Exibe a árvore após o teste
//     printf("\n### Estado da Árvore Após Remoções ###\n");
//     exibir_tree23(*raiz);
// }

void menu()
{
    printf("\n------------------------------------------------------------------------------------------------- \n");
    printf("\nMenu de opções:\n");
    printf("1 - Informar uma unidade e imprimir todas as palavras em português e as equivalentes em inglês.\n");
    printf("2 - Informar uma palavra em português e imprimir todas as palavras em inglês equivalentes.\n");
    printf("3 - Informar uma palavra em inglês e a unidade, removê-la da árvore binária e da árvore 2-3.\n");
    printf("4 - Informar uma palavra em português e a unidade, removê-la da árvore binária e da árvore 2-3.\n");
    printf("5 - Imprimir a árvore completa.\n");
    printf("6 - Imprimir todas as unidades existentes.\n");
    printf("7 - Imprimir todas as palavras em português de uma unidade específica.\n");
    printf("8 - Imprimir todas as palavras em inglês de uma unidade específica.\n");
    printf("0 - Sair.\n");
    printf("Escolha uma opção: \n");
    printf("\n------------------------------------------------------------------------------------------------- \n");
}

int main()
{
    Portugues23 *raiz = NULL;


    char palavra[50];
    int unidade;
    carregarArquivo("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/text.txt", &raiz);
    int op;
    int unidadeImpressa = 0;
    do
    {
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\n--------------------------------------------------------------- \n");
            printf("Insira a unidade que deseja imprimir as palavras: ");
            scanf("%d", &unidade);

            // Variável de controle para a impressão do cabeçalho
            unidadeImpressa = 0;

            // Chama a função para imprimir palavras da unidade no formato especificado
            imprimirPalavrasFormatadasPorUnidade(raiz, unidade, &unidadeImpressa);

            if (!unidadeImpressa)
            {
                printf("Nenhuma palavra encontrada para a unidade %d.\n", unidade);
            }

            printf("\n--------------------------------------------------------------- \n");
            break;

        case 2:
            printf("\n--------------------------------------------------------------- \n");
            printf("Insira a palavra em português que deseja imprimir as palavras em inglês: ");
            scanf("%s", palavra);

            // Busca a palavra em português na árvore e exibe suas traduções
            exibirTodasTraducoes(raiz, palavra);

            printf("\n--------------------------------------------------------------- \n");
            break;

case 3:
    printf("\n--------------------------------------------------------------- \n");
    printf("Insira a palavra em ingles que deseja remover: ");
    while (getchar() != '\n'); // Limpa o buffer
    fgets(palavra, sizeof(palavra), stdin);
    palavra[strcspn(palavra, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Insira a unidade associada à palavra que deseja remover: ");
    scanf("%d", &unidade);

    // Chama a função principal de remoção
    if (Remove_palavra_ingles_unidade(&raiz, palavra, unidade)) {
        printf("Remocao concluida com sucesso.\n");
    } else {
        printf("Erro ao realizar a remocao.\n");
    }
    printf("\n--------------------------------------------------------------- \n");
    break;

case 4:
    printf("\n--------------------------------------------------------------- \n");
    printf("Insira a palavra em português que deseja remover: ");
    scanf("%s", palavra);
    printf("Insira a unidade associada à palavra que deseja remover: ");
    scanf("%d", &unidade);

    // Chama a função principal de remoção
    if (Remove_palavra_portugues_unidade(&raiz, palavra, unidade)) {
        printf("Remoção concluída com sucesso.\n");
    } else {
        printf("Erro ao realizar a remoção.\n");
    }
    printf("\n--------------------------------------------------------------- \n");
    break;





        // case 5:
        //     printf("\n--------------------------------------------------------------- \n");
        //     exibir_tree23(raiz);
        //     printf("\n--------------------------------------------------------------- \n");
        //     break;

        // case 6:
        // {
        //     printf("\n--------------------------------------------------------------- \n");
        //     printf("Unidades existentes:\n");

        //     int unidades[100] = {0};
        //     int numUnidades = 0;
        //     imprimirUnidadesExistentes(raiz, unidades, &numUnidades);

        //     for (int i = 0; i < numUnidades; i++)
        //     {
        //         printf("Unidade: %d\n", unidades[i]);
        //     }
        //     printf("\n--------------------------------------------------------------- \n");
        //     break;
        // }
        // case 7:
        //     printf("\n--------------------------------------------------------------- \n");
        //     printf("Insira a unidade que deseja listar as palavras em português: ");
        //     scanf("%d", &unidade);

        //     imprimirPalavrasPortuguesPorUnidade(raiz, unidade, &unidadeImpressa);

        //     if (!unidadeImpressa)
        //     {
        //         printf("Nenhuma palavra encontrada para a unidade %d.\n", unidade);
        //     }

        //     printf("\n--------------------------------------------------------------- \n");
        //     break;
        // case 8:
        //     printf("\n--------------------------------------------------------------- \n");
        //     printf("Insira a unidade que deseja listar as palavras em inglês: ");
        //     scanf("%d", &unidade);

        //     int unidadeImpressa = 0;
        //     imprimirPalavrasInglesPorUnidade(raiz, unidade, &unidadeImpressa);

        //     if (!unidadeImpressa)
        //     {
        //         printf("Nenhuma palavra em inglês encontrada para a unidade %d.\n", unidade);
        //     }

        //     printf("\n--------------------------------------------------------------- \n");
        //     break;
        // case 9:
        //     printf("\n--------------------------------------------------------------- \n");
        //     printf("Executando teste automático de remoção...\n");
        //     testeAutomatizadoRemocao(&raiz, &pai);
        //     printf("\n--------------------------------------------------------------- \n");
        //     break;
        case 0:
            printf("\n--------------------------------------------------------------- \n");
            printf("Saindo do programa...\n");
            printf("\n--------------------------------------------------------------- \n");
            break;

        default:
            printf("Insira um valor válido. \n");
            break;
        }
    } while (op != 0);

    freeTree(&raiz);

    return 0;
}
