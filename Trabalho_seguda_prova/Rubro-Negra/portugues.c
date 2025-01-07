#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingles.h"
#include "portugues.h"
#include "unidade.h"
#define RED 1
#define BLACK 0

NodeData createInfo(char *portugueseWord, char *englishWord, int unit) {
    NodeData info;

  
    info.portugueseWord = malloc(strlen(portugueseWord) + 1);
    if (info.portugueseWord == NULL) {
        perror("Erro ao alocar memória para a palavra em português.");
        exit(EXIT_FAILURE);
    }
    strcpy(info.portugueseWord, portugueseWord);


    info.englishWordNode = NULL;

   
    info.englishWordNode = insertEnglishWord(info.englishWordNode, englishWord, unit);

    return info;
}

int insertPortugueseWord(RedBlackTreePT **redBlackTree, char *portugueseWord, char *englishWord, int unit) {
    int isInserted = 0; 
    RedBlackTreePT *nonExistentNode = NULL;

    nonExistentNode = SearchWordInTree(redBlackTree, portugueseWord);

    if (nonExistentNode != NULL) {
        addEnglishTranslation(nonExistentNode, englishWord, unit);
        isInserted = 1;
    } else {
        NodeData newNodeData = createInfo(portugueseWord, englishWord, unit);
        if (insertRedBlackTree(redBlackTree, &newNodeData)) {
            isInserted = 1;
        }
    }

    return isInserted; 
}

RedBlackTreePT *createNode(NodeData *nodeData)
{
    RedBlackTreePT *newRedBlackTree = (RedBlackTreePT *)malloc(sizeof(RedBlackTreePT));
    newRedBlackTree->info = *nodeData;
    newRedBlackTree->color = 1;
    newRedBlackTree->left = NULL;
    newRedBlackTree->right = NULL;
    return newRedBlackTree;
}
int getNodeColor(RedBlackTreePT *rootNode)
{
    int color;

    if (rootNode == NULL)
        color = BLACK;
    else
        color = rootNode->color;

    return color;
}

void switch_node_color(RedBlackTreePT **rootNode)
{
    (*rootNode)->color = !(*rootNode)->color;
    if ((*rootNode)->left)
        (*rootNode)->left->color = !(*rootNode)->left->color;
    if ((*rootNode)->right)
        (*rootNode)->right->color = !(*rootNode)->right->color;
}

void rotate_right(RedBlackTreePT **rootNode)
{
    RedBlackTreePT *aux = (*rootNode)->left;
    (*rootNode)->left = aux->right;
    aux->right = *rootNode;
    aux->color = (*rootNode)->color;
    (*rootNode)->color = RED;
    (*rootNode) = aux;
}

void left_rotate(RedBlackTreePT **treeRoot)
{
    RedBlackTreePT *aux = (*treeRoot)->right;
    (*treeRoot)->right = aux->left;
    aux->left = *treeRoot;
    aux->color = (*treeRoot)->color;
    (*treeRoot)->color = RED;
    (*treeRoot) = aux;
}

void balanceTree(RedBlackTreePT **treeRoot)
{
    if (*treeRoot)
    {
        if (getNodeColor((*treeRoot)->right) == RED && getNodeColor((*treeRoot)->left) == BLACK)
            left_rotate(treeRoot);
        if (getNodeColor((*treeRoot)->left) == RED && getNodeColor((*treeRoot)->left->left) == RED)
            rotate_right(treeRoot);
        if (getNodeColor((*treeRoot)->left) == RED && getNodeColor((*treeRoot)->right) == RED)
            switch_node_color(treeRoot);
    }
}

int insertRedBlackNode(RedBlackTreePT **rootNode, NodeData *nodeData)
{

    int isInserted = 1;
    if (*rootNode == NULL)
    {
        *rootNode = createNode(nodeData);
    }
    else
    {
        if (strcmp(nodeData->portugueseWord, (*rootNode)->info.portugueseWord) < 0)
        {
            isInserted = insertRedBlackNode(&(*rootNode)->left, nodeData);
        }
        else
        {
            isInserted = insertRedBlackNode(&(*rootNode)->right, nodeData);
        }
        balanceTree(&(*rootNode));
    }

    return isInserted;
}

