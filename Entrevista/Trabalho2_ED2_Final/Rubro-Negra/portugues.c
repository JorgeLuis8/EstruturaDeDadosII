#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingles.h"
#include "portugues.h"
#include "unidade.h"
#define RED 1
#define BLACK 0

// Função para criar e inicializar informações para um nó da árvore
NodeData createInfo(char *portugueseWord, char *englishWord, int unit) {
    NodeData info; // Estrutura para armazenar os dados do nó

    // Aloca memória para a palavra em português e verifica sucesso
    info.portugueseWord = malloc(strlen(portugueseWord) + 1);
    if (info.portugueseWord == NULL) {
        perror("Erro ao alocar memória para a palavra em português."); // Mensagem de erro em caso de falha
        exit(EXIT_FAILURE); // Encerra o programa em caso de falha
    }
    // Copia a palavra em português para a estrutura
    strcpy(info.portugueseWord, portugueseWord);

    // Inicializa o ponteiro para o nó da árvore de palavras em inglês como NULL
    info.englishWordNode = NULL;

    // Insere a palavra em inglês e a unidade na subárvore binária
    info.englishWordNode = insertEnglishWord(info.englishWordNode, englishWord, unit);

    // Retorna a estrutura preenchida
    return info;
}

// Função para inserir uma palavra em português e associar traduções
int insertPortugueseWord(RedBlackTreePT **redBlackTree, char *portugueseWord, char *englishWord, int unit) {
    int isInserted = 0; // Flag para indicar se a palavra foi inserida
    RedBlackTreePT *nonExistentNode = NULL; // Ponteiro para um nó que será buscado na árvore

    // Procura a palavra em português na árvore
    nonExistentNode = SearchWordInTree(redBlackTree, portugueseWord);

    if (nonExistentNode != NULL) {
        // Se a palavra em português já existir, adiciona a tradução em inglês
        addEnglishTranslation(nonExistentNode, englishWord, unit);
        isInserted = 1; // Marca que a palavra foi tratada
    } else {
        // Caso a palavra em português não exista, cria um novo nó com suas informações
        NodeData newNodeData = createInfo(portugueseWord, englishWord, unit);

        // Insere o novo nó na árvore vermelho-preta e verifica sucesso
        if (insertRedBlackTree(redBlackTree, &newNodeData)) {
            isInserted = 1; // Marca que a palavra foi inserida
        }
    }

    // Retorna se a palavra foi inserida ou tratada com sucesso
    return isInserted;
}

// Função para criar um novo nó na árvore vermelho-preta
RedBlackTreePT *createNode(NodeData *nodeData)
{
    // Aloca memória para o novo nó da árvore
    RedBlackTreePT *newRedBlackTree = (RedBlackTreePT *)malloc(sizeof(RedBlackTreePT));
    // Copia os dados do nó para o novo nó
    newRedBlackTree->info = *nodeData;
    // Define a cor do novo nó como vermelho (1)
    newRedBlackTree->color = 1; // Vermelho por padrão em árvores vermelho-pretas
    // Inicializa os filhos esquerdo e direito como NULL
    newRedBlackTree->left = NULL;
    newRedBlackTree->right = NULL;

    // Retorna o ponteiro para o novo nó criado
    return newRedBlackTree;
}

// Função para obter a cor de um nó na árvore
int getNodeColor(RedBlackTreePT *rootNode)
{
    int color;

    // Se o nó for NULL, sua cor é preta (árvore vermelho-preta considera NULL como preto)
    if (rootNode == NULL)
        color = BLACK;
    else
        // Caso contrário, retorna a cor do nó
        color = rootNode->color;

    return color;
}

// Função para alternar as cores de um nó e seus filhos
void switch_node_color(RedBlackTreePT **rootNode)
{
    // Alterna a cor do nó raiz
    (*rootNode)->color = !(*rootNode)->color;

    // Alterna a cor do filho esquerdo, se existir
    if ((*rootNode)->left)
        (*rootNode)->left->color = !(*rootNode)->left->color;

    // Alterna a cor do filho direito, se existir
    if ((*rootNode)->right)
        (*rootNode)->right->color = !(*rootNode)->right->color;
}

