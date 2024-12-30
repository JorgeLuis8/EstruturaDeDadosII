#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvbin.c"
#include "arvrb.c"

void loadFile(const char *nomeArquivo, RedBlackTreePT **arvore)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo != NULL)
    {
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
                while (traducaoPortugues != NULL)
                {
                    while (*traducaoPortugues == ' ')
                        traducaoPortugues++;

                    insertPortugueseWord(arvore, traducaoPortugues, palavraIngles, unidadeAtual);

                    traducaoPortugues = strtok(NULL, ",;");
                }
            }
        }

        fclose(arquivo);
        printf("Arquivo '%s' carregado com sucesso!\n", nomeArquivo);
    }
}

void menu()
{
    printf("\n-------------------------------------------------------------------------------------------------\n");
    printf("\nMenu de opcoes\n");
    printf("1 - Informar uma unidade e imprimir todas as palavras em portugues e as equivalentes em ingles\n");
    printf("2 - Informar uma palavra em portugues e imprimir todas as palavras em ingles equivalentes\n");
    printf("3 - Informar uma palavra em ingles e a unidade remove-la da arvore binaria e da arvore 2-3\n");
    printf("4 - Informar uma palavra em portugues e a unidade remove-la da arvore binaria e da arvore 2-3\n");
    printf("5 - Imprimir a arvore completa\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao\n");
    printf("\n-------------------------------------------------------------------------------------------------\n");
}

int main()
{

    RedBlackTreePT *rootNode = NULL;

    loadFile("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/trabalhoEd2.txt", &rootNode);

    int op;
    char word[50];
    int unit;
    int removedNode;
    do
    {
        menu();
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\n---------------------------------------------------------------\n");
            printf("Insira a unidade que deseja imprimir as palavras\n");
            scanf("%d", &unit);
            printWordsByUnit(rootNode, unit);
            printf("\n---------------------------------------------------------------\n");
            break;
        case 2:
            printf("\n---------------------------------------------------------------\n");
            printf("Insira a palavra em portugues que deseja imprimir as palavras em ingles\n");
            scanf("%s", word);
            showPortugueseTranslation(&rootNode, word);
            printf("\n---------------------------------------------------------------\n");
            break;
        case 3:
            printf("\n---------------------------------------------------------------\n");
            printf("Insira a palavra em ingles que deseja remover\n");
            scanf("%s", word);

            printf("Insira a unidade da palavra que deseja remover\n");
            scanf("%d", &unit);

            // Busca o no correspondente na Arvore Vermelho-Preto
            RedBlackTreePT *nodeToRemove = SearchEnglishWordInRBTree(rootNode, word, unit);

            if (nodeToRemove != NULL)
            {
                printf("No encontrado Palavra em portugues %s\n", nodeToRemove->info.portugueseWord);

                // Remover a palavra da arvore binaria associada
                int removed = removeEnglishWord(&nodeToRemove->info.englishWordNode, word);

                if (removed)
                {
                    printf("Palavra %s da unidade %d removida da arvore binaria\n", word, unit);

                    // Verificar se a arvore binaria associada ficou vazia
                    if (nodeToRemove->info.englishWordNode == NULL)
                    {
                        removeRBTreeNode(&rootNode, nodeToRemove->info.portugueseWord);
                        printf("O no correspondente a palavra %s foi removido da arvore Vermelho-Preto\n", word);
                    }
                }
                else
                {
                    printf("A palavra %s nao foi encontrada na arvore binaria associada a unidade %d\n", word, unit);
                }
            }
            else
            {
                printf("A palavra %s nao foi encontrada na arvore Vermelho-Preto\n", word);
            }
            printf("\n---------------------------------------------------------------\n");
            break;

        case 4:
            printf("\n---------------------------------------------------------------\n");
            printf("Insira a palavra em português que deseja remover\n");
            setbuf(stdin, NULL);
            scanf("%[^\n]", word);

            printf("Insira a unidade à qual a palavra pertence\n");
            int unit;
            scanf("%d", &unit);

            // Buscar a palavra em português na árvore rubro-negra
            RedBlackTreePT *node = SearchWordInTree(&rootNode, word);

            if (node != NULL)
            {
                printf("Palavra em português encontrada: %s\n", node->info.portugueseWord);

                // Verificar se a árvore binária correspondente está inicializada
                if (node->info.englishWordNode != NULL)
                {
                    printf("Árvore binária de palavras em inglês encontrada.\n");

                    // Remover a palavra em inglês na unidade especificada
                    int removed = removeEnglishWord(&(node->info.englishWordNode), word);

                    if (removed)
                    {
                        printf("A palavra %s foi removida com sucesso da unidade %d\n", word, unit);

                        // Verificar se a árvore binária ficou vazia
                        if (node->info.englishWordNode == NULL)
                        {
                            // Remove o nó da palavra em português na árvore rubro-negra
                            int removedPortuguese = removeRBTreeNode(&rootNode, word);

                            if (removedPortuguese)
                            {
                                printf("A palavra em português %s foi removida da árvore rubro-negra, pois não possui mais traduções.\n", word);
                            }
                            else
                            {
                                printf("Erro ao remover a palavra em português %s da árvore rubro-negra.\n", word);
                            }
                        }
                    }
                    else
                    {
                        printf("Erro ao remover a palavra %s da unidade %d.\n", word, unit);
                    }
                }
                else
                {
                    printf("A palavra em português %s não possui traduções em inglês.\n", word);
                }
            }
            else
            {
                printf("A palavra em português %s não foi encontrada na árvore rubro-negra.\n", word);
            }
            printf("\n---------------------------------------------------------------\n");
            break;

        case 5:
            printf("\n---------------------------------------------------------------\n");
            showRedBlackTree(rootNode);
            printf("\n---------------------------------------------------------------\n");
            break;
        case 0:
            printf("\n---------------------------------------------------------------\n");
            printf("\nSaindo do programa\n");
            printf("\n---------------------------------------------------------------\n");
            break;
        default:
            printf("Insira um valor valido\n");
            break;
        }
    } while (op != 0);

    // freeTree(raiz);

    return 0;
}