int insertRedBlackTree(RedBlackTreePT **rootNode, NodeData *nodeData)
{
    int isInserted = insertRedBlackNode(rootNode, nodeData);
    if (isInserted)
    {
        (*rootNode)->color = BLACK;
    }
    return isInserted;
}

void shiftLeftRed(RedBlackTreePT **rootNode)
{
    switch_node_color(rootNode);

    if ((*rootNode)->right && getNodeColor((*rootNode)->right->left) == RED)
    {
        rotate_right(&(*rootNode)->right);
        left_rotate((rootNode));
        switch_node_color(rootNode);
    }
}

void rotateRedRight(RedBlackTreePT **rootNode)
{
    switch_node_color(rootNode);

    if ((*rootNode)->left && getNodeColor((*rootNode)->left->left) == RED)
    {
        rotate_right(rootNode);
        switch_node_color(rootNode);
    }
}

void removeMinimum(RedBlackTreePT **rootNode)
{
    if (!((*rootNode)->left))
    {
        free(*rootNode);
        *rootNode = NULL;
    }
    else
    {
        if (getNodeColor((*rootNode)->left) == BLACK && getNodeColor((*rootNode)->left->left) == BLACK)
            shiftLeftRed(rootNode);

        removeMinimum(&(*rootNode)->left);
        balanceTree(rootNode);
    }
}

RedBlackTreePT *findMinimum(RedBlackTreePT *rootNode)
{
    RedBlackTreePT *minimumNode;
    minimumNode = rootNode;

    if (rootNode)
        if (rootNode->left)
            minimumNode = findMinimum(rootNode->left);

    return minimumNode;
}

int removeNodeFromRBTree(RedBlackTreePT **treeRoot, char *nodeValue)
{
    int isExist = 0;

    if (*treeRoot)
    {
        if (strcmp(nodeValue, (*treeRoot)->info.portugueseWord) < 0)
        {
            if ((*treeRoot)->left && getNodeColor((*treeRoot)->left) == BLACK && getNodeColor((*treeRoot)->left->left) == BLACK)
                shiftLeftRed(treeRoot);

            isExist = removeNodeFromRBTree(&(*treeRoot)->left, nodeValue);
        }
        else
        {
            if (getNodeColor((*treeRoot)->left) == RED)
                rotate_right(treeRoot);

            if (strcmp(nodeValue, (*treeRoot)->info.portugueseWord) == 0 && (*treeRoot)->right == NULL)
            {
                free(*treeRoot);
                *treeRoot = NULL;

                isExist = 1;
            }else{
                if ((*treeRoot)->right && getNodeColor((*treeRoot)->right) == BLACK && getNodeColor((*treeRoot)->right->left) == BLACK)
                rotateRedRight(treeRoot);

                if (strcmp(nodeValue, (*treeRoot)->info.portugueseWord) == 0)
                {
                    RedBlackTreePT *aux;
                    aux = findMinimum((*treeRoot)->right);
                    (*treeRoot)->info = aux->info;
                    removeMinimum(&(*treeRoot)->right);

                    isExist = 1;
                }
                else
                {
                    isExist = removeNodeFromRBTree(&(*treeRoot)->right, nodeValue);
                }
            }
        }
    }
    balanceTree(treeRoot);
    return isExist;
}

int removeRBTreeNode(RedBlackTreePT **rootNode, char *nodeValue)
{
    int isNodeRemoved = removeNodeFromRBTree(rootNode, nodeValue);
    if (isNodeRemoved)
    {
        (*rootNode)->color = BLACK;
    }
    return isNodeRemoved;
}


