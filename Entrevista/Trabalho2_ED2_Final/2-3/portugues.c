#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portugues.h"

// Função para encontrar uma palavra específica na árvore binária em português.
PortugueseTree *FindWord(PortugueseTree **node, const char *wordInPortuguese)
{
    PortugueseTree *result = NULL; // Inicializa o ponteiro de resultado como NULL.

    if (node != NULL && *node != NULL) // Verifica se o nó atual não é nulo.
    {
        // Compara a palavra procurada com a palavra principal (info1) do nó atual.
        if (strcmp(wordInPortuguese, (*node)->info1.portugueseWord) == 0)
        {
            result = *node; // Se for igual, retorna o nó atual.
        }
        else if ((*node)->nInfos == 2) // Se o nó tem duas informações (info1 e info2).
        {
            // Compara a palavra procurada com a palavra secundária (info2).
            if (strcmp(wordInPortuguese, (*node)->info2.portugueseWord) == 0)
            {
                result = *node; // Se for igual, retorna o nó atual.
            }
        }

        if (result == NULL) // Se o nó atual não contém a palavra, busca recursivamente.
        {
            if (strcmp(wordInPortuguese, (*node)->info1.portugueseWord) < 0) // Verifica se está à esquerda.
            {
                result = FindWord(&(*node)->left, wordInPortuguese);
            }
            else if ((*node)->nInfos == 1 || strcmp(wordInPortuguese, (*node)->info2.portugueseWord) < 0)
            {
                result = FindWord(&(*node)->cent, wordInPortuguese); // Busca no centro.
            }
            else
            {
                result = FindWord(&(*node)->right, wordInPortuguese); // Busca à direita.
            }
        }
    }

    return result; // Retorna o nó encontrado ou NULL.
}

// Função para inserir uma tradução em um nó existente.
void insertTranslation(PortugueseTree *node, const char *portugueseWord, const char *englishWord, int unit)
{
    if (strcmp(portugueseWord, node->info1.portugueseWord) == 0) // Verifica se a palavra corresponde à principal.
    {
        // Insere a tradução associada à palavra principal (info1).
        node->info1.englishWord = insertEnglishWord(node->info1.englishWord, englishWord, unit);
    }
    else if (node->nInfos == 2 && strcmp(portugueseWord, node->info2.portugueseWord) == 0) // Verifica se corresponde à secundária.
    {
        // Insere a tradução associada à palavra secundária (info2).
        node->info2.englishWord = insertEnglishWord(node->info2.englishWord, englishWord, unit);
    }
}

// Função para inserir um termo português na árvore.
int insertPortugueseTerm(PortugueseTree **portugueseTree, char *portugueseWord, char *englishWord, int unit)
{
    NodeInfo promotionInfo; // Armazena informações promovidas (em caso de divisão de nó).
    PortugueseTree *parentNode = NULL; // Nó pai, usado em inserções.
    int result = 0; // Variável para indicar se o termo já existia.

    // Busca o nó contendo a palavra em português na árvore.
    PortugueseTree *foundNode = FindWord(portugueseTree, portugueseWord);

    if (foundNode != NULL) // Se o nó foi encontrado.
    {
        // Insere a tradução no nó existente.
        insertTranslation(foundNode, portugueseWord, englishWord, unit);
        result = 1; // Indica que a palavra já existia.
    }
    else
    {
        // Cria uma nova informação para o termo português e suas traduções.
        NodeInfo novoInfo = createInfo(portugueseWord, englishWord, unit);
        // Insere o novo nó na árvore 2-3.
        insertNode23(portugueseTree, &novoInfo, &promotionInfo, &parentNode);
    }

    return result; // Retorna 1 se o termo já existia, ou 0 se foi inserido.
}

// Função para criar um objeto `NodeInfo` com palavra e traduções.
NodeInfo createInfo(char *portugueseWord, char *englishWord, int unit)
{
    NodeInfo newNodeInfo; // Estrutura para armazenar as informações do nó.
    newNodeInfo.portugueseWord = strdup(portugueseWord); // Duplica a palavra em português.
    newNodeInfo.englishWord = NULL; // Inicializa a lista de palavras em inglês como NULL.
    // Insere a tradução em inglês e a associa à unidade.
    newNodeInfo.englishWord = insertEnglishWord(newNodeInfo.englishWord, englishWord, unit);
    return newNodeInfo; // Retorna o objeto criado.
}

// Função para criar um novo nó na árvore 2-3.
PortugueseTree *createNode(NodeInfo *nodeInfo, PortugueseTree *leftChild, PortugueseTree *middlechild)
{
    PortugueseTree *no = (PortugueseTree *)malloc(sizeof(PortugueseTree)); // Aloca memória para o novo nó.
    no->info1 = *nodeInfo; // Copia as informações do nó principal (info1).
    no->info2.englishWord = NULL; // Inicializa a informação secundária como nula.
    no->info2.portugueseWord = NULL;
    no->left = leftChild; // Define o filho esquerdo.
    no->cent = middlechild; // Define o filho central.
    no->right = NULL; // Inicializa o filho direito como NULL.
    no->nInfos = 1; // Define que o nó possui apenas uma informação inicialmente.

    return no; // Retorna o ponteiro para o novo nó criado.
}


// Atualiza um nó existente na árvore 2-3 quando um novo valor é adicionado ao nó.
PortugueseTree *updateNode23(PortugueseTree *currentNode, NodeInfo *nodeInfo, PortugueseTree *childNode)
{
    // Verifica se a nova palavra deve ser inserida após a primeira palavra (info1).
    if (strcmp(nodeInfo->portugueseWord, currentNode->info1.portugueseWord) > 0)
    {
        currentNode->info2 = *nodeInfo;  // Define a nova palavra como info2.
        currentNode->right = childNode; // Atualiza o filho direito para o nó fornecido.
    }
    else // Caso a nova palavra seja menor que a primeira palavra (info1).
    {
        currentNode->info2 = currentNode->info1;  // Move info1 para info2.
        currentNode->right = currentNode->cent;   // Move o filho central para o filho direito.
        currentNode->info1 = *nodeInfo;          // Define a nova palavra como info1.
        currentNode->cent = childNode;           // Atualiza o filho central para o nó fornecido.
    }

    currentNode->nInfos = 2; // Atualiza o número de informações no nó para 2.
    return currentNode;      // Retorna o nó atualizado.
}

// Divide um nó da árvore 2-3 quando ele já contém duas informações (nós completos).
PortugueseTree *splitNode(PortugueseTree **currentNode, NodeInfo *nodeInfo, NodeInfo *promotedInfo, PortugueseTree **childNode)
{
    PortugueseTree *largestNode; // Cria o nó que receberá as maiores informações após a divisão.

    // Verifica se a nova palavra é maior que info2 (a maior palavra no nó atual).
    if (strcmp(nodeInfo->portugueseWord, (*currentNode)->info2.portugueseWord) > 0)
    {
        *promotedInfo = (*currentNode)->info2; // Promove info2 para o nó pai.
        // Cria um novo nó com a nova palavra e os filhos associados.
        largestNode = createNode(nodeInfo, (*currentNode)->right, childNode ? *childNode : NULL);
    }
    // Verifica se a nova palavra está entre info1 e info2.
    else if (strcmp(nodeInfo->portugueseWord, (*currentNode)->info1.portugueseWord) > 0)
    {
        *promotedInfo = *nodeInfo; // Promove a nova palavra para o nó pai.
        // Cria um novo nó com info2 e os filhos associados.
        largestNode = createNode(&(*currentNode)->info2, childNode ? *childNode : NULL, (*currentNode)->right);
    }
    // Caso a nova palavra seja menor que info1 (a menor palavra no nó atual).
    else
    {
        *promotedInfo = (*currentNode)->info1; // Promove info1 para o nó pai.
        // Cria um novo nó com info2 e os filhos associados.
        largestNode = createNode(&(*currentNode)->info2, (*currentNode)->cent, (*currentNode)->right);
        (*currentNode)->info1 = *nodeInfo;     // Substitui info1 pela nova palavra.
        (*currentNode)->cent = childNode ? *childNode : NULL; // Atualiza o filho central.
    }

    (*currentNode)->nInfos = 1; // Reduz o número de informações no nó original para 1.
    return largestNode;         // Retorna o nó criado para conter as maiores informações.
}

