#include "arv_ingles-binaria.h"


// Função para criar um novo nó na árvore binária de busca
TreeNode* createNode(const char* word, int unit) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        strcpy(newNode->englishWord, word);
        newNode->unit = unit;
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}

// Função para inserir uma palavra em inglês na árvore binária de busca
TreeNode* insertEnglishWord(TreeNode* root, const char* word, int unit) {
    TreeNode *result;
    if (root == NULL) {
        result = createNode(word, unit);
    } else {
        if (strcmp(word, root->englishWord) < 0) {
            root->left = insertEnglishWord(root->left, word, unit);
        } else if (strcmp(word, root->englishWord) > 0) {
            root->right = insertEnglishWord(root->right, word, unit);
        }
        result = root;
    }
    return result;
}

// Função para buscar uma palavra em inglês na árvore binária de busca
TreeNode* searchEnglishWord(TreeNode* root, const char* word) {
    TreeNode *result;
    if (root == NULL || strcmp(root->englishWord, word) == 0) {
        result = root;
    } else {
        if (strcmp(word, root->englishWord) < 0) {
            result = searchEnglishWord(root->left, word);
        } else {
            result = searchEnglishWord(root->right, word);
        }
    }
    return result;
}

// Função para imprimir a árvore binária em ordem alfabética (simples visualização)
void printBinaryTree(TreeNode* root) {
    if (root != NULL) {
        printBinaryTree(root->left);
        printf("%s \n", root->englishWord);
        printBinaryTree(root->right);
    }
}

TreeNode* removeEnglishWord(TreeNode* root, const char* word) {
    if (root != NULL) {
        if (strcmp(word, root->englishWord) < 0) {
            // A palavra a ser removida está na subárvore esquerda
            root->left = removeEnglishWord(root->left, word);
        } else if (strcmp(word, root->englishWord) > 0) {
            // A palavra a ser removida está na subárvore direita
            root->right = removeEnglishWord(root->right, word);
        } else {
            // Encontrou o nó a ser removido
            if (root->left == NULL && root->right == NULL) {
                // Caso 1: O nó é uma folha
                free(root);
                root = NULL;
            } else if (root->left == NULL) {
                // Caso 2: O nó tem apenas um filho à direita
                TreeNode* aux = root;
                root = root->right;
                free(aux);
            } else if (root->right == NULL) {
                // Caso 3: O nó tem apenas um filho à esquerda
                TreeNode* aux = root;
                root = root->left;
                free(aux);
            } else {
                // Caso 4: O nó tem dois filhos
                // Encontrar o maior elemento da subárvore esquerda (ou o menor da subárvore direita)
                TreeNode* aux = root->left;
                while (aux->right != NULL) {
                    aux = aux->right;
                }
                // Copiar o valor do maior elemento encontrado para o nó atual
                strcpy(root->englishWord, aux->englishWord);
                root->unit = aux->unit;
                // Remover o nó duplicado da subárvore esquerda
                root->left = removeEnglishWord(root->left, aux->englishWord);
            }
        }
    }
    return root;
}

void imprimirTraducoes(TreeNode *node, const char *palavraPortugues, int *primeira) {
    if (node) {
        // Imprime o nó esquerdo
        imprimirTraducoes(node->left, palavraPortugues, primeira);

        // Imprime a palavra em inglês e a tradução em português
        if (!*primeira) {
            printf("\n");
        }
        printf("%s: %s;", node->englishWord, palavraPortugues);
        *primeira = 0;

        // Imprime o nó direito
        imprimirTraducoes(node->right, palavraPortugues, primeira);
    }
}