// Função para realizar uma rotação à direita
void rotate_right(RedBlackTreePT **rootNode)
{
    // Armazena o filho esquerdo do nó raiz em uma variável auxiliar
    RedBlackTreePT *aux = (*rootNode)->left;

    // O filho direito do auxiliar se torna o filho esquerdo do nó raiz
    (*rootNode)->left = aux->right;

    // O nó raiz se torna o filho direito do auxiliar
    aux->right = *rootNode;

    // A cor do auxiliar herda a cor do nó raiz
    aux->color = (*rootNode)->color;

    // O nó raiz é definido como vermelho
    (*rootNode)->color = RED;

    // O nó auxiliar se torna a nova raiz
    (*rootNode) = aux;
}

// Função para realizar uma rotação à esquerda
void left_rotate(RedBlackTreePT **treeRoot)
{
    // Armazena o filho direito do nó raiz em uma variável auxiliar
    RedBlackTreePT *aux = (*treeRoot)->right;

    // O filho esquerdo do auxiliar se torna o filho direito do nó raiz
    (*treeRoot)->right = aux->left;

    // O nó raiz se torna o filho esquerdo do auxiliar
    aux->left = *treeRoot;

    // A cor do auxiliar herda a cor do nó raiz
    aux->color = (*treeRoot)->color;

    // O nó raiz é definido como vermelho
    (*treeRoot)->color = RED;

    // O nó auxiliar se torna a nova raiz
    (*treeRoot) = aux;
}

// Função para balancear a árvore vermelho-preta após inserções
void balanceTree(RedBlackTreePT **treeRoot)
{
    if (*treeRoot) // Verifica se a raiz da árvore não é NULL
    {
        // Caso 1: O filho direito é vermelho e o filho esquerdo é preto
        if (getNodeColor((*treeRoot)->right) == RED && getNodeColor((*treeRoot)->left) == BLACK)
            left_rotate(treeRoot); // Realiza uma rotação à esquerda

        // Caso 2: O filho esquerdo e o filho do filho esquerdo são vermelhos
        if (getNodeColor((*treeRoot)->left) == RED && getNodeColor((*treeRoot)->left->left) == RED)
            rotate_right(treeRoot); // Realiza uma rotação à direita

        // Caso 3: Ambos os filhos (esquerdo e direito) são vermelhos
        if (getNodeColor((*treeRoot)->left) == RED && getNodeColor((*treeRoot)->right) == RED)
            switch_node_color(treeRoot); // Alterna a cor do nó raiz e de seus filhos
    }
}


// Função para inserir um nó na árvore vermelho-preta
int insertRedBlackNode(RedBlackTreePT **rootNode, NodeData *nodeData)
{
    int isInserted = 1; // Flag para indicar sucesso da inserção

    // Caso base: Se o nó atual é NULL, cria um novo nó
    if (*rootNode == NULL)
    {
        *rootNode = createNode(nodeData); // Cria um novo nó com os dados fornecidos
    }
    else
    {
        // Se a palavra em português no novo nó for menor, insere no lado esquerdo
        if (strcmp(nodeData->portugueseWord, (*rootNode)->info.portugueseWord) < 0)
        {
            isInserted = insertRedBlackNode(&(*rootNode)->left, nodeData);
        }
        // Caso contrário, insere no lado direito
        else
        {
            isInserted = insertRedBlackNode(&(*rootNode)->right, nodeData);
        }
        // Após a inserção, reequilibra a árvore para manter as propriedades vermelho-preta
        balanceTree(&(*rootNode));
    }

    return isInserted; // Retorna o status da inserção
}

// Função para inserir um nó na árvore vermelho-preta e garantir que a raiz seja preta
int insertRedBlackTree(RedBlackTreePT **rootNode, NodeData *nodeData)
{
    // Insere o nó usando a função auxiliar
    int isInserted = insertRedBlackNode(rootNode, nodeData);

    // Após a inserção, garante que a raiz seja preta
    if (isInserted)
    {
        (*rootNode)->color = BLACK;
    }

    return isInserted; // Retorna o status da inserção
}