// Verifica se um nó é uma folha (não possui filhos).
int isNodeLeaf(PortugueseTree *no)
{
    return (no->left == NULL); // Retorna verdadeiro (1) se o nó não possuir um filho esquerdo.
}


// Insere um nó na árvore 2-3
PortugueseTree *insertNode23(PortugueseTree **currentNode, NodeInfo *nodeData, NodeInfo *promotionNode, PortugueseTree **parentNode)
{
    NodeInfo promotionInfo1;               // Variável para armazenar informações promovidas durante a divisão do nó
    PortugueseTree *largestNode = NULL;   // Ponteiro para o nó com os valores maiores após a divisão

    if (*currentNode == NULL) // Se o nó atual é nulo, cria um novo nó
    {
        *currentNode = createNode(nodeData, NULL, NULL); // Cria um nó com os dados fornecidos
    }
    else
    {
        if (isNodeLeaf(*currentNode)) // Verifica se o nó atual é uma folha
        { 
            if ((*currentNode)->nInfos == 1) // Se o nó tem apenas uma informação (não está cheio)
            {
                *currentNode = updateNode23(*currentNode, nodeData, NULL); // Atualiza o nó com o novo dado
            }
            else // Caso o nó já esteja cheio (possui 2 informações)
            {
                // Divide o nó em dois e promove uma informação para o nó pai
                largestNode = splitNode(currentNode, nodeData, promotionNode, NULL);
                if (*parentNode == NULL) // Se o nó não possui pai, cria uma nova raiz
                { 
                    *currentNode = createNode(promotionNode, *currentNode, largestNode);
                    largestNode = NULL; // Após promover, o maior nó é descartado
                }
            }
        }
        else // Se o nó atual não é uma folha, navega pelos filhos para inserir o dado
        { 
            // Determina em qual subárvore o dado deve ser inserido
            if (strcmp(nodeData->portugueseWord, (*currentNode)->info1.portugueseWord) < 0) // Vai para o filho esquerdo
            {
                largestNode = insertNode23(&((*currentNode)->left), nodeData, promotionNode, currentNode);
            }
            else if ((*currentNode)->nInfos == 1 || strcmp(nodeData->portugueseWord, (*currentNode)->info2.portugueseWord) < 0) // Vai para o filho central
            {
                largestNode = insertNode23(&((*currentNode)->cent), nodeData, promotionNode, currentNode);
            }
            else // Vai para o filho direito
            {
                largestNode = insertNode23(&((*currentNode)->right), nodeData, promotionNode, currentNode);
            }

            if (largestNode) // Se um nó foi promovido durante a inserção nos filhos
            {
                if ((*currentNode)->nInfos == 1) // Se o nó atual tem apenas uma informação
                {
                    *currentNode = updateNode23(*currentNode, promotionNode, largestNode); // Atualiza o nó com a promoção
                    largestNode = NULL;
                }
                else // Caso o nó já esteja cheio
                { 
                    PortugueseTree *newnode;
                    // Divide o nó atual e promove uma informação para o nó pai
                    newnode = splitNode(currentNode, promotionNode, &promotionInfo1, &largestNode); 
                    if (*parentNode == NULL) // Se o nó atual não tem pai (é a raiz)
                    {
                        PortugueseTree *novaRaiz;
                        // Cria uma nova raiz para a árvore
                        novaRaiz = createNode(&promotionInfo1, *currentNode, newnode); 
                        *currentNode = novaRaiz;
                        largestNode = NULL;
                    }
                    else
                    {
                        largestNode = newnode; // O nó maior é retornado para ser tratado pelo pai
                        *promotionNode = promotionInfo1; // Atualiza o nó promovido
                    }
                }
            }
        }
    }

    return largestNode; // Retorna o maior nó gerado após a operação
}

// Função para imprimir a árvore 2-3 em ordem
void print_tree23(PortugueseTree *rootNode)
{
    if (rootNode != NULL) // Verifica se o nó não é nulo
    {
        print_tree23(rootNode->left); // Imprime a subárvore esquerda

        // Imprime a primeira informação do nó
        printf("Palavra (PT): %s", rootNode->info1.portugueseWord);
        if (rootNode->info1.englishWord != NULL && rootNode->info1.englishWord->englishWord != NULL)
        {
            printBinaryTree(rootNode->info1.englishWord); // Imprime as traduções associadas
            printf("\n");
        }

        print_tree23(rootNode->cent); // Imprime a subárvore central
  
        if (rootNode->nInfos == 2) // Se o nó possui uma segunda informação
        {
            printf("Palavra (PT): %s", rootNode->info2.portugueseWord);

            if (rootNode->info2.englishWord != NULL && rootNode->info2.englishWord->englishWord != NULL)
            {
                printBinaryTree(rootNode->info2.englishWord); // Imprime as traduções associadas
            }
            printf("\n");
        }

        if (rootNode->nInfos == 2) // Imprime a subárvore direita, se existir
        {
            print_tree23(rootNode->right);
        }
    }
}


// Função para imprimir palavras de uma unidade específica na árvore 2-3.
void printWordsAtUnit(PortugueseTree *portugueseTree, int unit, int *printedUnit)
{
    if (portugueseTree) // Verifica se o nó atual não é nulo.
    {
        // Recursivamente percorre a subárvore esquerda.
        printWordsAtUnit(portugueseTree->left, unit, printedUnit);

        // Imprime o cabeçalho da unidade uma única vez.
        if (!(*printedUnit)) // Se a unidade ainda não foi impressa.
        {
            printf("%% Unidade %d\n", unit); // Imprime o identificador da unidade.
            *printedUnit = 1;              // Marca que a unidade foi impressa.
        }

        // Verifica se há palavras em inglês associadas a info1 e as imprime.
        if (portugueseTree->info1.englishWord != NULL)
        {
            printTranslationsInFormat(portugueseTree->info1.englishWord, unit, portugueseTree->info1.portugueseWord);
        }

        // Recursivamente percorre a subárvore central.
        printWordsAtUnit(portugueseTree->cent, unit, printedUnit);

        // Verifica se há palavras em inglês associadas a info2 e as imprime.
        if (portugueseTree->nInfos == 2 && portugueseTree->info2.englishWord != NULL)
        {
            printTranslationsInFormat(portugueseTree->info2.englishWord, unit, portugueseTree->info2.portugueseWord);
        }

        // Recursivamente percorre a subárvore direita, se info2 existir.
        if (portugueseTree->nInfos == 2)
        {
            printWordsAtUnit(portugueseTree->right, unit, printedUnit);
        }
    }
}

