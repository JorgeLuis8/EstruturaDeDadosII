#include "arv-ingles-bin.h"


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
TreeNode* insertEnglishWord(TreeNode* root, const char* word, int unidade) {
    if (root == NULL) {
        root = createNode(word, unidade);
    } else if (strcmp(word, root->englishWord) < 0) {
        root->left = insertEnglishWord(root->left, word, unidade);
    } else {
        root->right = insertEnglishWord(root->right, word, unidade);
    }
    return root;
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
        // Percorre à esquerda
        printBinaryTree(root->left);
        
        // Imprime a palavra em inglês
        printf("%s \n", root->englishWord);
        
        // Percorre à direita
        printBinaryTree(root->right);
    }
}


TreeNode* removeEnglishWord(TreeNode* root, const char* word, int unit) {
    if (root != NULL) {
        if (strcmp(word, root->englishWord) < 0) {
            // A palavra a ser removida está na subárvore esquerda
            root->left = removeEnglishWord(root->left, word, unit);
        } else if (strcmp(word, root->englishWord) > 0) {
            // A palavra a ser removida está na subárvore direita
            root->right = removeEnglishWord(root->right, word, unit);
        } else if (root->unit == unit) {
            // Encontrou o nó a ser removido e a unidade corresponde
            if (root->left == NULL && root->right == NULL) {
                // Caso 1: O nó é uma folha e é o único elemento na árvore
                free(root);
                return NULL; // Retorna NULL para indicar que a árvore está vazia
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
                root->left = removeEnglishWord(root->left, aux->englishWord, aux->unit);
            }
        }
    }
    return root;
}




void printTree(TreeNode* root) {
    if (root != NULL) {
        printTree(root->left);
        printf("Palavra: %s, Unidade: %d\n", root->englishWord, root->unit);
        printTree(root->right);
    }
}


// Função para limpar todos os nós de uma árvore binária
void limparArvoreBinaria(TreeNode** root) {
    if (*root != NULL) {
        // Recursivamente limpa os nós da subárvore esquerda e direita
        limparArvoreBinaria(&((*root)->left));
        limparArvoreBinaria(&((*root)->right));

        // Libera o nó atual
        free(*root);
        *root = NULL; // Garante que o ponteiro seja definido como NULL
    }
}

