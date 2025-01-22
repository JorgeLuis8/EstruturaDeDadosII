#include "ingles.h" // Inclui o cabeçalho com as definições para a estrutura "Inglesbin".
#include <stdio.h>  // Inclui as funções padrão de entrada e saída.
#include <stdlib.h> // Inclui as funções para alocação e gerenciamento de memória.
#include <string.h> // Inclui as funções para manipulação de strings.
#include "unidade.h" // Inclui o cabeçalho com as definições para a estrutura "Unit".

// Função para inicializar um novo nó na árvore binária.
Inglesbin *initializeNode(const char *englishWord, int unit)
{
    Inglesbin *novoNo = (Inglesbin *)malloc(sizeof(Inglesbin)); // Aloca memória para um novo nó.
    if (novoNo != NULL) // Verifica se a alocação foi bem-sucedida.
    {
        // Aloca memória para armazenar a palavra em inglês e copia a palavra.
        novoNo->englishWord = (char *)malloc(strlen(englishWord) + 1);
        if (novoNo->englishWord != NULL)
        {
            strcpy(novoNo->englishWord, englishWord); // Copia a palavra para o nó.
        }

        novoNo->unitList = create_unit(unit); // Cria uma unidade e a associa ao nó.

        // Inicializa os ponteiros para os filhos como NULL.
        novoNo->leftChild = novoNo->rightChild = NULL;
    }
    return novoNo; // Retorna o ponteiro para o novo nó.
}

// Função para inserir uma palavra em inglês na árvore binária.
Inglesbin *insertEnglishWord(Inglesbin *root, const char *englishWord, int unit)
{
    Inglesbin *result;

    if (root == NULL) // Se a raiz for nula, cria um novo nó.
    {
        result = initializeNode(englishWord, unit);
    }
    else
    {
        // Se a palavra já existir, adiciona a unidade de forma ordenada.
        if (strcmp(englishWord, root->englishWord) == 0)
        {
            root->unitList = insert_unit_sorted(root->unitList, create_unit(unit));
            result = root;
        }
        else
        {
            // Decide para qual filho seguir com base na comparação das palavras.
            if (strcmp(englishWord, root->englishWord) < 0)
            {
                root->leftChild = insertEnglishWord(root->leftChild, englishWord, unit);
            }
            else
            {
                root->rightChild = insertEnglishWord(root->rightChild, englishWord, unit);
            }
            result = root;
        }
    }

    return result; // Retorna a raiz da árvore.
}

// Função para adicionar uma tradução em inglês a uma estrutura NodeInfo.
void addEnglishTranslation(NodeInfo *info, const char *englishWord, int unit)
{
    if (info->englishWord == NULL) // Se a lista de palavras em inglês for nula.
    {
        info->englishWord = initializeNode(englishWord, unit); // Inicializa um novo nó.
    }
    else
    {
        info->englishWord = insertEnglishWord(info->englishWord, englishWord, unit); // Insere a palavra na árvore existente.
    }

    // Adiciona a unidade de forma ordenada à lista.
    info->englishWord->unitList = insert_unit_sorted(info->englishWord->unitList, create_unit(unit));
}

// Função para imprimir as palavras da árvore binária em ordem.
void printBinaryTree(Inglesbin *root)
{
    if (root != NULL) // Verifica se a árvore não está vazia.
    {
        printBinaryTree(root->leftChild); // Percorre a subárvore esquerda.

        printf("\nPalavra em Inglês: %s\n", root->englishWord); // Imprime a palavra.

        if (root->unitList != NULL) // Se a lista de unidades não for nula.
        {
            printf("Unidades associadas: ");
            print_units(root->unitList); // Imprime as unidades associadas.
        }
        else
        {
            printf("Nenhuma unidade associada.\n");
        }

        printBinaryTree(root->rightChild); // Percorre a subárvore direita.
    }
}

// Função para verificar se um nó é uma folha.
int isLeafNode(Inglesbin *raiz)
{
    return (raiz->leftChild == NULL && raiz->rightChild == NULL); // Retorna verdadeiro se ambos os filhos forem NULL.
}

// Função para obter o único filho de um nó.
Inglesbin *getSingleChild(Inglesbin *raiz)
{
    Inglesbin *aux = NULL;

    // Retorna o filho esquerdo se o direito for NULL e vice-versa.
    if (raiz->rightChild == NULL)
    {
        aux = raiz->leftChild;
    }
    else if (raiz->leftChild == NULL)
    {
        aux = raiz->rightChild;
    }

    return aux;
}

// Função para obter o filho mais à esquerda de um nó.
Inglesbin *getMinimumChild(Inglesbin *raiz)
{
    Inglesbin *aux = raiz;

    // Percorre recursivamente para a esquerda até encontrar o menor nó.
    if (raiz)
    {
        if (raiz->leftChild)
            aux = getMinimumChild(raiz->leftChild);
    }

    return aux;
}