// Função para ajustar a árvore se o lado esquerdo for vermelho e o lado direito for preto
void shiftLeftRed(RedBlackTreePT **rootNode)
{
    // Alterna as cores do nó e de seus filhos
    switch_node_color(rootNode);

    // Verifica se o filho direito possui um filho esquerdo vermelho
    if ((*rootNode)->right && getNodeColor((*rootNode)->right->left) == RED)
    {
        // Rotaciona o filho direito para a direita
        rotate_right(&(*rootNode)->right);
        // Rotaciona o nó atual para a esquerda
        left_rotate(rootNode);
        // Alterna novamente as cores para corrigir o balanceamento
        switch_node_color(rootNode);
    }
}

// Função para ajustar a árvore caso o lado direito seja vermelho e o lado esquerdo seja preto
void rotateRedRight(RedBlackTreePT **rootNode)
{
    // Alterna as cores do nó e de seus filhos
    switch_node_color(rootNode);

    // Verifica se o filho esquerdo possui um filho esquerdo vermelho
    if ((*rootNode)->left && getNodeColor((*rootNode)->left->left) == RED)
    {
        // Rotaciona o nó atual para a direita
        rotate_right(rootNode);
        // Alterna novamente as cores para corrigir o balanceamento
        switch_node_color(rootNode);
    }
}

// Função para remover o nó mínimo (mais à esquerda) de uma subárvore
void removeMinimum(RedBlackTreePT **rootNode)
{
    // Caso base: Se não houver filho à esquerda, libera o nó atual
    if (!((*rootNode)->left))
    {
        free(*rootNode); // Libera a memória do nó
        *rootNode = NULL; // Define o ponteiro como NULL
    }
    else
    {
        // Se o filho esquerdo e o neto esquerdo forem pretos, ajusta o balanceamento
        if (getNodeColor((*rootNode)->left) == BLACK && getNodeColor((*rootNode)->left->left) == BLACK)
        {
            shiftLeftRed(rootNode); // Ajusta as cores e balanceia
        }

        // Continua recursivamente para remover o mínimo na subárvore esquerda
        removeMinimum(&(*rootNode)->left);

        // Reequilibra a árvore após a remoção
        balanceTree(rootNode);
    }
}


// Função para encontrar o nó com o menor valor na árvore vermelho-preta
RedBlackTreePT *findMinimum(RedBlackTreePT *rootNode)
{
    RedBlackTreePT *minimumNode; // Ponteiro para armazenar o nó mínimo
    minimumNode = rootNode; // Inicializa o mínimo como o nó atual

    // Procura recursivamente pelo nó mais à esquerda (menor valor)
    if (rootNode)
        if (rootNode->left)
            minimumNode = findMinimum(rootNode->left);

    // Retorna o nó com o menor valor encontrado
    return minimumNode;
}

// Função para remover um nó da árvore vermelho-preta
int removeNodeFromRBTree(RedBlackTreePT **treeRoot, char *nodeValue)
{
    int isExist = 0; // Flag para indicar se o nó foi encontrado e removido

    if (*treeRoot) // Verifica se a árvore não está vazia
    {
        // Se o valor procurado é menor que o valor no nó atual, busca no lado esquerdo
        if (strcmp(nodeValue, (*treeRoot)->info.portugueseWord) < 0)
        {
            // Caso o filho esquerdo e seu neto esquerdo sejam pretos, ajusta o balanceamento
            if ((*treeRoot)->left && getNodeColor((*treeRoot)->left) == BLACK && getNodeColor((*treeRoot)->left->left) == BLACK)
                shiftLeftRed(treeRoot);

            // Continua a busca no lado esquerdo
            isExist = removeNodeFromRBTree(&(*treeRoot)->left, nodeValue);
        }
        else
        {
            // Se o filho esquerdo for vermelho, realiza uma rotação à direita
            if (getNodeColor((*treeRoot)->left) == RED)
                rotate_right(treeRoot);

            // Se o nó atual contém o valor procurado e não tem filho à direita, remove o nó
            if (strcmp(nodeValue, (*treeRoot)->info.portugueseWord) == 0 && (*treeRoot)->right == NULL)
            {
                free(*treeRoot); // Libera o nó
                *treeRoot = NULL; // Define o ponteiro como NULL
                isExist = 1; // Indica que o nó foi removido
            }
            else
            {
                // Caso o filho direito e seu neto esquerdo sejam pretos, ajusta o balanceamento
                if ((*treeRoot)->right && getNodeColor((*treeRoot)->right) == BLACK && getNodeColor((*treeRoot)->right->left) == BLACK)
                    rotateRedRight(treeRoot);

                // Se o nó atual contém o valor procurado, substitui pelo sucessor
                if (strcmp(nodeValue, (*treeRoot)->info.portugueseWord) == 0)
                {
                    RedBlackTreePT *aux = findMinimum((*treeRoot)->right); // Encontra o sucessor
                    (*treeRoot)->info = aux->info; // Substitui os dados do nó pelo sucessor
                    removeMinimum(&(*treeRoot)->right); // Remove o sucessor

                    isExist = 1; // Indica que o nó foi removido
                }
                else
                {
                    // Continua a busca no lado direito
                    isExist = removeNodeFromRBTree(&(*treeRoot)->right, nodeValue);
                }
            }
        }
    }

    // Reequilibra a árvore após a remoção
    balanceTree(treeRoot);
    return isExist; // Retorna o status da remoção
}

