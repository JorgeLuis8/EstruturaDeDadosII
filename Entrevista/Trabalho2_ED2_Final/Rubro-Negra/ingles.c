#include "ingles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portugues.h"
#include "unidade.h"

// Função para inicializar um nó da árvore binária
BinaryTreeNode *initializeBinaryTreeNode(char *englishWord, int unit) {
    // Aloca memória para um novo nó da árvore binária
    BinaryTreeNode *newNode = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    // Verifica se a alocação foi bem-sucedida
    if (newNode == NULL) {
        // Exibe mensagem de erro e encerra o programa em caso de falha
        perror("Erro ao alocar memória para o nó da árvore binária");
        exit(EXIT_FAILURE);
    }

    // Copia a palavra em inglês para o campo `englishWord` do nó
    strcpy(newNode->englishWord, englishWord);
    // Cria uma estrutura para armazenar os valores associados à unidade
    newNode->unitValues = create_unit(unit);
    // Inicializa os ponteiros dos filhos esquerdo e direito como `NULL`
    newNode->left = NULL;
    newNode->right = NULL;

    // Retorna o novo nó criado
    return newNode;
}

// Função para inserir uma palavra em inglês na árvore binária
BinaryTreeNode *insertEnglishWord(BinaryTreeNode *rootNode, char *englishWord, int unit) {
    // Define o nó raiz como o nó atual
    BinaryTreeNode *result = rootNode;

    // Se a raiz da árvore for nula, cria um novo nó
    if (rootNode == NULL) {
        // Inicializa um novo nó da árvore binária
        BinaryTreeNode *newTreeNode = initializeBinaryTreeNode(englishWord, unit);
        // Verifica se o novo nó foi criado com sucesso
        if (newTreeNode != NULL) {
            // Atualiza o resultado para o novo nó
            result = newTreeNode;
        } else {
            // Exibe mensagem de erro em caso de falha na alocação de memória
            perror("Erro ao alocar memória para o nó da árvore binária.");
        }
    } else {
        // Compara a palavra em inglês com a palavra no nó atual
        int cmp = strcmp(englishWord, rootNode->englishWord);
        // Se a palavra for menor (em ordem alfabética), insere no subárvore esquerda
        if (cmp < 0) {
            rootNode->left = insertEnglishWord(rootNode->left, englishWord, unit);
        // Se a palavra for maior (em ordem alfabética), insere no subárvore direita
        } else if (cmp > 0) {
            rootNode->right = insertEnglishWord(rootNode->right, englishWord, unit);
        // Se a palavra já existir no nó atual
        } else {
            // Cria uma nova unidade associada à palavra
            Unit *newUnit = create_unit(unit);
            // Verifica se a unidade foi criada com sucesso
            if (newUnit != NULL) {
                // Insere a nova unidade na lista de unidades ordenadamente
                rootNode->unitValues = insert_unit_sorted(rootNode->unitValues, newUnit);
            } else {
                // Exibe mensagem de erro em caso de falha na criação da unidade
                perror("Erro ao alocar memória para a unidade.");
            }
        }
    }

    // Retorna o nó atualizado (ou o novo nó criado)
    return result;
}


// Função para adicionar uma tradução em inglês à estrutura de uma árvore vermelho-preta
void addEnglishTranslation(RedBlackTreePT *rootNode, char *englishWord, int unit) {
    // Verifica se o nó da árvore vermelho-preta não é nulo
    if (rootNode != NULL) {
        // Insere a nova palavra na subárvore binária associada
        BinaryTreeNode *novoRoot = insertEnglishWord(rootNode->info.englishWordNode, englishWord, unit);
        // Atualiza a subárvore binária no nó da árvore vermelho-preta
        rootNode->info.englishWordNode = novoRoot;
    } else {
        // Exibe mensagem de erro se o nó da árvore vermelho-preta for nulo
        perror("Erro: Nó da árvore vermelho-preta é nulo.");
    }
}