// Função para remover uma palavra em inglês da árvore.
int removeEnglishWord(Inglesbin **raiz, const char *englishWord, int unit)
{
    Inglesbin *childPointer = NULL;
    int isExists = 0;

    if (*raiz) // Se a raiz não for nula.
    {
        if (strcmp(englishWord, (*raiz)->englishWord) == 0) // Se a palavra foi encontrada.
        {
            Inglesbin *aux = *raiz;
            isExists = 1;

            if (isLeafNode(*raiz)) // Caso seja uma folha, libera o nó.
            {
                free(aux);
                *raiz = NULL;
            }
            else if ((childPointer = getSingleChild(*raiz)) != NULL) // Se tiver um único filho.
            {
                free(aux);
                *raiz = childPointer;
            }
            else // Caso tenha dois filhos, substitui pela menor palavra da subárvore direita.
            {
                childPointer = getMinimumChild((*raiz)->rightChild);
                strcpy((*raiz)->englishWord, childPointer->englishWord);
                (*raiz)->unitList = childPointer->unitList;

                // Remove recursivamente o nó substituído.
                removeEnglishWord(&(*raiz)->rightChild, childPointer->englishWord, unit);
            }
        }
        else if (strcmp(englishWord, (*raiz)->englishWord) < 0) // Procura na subárvore esquerda.
        {
            isExists = removeEnglishWord(&(*raiz)->leftChild, englishWord, unit);
        }
        else // Procura na subárvore direita.
        {
            isExists = removeEnglishWord(&(*raiz)->rightChild, englishWord, unit);
        }
    }

    return isExists; // Retorna se a palavra foi encontrada e removida.
}

// Função para liberar todos os nós da árvore.
void clear_binary_tree(Inglesbin *rootNode)
{
    if (rootNode != NULL)
    {
        printf("Liberando nó da árvore binária com palavra: %s\n", rootNode->englishWord);

        clear_binary_tree(rootNode->leftChild); // Libera a subárvore esquerda.
        clear_binary_tree(rootNode->rightChild); // Libera a subárvore direita.

        free_list(rootNode->unitList); // Libera a lista de unidades associadas.
        free(rootNode->englishWord); // Libera a palavra em inglês.
        free(rootNode); // Libera o nó.
    }
}

// Função para imprimir traduções associadas a uma unidade específica.
void printTranslations(Inglesbin *node, int unit, const char *portugueseWord)
{
    if (node)
    {
        printTranslations(node->leftChild, unit, portugueseWord); // Verifica a subárvore esquerda.

        if (find_unit(node->unitList, unit)) // Se a unidade for encontrada na lista.
        {
            printf("Palavra em Português: %s\n", portugueseWord);
            printf("Tradução em Inglês: %s\n", node->englishWord);
        }

        printTranslations(node->rightChild, unit, portugueseWord); // Verifica a subárvore direita.
    }
}

// Função para buscar uma palavra em inglês na árvore binária.
Inglesbin *findEnglishWord(Inglesbin *rootNode, const char *englishWord)
{
    Inglesbin *englishResult = NULL;

    if (rootNode != NULL)
    {
        int comparisonResult = strcmp(englishWord, rootNode->englishWord);

        if (comparisonResult == 0) // Palavra encontrada.
        {
            englishResult = rootNode;
        }
        else if (comparisonResult < 0) // Procura na subárvore esquerda.
        {
            englishResult = findEnglishWord(rootNode->leftChild, englishWord);
        }
        else // Procura na subárvore direita.
        {
            englishResult = findEnglishWord(rootNode->rightChild, englishWord);
        }
    }

    return englishResult; // Retorna o nó encontrado ou NULL.
}

// Função para buscar palavras em inglês associadas a uma unidade e exibir informações.
void FindEnglishWord(PortugueseTree **englishTreeRoot, char *englishWord, int unitIndex, PortugueseTree **parentNode)
{
    if (*englishTreeRoot != NULL)
    {
        FindEnglishWord(&(*englishTreeRoot)->left, englishWord, unitIndex, parentNode); // Busca na subárvore esquerda.

        if ((*englishTreeRoot)->info1.englishWord != NULL)
        {
            Inglesbin *traducaoEncontrada = findEnglishWord((*englishTreeRoot)->info1.englishWord, englishWord);
            if (traducaoEncontrada != NULL && find_unit(traducaoEncontrada->unitList, unitIndex))
            {
                printf("Palavra em Inglês: %s encontrada na Unidade: %d\n", englishWord, unitIndex);
            }
        }

        FindEnglishWord(&(*englishTreeRoot)->cent, englishWord, unitIndex, englishTreeRoot); // Busca no centro.

        if ((*englishTreeRoot)->nInfos == 2 && (*englishTreeRoot)->info2.englishWord != NULL)
        {
            Inglesbin *foundTranslation = findEnglishWord((*englishTreeRoot)->info2.englishWord, englishWord);
            if (foundTranslation != NULL && find_unit(foundTranslation->unitList, unitIndex))
            {
                printf("Palavra em Inglês: %s encontrada na Unidade: %d\n", englishWord, unitIndex);
            }
        }

        if ((*englishTreeRoot)->nInfos == 2)
        {
            FindEnglishWord(&(*englishTreeRoot)->right, englishWord, unitIndex, englishTreeRoot); // Busca na subárvore direita.
        }
    }
}

// Função para exibir todas as traduções em inglês em ordem.
void showEnglishTranslations(Inglesbin *englishRoot)
{
    if (englishRoot)
    {
        showEnglishTranslations(englishRoot->leftChild); // Percorre a subárvore esquerda.
        printf("- %s\n", englishRoot->englishWord); // Exibe a palavra.
        showEnglishTranslations(englishRoot->rightChild); // Percorre a subárvore direita.
    }
}