// Função para remover um nó da árvore e garantir que a raiz seja preta
int removeRBTreeNode(RedBlackTreePT **rootNode, char *nodeValue)
{
    // Chama a função auxiliar para remover o nó
    int isNodeRemoved = removeNodeFromRBTree(rootNode, nodeValue);

    // Garante que a raiz seja preta após a remoção
    if (isNodeRemoved)
    {
        (*rootNode)->color = BLACK;
    }

    return isNodeRemoved; // Retorna o status da remoção
}

// Função para buscar uma palavra em português na árvore vermelho-preta
RedBlackTreePT *SearchWordInTree(RedBlackTreePT **redBlackTree, char *portugueseWord)
{
    RedBlackTreePT *currentNode = NULL; // Ponteiro para armazenar o nó encontrado

    if (*redBlackTree != NULL) // Verifica se a árvore não está vazia
    {
        // Se a palavra no nó atual é igual à palavra procurada
        if (strcmp(portugueseWord, (*redBlackTree)->info.portugueseWord) == 0)
        {
            currentNode = *redBlackTree; // O nó atual é o resultado da busca
        }
        // Se a palavra procurada é menor, busca no lado esquerdo
        else if (strcmp(portugueseWord, (*redBlackTree)->info.portugueseWord) < 0)
        {
            currentNode = SearchWordInTree(&(*redBlackTree)->left, portugueseWord);
        }
        // Se a palavra procurada é maior, busca no lado direito
        else
        {
            currentNode = SearchWordInTree(&(*redBlackTree)->right, portugueseWord);
        }
    }

    return currentNode; // Retorna o nó encontrado ou NULL se não existir
}


// Função para imprimir palavras associadas a uma unidade específica na árvore vermelho-preta
void printWordsByUnit(RedBlackTreePT *redBlackTree, int unit) {
    if (redBlackTree) { // Verifica se a árvore não é nula
        // Percorre recursivamente o lado esquerdo da árvore
        printWordsByUnit(redBlackTree->left, unit);

        // Obtém o nó que armazena as traduções em inglês
        BinaryTreeNode *englishWordNode = redBlackTree->info.englishWordNode;

        // Percorre os nós binários contendo traduções em inglês
        while (englishWordNode != NULL) {
            Unit *currentUnit = englishWordNode->unitValues; // Obtém a lista de unidades associadas
            int foundUnit = 0; // Flag para verificar se a unidade foi encontrada

            // Percorre as unidades associadas ao nó atual
            while (currentUnit != NULL && !foundUnit) {
                if (currentUnit->unitValue == unit) { // Verifica se a unidade corresponde à desejada
                    printf("%s: %s;\n", redBlackTree->info.portugueseWord, englishWordNode->englishWord);
                    foundUnit = 1; // Marca que a unidade foi encontrada
                }
                currentUnit = currentUnit->nextNode; // Move para a próxima unidade
            }

            // Navega para os próximos nós binários
            if (englishWordNode->left != NULL) {
                englishWordNode = englishWordNode->left; // Vai para o filho à esquerda
            } else if (englishWordNode->right != NULL) {
                englishWordNode = englishWordNode->right; // Vai para o filho à direita
            } else {
                englishWordNode = NULL; // Não há mais nós para visitar
            }
        }

        // Percorre recursivamente o lado direito da árvore
        printWordsByUnit(redBlackTree->right, unit);
    }
}