RedBlackTreePT *SearchWordInTree(RedBlackTreePT **redBlackTree, char *portugueseWord) {
    RedBlackTreePT *currentNode = NULL;

    if (*redBlackTree != NULL) {

        if (strcmp(portugueseWord, (*redBlackTree)->info.portugueseWord) == 0) {
            printf("[DEBUG] Palavra encontrada: '%s'\n", (*redBlackTree)->info.portugueseWord);
            currentNode = *redBlackTree;
        } else if (strcmp(portugueseWord, (*redBlackTree)->info.portugueseWord) < 0) {
 
            currentNode = SearchWordInTree(&(*redBlackTree)->left, portugueseWord);
        } else {

            currentNode = SearchWordInTree(&(*redBlackTree)->right, portugueseWord);
        }
    } else {

    }

    return currentNode;
}


void printWordsByUnit(RedBlackTreePT *redBlackTree, int unit) {
    if (redBlackTree) {
      
        printWordsByUnit(redBlackTree->left, unit);

  
        BinaryTreeNode *englishWordNode = redBlackTree->info.englishWordNode;

   
        while (englishWordNode != NULL) {
            Unit *currentUnit = englishWordNode->unitValues;

        
            int foundUnit = 0;
            while (currentUnit != NULL && !foundUnit) {
                if (currentUnit->unitValue == unit) {
                    printf("%s: %s;\n", redBlackTree->info.portugueseWord, englishWordNode->englishWord);
                    foundUnit = 1; 
                }
                currentUnit = currentUnit->nextNode;
            }


            if (englishWordNode->left != NULL) {
                englishWordNode = englishWordNode->left;
            } else if (englishWordNode->right != NULL) {
                englishWordNode = englishWordNode->right;
            } else {
                englishWordNode = NULL;
            }
        }


        printWordsByUnit(redBlackTree->right, unit);
    }
}





void printTranslations(BinaryTreeNode *currentNode, int unit, char *portugueseWord) {
    if (currentNode) {
        Unit *currentUnit = currentNode->unitValues;
        int foundUnit = 0;

        // Verifica se a unidade está presente na lista de unidades
        while (currentUnit != NULL && !foundUnit) {
            if (currentUnit->unitValue == unit) {
                foundUnit = 1;
            }
            currentUnit = currentUnit->nextNode;
        }

        // Imprime se a unidade foi encontrada
        if (foundUnit) {
            printf("Palavra em Português: %s\n", portugueseWord);
            printf("Palavra em inglês: %s\n", currentNode->englishWord);
        }

        // Processa os nós à esquerda e à direita
        printTranslations(currentNode->left, unit, portugueseWord);
        printTranslations(currentNode->right, unit, portugueseWord);
    }
}


void showPortugueseTranslation(RedBlackTreePT **rootNode, char *portugueseWord) {
    if (*rootNode != NULL) {
      
        printf("[DEBUG] Buscando a palavra em português: '%s'\n", portugueseWord);
        RedBlackTreePT *resultado = SearchWordInTree(rootNode, portugueseWord);

        if (resultado != NULL) {
            printf("[DEBUG] Palavra encontrada na árvore rubro-negra.\n");
            printf("Traduções em inglês para a palavra '%s':\n", portugueseWord);

      
            BinaryTreeNode *node = resultado->info.englishWordNode;
            if (node == NULL) {
                printf("Nenhuma tradução encontrada.\n");
            } else {
                printBinaryTree(node);
            }
        } else {
            printf("[DEBUG] Palavra '%s' não encontrada na árvore rubro-negra.\n", portugueseWord);
            printf("Nenhuma tradução encontrada para '%s'.\n", portugueseWord);
        }
    } else {
        printf("[DEBUG] A árvore rubro-negra está vazia.\n");
    }
}


void showRedBlackTree(RedBlackTreePT *rootNode)
{
    if (rootNode)
    {
        showRedBlackTree(rootNode->left);
        printf("Cor - %d\n", rootNode->color);
        printf("Palavra em Português - %s\n", rootNode->info.portugueseWord);
        printBinaryTree(rootNode->info.englishWordNode);
        printf("\n");
        showRedBlackTree(rootNode->right);
    }
}