// Função para imprimir traduções em formato específico para uma unidade.
void printTranslationsInFormat(Inglesbin *node, int unit, const char *portugueseWord)
{
    if (node) // Verifica se o nó não é nulo.
    {
        // Recursivamente percorre a subárvore esquerda.
        printTranslationsInFormat(node->leftChild, unit, portugueseWord);

        // Verifica se a unidade está associada à palavra atual.
        if (find_unit(node->unitList, unit)) 
        {
            // Remove um ponto e vírgula extra no final da palavra portuguesa, se existir.
            char formattedWord[256];
            strcpy(formattedWord, portugueseWord); // Copia a palavra para evitar alterações no original.
            size_t len = strlen(formattedWord);
            if (len > 0 && formattedWord[len - 1] == ';')
            {
                formattedWord[len - 1] = '\0'; // Remove o ponto e vírgula final.
            }

            // Imprime a palavra em formato "Português: Inglês;".
            printf("%s: %s;\n", formattedWord, node->englishWord);
        }

        // Recursivamente percorre a subárvore direita.
        printTranslationsInFormat(node->rightChild, unit, portugueseWord);
    }
}

// Função para imprimir todas as traduções associadas a uma palavra em português.
void printAllTranslations(PortugueseTree *rootNode, const char *portugueseWord)
{
    int isFound = 0; // Flag para verificar se a palavra foi encontrada.

    if (rootNode == NULL) // Se o nó atual é nulo, a palavra não foi encontrada.
    {
        printf("A palavra '%s' nao foi encontrada.\n", portugueseWord);
    }
    else
    {
        // Verifica se a palavra corresponde ao info1 do nó atual.
        if (strcmp(rootNode->info1.portugueseWord, portugueseWord) == 0)
        {
            printf("Traducoes para '%s':\n", portugueseWord);
            showEnglishTranslations(rootNode->info1.englishWord); // Imprime traduções associadas.
            isFound = 1; // Marca que a palavra foi encontrada.
        }

        // Verifica se a palavra corresponde ao info2 do nó atual.
        if (!isFound && rootNode->nInfos == 2 && strcmp(rootNode->info2.portugueseWord, portugueseWord) == 0)
        {
            printf("Traducoes para '%s':\n", portugueseWord);
            showEnglishTranslations(rootNode->info2.englishWord); // Imprime traduções associadas.
            isFound = 1;
        }

        // Se a palavra não foi encontrada, busca nas subárvores apropriadas.
        if (!isFound)
        {
            if (strcmp(portugueseWord, rootNode->info1.portugueseWord) < 0) // Busca na subárvore esquerda.
            {
                printAllTranslations(rootNode->left, portugueseWord);
            }
            else if (rootNode->nInfos == 1 || strcmp(portugueseWord, rootNode->info2.portugueseWord) < 0) // Busca na subárvore central.
            {
                printAllTranslations(rootNode->cent, portugueseWord);
            }
            else // Busca na subárvore direita.
            {
                printAllTranslations(rootNode->right, portugueseWord);
            }
        }
    }
}

// Função para imprimir as traduções em inglês associadas a uma palavra em português.
void printPortugueseTranslation(PortugueseTree **rootNode, const char *portugueseWord)
{
    // Busca a palavra em português na árvore.
    PortugueseTree *foundPortugueseWord = FindWord(rootNode, portugueseWord);
    if (foundPortugueseWord) // Se a palavra foi encontrada.
    {
        printf("Traduções em inglês para a palavra '%s':\n", portugueseWord);

        // Verifica se a palavra corresponde ao info1 e imprime as traduções.
        if (strcmp(portugueseWord, foundPortugueseWord->info1.portugueseWord) == 0)
        {
            printBinaryTree(foundPortugueseWord->info1.englishWord);
        }
        // Verifica se a palavra corresponde ao info2 e imprime as traduções.
        else if (foundPortugueseWord->nInfos == 2 && strcmp(portugueseWord, foundPortugueseWord->info2.portugueseWord) == 0)
        {
            printBinaryTree(foundPortugueseWord->info2.englishWord);
        }
    }
    else // Se a palavra não foi encontrada.
    {
        printf("A palavra '%s' não foi encontrada na árvore.\n", portugueseWord);
    }
}


// Retorna a maior informação presente no nó (info2, se existir, caso contrário, info1).
NodeInfo getLargestNodeInfo(PortugueseTree *rootNode)
{
    return rootNode->nInfos == 2 ? rootNode->info2 : rootNode->info1; // Verifica se o nó tem duas informações.
}

// Verifica se a palavra fornecida corresponde à info1 do nó.
int eh_info1(PortugueseTree node, char *info)
{
    return strcmp(info, node.info1.portugueseWord) == 0; // Compara a palavra com a info1.
}

// Verifica se a palavra fornecida corresponde à info2 do nó.
int eh_info2(PortugueseTree node, char *nodeInfo)
{
    // Verifica se o nó tem duas informações e compara a palavra com info2.
    return node.nInfos == 2 && strcmp(nodeInfo, node.info2.portugueseWord) == 0;
}

// Encontra o filho máximo na árvore (nó mais à direita).
PortugueseTree *get_maximum_child_from_tree(PortugueseTree *rootNode, PortugueseTree **parentNode, NodeInfo *max_value)
{
    PortugueseTree *filho; // Ponteiro para armazenar o nó filho.
    filho = rootNode; // Inicializa com o nó raiz.

    // Navega para o nó folha mais à direita.
    while (!isNodeLeaf(filho)) // Continua até encontrar um nó folha.
    {
        *parentNode = filho; // Atualiza o nó pai durante a navegação.
        if (filho->nInfos == 1) // Se o nó tem uma informação, move para o filho central.
            filho = filho->cent;
        else // Se o nó tem duas informações, move para o filho direito.
            filho = filho->right;
    }

    // Obtém a maior informação do nó folha encontrado.
    if (filho != NULL)
        *max_value = getLargestNodeInfo(filho);

    return filho; // Retorna o nó folha encontrado.
}

// Encontra o filho mínimo na árvore (nó mais à esquerda).
PortugueseTree *findMinimumChild(PortugueseTree *rootNode, PortugueseTree **parentNode)
{
    PortugueseTree *filho; // Ponteiro para armazenar o nó filho.
    filho = rootNode; // Inicializa com o nó raiz.

    // Navega para o nó folha mais à esquerda.
    while (!isNodeLeaf(filho)) // Continua até encontrar um nó folha.
    {
        *parentNode = filho; // Atualiza o nó pai durante a navegação.
        filho = filho->left; // Move para o filho esquerdo.
    }

    return filho; // Retorna o nó folha encontrado.
}

// Calcula a altura da árvore a partir de um nó.
int calculate_height(PortugueseTree *node)
{
    int altura = -1; // Inicializa a altura como -1 (caso o nó seja nulo).
    if (node != NULL) // Verifica se o nó não é nulo.
        altura = 1 + calculate_height(node->left); // Adiciona 1 à altura e calcula recursivamente pela subárvore esquerda.
    return altura; // Retorna a altura calculada.
}

// Realiza a movimentação de nós durante remoções e reequilíbrio.
int wave_movement(NodeInfo nodeLeaving, NodeInfo *inputNode, PortugueseTree *parentNode, PortugueseTree **originPointer, PortugueseTree **rootNode, PortugueseTree **largestNode, int (*remove_node)(PortugueseTree **, char *, PortugueseTree *, PortugueseTree **, PortugueseTree **))
{
    // Remove o nó especificado da árvore.
    int isRemoved = remove_node(rootNode, nodeLeaving.portugueseWord, parentNode, originPointer, largestNode);
    *inputNode = nodeLeaving; // Atualiza o nó de entrada com o nó que está saindo.
    return isRemoved; // Retorna o status da remoção.
}


