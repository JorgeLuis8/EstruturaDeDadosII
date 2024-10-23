#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int qtd_folhas(struct Node* root, int* soma) {
    int qtd = 0;
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) { // Nó folha
            qtd += 1; // Incrementa a quantidade de folhas
            if (root->data % 3 == 0) { // Verifica se é múltiplo de 3
                *soma += root->data; // Adiciona ao somatório
            }
        }
        // Chama recursivamente para os filhos
        qtd += qtd_folhas(root->left, soma);
        qtd += qtd_folhas(root->right, soma);
    }
    return qtd;
}

int main() {
    // Criando a árvore para teste
    struct Node* root = newNode(30);
    root->left = newNode(9);
    root->right = newNode(18);
    root->left->left = newNode(12);
    root->left->right = newNode(27);
    
    // Variável para armazenar a soma dos múltiplos de 3
    int soma_multiplos_de_3 = 0;
    
    // Chamando a função qtd_folhas
    int qtd_de_folhas = qtd_folhas(root, &soma_multiplos_de_3);
    
    // Imprimindo os resultados
    printf("Quantidade de folhas: %d\n", qtd_de_folhas);
    printf("Soma dos múltiplos de 3 das folhas: %d\n", soma_multiplos_de_3);
    
    // Liberar memória
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);
    
    return 0;
}
