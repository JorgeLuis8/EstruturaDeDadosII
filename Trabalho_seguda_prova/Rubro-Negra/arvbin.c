#include "arvbin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvrb.h"
#include "unidade.h"

BinaryTreeNode *initializeBinaryTreeNode(char *englishWord, int unit) {
    BinaryTreeNode *newNode = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    if (newNode == NULL) {
        perror("Erro ao alocar memória para o nó da árvore binária");
        exit(EXIT_FAILURE);
    }

 
    strcpy(newNode->englishWord, englishWord);
    newNode->unitValues = create_unit(unit); 
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

BinaryTreeNode *insertEnglishWord(BinaryTreeNode *rootNode, char *englishWord, int unit) {
    BinaryTreeNode *result = rootNode; 

    if (rootNode == NULL) {
       
        BinaryTreeNode *newTreeNode = initializeBinaryTreeNode(englishWord, unit);
        if (newTreeNode != NULL) {
            result = newTreeNode;
        } else {
            perror("Erro ao alocar memória para o nó da árvore binária.");
        }
    } else {
        int cmp = strcmp(englishWord, rootNode->englishWord);
        if (cmp < 0) {
            rootNode->left = insertEnglishWord(rootNode->left, englishWord, unit);
        } else if (cmp > 0) {
            rootNode->right = insertEnglishWord(rootNode->right, englishWord, unit);
        } else {
            
            Unit *newUnit = create_unit(unit);
            if (newUnit != NULL) {
                rootNode->unitValues = insert_unit_sorted(rootNode->unitValues, newUnit);
            } else {
                perror("Erro ao alocar memória para a unidade.");
            }
        }
    }

    return result; 
}

void addEnglishTranslation(RedBlackTreePT *rootNode, char *englishWord, int unit) {
    if (rootNode != NULL) {
        BinaryTreeNode *novoRoot = insertEnglishWord(rootNode->info.englishWordNode, englishWord, unit);
        rootNode->info.englishWordNode = novoRoot;
    } else {
        perror("Erro: Nó da árvore vermelho-preto é nulo.");
    }
}

void printBinaryTree(BinaryTreeNode *root) {
    if (root != NULL) {
        printBinaryTree(root->left);


        printf("Palavra em inglês: %s\n", root->englishWord);

        Unit *currentUnit = root->unitValues;
        printf("Unidades: ");
        while (currentUnit != NULL) {
            printf("%d ", currentUnit->unitValue);
            currentUnit = currentUnit->nextNode;
        }
        printf("\n");

        printBinaryTree(root->right);
    }
}



int isLeafNodes(BinaryTreeNode *rootNode)
{
    return (rootNode->left == NULL && rootNode->right == NULL);
}

BinaryTreeNode *singleChildNode(BinaryTreeNode *rootNode)
{
    BinaryTreeNode *aux;
    aux = NULL;

    if (rootNode->right == NULL)
    {
        aux = rootNode->left;
    }
    else if (rootNode->left == NULL)
    {
        aux = rootNode->right;
    }

    return aux;
}

BinaryTreeNode *minimumChildNode(BinaryTreeNode *rootNode)
{
    BinaryTreeNode *aux;
    aux = rootNode;

    if (rootNode)
    {
        if (rootNode->left)
            aux = minimumChildNode(rootNode->left);
    }

    return aux;
}

int removeEnglishWord(BinaryTreeNode **rootNode, const char *wordToRemove, int unit) {
    BinaryTreeNode *childNode = NULL;
    int isFound = 0;

    if (*rootNode) {
        if (strcmp(wordToRemove, (*rootNode)->englishWord) == 0) {
            BinaryTreeNode *aux = *rootNode;
            isFound = 1;

            // Atualiza a lista de unidades
            Unit *newUnitList = remove_unit((*rootNode)->unitValues, unit);

            if (newUnitList != (*rootNode)->unitValues) {
                (*rootNode)->unitValues = newUnitList;

                // Se a lista de unidades está vazia, remova o nó
                if (newUnitList == NULL) {
                    if (isLeafNodes(*rootNode)) {
                        // Caso o nó seja uma folha
                        free(aux);
                        *rootNode = NULL;
                    } else if ((childNode = singleChildNode(*rootNode)) != NULL) {
                        // Caso o nó tenha um único filho
                        free(aux);
                        *rootNode = childNode;
                    } else {
                        // Caso o nó tenha dois filhos
                        childNode = minimumChildNode((*rootNode)->right);
                        strcpy((*rootNode)->englishWord, childNode->englishWord);
                        (*rootNode)->unitValues = childNode->unitValues;

                        // Remove o menor nó da subárvore direita
                        removeEnglishWord(&(*rootNode)->right, childNode->englishWord, unit);
                    }
                }
            }
        } else if (strcmp(wordToRemove, (*rootNode)->englishWord) < 0) {
            // Busca na subárvore esquerda
            isFound = removeEnglishWord(&(*rootNode)->left, wordToRemove, unit);
        } else {
            // Busca na subárvore direita
            isFound = removeEnglishWord(&(*rootNode)->right, wordToRemove, unit);
        }
    }

    return isFound;
}



void FindEnglishTerm(RedBlackTreePT **rootNode, char *englishTerm, int unit) {
    if (*rootNode != NULL) {
        FindEnglishTerm(&(*rootNode)->left, englishTerm, unit);

        
        if ((*rootNode)->info.englishWordNode != NULL) {
          
            BinaryTreeNode *currentNode = (*rootNode)->info.englishWordNode;
            while (currentNode != NULL) {
                if (strcmp(currentNode->englishWord, englishTerm) == 0) {
                   
                    Unit *novaLista = remove_unit(currentNode->unitValues, unit);
                    currentNode->unitValues = novaLista;

                  
                    if (currentNode->unitValues == NULL) {
                       
                        removeEnglishWord(&(*rootNode)->info.englishWordNode, englishTerm, unit);
                    }
                    break; 
                }


                if (strcmp(englishTerm, currentNode->englishWord) < 0) {
                    currentNode = currentNode->left;
                } else {
                    currentNode = currentNode->right;
                }
            }
        }
        FindEnglishTerm(&(*rootNode)->right, englishTerm, unit);
    }
}

void exibir_arvorebinaria(BinaryTreeNode *rootNode) {
    if (rootNode != NULL) {
        exibir_arvorebinaria(rootNode->left);

  
        printf("Palavra em inglês: %s\n", rootNode->englishWord);

    
        Unit *currentUnit = rootNode->unitValues;
        printf("Unidades: ");
        while (currentUnit != NULL) {
            printf("%d ", currentUnit->unitValue);
            currentUnit = currentUnit->nextNode;
        }
        printf("\n");

        exibir_arvorebinaria(rootNode->right);
    }
}