// Função para encontrar o nó pai de um nó específico em uma árvore 2-3.
PortugueseTree *findParentIn23Tree(PortugueseTree *rootNode, char *nodeValue)
{
    PortugueseTree *parentNode = NULL; // Inicializa o ponteiro do nó pai como nulo.

    if (rootNode != NULL) // Verifica se o nó raiz não é nulo.
    {
        // Verifica se o valor procurado não está presente no nó atual (nem em info1 nem em info2).
        if (!eh_info1(*rootNode, nodeValue) && !eh_info2(*rootNode, nodeValue))
        {
            // Decide qual subárvore explorar com base no valor do nó.
            if (strcmp(nodeValue, rootNode->info1.portugueseWord) < 0) // Vai para a subárvore esquerda.
                parentNode = findParentIn23Tree(rootNode->left, nodeValue);
            else if (rootNode->nInfos == 1 || (strcmp(nodeValue, rootNode->info2.portugueseWord) < 0)) // Vai para a subárvore central.
                parentNode = findParentIn23Tree(rootNode->cent, nodeValue);
            else // Vai para a subárvore direita.
                parentNode = findParentIn23Tree(rootNode->right, nodeValue);

            // Se o nó pai não foi encontrado nas subárvores, o nó atual é o pai.
            if (parentNode == NULL)
                parentNode = rootNode;
        }
    }

    return parentNode; // Retorna o nó pai encontrado (ou nulo, se não encontrado).
}

// Função para encontrar o maior nó pai de um valor na árvore 2-3.
PortugueseTree *findLargestParentIn23Tree(PortugueseTree *rootNode, char *nodeInfo)
{
    PortugueseTree *parentNode = NULL; // Inicializa o ponteiro do nó pai como nulo.

    if (rootNode != NULL) // Verifica se o nó raiz não é nulo.
    {
        // Verifica se o valor procurado não está presente no nó atual.
        if (!eh_info1(*rootNode, nodeInfo) && !eh_info2(*rootNode, nodeInfo))
        {
            // Decide qual subárvore explorar com base no valor do nó.
            if (strcmp(nodeInfo, rootNode->info1.portugueseWord) < 0) // Vai para a subárvore esquerda.
                parentNode = findLargestParentIn23Tree(rootNode->left, nodeInfo);
            else if (rootNode->nInfos == 1 || (strcmp(nodeInfo, rootNode->info2.portugueseWord) < 0)) // Vai para a subárvore central.
                parentNode = findLargestParentIn23Tree(rootNode->cent, nodeInfo);
            else // Vai para a subárvore direita.
                parentNode = findLargestParentIn23Tree(rootNode->right, nodeInfo);

            // Se o nó pai não foi encontrado nas subárvores, verifica se o nó atual é um candidato.
            if (parentNode == NULL &&
                ((rootNode->nInfos == 1 && (strcmp(rootNode->info1.portugueseWord, nodeInfo) > 0)) || // Compara com info1.
                 (rootNode->nInfos == 2 && (strcmp(rootNode->info2.portugueseWord, nodeInfo) > 0)))) // Compara com info2.
            {
                parentNode = rootNode; // Atualiza o nó pai como o nó atual.
            }
        }
    }

    return parentNode; // Retorna o maior nó pai encontrado.
}

// Função para encontrar o menor nó pai que possui duas informações.
PortugueseTree *findSmallestParentWithTwoInfo(PortugueseTree *rootNode, char *nodeInfo)
{
    PortugueseTree *parentNode = NULL; // Inicializa o ponteiro do nó pai como nulo.

    if (rootNode != NULL) // Verifica se o nó raiz não é nulo.
    {
        // Verifica se o valor procurado não está presente no nó atual.
        if (!eh_info1(*rootNode, nodeInfo) && !eh_info2(*rootNode, nodeInfo))
        {
            // Decide qual subárvore explorar com base no valor do nó.
            if (strcmp(nodeInfo, rootNode->info1.portugueseWord) < 0) // Vai para a subárvore esquerda.
                parentNode = findSmallestParentWithTwoInfo(rootNode->left, nodeInfo);
            else if (rootNode->nInfos == 1 || (strcmp(nodeInfo, rootNode->info2.portugueseWord) < 0)) // Vai para a subárvore central.
                parentNode = findSmallestParentWithTwoInfo(rootNode->cent, nodeInfo);
            else // Vai para a subárvore direita.
                parentNode = findSmallestParentWithTwoInfo(rootNode->right, nodeInfo);

            // Se o nó pai não foi encontrado nas subárvores, verifica se o nó atual possui duas informações.
            if (parentNode == NULL && rootNode->nInfos == 2 && strcmp(rootNode->info2.portugueseWord, nodeInfo) < 0)
                parentNode = rootNode; // Atualiza o nó pai como o nó atual.
        }
    }

    return parentNode; // Retorna o menor nó pai encontrado.
}

// Função para encontrar o menor nó pai em uma árvore 2-3.
PortugueseTree *findSmallestParent23(PortugueseTree *rootNode, char *nodeInfo)
{
    PortugueseTree *parentNode = NULL; // Inicializa o ponteiro do nó pai como nulo.

    if (rootNode != NULL) // Verifica se o nó raiz não é nulo.
    {
        // Verifica se o valor procurado não está presente no nó atual.
        if (!eh_info1(*rootNode, nodeInfo) && !eh_info2(*rootNode, nodeInfo))
        {
            // Decide qual subárvore explorar com base no valor do nó.
            if (strcmp(nodeInfo, rootNode->info1.portugueseWord) < 0) // Vai para a subárvore esquerda.
                parentNode = findSmallestParent23(rootNode->left, nodeInfo);
            else if (rootNode->nInfos == 1 || strcmp(nodeInfo, rootNode->info2.portugueseWord) < 0) // Vai para a subárvore central.
                parentNode = findSmallestParent23(rootNode->cent, nodeInfo);
            else // Vai para a subárvore direita.
                parentNode = findSmallestParent23(rootNode->right, nodeInfo);

            // Se o nó pai não foi encontrado nas subárvores, verifica se o nó atual é um candidato.
            if (parentNode == NULL && strcmp(rootNode->info1.portugueseWord, nodeInfo) < 0)
                parentNode = rootNode; // Atualiza o nó pai como o nó atual.
        }
    }

    return parentNode; // Retorna o menor nó pai encontrado.
}


// Função para remover um nó não folha de uma árvore 2-3.
int removeNonLeafNodeFrom23Tree(PortugueseTree **treeRoot, PortugueseTree *rootNode, NodeInfo *nodeInfo, PortugueseTree *leftChild, PortugueseTree *rightChild, PortugueseTree **maxNode)
{
    int isRemoved; // Variável para armazenar o status da remoção.
    PortugueseTree *childNode, *parentNode; // Ponteiros para o nó filho e pai.
    NodeInfo child_node_info; // Informação do nó filho.

    parentNode = rootNode; // Inicializa o nó pai como o nó raiz.

    // Obtém o nó máximo da subárvore esquerda.
    childNode = get_maximum_child_from_tree(leftChild, &parentNode, &child_node_info);

    // Verifica se o nó máximo encontrado tem duas informações.
    if (childNode->nInfos == 2)
    {
        *nodeInfo = child_node_info; // Atualiza a informação do nó removido.
        childNode->nInfos = 1; // Reduz o número de informações no nó filho.
        isRemoved = 1; // Marca como removido com sucesso.
    }
    else
    {
        // Se o nó máximo não tem duas informações, procura o nó mínimo da subárvore direita.
        childNode = findMinimumChild(rightChild, &parentNode);
        
        // Realiza o movimento de reequilíbrio e remoção.
        isRemoved = wave_movement(childNode->info1, nodeInfo, parentNode, treeRoot, &childNode, maxNode, deleteFrom23Tree);
    }

    return isRemoved; // Retorna o status da remoção.
}