// Função para imprimir os elementos da árvore binária em ordem
void printBinaryTree(BinaryTreeNode *root) {
    // Verifica se o nó atual não é nulo
    if (root != NULL) {
        // Imprime o lado esquerdo da árvore (ordem crescente)
        printBinaryTree(root->left);

        // Imprime a palavra em inglês armazenada no nó
        printf("Palavra em inglês: %s\n", root->englishWord);

        // Imprime a lista de unidades associadas à palavra
        Unit *currentUnit = root->unitValues;
        printf("Unidades: ");
        while (currentUnit != NULL) {
            // Imprime o valor da unidade atual
            printf("%d ", currentUnit->unitValue);
            currentUnit = currentUnit->nextNode;
        }
        printf("\n");

        // Imprime o lado direito da árvore (ordem crescente)
        printBinaryTree(root->right);
    }
}

// Função para verificar se um nó da árvore binária é uma folha
int isLeafNodes(BinaryTreeNode *rootNode) {
    // Retorna 1 (verdadeiro) se o nó não possuir filhos, caso contrário, retorna 0 (falso)
    return (rootNode->left == NULL && rootNode->right == NULL);
}

// Função para encontrar o único filho de um nó da árvore binária
BinaryTreeNode *singleChildNode(BinaryTreeNode *rootNode) {
    // Declara um ponteiro auxiliar inicializado como nulo
    BinaryTreeNode *aux;
    aux = NULL;

    // Verifica se o nó possui apenas um filho à esquerda
    if (rootNode->right == NULL) {
        aux = rootNode->left;
    }
    // Verifica se o nó possui apenas um filho à direita
    else if (rootNode->left == NULL) {
        aux = rootNode->right;
    }

    // Retorna o ponteiro para o único filho ou nulo caso ambos os filhos existam
    return aux;
}

// Função para encontrar o nó com o menor valor na subárvore
BinaryTreeNode *minimumChildNode(BinaryTreeNode *rootNode) {
    // Declara um ponteiro auxiliar inicializado com o nó raiz
    BinaryTreeNode *aux;
    aux = rootNode;

    // Verifica se o nó raiz não é nulo
    if (rootNode) {
        // Continua descendo pela subárvore à esquerda até encontrar o menor nó
        if (rootNode->left)
            aux = minimumChildNode(rootNode->left);
    }

    // Retorna o nó com o menor valor encontrado
    return aux;
}


// Função para remover uma palavra em inglês da árvore binária
int removeEnglishWord(BinaryTreeNode **rootNode, const char *wordToRemove, int unit) {
    int isFound = 0; // Flag para indicar se a palavra foi encontrada

    // Verifica se o ponteiro para o nó raiz, o nó em si e a palavra não são nulos
    if (rootNode != NULL && *rootNode != NULL && wordToRemove != NULL) {
        // Compara a palavra a ser removida com a palavra do nó atual
        if (strcmp(wordToRemove, (*rootNode)->englishWord) == 0) {
            // Palavra encontrada
            isFound = 1;
            // Remove a unidade específica associada à palavra
            Unit *newUnitList = remove_unit((*rootNode)->unitValues, unit);
            (*rootNode)->unitValues = newUnitList;

            // Se a lista de unidades ficar vazia, o nó deve ser removido
            if (newUnitList == NULL) {
                BinaryTreeNode *nodeToRemove = *rootNode;

                // Caso 1: O nó é uma folha
                if (isLeafNodes(*rootNode)) {
                    free(nodeToRemove); // Libera a memória do nó
                    *rootNode = NULL;   // Atualiza o ponteiro para nulo
                }
                // Caso 2: O nó tem apenas um filho
                else if ((nodeToRemove = singleChildNode(*rootNode)) != NULL) {
                    free(*rootNode);     // Libera a memória do nó atual
                    *rootNode = nodeToRemove; // Atualiza o ponteiro para o filho
                }
                // Caso 3: O nó tem dois filhos
                else {
                    // Encontra o sucessor (menor nó na subárvore direita)
                    BinaryTreeNode *successor = minimumChildNode((*rootNode)->right);
                    // Substitui os dados do nó atual pelos dados do sucessor
                    strcpy((*rootNode)->englishWord, successor->englishWord);
                    (*rootNode)->unitValues = successor->unitValues;
                    // Remove o sucessor recursivamente
                    removeEnglishWord(&(*rootNode)->right, successor->englishWord, unit);
                }
            }
        }
        // Se a palavra a ser removida for menor, busca no lado esquerdo da árvore
        else if (strcmp(wordToRemove, (*rootNode)->englishWord) < 0) {
            isFound = removeEnglishWord(&(*rootNode)->left, wordToRemove, unit);
        }
        // Se a palavra a ser removida for maior, busca no lado direito da árvore
        else {
            isFound = removeEnglishWord(&(*rootNode)->right, wordToRemove, unit);
        }
    }

    return isFound; // Retorna se a palavra foi encontrada e tratada
}

