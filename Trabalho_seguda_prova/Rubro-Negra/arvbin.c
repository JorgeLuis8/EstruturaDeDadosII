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

int removeEnglishWord(BinaryTreeNode **rootNode, char *wordToRemove) {
    int isFound = 0; 
    BinaryTreeNode *lastChild = NULL;

    if (*rootNode) {
        if (strcmp(wordToRemove, (*rootNode)->englishWord) == 0) {
            isFound = 1;
            printf("Removendo palavra: %s\n", wordToRemove);
            BinaryTreeNode *aux = *rootNode;

            if (isLeafNodes(*rootNode)) {
               
                free_list(aux->unitValues);
                free(aux);
                *rootNode = NULL;
            } else if ((lastChild = singleChildNode(*rootNode)) != NULL) {
              
                free_list(aux->unitValues);
                free(aux);
                *rootNode = lastChild;
            } else {
                
                lastChild = minimumChildNode((*rootNode)->right);
                strcpy((*rootNode)->englishWord, lastChild->englishWord);

              
                free_list((*rootNode)->unitValues);
                (*rootNode)->unitValues = NULL;

               
                Unit *currentUnit = lastChild->unitValues;
                while (currentUnit != NULL) {
                    Unit *novaUnidade = create_unit(currentUnit->unitValue);
                    (*rootNode)->unitValues = insert_unit_sorted((*rootNode)->unitValues, novaUnidade);
                    currentUnit = currentUnit->nextNode;
                }

                removeEnglishWord(&(*rootNode)->right, lastChild->englishWord);
            }
        } else if (strcmp(wordToRemove, (*rootNode)->englishWord) < 0) {
            isFound = removeEnglishWord(&(*rootNode)->left, wordToRemove);
        } else {
            isFound = removeEnglishWord(&(*rootNode)->right, wordToRemove);
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
                       
                        removeEnglishWord(&(*rootNode)->info.englishWordNode, englishTerm);
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