// Função para imprimir traduções de palavras em inglês associadas a uma unidade específica
void printTranslations(BinaryTreeNode *currentNode, int unit, char *portugueseWord) {
    if (currentNode) { // Verifica se o nó atual não é nulo
        Unit *currentUnit = currentNode->unitValues; // Obtém a lista de unidades do nó atual
        int foundUnit = 0; // Flag para verificar se a unidade foi encontrada

        // Percorre a lista de unidades
        while (currentUnit != NULL && !foundUnit) {
            if (currentUnit->unitValue == unit) { // Verifica se a unidade corresponde à desejada
                foundUnit = 1; // Marca que a unidade foi encontrada
            }
            currentUnit = currentUnit->nextNode; // Move para a próxima unidade
        }

        // Se a unidade foi encontrada, imprime as palavras em português e inglês
        if (foundUnit) {
            printf("Palavra em Portugues: %s\n", portugueseWord);
            printf("Palavra em ingles: %s\n", currentNode->englishWord);
        }

        // Percorre recursivamente o lado esquerdo e direito da subárvore
        printTranslations(currentNode->left, unit, portugueseWord);
        printTranslations(currentNode->right, unit, portugueseWord);
    }
}

// Função para exibir traduções de uma palavra em português
void showPortugueseTranslation(RedBlackTreePT **rootNode, char *portugueseWord) {
    if (*rootNode != NULL) { // Verifica se a árvore não está vazia
        // Busca a palavra em português na árvore
        RedBlackTreePT *resultado = SearchWordInTree(rootNode, portugueseWord);

        if (resultado != NULL) { // Se a palavra foi encontrada
            printf("Traducoes em ingles para a palavra '%s':\n", portugueseWord);

            // Obtém o nó que contém as traduções em inglês
            BinaryTreeNode *node = resultado->info.englishWordNode;

            if (node == NULL) {
                printf("Nenhuma traducao encontrada.\n"); // Nenhuma tradução disponível
            } else {
                printBinaryTree(node); // Imprime as traduções em inglês
            }
        } else {
            printf("Nenhuma traducao encontrada para '%s'.\n", portugueseWord);
        }
    } else {
        printf("Arvore vazia.\n"); // A árvore está vazia
    }
}


// Função para exibir a estrutura da árvore vermelho-preta
void showRedBlackTree(RedBlackTreePT *rootNode)
{
    if (rootNode) // Verifica se o nó atual não é nulo
    {
        // Percorre recursivamente o lado esquerdo da árvore
        showRedBlackTree(rootNode->left);

        // Exibe a cor do nó (vermelho ou preto)
        printf("Cor - %d\n", rootNode->color);

        // Exibe a palavra em português armazenada no nó
        printf("Palavra em Português - %s\n", rootNode->info.portugueseWord);

        // Exibe a subárvore binária associada (traduções em inglês)
        printBinaryTree(rootNode->info.englishWordNode);

        // Adiciona uma linha em branco para separar os nós na saída
        printf("\n");

        // Percorre recursivamente o lado direito da árvore
        showRedBlackTree(rootNode->right);
    }
}