// Função para remover uma unidade associada a um termo em inglês na árvore vermelho-preta
void RemoveUnitFromEnglishTerm(RedBlackTreePT **rootNode, char *englishTerm, int unit) {
    // Verifica se a árvore vermelho-preta não está vazia
    if (*rootNode != NULL) {
        // Processa o lado esquerdo da árvore recursivamente
        RemoveUnitFromEnglishTerm(&(*rootNode)->left, englishTerm, unit);

        // Se o nó atual possui uma subárvore binária associada
        if ((*rootNode)->info.englishWordNode != NULL) {
            BinaryTreeNode *currentNode = (*rootNode)->info.englishWordNode;
            int found = 0; // Flag para indicar se o termo foi encontrado

            // Busca o termo na subárvore binária
            while (currentNode != NULL && !found) {
                // Se encontrar o termo
                if (strcmp(currentNode->englishWord, englishTerm) == 0) {
                    // Remove a unidade específica do termo
                    Unit *novaLista = remove_unit(currentNode->unitValues, unit);
                    currentNode->unitValues = novaLista;

                    // Se a lista de unidades ficar vazia, remove o nó da árvore binária
                    if (currentNode->unitValues == NULL) {
                        removeEnglishWord(&(*rootNode)->info.englishWordNode, englishTerm, unit);
                    }

                    found = 1; // Atualiza a flag para indicar que o termo foi encontrado
                }
                // Se o termo é menor, move para o filho à esquerda
                else if (strcmp(englishTerm, currentNode->englishWord) < 0) {
                    currentNode = currentNode->left;
                }
                // Se o termo é maior, move para o filho à direita
                else {
                    currentNode = currentNode->right;
                }
            }
        }

        // Processa o lado direito da árvore recursivamente
        RemoveUnitFromEnglishTerm(&(*rootNode)->right, englishTerm, unit);
    }
}

// Função para exibir os elementos de uma árvore binária
void show_binary_tree(BinaryTreeNode *rootNode) {
    // Verifica se o nó atual não é nulo
    if (rootNode != NULL) {
        // Exibe o lado esquerdo da árvore (ordem crescente)
        show_binary_tree(rootNode->left);

        // Imprime a palavra em inglês armazenada no nó
        printf("Palavra em inglês: %s\n", rootNode->englishWord);

        // Imprime as unidades associadas à palavra
        Unit *currentUnit = rootNode->unitValues;
        printf("Unidades: ");
        while (currentUnit != NULL) {
            printf("%d ", currentUnit->unitValue); // Imprime o valor da unidade atual
            currentUnit = currentUnit->nextNode;  // Move para a próxima unidade
        }
        printf("\n");

        // Exibe o lado direito da árvore (ordem crescente)
        show_binary_tree(rootNode->right);
    }
}