RedBlackTreePT *SearchEnglishWordInRBTree(RedBlackTreePT *rootNode, char *englishWord, int unit) {
    RedBlackTreePT *rbTreeOutput = NULL;

    if (rootNode != NULL) {
        BinaryTreeNode *currentNode = rootNode->info.englishWordNode;
        int found = 0; // Flag para indicar se a palavra foi encontrada

        // Percorre a árvore binária associada ao nó rubro-negro
        while (currentNode != NULL && !found) {
            printf("Verificando palavra: '%s' na unidade %d\n", currentNode->englishWord, unit);

            Unit *currentUnit = currentNode->unitValues;
            int unitFound = 0;

            // Verifica se a unidade está associada à palavra inglesa
            while (currentUnit != NULL && !unitFound) {
                if (currentUnit->unitValue == unit) {
                    unitFound = 1;
                }
                currentUnit = currentUnit->nextNode;
            }

            // Verifica se a palavra inglesa corresponde
            if (unitFound && strcmp(currentNode->englishWord, englishWord) == 0) {
                printf("Palavra encontrada na árvore binária associada ao nó português: '%s'\n", rootNode->info.portugueseWord);
                rbTreeOutput = rootNode;
                found = 1;
            } else if (strcmp(englishWord, currentNode->englishWord) < 0) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
        }

        // Se não encontrada na árvore binária, busca nas subárvores da rubro-negra
        if (!found) {
            RedBlackTreePT *leftResult = SearchEnglishWordInRBTree(rootNode->left, englishWord, unit);
            if (leftResult != NULL) {
                rbTreeOutput = leftResult;
            } else {
                rbTreeOutput = SearchEnglishWordInRBTree(rootNode->right, englishWord, unit);
            }
        }
    }

    return rbTreeOutput;
}

void removeWordFromTree(RedBlackTreePT **node, char *wordToRemove, int *totalRemovido, RedBlackTreePT **rootNode, int unit) {
    if (*node != NULL) {
    
        removeWordFromTree(&(*node)->left, wordToRemove, totalRemovido, rootNode, unit);

      
        BinaryTreeNode *binaryRoot = (*node)->info.englishWordNode;
        int removed = removeEnglishWord(&binaryRoot, wordToRemove, unit);
        if (removed) {
            (*totalRemovido)++;
            printf("[DEBUG] Palavra '%s' removida da árvore binária associada ao nó com palavra portuguesa: '%s'.\n",
                   wordToRemove, (*node)->info.portugueseWord);
        }

      
        if (binaryRoot == NULL) {
            printf("[DEBUG] Árvore binária associada ao nó '%s' ficou vazia. Removendo nó da Árvore Rubro-Negra.\n",
                   (*node)->info.portugueseWord);
            removeRBTreeNode(rootNode, (*node)->info.portugueseWord);
        } else {
            (*node)->info.englishWordNode = binaryRoot;
        }

      
        removeWordFromTree(&(*node)->right, wordToRemove, totalRemovido, rootNode,unit);
    }
}
void removeWordByUnit(RedBlackTreePT **node, char *wordToRemove, int unit, int *removidos, RedBlackTreePT **rootNode) {
    if (node != NULL && *node != NULL && wordToRemove != NULL && rootNode != NULL) {
        // Processa a subárvore esquerda
        removeWordByUnit(&(*node)->left, wordToRemove, unit, removidos, rootNode);

        BinaryTreeNode *binaryRoot = (*node)->info.englishWordNode;
        if (binaryRoot != NULL) {
            BinaryTreeNode *currentNode = binaryRoot;
            int found = 0; // Flag para indicar se a palavra foi encontrada

            // Percorre a árvore binária associada
            while (currentNode != NULL && !found) {
                if (strcmp(currentNode->englishWord, wordToRemove) == 0) {
                    Unit *novaLista = remove_unit(currentNode->unitValues, unit);
                    currentNode->unitValues = novaLista;

                    // Se a palavra inglesa não tem mais unidades, remova-a
                    if (currentNode->unitValues == NULL) {
                        *removidos += removeEnglishWord(&binaryRoot, wordToRemove, unit);
                    }
                    found = 1; // Palavra encontrada e processada
                } else if (strcmp(wordToRemove, currentNode->englishWord) < 0) {
                    currentNode = currentNode->left;
                } else {
                    currentNode = currentNode->right;
                }
            }

            // Atualiza a árvore binária associada no nó da árvore rubro-negra
            (*node)->info.englishWordNode = binaryRoot;

            // Se a árvore binária ficou vazia, remova o nó da árvore rubro-negra
            if (binaryRoot == NULL) {
                removeRBTreeNode(rootNode, (*node)->info.portugueseWord);
            }
        }

        // Processa a subárvore direita
        removeWordByUnit(&(*node)->right, wordToRemove, unit, removidos, rootNode);
    }
}