// Função para buscar uma palavra em inglês e sua unidade na árvore vermelho-preta
RedBlackTreePT *SearchEnglishWordInRBTree(RedBlackTreePT *rootNode, char *englishWord, int unit)
{
    RedBlackTreePT *rbTreeOutput = NULL; // Variável para armazenar o nó encontrado

    if (rootNode != NULL) // Verifica se a árvore não está vazia
    {
        BinaryTreeNode *currentNode = rootNode->info.englishWordNode; // Obtém a subárvore binária do nó atual
        int found = 0; // Flag para indicar se a palavra foi encontrada

        // Percorre a subárvore binária (traduções em inglês)
        while (currentNode != NULL && !found)
        {
            Unit *currentUnit = currentNode->unitValues; // Obtém a lista de unidades associadas
            int unitFound = 0; // Flag para verificar se a unidade foi encontrada

            // Percorre as unidades associadas à palavra
            while (currentUnit != NULL && !unitFound)
            {
                if (currentUnit->unitValue == unit) // Verifica se a unidade corresponde à desejada
                {
                    unitFound = 1; // Marca que a unidade foi encontrada
                }
                currentUnit = currentUnit->nextNode; // Avança para a próxima unidade
            }

            // Se a palavra e a unidade foram encontradas, salva o nó atual
            if (unitFound && strcmp(currentNode->englishWord, englishWord) == 0)
            {
                rbTreeOutput = rootNode;
                found = 1; // Marca que a busca foi concluída
            }
            // Se a palavra procurada é menor, continua à esquerda
            else if (strcmp(englishWord, currentNode->englishWord) < 0)
            {
                currentNode = currentNode->left;
            }
            // Se a palavra procurada é maior, continua à direita
            else
            {
                currentNode = currentNode->right;
            }
        }

        // Se a palavra não foi encontrada na subárvore binária, busca nos filhos da árvore vermelho-preta
        if (!found)
        {
            // Busca no lado esquerdo da árvore
            RedBlackTreePT *leftResult = SearchEnglishWordInRBTree(rootNode->left, englishWord, unit);
            if (leftResult != NULL)
            {
                rbTreeOutput = leftResult;
            }
            else
            {
                // Se não encontrou no lado esquerdo, busca no lado direito
                rbTreeOutput = SearchEnglishWordInRBTree(rootNode->right, englishWord, unit);
            }
        }
    }

    // Retorna o nó da árvore vermelho-preta que contém a palavra e unidade procuradas
    return rbTreeOutput;
}

// Função para remover uma palavra e suas traduções da árvore vermelho-preta
void removeWordFromTree(RedBlackTreePT **node, char *wordToRemove, int *totalRemovido, RedBlackTreePT **rootNode, int unit)
{
    if (*node != NULL) // Verifica se o nó atual não é nulo
    {
        // Percorre recursivamente o lado esquerdo da árvore
        removeWordFromTree(&(*node)->left, wordToRemove, totalRemovido, rootNode, unit);

        BinaryTreeNode *binaryRoot = (*node)->info.englishWordNode; // Obtém a subárvore binária do nó atual
        // Remove a palavra e a unidade da subárvore binária
        int removed = removeEnglishWord(&binaryRoot, wordToRemove, unit);
        if (removed) // Verifica se a palavra foi removida
        {
            (*totalRemovido)++; // Incrementa o contador de palavras removidas
        }

        // Se a subárvore binária está vazia após a remoção, remove o nó da árvore vermelho-preta
        if (binaryRoot == NULL)
        {
            removeRBTreeNode(rootNode, (*node)->info.portugueseWord);
        }
        else
        {
            // Atualiza a subárvore binária do nó atual
            (*node)->info.englishWordNode = binaryRoot;
        }

        // Percorre recursivamente o lado direito da árvore
        removeWordFromTree(&(*node)->right, wordToRemove, totalRemovido, rootNode, unit);
    }
}


// Função para remover uma palavra associada a uma unidade na árvore vermelho-preta
void removeWordByUnit(RedBlackTreePT **node, char *wordToRemove, int unit, int *removidos, RedBlackTreePT **rootNode) {
    if (node != NULL && *node != NULL && wordToRemove != NULL) { // Verifica se os ponteiros e a palavra são válidos
        // Percorre recursivamente o lado esquerdo da árvore
        removeWordByUnit(&(*node)->left, wordToRemove, unit, removidos, rootNode);

        // Obtém a raiz da subárvore binária associada ao nó atual
        BinaryTreeNode *binaryRoot = (*node)->info.englishWordNode;
        if (binaryRoot != NULL) { // Verifica se a subárvore binária não está vazia
            BinaryTreeNode *currentNode = binaryRoot;

            // Percorre a subárvore binária de palavras em inglês
            while (currentNode != NULL) {
                if (strcmp(currentNode->englishWord, wordToRemove) == 0) { // Verifica se a palavra corresponde à desejada
                    // Remove a unidade específica associada à palavra
                    Unit *novaLista = remove_unit(currentNode->unitValues, unit);
                    currentNode->unitValues = novaLista;

                    // Se a lista de unidades ficar vazia, remove o nó da subárvore binária
                    if (currentNode->unitValues == NULL) {
                        *removidos += removeEnglishWord(&binaryRoot, wordToRemove, unit);
                    }
                }

                // Navega para os filhos da subárvore binária com base na ordem alfabética
                if (strcmp(wordToRemove, currentNode->englishWord) < 0) {
                    currentNode = currentNode->left;
                } else {
                    currentNode = currentNode->right;
                }
            }

            // Atualiza a subárvore binária no nó da árvore vermelho-preta
            (*node)->info.englishWordNode = binaryRoot;

            // Se a subárvore binária ficar vazia, remove o nó da árvore vermelho-preta
            if (binaryRoot == NULL) {
                removeRBTreeNode(rootNode, (*node)->info.portugueseWord);
                return; // Retorna para evitar continuar a busca no lado direito
            }
        }

        // Percorre recursivamente o lado direito da árvore
        removeWordByUnit(&(*node)->right, wordToRemove, unit, removidos, rootNode);
    }
}