// Função para a remoção de nós não folha com uma lógica específica.
int nonLeafNodeDeletion(PortugueseTree **treeRoot, PortugueseTree *rootNode, NodeInfo *nodeInfo, PortugueseTree *leftChild, PortugueseTree *rightChild, PortugueseTree **maxNode)
{
    int isRemoved = 0; // Variável para armazenar o status da remoção.
    PortugueseTree *childNode, *parentNode; // Ponteiros para o nó filho e pai.
    NodeInfo info_filho; // Informação do nó filho.

    parentNode = rootNode; // Inicializa o nó pai como o nó raiz.

    // Obtém o nó mínimo da subárvore esquerda.
    childNode = findMinimumChild(leftChild, &parentNode);

    // Verifica se o nó mínimo encontrado tem duas informações.
    if (childNode->nInfos == 2)
    {
        *nodeInfo = childNode->info1; // Atualiza a informação do nó removido.
        childNode->info1 = childNode->info2; // Move info2 para info1.
        childNode->nInfos = 1; // Reduz o número de informações no nó filho.
        isRemoved = 1; // Marca como removido com sucesso.
    }
    else
    {
        // Se o nó mínimo não tem duas informações, procura o nó máximo da subárvore direita.
        childNode = get_maximum_child_from_tree(rightChild, &parentNode, &info_filho);
        
        // Realiza o movimento de reequilíbrio e remoção.
        isRemoved = wave_movement(info_filho, nodeInfo, parentNode, treeRoot, &childNode, maxNode, removeNodeFrom23Tree);
    }

    return isRemoved; // Retorna o status da remoção.
}


// Função para remover um nó da árvore 2-3.
int deleteFrom23Tree(PortugueseTree **rootNode, char *nodeInfo, PortugueseTree *parentNode, PortugueseTree **sourceNode, PortugueseTree **maxNode)
{
    int isRemoved = 0; // Variável para indicar se o nó foi removido.

    if (*rootNode != NULL) // Verifica se a árvore não está vazia.
    {
        int info1 = eh_info1(**rootNode, nodeInfo); // Verifica se o valor está em info1.
        int info2 = eh_info2(**rootNode, nodeInfo); // Verifica se o valor está em info2.

        if (info1 || info2) // Se o valor está no nó atual.
        {
            isRemoved = 1; // Indica que o nó foi encontrado.

            if (isNodeLeaf(*rootNode)) // Se o nó atual é uma folha.
            {
                if ((*rootNode)->nInfos == 2) // Caso o nó tenha dois valores.
                {
                    if (info1) // Se o valor está em info1.
                    {
                        (*rootNode)->info1 = (*rootNode)->info2; // Move info2 para info1.
                        (*rootNode)->nInfos = 1; // Reduz o número de valores no nó.
                    }
                }
                else // Caso o nó tenha apenas um valor.
                {
                    if (parentNode == NULL) // Se o nó não tem pai, desaloca o nó.
                        deallocateTree(rootNode);
                    else // Caso contrário, realiza movimentos de reequilíbrio.
                    {
                        PortugueseTree *parent_node_temp;
                        NodeInfo parent_node_info;

                        if (*rootNode == parentNode->left || (parentNode->nInfos == 2 && *rootNode == parentNode->cent))
                        {
                            // Encontra o pai do nó para reequilibrar.
                            parent_node_temp = findParentIn23Tree(*sourceNode, parentNode->info1.portugueseWord);

                            parent_node_info = (*rootNode == parentNode->left) ? parentNode->info1 : parentNode->info2;

                            // Realiza o movimento de reequilíbrio.
                            isRemoved = wave_movement(parent_node_info, &((*rootNode)->info1), parent_node_temp, sourceNode, &parentNode, maxNode, deleteFrom23Tree);
                        }
                        else
                        {
                            // Caso contrário, ajusta os nós a partir do maior pai.
                            parent_node_temp = findLargestParentIn23Tree(*sourceNode, (*rootNode)->info1.portugueseWord);

                            PortugueseTree *smallest_parent = findSmallestParentWithTwoInfo(*sourceNode, (*rootNode)->info1.portugueseWord);

                            if (parent_node_temp != NULL)
                            {
                                if (strcmp(parent_node_temp->info1.portugueseWord, (*rootNode)->info1.portugueseWord) > 0)
                                    parent_node_info = parent_node_temp->info1;
                                else
                                    parent_node_info = parent_node_temp->info2;
                            }

                            int height_of_smaller_parent = calculate_height(smallest_parent);
                            int parent_node_height = calculate_height(parent_node_temp);

                            if (parent_node_temp == NULL || (parent_node_temp != parentNode && smallest_parent != NULL &&
                                                             height_of_smaller_parent <= parent_node_height &&
                                                             strcmp(parent_node_info.portugueseWord, smallest_parent->info2.portugueseWord) > 0))
                            {
                                *maxNode = parentNode;
                                (*rootNode)->nInfos = 0; // Marca o nó como vazio.
                                isRemoved = -1; // Indica falha na remoção.
                            }
                            else
                            {
                                PortugueseTree *grandparent = findParentIn23Tree(*sourceNode, parent_node_info.portugueseWord);
                                isRemoved = wave_movement(parent_node_info, &((*rootNode)->info1), grandparent, sourceNode, &parent_node_temp, maxNode, deleteFrom23Tree);
                            }
                        }
                    }
                }
            }
            else if (info2) // Caso o valor esteja em info2.
                isRemoved = removeNonLeafNodeFrom23Tree(sourceNode, *rootNode, &((*rootNode)->info2), (*rootNode)->cent, (*rootNode)->right, maxNode);
            else if (info1) // Caso o valor esteja em info1.
                isRemoved = removeNonLeafNodeFrom23Tree(sourceNode, *rootNode, &((*rootNode)->info1), (*rootNode)->left, (*rootNode)->cent, maxNode);
        }
        else // Se o valor não está no nó atual.
        {
            if (strcmp(nodeInfo, (*rootNode)->info1.portugueseWord) < 0) // Vai para a subárvore esquerda.
                isRemoved = deleteFrom23Tree(&(*rootNode)->left, nodeInfo, *rootNode, sourceNode, maxNode);
            else if ((*rootNode)->nInfos == 1 || (strcmp(nodeInfo, (*rootNode)->info2.portugueseWord) < 0)) // Vai para a subárvore central.
                isRemoved = deleteFrom23Tree(&(*rootNode)->cent, nodeInfo, *rootNode, sourceNode, maxNode);
            else // Vai para a subárvore direita.
                isRemoved = deleteFrom23Tree(&(*rootNode)->right, nodeInfo, *rootNode, sourceNode, maxNode);
        }
    }

    return isRemoved; // Retorna o status da remoção.
}