void exibir_arvorebianria_dada_palavra_portuguesa(RedBlackTreePT *rootNode, char *portugueseWord)
{
    if (rootNode)
    {
        exibir_arvorebianria_dada_palavra_portuguesa(rootNode->left, portugueseWord);
        if (strcmp(rootNode->info.portugueseWord, portugueseWord) == 0)
        {
            exibir_arvorebinaria(rootNode->info.englishWordNode);
        }
        exibir_arvorebianria_dada_palavra_portuguesa(rootNode->right, portugueseWord);
    }
}
void deleteWordFromTreeByUnit(RedBlackTreePT **redBlackTreeRoot, char *portugueseWord, int unit) {
    int erro = 0; // Flag para indicar se há erro

    // Validação inicial
    if (redBlackTreeRoot == NULL || *redBlackTreeRoot == NULL || portugueseWord == NULL) {
        printf("Erro: Entrada inválida ou árvore vazia.\n");
        erro = 1;
    }

    // Busca o nó da palavra portuguesa na árvore rubro-negra
    RedBlackTreePT *noRBT = NULL;
    if (!erro) {
        noRBT = SearchWordInTree(redBlackTreeRoot, portugueseWord);
        if (noRBT == NULL) {
            printf("Palavra '%s' não encontrada na árvore rubro-negra.\n", portugueseWord);
            erro = 1;
        }
    }

    // Processamento da árvore binária associada
    if (!erro && noRBT != NULL) {
        BinaryTreeNode *raizBST = noRBT->info.englishWordNode;
        if (raizBST != NULL) {
            BinaryTreeNode *currentNode = raizBST;

            while (currentNode != NULL) {
                // Remove a unidade da palavra inglesa
                Unit *novaLista = remove_unit(currentNode->unitValues, unit);
                currentNode->unitValues = novaLista;

                // Se a palavra inglesa não tem mais unidades, remova-a da árvore binária
                if (currentNode->unitValues == NULL) {
                    printf("Palavra '%s' na unidade %d ficou sem unidades. Removendo.\n", currentNode->englishWord, unit);
                    removeEnglishWord(&raizBST, currentNode->englishWord, unit);
                    currentNode = raizBST; // Reinicia a navegação a partir da raiz atualizada
                } else {
                    // Percorre a árvore binária
                    if (strcmp(currentNode->englishWord, portugueseWord) > 0) {
                        currentNode = currentNode->left;
                    } else {
                        currentNode = currentNode->right;
                    }
                }
            }

            // Atualiza a árvore binária associada no nó rubro-negro
            noRBT->info.englishWordNode = raizBST;

            // Se a árvore binária ficou vazia, remova o nó da árvore rubro-negra
            if (raizBST == NULL) {
                printf("Árvore binária associada ao nó '%s' ficou vazia. Removendo nó da árvore rubro-negra.\n", portugueseWord);
                removeRBTreeNode(redBlackTreeRoot, portugueseWord);
            }
        } else {
            printf("Não há palavras em inglês associadas ao nó '%s'.\n", portugueseWord);
        }
    }

    // Mensagem final
    if (erro) {
        printf("A operação não pôde ser concluída devido a erros.\n");
    } else {
        printf("Operação concluída.\n");
    }
}