// Função para exibir palavras em português específicas na árvore vermelho-preta
void showPortugueseWordInRedBlackTree(RedBlackTreePT *rootNode, char *portugueseWord) {
    if (rootNode) { // Verifica se o nó atual não é nulo
        // Percorre recursivamente o lado esquerdo da árvore
        showPortugueseWordInRedBlackTree(rootNode->left, portugueseWord);

        // Verifica se o nó atual contém a palavra em português procurada
        if (strcmp(rootNode->info.portugueseWord, portugueseWord) == 0) {
            // Exibe a subárvore binária associada ao nó
            show_binary_tree(rootNode->info.englishWordNode);
        }

        // Percorre recursivamente o lado direito da árvore
        showPortugueseWordInRedBlackTree(rootNode->right, portugueseWord);
    }
}

// Função para remover uma palavra em português e suas traduções associadas a uma unidade
void deleteWordFromTreeByUnit(RedBlackTreePT **redBlackTreeRoot, char *portugueseWord, int unit) {
    int error = 0; // Flag para verificar erros na operação

    // Verifica se os ponteiros ou a palavra são inválidos
    if (redBlackTreeRoot == NULL || *redBlackTreeRoot == NULL || portugueseWord == NULL) {
        printf("Erro: Entrada invalida ou arvore vazia.\n");
        error = 1;
    }

    RedBlackTreePT *noRBT = NULL;
    if (!error) { // Se não houve erro, procura a palavra em português na árvore
        noRBT = SearchWordInTree(redBlackTreeRoot, portugueseWord);
        if (noRBT == NULL) { // Se a palavra não for encontrada
            printf("Palavra '%s' nao encontrada na arvore rubro-negra.\n", portugueseWord);
            error = 1;
        }
    }

    if (!error && noRBT != NULL) { // Se a palavra foi encontrada
        BinaryTreeNode *raizBST = noRBT->info.englishWordNode; // Obtém a subárvore binária associada
        if (raizBST != NULL) { // Verifica se há traduções associadas
            BinaryTreeNode *currentNode = raizBST;
            BinaryTreeNode *nextNode = NULL;

            // Percorre os nós da subárvore binária
            while (currentNode != NULL) {
                nextNode = (currentNode->left != NULL) ? currentNode->left : currentNode->right;

                // Remove a unidade específica associada à palavra em inglês
                Unit *novaLista = remove_unit(currentNode->unitValues, unit);
                currentNode->unitValues = novaLista;

                // Se a lista de unidades ficar vazia, remove o nó
                if (currentNode->unitValues == NULL) {
                    removeEnglishWord(&raizBST, currentNode->englishWord, unit);
                }

                currentNode = nextNode; // Avança para o próximo nó
            }

            // Atualiza a subárvore binária no nó da árvore vermelho-preta
            noRBT->info.englishWordNode = raizBST;

            // Se a subárvore binária ficar vazia, remove o nó da árvore vermelho-preta
            if (raizBST == NULL) {
                removeRBTreeNode(redBlackTreeRoot, portugueseWord);
            }
        } else {
            printf("Nao ha palavras em ingles associadas ao no '%s'.\n", portugueseWord);
        }
    }

    // Exibe mensagens de erro ou sucesso
    if (error) {
        printf("Operacao nao concluida devido a erros.\n");
    } else {
        printf("Operacao concluida com sucesso.\n");
    }
}