// Função para remover um nó de uma árvore 2-3.
int removeNodeFrom23Tree(PortugueseTree **treeRoot, char *nodeData, PortugueseTree *parentNode, PortugueseTree **sourceNode, PortugueseTree **largestNode)
{
    int isRemoved = 0; // Variável para indicar se o nó foi removido.

    if (*treeRoot != NULL) // Verifica se a árvore não está vazia.
    {
        int info1 = eh_info1(**treeRoot, nodeData); // Verifica se o valor está em info1.
        int info2 = eh_info2(**treeRoot, nodeData); // Verifica se o valor está em info2.

        if (info1 || info2) // Se o valor está no nó atual.
        {
            isRemoved = 1; // Indica que o nó foi encontrado.

            if (isNodeLeaf(*treeRoot)) // Se o nó atual é uma folha.
            {
                if ((*treeRoot)->nInfos == 2) // Caso o nó tenha dois valores.
                {
                    if (info1)
                        (*treeRoot)->info1 = (*treeRoot)->info2; // Move info2 para info1.

                    (*treeRoot)->nInfos = 1; // Reduz o número de valores no nó.
                }
                else // Caso o nó tenha apenas um valor.
                {
                    if (parentNode == NULL) // Se o nó não tem pai, desaloca o nó.
                        deallocateTree(treeRoot);
                    else // Caso contrário, realiza movimentos de reequilíbrio.
                    {
                        PortugueseTree *parent_node = findParentIn23Tree(*sourceNode, parentNode->info1.portugueseWord);

                        PortugueseTree *minimum_parent = findSmallestParentWithTwoInfo(*sourceNode, (*treeRoot)->info1.portugueseWord);

                        if (parent_node == NULL || (parent_node != parentNode && minimum_parent != NULL))
                        {
                            isRemoved = -1; // Indica falha na remoção.
                            *largestNode = parentNode; // Atualiza o maior nó.
                        }
                        else
                        {
                            NodeInfo parent_node_info = parent_node->nInfos == 2 && parent_node->info2.portugueseWord < (*treeRoot)->info1.portugueseWord
                                                            ? parent_node->info2
                                                            : parent_node->info1;

                            PortugueseTree *ancestorNode = findParentIn23Tree(*sourceNode, parent_node_info.portugueseWord);
                            isRemoved = wave_movement(parent_node_info, &((*treeRoot)->info1), ancestorNode, sourceNode, &parent_node, largestNode, removeNodeFrom23Tree);
                        }
                    }
                }
            }
            else if (info2) // Caso o valor esteja em info2.
                isRemoved = nonLeafNodeDeletion(sourceNode, *treeRoot, &((*treeRoot)->info2), (*treeRoot)->right, (*treeRoot)->cent, largestNode);
            else if (info1) // Caso o valor esteja em info1.
                isRemoved = nonLeafNodeDeletion(sourceNode, *treeRoot, &((*treeRoot)->info1), (*treeRoot)->cent, (*treeRoot)->left, largestNode);
        }
        else // Se o valor não está no nó atual.
        {
            if (strcmp(nodeData, (*treeRoot)->info1.portugueseWord) < 0) // Vai para a subárvore esquerda.
                isRemoved = removeNodeFrom23Tree(&(*treeRoot)->left, nodeData, *treeRoot, sourceNode, largestNode);
            else if ((*treeRoot)->nInfos == 1 || (strcmp(nodeData, (*treeRoot)->info2.portugueseWord) < 0)) // Vai para a subárvore central.
                isRemoved = removeNodeFrom23Tree(&(*treeRoot)->cent, nodeData, *treeRoot, sourceNode, largestNode);
            else // Vai para a subárvore direita.
                isRemoved = removeNodeFrom23Tree(&(*treeRoot)->right, nodeData, *treeRoot, sourceNode, largestNode);
        }
    }

    return isRemoved; // Retorna o status da remoção.
}

// Verifica se é possível remover um nó da árvore 2-3.
int can_remove_node(PortugueseTree *rootNode)
{
    int isPossible = 0; // Variável para indicar se a remoção é possível.

    if (rootNode != NULL) // Verifica se o nó não é nulo.
    {
        isPossible = rootNode->nInfos == 2; // Pode remover se o nó tiver 2 informações.

        if (!isPossible) // Caso o nó não tenha 2 informações, verifica as subárvores.
        {
            isPossible = can_remove_node(rootNode->cent); // Verifica a subárvore central.

            if (!isPossible) // Se ainda não é possível, verifica a subárvore esquerda.
                isPossible = can_remove_node(rootNode->left);
        }
    }

    return isPossible; // Retorna se é possível remover.
}

// Realiza a fusão de dois nós na árvore 2-3.
PortugueseTree *mergeNode23(PortugueseTree *leftChild, NodeInfo *nodeData, PortugueseTree *largestChild, PortugueseTree **treeRoot)
{
    updateNode23(leftChild, nodeData, largestChild); // Atualiza o nó esquerdo com os dados fornecidos e o maior filho.

    (*treeRoot)->nInfos--; // Reduz o número de informações no nó raiz.

    if ((*treeRoot)->nInfos == 0) // Se o nó raiz ficou vazio, desaloca-o.
        deallocateTree(treeRoot);

    return leftChild; // Retorna o nó esquerdo atualizado.
}

// Realiza o balanceamento dos nós em uma árvore 2-3.
void balanceTreeNodes(PortugueseTree **rootNode, PortugueseTree *leftChild, PortugueseTree **secondChild, NodeInfo nodeInfo, PortugueseTree **largestNode)
{
    if (*secondChild == NULL || (*secondChild)->nInfos == 0) // Se o segundo filho não existe ou está vazio.
    {
        if (*secondChild != NULL) // Se o segundo filho não é nulo, desaloca-o.
            deallocateTree(secondChild);

        // Faz a fusão dos nós para balancear a árvore.
        *largestNode = mergeNode23(leftChild, &nodeInfo, *largestNode, rootNode);
    }
}

// Realiza o reequilíbrio da árvore 2-3 após uma remoção.
int rebalanceTree23(PortugueseTree **treeRoot, char *nodeData, PortugueseTree **largestNode)
{
    int isBalanced = 0; // Variável para indicar se a árvore está balanceada.

    if (*treeRoot != NULL) // Verifica se a árvore não está vazia.
    {
        if (!isNodeLeaf(*treeRoot)) // Se o nó atual não é uma folha.
        {
            // Determina a subárvore apropriada para continuar a busca.
            if (strcmp(nodeData, (*treeRoot)->info1.portugueseWord) < 0)
                isBalanced = rebalanceTree23(&((*treeRoot)->left), nodeData, largestNode); // Subárvore esquerda.
            else if ((*treeRoot)->nInfos == 1 || (strcmp(nodeData, (*treeRoot)->info2.portugueseWord) < 0))
            {
                // Verifica se pode remover do centro, senão retorna erro.
                if ((*treeRoot)->left->nInfos == 2 && !can_remove_node((*treeRoot)->cent))
                    isBalanced = -1; // Indica falha no balanceamento.
                else
                    isBalanced = rebalanceTree23(&((*treeRoot)->cent), nodeData, largestNode); // Subárvore central.
            }
            else
            {
                // Verifica se pode remover da direita, senão retorna erro.
                if ((*treeRoot)->cent->nInfos == 2 && !can_remove_node((*treeRoot)->right))
                    isBalanced = -1; // Indica falha no balanceamento.
                else
                    isBalanced = rebalanceTree23(&((*treeRoot)->right), nodeData, largestNode); // Subárvore direita.
            }

            // Se o balanceamento foi bem-sucedido, ajusta os nós.
            if (isBalanced != -1)
            {
                if ((*treeRoot)->nInfos == 1) // Se o nó raiz tem 1 informação.
                    balanceTreeNodes(treeRoot, (*treeRoot)->left, &((*treeRoot)->cent), (*treeRoot)->info1, largestNode); // Balanceia entre esquerda e centro.
                else if ((*treeRoot)->nInfos == 2) // Se o nó raiz tem 2 informações.
                    balanceTreeNodes(treeRoot, (*treeRoot)->cent, &((*treeRoot)->right), (*treeRoot)->info2, largestNode); // Balanceia entre centro e direita.

                isBalanced = 1; // Indica sucesso no balanceamento.
            }
        }
    }

    return isBalanced; // Retorna o status do balanceamento.
}


