#include "arv-ingles-bin.h"

// Função para criar um novo nó na árvore binária de busca
TreeNodeEn* createNodeEn(const char* word, int unit) {
    TreeNodeEn* newNode = (TreeNodeEn*)malloc(sizeof(TreeNodeEn));
    if (newNode != NULL) {
        strcpy(newNode->englishWord, word);
        newNode->unit = unit;
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}

// Função para inserir uma palavra em inglês na árvore binária de busca
TreeNodeEn* insertEnglishWordEn(TreeNodeEn* root, const char* word, int unit) {
    if (root == NULL) {
        return createNodeEn(word, unit);
    }
    if (strcmp(word, root->englishWord) < 0) {
        root->left = insertEnglishWordEn(root->left, word, unit);
    } else if (strcmp(word, root->englishWord) > 0) {
        root->right = insertEnglishWordEn(root->right, word, unit);
    }
    return root;
}

// Função para buscar uma palavra em inglês na árvore binária de busca
TreeNodeEn* searchEnglishWordEn(TreeNodeEn* root, const char* word) {
    if (root == NULL || strcmp(root->englishWord, word) == 0) {
        return root;
    }
    if (strcmp(word, root->englishWord) < 0) {
        return searchEnglishWordEn(root->left, word);
    } else {
        return searchEnglishWordEn(root->right, word);
    }
}

// Função para imprimir a árvore binária em ordem alfabética (simples visualização)
void printBinaryTreeEn(TreeNodeEn* root) {
    if (root != NULL) {
        printBinaryTreeEn(root->left);
        printf("%s \n", root->englishWord);
        printBinaryTreeEn(root->right);
    }
}

// Função para remover uma palavra da árvore binária de busca
TreeNodeEn* removeEnglishWordEn(TreeNodeEn* root, const char* word, int unit) {
    if (root != NULL) {
        if (strcmp(word, root->englishWord) < 0) {
            root->left = removeEnglishWordEn(root->left, word, unit);
        } else if (strcmp(word, root->englishWord) > 0) {
            root->right = removeEnglishWordEn(root->right, word, unit);
        } else if (root->unit == unit) {
            if (root->left == NULL && root->right == NULL) {
                free(root);
                return NULL;
            } else if (root->left == NULL) {
                TreeNodeEn* aux = root;
                root = root->right;
                free(aux);
            } else if (root->right == NULL) {
                TreeNodeEn* aux = root;
                root = root->left;
                free(aux);
            } else {
                TreeNodeEn* aux = root->left;
                while (aux->right != NULL) {
                    aux = aux->right;
                }
                strcpy(root->englishWord, aux->englishWord);
                root->unit = aux->unit;
                root->left = removeEnglishWordEn(root->left, aux->englishWord, aux->unit);
            }
        }
    }
    return root;
}

// Função para imprimir traduções
void imprimirTraducoesEn(TreeNodeEn* node, const char* palavraPortugues, int* primeira) {
    if (node) {
        imprimirTraducoesEn(node->left, palavraPortugues, primeira);
        if (!*primeira) {
            printf("\n");
        }
        printf("%s: %s;", node->englishWord, palavraPortugues);
        *primeira = 0;
        imprimirTraducoesEn(node->right, palavraPortugues, primeira);
    }
}

// Função para imprimir a árvore com informações adicionais
void printTreeEn(TreeNodeEn* root) {
    if (root != NULL) {
        printTreeEn(root->left);
        printf("Palavra: %s, Unidade: %d\n", root->englishWord, root->unit);
        printTreeEn(root->right);
    }
}

// Função para limpar todos os nós de uma árvore binária
void limparArvoreBinariaEn(TreeNodeEn** root) {
    if (*root != NULL) {
        limparArvoreBinariaEn(&((*root)->left));
        limparArvoreBinariaEn(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}