int remove_node_from23_tree(PortugueseTree **root, char *nodeValue) {
    // Declara ponteiros auxiliares para o maior nó e a posição de junção.
    PortugueseTree *largestNode, *junction_position;

    // Chama a função `deleteFrom23Tree` para remover o nó e determinar o status da remoção.
    int isDeleted = deleteFrom23Tree(root, nodeValue, NULL, root, &junction_position);

    // Verifica se a remoção resultou em uma necessidade de reequilíbrio.
    if (isDeleted == -1) {
        // Obtém o maior valor associado ao nó de junção.
        NodeInfo junction_node_value = getLargestNodeInfo(junction_position);
        largestNode = NULL;

        // Reequilibra a árvore com base no maior valor do nó de junção.
        isDeleted = rebalanceTree23(root, junction_node_value.portugueseWord, &largestNode);

        if (isDeleted == -1) {
            // Caso o reequilíbrio tenha falhado, prepara-se para realizar um movimento de onda.
            PortugueseTree *parentNode, *junction_position_two;
            NodeInfo *inputNode;

            // Encontra o nó pai correspondente ao valor de junção.
            parentNode = findParentIn23Tree(*root, junction_node_value.portugueseWord);

            // Determina o nó de entrada com base na posição na subárvore.
            if (eh_info1(*junction_position, junction_node_value.portugueseWord))
                inputNode = &(junction_position->cent->info1);
            else
                inputNode = &(junction_position->right->info1);

            // Realiza o movimento de onda para tentar balancear a árvore.
            isDeleted = wave_movement(junction_node_value, inputNode, parentNode, root, &junction_position, &junction_position_two, removeNodeFrom23Tree);

            if (isDeleted == -1) {
                // Atualiza os valores e tenta um novo movimento de onda.
                junction_node_value = junction_position_two->info1;
                parentNode = findParentIn23Tree(*root, junction_node_value.portugueseWord);
                isDeleted = wave_movement(junction_node_value, &(junction_position_two->left->info1), parentNode, root, &junction_position_two, &junction_position, deleteFrom23Tree);

                // Reequilibra a árvore novamente após o movimento.
                junction_node_value = getLargestNodeInfo(junction_position);
                largestNode = NULL;
                isDeleted = rebalanceTree23(root, junction_node_value.portugueseWord, &largestNode);
            }
        }

        // Atualiza a raiz da árvore, se necessário.
        if (*root == NULL)
            *root = largestNode;
    }

    return isDeleted; // Retorna o status da remoção.
}


void removeNodeInfo(NodeInfo *nodeInfo) {
    if (nodeInfo != NULL) {
        // Limpa a árvore binária associada às traduções em inglês.
        clear_binary_tree(nodeInfo->englishWord);

        // Libera a memória alocada para a palavra em português.
        free(nodeInfo->portugueseWord);
    }
}

void deallocateTree(PortugueseTree **node) {
    if (*node != NULL) {
        // Desaloca recursivamente a subárvore esquerda.
        deallocateTree(&((*node)->left));

        // Desaloca recursivamente a subárvore central.
        deallocateTree(&((*node)->cent));

        // Se o nó possui duas informações, remove a segunda e desaloca a subárvore direita.
        if ((*node)->nInfos == 2) {
            removeNodeInfo(&((*node)->info2));
            deallocateTree(&((*node)->right));
        }

        // Remove a primeira informação e libera o nó atual.
        removeNodeInfo(&((*node)->info1));
        free(*node);

        // Define o ponteiro para nulo para evitar acessos inválidos.
        *node = NULL;
    }
}

void removeEnglishTranslation(PortugueseTree **rootNode, char *englishWord, int unit, PortugueseTree **parentNode) {
    if (*rootNode != NULL) {
        // Chama recursivamente para a subárvore esquerda.
        removeEnglishTranslation(&(*rootNode)->left, englishWord, unit, parentNode);

        // Verifica e remove traduções associadas à `info1`.
        if ((*rootNode)->info1.englishWord != NULL) {
            int removed = remove_unit_from_tree(&(*rootNode)->info1.englishWord, englishWord, unit);

            // Se todas as traduções foram removidas, tenta remover a palavra em inglês.
            if (removed && (*rootNode)->info1.englishWord == NULL) {
                removeEnglishWord(&(*rootNode)->info1.englishWord, englishWord, unit);

                // Remove o nó da árvore 2-3, se necessário.
                if ((*rootNode)->info1.englishWord == NULL) {
                    remove_node_from23_tree(rootNode, (*rootNode)->info1.portugueseWord);
                }
            }
        }

        // Chama recursivamente para a subárvore central.
        removeEnglishTranslation(&(*rootNode)->cent, englishWord, unit, parentNode);

        // Verifica e remove traduções associadas à `info2`, se existirem.
        if ((*rootNode)->nInfos == 2 && (*rootNode)->info2.englishWord != NULL) {
            int removed = remove_unit_from_tree(&(*rootNode)->info2.englishWord, englishWord, unit);

            if (removed && (*rootNode)->info2.englishWord == NULL) {
                removeEnglishWord(&(*rootNode)->info2.englishWord, englishWord, unit);

                // Remove o nó da árvore 2-3, se necessário.
                if ((*rootNode)->info2.englishWord == NULL) {
                    remove_node_from23_tree(rootNode, (*rootNode)->info2.portugueseWord);
                }
            }
        }

        // Chama recursivamente para a subárvore direita, se houver.
        if ((*rootNode)->nInfos == 2) {
            removeEnglishTranslation(&(*rootNode)->right, englishWord, unit, parentNode);
        }
    }
}


int remove_unit_from_tree(Inglesbin **root, const char *englishWord, int unit) {
    // Inicializa a variável de retorno como 0, indicando que nenhuma unidade foi removida ainda.
    int result = 0;

    // Verifica se o nó atual existe.
    if (*root != NULL) {
        // Compara a palavra inglesa com o nó atual.
        if (strcmp(englishWord, (*root)->englishWord) == 0) {
            // Se for igual, tenta remover a unidade associada à palavra inglesa.
            result = remove_unit(&(*root)->unitList, unit);
        } else if (strcmp(englishWord, (*root)->englishWord) < 0) {
            // Se a palavra for menor, procura na subárvore esquerda.
            result = remove_unit_from_tree(&(*root)->leftChild, englishWord, unit);
        } else {
            // Se a palavra for maior, procura na subárvore direita.
            result = remove_unit_from_tree(&(*root)->rightChild, englishWord, unit);
        }
    }

    // Retorna se a remoção foi realizada ou não.
    return result;
}

void printFormattedWordsByUnit(PortugueseTree *portugueseTree, int unit, int *printedUnit) {
    // Verifica se a árvore existe.
    if (portugueseTree) {
        // Percorre a subárvore esquerda.
        printFormattedWordsByUnit(portugueseTree->left, unit, printedUnit);

        // Verifica se a info1 tem palavras em inglês associadas.
        if (portugueseTree->info1.englishWord != NULL) {
            Inglesbin *englishWordNode = portugueseTree->info1.englishWord;
            // Itera pelas palavras em inglês associadas.
            while (englishWordNode) {
                if (find_unit(englishWordNode->unitList, unit)) {
                    // Se encontrar a unidade, imprime o cabeçalho da unidade apenas uma vez.
                    if (!(*printedUnit)) {
                        printf("%% Unidade %d\n", unit);
                        *printedUnit = 1;
                    }
                    // Imprime a palavra em português e sua tradução.
                    printf("%s: %s;\n", portugueseTree->info1.portugueseWord, englishWordNode->englishWord);
                }
                // Avança para o próximo nó (esquerda ou direita).
                englishWordNode = englishWordNode->leftChild ? englishWordNode->leftChild : englishWordNode->rightChild;
            }
        }

        // Percorre a subárvore central.
        printFormattedWordsByUnit(portugueseTree->cent, unit, printedUnit);

        // Verifica se a info2 tem palavras em inglês associadas (para nós com 2 informações).
        if (portugueseTree->nInfos == 2 && portugueseTree->info2.englishWord != NULL) {
            Inglesbin *englishWordPtr = portugueseTree->info2.englishWord;
            // Itera pelas palavras em inglês associadas.
            while (englishWordPtr) {
                if (find_unit(englishWordPtr->unitList, unit)) {
                    // Imprime o cabeçalho da unidade, se necessário.
                    if (!(*printedUnit)) {
                        printf("%% Unidade %d\n", unit);
                        *printedUnit = 1;
                    }
                    // Imprime a palavra em português e sua tradução.
                    printf("%s: %s;\n", portugueseTree->info2.portugueseWord, englishWordPtr->englishWord);
                }
                // Avança para o próximo nó (esquerda ou direita).
                englishWordPtr = englishWordPtr->leftChild ? englishWordPtr->leftChild : englishWordPtr->rightChild;
            }
        }

        // Percorre a subárvore direita (se existir).
        if (portugueseTree->nInfos == 2) {
            printFormattedWordsByUnit(portugueseTree->right, unit, printedUnit);
        }
    }
}

void removePortugueseWordByUnit(PortugueseTree **rootNode, char *portugueseWord, int nodeLevel) {
    // Procura o nó correspondente à palavra em português.
    PortugueseTree *foundPortugueseNode = FindWord(rootNode, portugueseWord);
    int isFound = 0; // Variável para rastrear se algo foi encontrado.

    if (foundPortugueseNode != NULL) {
        // Verifica se a palavra corresponde à info1 do nó encontrado.
        if (strcmp(foundPortugueseNode->info1.portugueseWord, portugueseWord) == 0) {
            Inglesbin *englishWordPtr = foundPortugueseNode->info1.englishWord;
            while (englishWordPtr) {
                // Verifica se a palavra em inglês está associada ao nível especificado.
                if (find_unit(englishWordPtr->unitList, nodeLevel)) {
                    isFound = 1;
                    // Remove a palavra em inglês associada ao nível.
                    removeEnglishWord(&(foundPortugueseNode->info1.englishWord), englishWordPtr->englishWord, nodeLevel);

                    // Se não houver mais palavras associadas, limpa a info1.
                    if (foundPortugueseNode->info1.englishWord == NULL) {
                        removeNodeInfo(&(foundPortugueseNode->info1));
                        foundPortugueseNode->info1.portugueseWord = NULL; 
                    }
                }
                // Avança para o próximo nó em inglês (esquerda ou direita).
                englishWordPtr = englishWordPtr->leftChild ? englishWordPtr->leftChild : englishWordPtr->rightChild;
            }
        }

        // Verifica se a palavra corresponde à info2 do nó encontrado (se houver).
        if (!isFound && foundPortugueseNode->nInfos == 2 && strcmp(foundPortugueseNode->info2.portugueseWord, portugueseWord) == 0) {
            Inglesbin *ingles = foundPortugueseNode->info2.englishWord;
            while (ingles) {
                // Verifica se a palavra em inglês está associada ao nível especificado.
                if (find_unit(ingles->unitList, nodeLevel)) {
                    isFound = 1;
                    // Remove a palavra em inglês associada ao nível.
                    removeEnglishWord(&(foundPortugueseNode->info2.englishWord), ingles->englishWord, nodeLevel);

                    // Se não houver mais palavras associadas, limpa a info2.
                    if (foundPortugueseNode->info2.englishWord == NULL) {
                        removeNodeInfo(&(foundPortugueseNode->info2));
                        foundPortugueseNode->info2.portugueseWord = NULL; 
                    }
                }
                // Avança para o próximo nó em inglês (esquerda ou direita).
                ingles = ingles->leftChild ? ingles->leftChild : ingles->rightChild;
            }
        }
    }
}


int Delete_portuguese_word_unit(Inglesbin **rootNode, char *portugueseWord, int unit) {
    int isConfirmed = 0; // Inicializa a variável para confirmar se a remoção foi feita.

    if (*rootNode) { // Verifica se o nó atual existe.
        // Tenta deletar a palavra nas subárvores esquerda e direita e atualiza a confirmação.
        isConfirmed = Delete_portuguese_word_unit(&(*rootNode)->leftChild, portugueseWord, unit);
        isConfirmed = Delete_portuguese_word_unit(&(*rootNode)->rightChild, portugueseWord, unit) || isConfirmed;

        // Remove a unidade associada ao nó atual.
        isConfirmed = remove_unit(&(*rootNode)->unitList, unit);

        // Se a lista de unidades estiver vazia após a remoção, remove o nó da árvore.
        if (!(*rootNode)->unitList) {
            isConfirmed = removeEnglishWord(rootNode, (*rootNode)->englishWord, unit);
        }
    }

    return isConfirmed; // Retorna o status de confirmação (1 se algo foi removido, 0 caso contrário).
}

int delete_portuguese_word_in_unit(PortugueseTree *rootNode, char *portugueseWord, int unit, PortugueseTree **topNodePtr) {
    int isConfirmed = 0; // Inicializa a variável para confirmar a remoção.

    if (rootNode) { // Verifica se o nó atual existe.
        // Verifica se a palavra em português corresponde à `info1`.
        if (strcmp(rootNode->info1.portugueseWord, portugueseWord) == 0) {
            // Tenta remover a palavra no nó `info1`.
            isConfirmed = Delete_portuguese_word_unit(&rootNode->info1.englishWord, portugueseWord, unit);

            // Se não houver mais palavras associadas ao `info1`, remove o nó da árvore 2-3.
            if (!rootNode->info1.englishWord) {
                isConfirmed = remove_node_from23_tree(topNodePtr, portugueseWord);
            }
        }
        // Verifica se a palavra em português corresponde à `info2` (caso o nó tenha duas informações).
        else if (rootNode->nInfos == 2 && strcmp(rootNode->info2.portugueseWord, portugueseWord) == 0) {
            // Tenta remover a palavra no nó `info2`.
            isConfirmed = Delete_portuguese_word_unit(&rootNode->info2.englishWord, portugueseWord, unit);

            // Se não houver mais palavras associadas ao `info2`, remove o nó da árvore 2-3.
            if (!rootNode->info2.englishWord) {
                isConfirmed = remove_node_from23_tree(topNodePtr, portugueseWord);
            }
        }
        // Se a palavra em português for menor que `info1`, percorre a subárvore esquerda.
        else if (strcmp(portugueseWord, rootNode->info1.portugueseWord) < 0) {
            isConfirmed = delete_portuguese_word_in_unit(rootNode->left, portugueseWord, unit, topNodePtr);
        }
        // Se o nó tiver apenas uma informação ou a palavra for menor que `info2`, percorre a subárvore central.
        else if (rootNode->nInfos == 1 || strcmp(portugueseWord, rootNode->info2.portugueseWord) < 0) {
            isConfirmed = delete_portuguese_word_in_unit(rootNode->cent, portugueseWord, unit, topNodePtr);
        }
        // Caso contrário, percorre a subárvore direita.
        else {
            isConfirmed = delete_portuguese_word_in_unit(rootNode->right, portugueseWord, unit, topNodePtr);
        }
    }

    return isConfirmed; // Retorna o status de confirmação.
}

int Remove_word_from_portuguese_unit(PortugueseTree **rootNode, char *portugueseWord, int unit) {
    int isConfirmed = 0; // Inicializa a variável para confirmar a remoção.

    // Chama a função para deletar a palavra de uma unidade específica.
    isConfirmed = delete_portuguese_word_in_unit(*rootNode, portugueseWord, unit, rootNode);

    return isConfirmed; // Retorna o status da operação.
}
