#include <stdio.h>
#include <stdlib.h>
#include "23.h"

// Função para exibir informações de todos os nós da árvore 2-3
void DisplayInfos(TreeNode23 *root) {
    if (root->left) { // Verifica se há um filho à esquerda
        DisplayInfos(root->left); // Chama a função recursivamente para o filho à esquerda
    }

    // Exibe as informações do primeiro bloco (info1)
    printf("Começo: %d | Fim: %d | Status: %d\n", root->info1.num_start, root->info1.num_end, root->info1.status);

    if (root->center) { // Verifica se há um filho central
        DisplayInfos(root->center); // Chama a função recursivamente para o filho central
    }

    if (root->n_infos == 2) { // Se o nó possui dois blocos de informações
        // Exibe as informações do segundo bloco (info2)
        printf("Começo: %d | Fim: %d | Status: %d\n", root->info2.num_start, root->info2.num_end, root->info2.status);
        if (root->right) { // Verifica se há um filho à direita
            DisplayInfos(root->right); // Chama a função recursivamente para o filho à direita
        }
    }
}

// Função para alocar memória para um novo nó da árvore 2-3
TreeNode23 *allocate_nodo() {
    TreeNode23 *node;
    node = (TreeNode23 *)malloc(sizeof(TreeNode23)); // Aloca memória para o nó

    if (!node) { // Verifica se a alocação falhou
        printf("Erro ao alocar nó da árvore"); // Exibe uma mensagem de erro
        exit(EXIT_FAILURE); // Encerra o programa
    }

    return node; // Retorna o ponteiro para o nó alocado
}

// Função para liberar a memória de um nó da árvore 2-3
void free_nodo(TreeNode23 **node) {
    free(*node); // Libera a memória do nó
    *node = NULL; // Define o ponteiro como NULL para evitar acessos inválidos
}

// Função para criar e inicializar um novo nó da árvore 2-3
TreeNode23 *Create_nodo(Info info, TreeNode23 *left_child, TreeNode23 *center_child) {
    TreeNode23 *node;
    node = allocate_nodo(); // Aloca memória para o nó

    // Inicializa o nó com os valores fornecidos
    node->info1 = info; // Define o primeiro bloco de informações
    node->left = left_child; // Define o filho à esquerda
    node->center = center_child; // Define o filho central
    node->right = NULL; // Inicializa o filho à direita como NULL
    node->n_infos = 1; // Define que o nó possui apenas um bloco de informações

    return node; // Retorna o ponteiro para o nó criado
}


// Função para dividir um nó cheio em dois nós, retornando o maior nó criado
TreeNode23 *SplitNode(TreeNode23 *node, Info info, Info *up, TreeNode23 *right_child)
{
    TreeNode23 *largestNode;

    // Caso a nova informação seja maior que info2 do nó atual
    if (info.num_start > node->info2.num_start)
    {
        *up = node->info2; // Define o valor que será promovido ao nó pai
        // Cria o maior nó com a nova informação
        largestNode = Create_nodo(info, node->right, right_child);
    }
    // Caso a nova informação esteja entre info1 e info2 do nó atual
    else if (info.num_start > node->info1.num_start)
    {
        *up = info; // A nova informação é promovida ao nó pai
        // Cria o maior nó com o valor info2 do nó atual
        largestNode = Create_nodo(node->info2, right_child, node->right);
    }
    // Caso a nova informação seja menor que info1 do nó atual
    else
    {
        *up = node->info1; // Define info1 como o valor promovido ao nó pai
        // Cria o maior nó com o valor info2 do nó atual
        largestNode = Create_nodo(node->info2, node->center, node->right);
        // Atualiza o nó atual para conter a nova informação como info1
        node->info1 = info;
        node->center = right_child; // Define o filho central
    }

    node->n_infos = 1; // Após a divisão, o nó original passa a ter apenas uma informação
    return largestNode; // Retorna o maior nó criado
}

// Função para adicionar uma nova informação a um nó que possui apenas uma informação
void add_info(TreeNode23 *node, Info info, TreeNode23 *right_child)
{
    // Caso a nova informação seja maior que info1
    if (info.num_start > node->info1.num_start)
    {
        node->info2 = info;         // Armazena a nova informação como info2
        node->right = right_child; // Define o filho direito
    }
    else
    {
        // Move info1 para info2 e ajusta os filhos
        node->info2 = node->info1;
        node->right = node->center;
        node->center = right_child;
        node->info1 = info; // Define a nova informação como info1
    }

    node->n_infos = 2; // Atualiza o número de informações no nó para 2
}

// Função para verificar se um nó é uma folha
int isLeaf(TreeNode23 node)
{
    return node.left == NULL; // Retorna verdadeiro (1) se o filho esquerdo for NULL
}

// Função para verificar se uma informação está em info1 do nó
int isInfo1(TreeNode23 node, int info)
{
    return info == node.info1.num_start; // Retorna verdadeiro se o valor for igual ao início de info1
}

// Função para verificar se uma informação está em info2 do nó
int isInfo2(TreeNode23 node, int info)
{
    return node.n_infos == 2 && info == node.info2.num_start; // Retorna verdadeiro se o nó possui info2 e o valor corresponde a ele
}

// Função para calcular a altura de uma subárvore
int height_size(TreeNode23 *node)
{
    int height = -1; // Inicializa a altura como -1 (árvore vazia)

    if (node != NULL) // Verifica se o nó não é nulo
        height = 1 + height_size(node->left); // Calcula a altura recursivamente no filho esquerdo

    return height; // Retorna a altura da subárvore
}


// Função para confirmar se a remoção é possível
int confirm_remove(TreeNode23 *root)
{
    int confirm = 0; // Inicializa a variável de confirmação como falsa

    if (root != NULL) // Verifica se o nó atual não é nulo
    {
        confirm = root->n_infos == 2; // Confirma se o nó possui duas informações

        if (!confirm) // Caso não tenha duas informações, verifica os filhos
        {
            confirm = confirm_remove(root->center); // Verifica recursivamente no filho central

            if (!confirm) // Se não confirmado, verifica recursivamente no filho à esquerda
                confirm = confirm_remove(root->left);
        }
    }

    return confirm; // Retorna o resultado da confirmação
}

// Função para mesclar um nó da árvore 2-3
TreeNode23 *no23_merge(TreeNode23 *leftChild, Info info, TreeNode23 *largestNode, TreeNode23 **root)
{
    add_info(leftChild, info, largestNode); // Adiciona a informação ao filho esquerdo, ajustando os filhos

    (*root)->n_infos--; // Reduz o número de informações do nó atual

    if ((*root)->n_infos == 0) // Se o nó ficar vazio, libera a memória
        free_nodo(root);

    return leftChild; // Retorna o nó esquerdo atualizado
}

// Função para obter a maior informação de um nó
Info *getMaxNodeInfo(TreeNode23 *root)
{
    // Retorna info2 se o nó tiver duas informações, caso contrário retorna info1
    return root->n_infos == 2 ? &(root->info2) : &(root->info1);
}

// Função para buscar um nó específico na árvore
TreeNode23 *Search_nodo(TreeNode23 *root, int info)
{
    TreeNode23 *node = NULL; // Inicializa o nó de retorno como NULL

    if (root != NULL) // Verifica se o nó atual não é nulo
    {
        // Verifica se a informação está presente no nó atual
        if (isInfo1(*root, info) || isInfo2(*root, info))
            node = root; // Define o nó atual como o nó encontrado
        else if (info < root->info1.num_start) // Busca no filho esquerdo
            node = Search_nodo(root->left, info);
        else if (root->n_infos == 1 || info < root->info2.num_start) // Busca no filho central
            node = Search_nodo(root->center, info);
        else // Busca no filho direito
            node = Search_nodo(root->right, info);
    }

    return node; // Retorna o nó encontrado ou NULL
}

// Função para encontrar o nó filho com o menor valor
TreeNode23 *Find_min_child_node(TreeNode23 *root, TreeNode23 **parentNode)
{
    TreeNode23 *childNode = root; // Inicializa o nó filho como o nó raiz

    while (!isLeaf(*childNode)) // Enquanto o nó não for uma folha
    {
        *parentNode = childNode; // Atualiza o nó pai
        childNode = childNode->left; // Move para o filho à esquerda
    }

    return childNode; // Retorna o menor nó encontrado
}

// Função para encontrar o nó filho com o maior valor
TreeNode23 *Find_largest_child_node(TreeNode23 *root, TreeNode23 **parentNode, Info **maior_valor)
{
    TreeNode23 *childNode = root; // Inicializa o nó filho como o nó raiz

    while (!isLeaf(*childNode)) // Enquanto o nó não for uma folha
    {
        *parentNode = childNode; // Atualiza o nó pai
        // Move para o filho central ou direito, dependendo do número de informações no nó
        if (childNode->n_infos == 1)
            childNode = childNode->center;
        else
            childNode = childNode->right;
    }

    if (childNode != NULL) // Verifica se o nó filho não é nulo
        *maior_valor = getMaxNodeInfo(childNode); // Obtém o maior valor do nó filho

    return childNode; // Retorna o maior nó encontrado
}


// Função para encontrar o nó pai de um nó que contém a informação especificada
TreeNode23 *Find_parent_node(TreeNode23 *root, int info)
{
    TreeNode23 *parentNode = NULL; // Inicializa o ponteiro para o nó pai como NULL

    if (root != NULL) // Verifica se o nó atual não é nulo
    {
        // Se o nó atual não contém a informação especificada
        if (!isInfo1(*root, info) && !isInfo2(*root, info))
        {
            // Busca recursivamente no filho correspondente
            if (info < root->info1.num_start)
                parentNode = Find_parent_node(root->left, info);
            else if (root->n_infos == 1 || info < root->info2.num_start)
                parentNode = Find_parent_node(root->center, info);
            else
                parentNode = Find_parent_node(root->right, info);

            // Caso nenhum nó filho contenha a informação, define o nó atual como pai
            if (parentNode == NULL)
                parentNode = root;
        }
    }

    return parentNode; // Retorna o nó pai encontrado ou NULL
}

// Função para encontrar o maior nó pai que contém a informação especificada
TreeNode23 *Find_max_parent_node(TreeNode23 *root, int info)
{
    TreeNode23 *parentNode = NULL; // Inicializa o ponteiro para o nó pai como NULL

    if (root != NULL)
    {
        // Se o nó atual não contém a informação especificada
        if (!isInfo1(*root, info) && !isInfo2(*root, info))
        {
            // Busca recursivamente no filho correspondente
            if (info < root->info1.num_start)
                parentNode = Find_max_parent_node(root->left, info);
            else if (root->n_infos == 1 || info < root->info2.num_start)
                parentNode = Find_max_parent_node(root->center, info);
            else
                parentNode = Find_max_parent_node(root->right, info);

            // Caso nenhum nó filho contenha a informação, verifica se o nó atual é um candidato válido
            if (parentNode == NULL && ((root->n_infos == 1 && root->info1.num_start > info) || 
                                       (root->n_infos == 2 && root->info2.num_start > info)))
                parentNode = root;
        }
    }

    return parentNode; // Retorna o maior nó pai encontrado ou NULL
}

// Função para encontrar o menor nó pai que contém a informação especificada
TreeNode23 *Find_smallest_parent_node(TreeNode23 *root, int info)
{
    TreeNode23 *parentNode = NULL; // Inicializa o ponteiro para o nó pai como NULL

    if (root != NULL)
    {
        // Se o nó atual não contém a informação especificada
        if (!isInfo1(*root, info) && !isInfo2(*root, info))
        {
            // Busca recursivamente no filho correspondente
            if (info < root->info1.num_start)
                parentNode = Find_smallest_parent_node(root->left, info);
            else if (root->n_infos == 1 || info < root->info2.num_start)
                parentNode = Find_smallest_parent_node(root->center, info);
            else
                parentNode = Find_smallest_parent_node(root->right, info);

            // Caso nenhum nó filho contenha a informação, verifica se o nó atual é um candidato válido
            if (parentNode == NULL && root->info1.num_start < info)
                parentNode = root;
        }
    }

    return parentNode; // Retorna o menor nó pai encontrado ou NULL
}

// Função para encontrar o menor nó pai que possui duas informações e contém a informação especificada
TreeNode23 *Find_smallest_parent_with_two_info(TreeNode23 *root, int info)
{
    TreeNode23 *parentNode = NULL; // Inicializa o ponteiro para o nó pai como NULL

    if (root != NULL)
    {
        // Se o nó atual não contém a informação especificada
        if (!isInfo1(*root, info) && !isInfo2(*root, info))
        {
            // Busca recursivamente no filho correspondente
            if (info < root->info1.num_start)
                parentNode = Find_smallest_parent_with_two_info(root->left, info);
            else if (root->n_infos == 1 || info < root->info2.num_start)
                parentNode = Find_smallest_parent_with_two_info(root->center, info);
            else
                parentNode = Find_smallest_parent_with_two_info(root->right, info);

            // Caso nenhum nó filho contenha a informação, verifica se o nó atual é um candidato válido
            if (parentNode == NULL && root->n_infos == 2 && root->info2.num_start < info)
                parentNode = root;
        }
    }

    return parentNode; // Retorna o menor nó pai com duas informações encontrado ou NULL
}

// Função para realizar um movimento de onda durante a remoção ou ajuste de nós
int wave_movement(Info exitInfo, Info *inputData, TreeNode23 *parentNode, TreeNode23 **sourceNode, TreeNode23 **root, TreeNode23 **largestNode, int (*remove_node)(TreeNode23 **, int, TreeNode23 *, TreeNode23 **, TreeNode23 **))
{
    // Remove o nó utilizando a função de remoção fornecida
    int isNodeRemoved = remove_node(root, exitInfo.num_start, parentNode, sourceNode, largestNode);

    // Atualiza os dados de entrada com as informações removidas
    *inputData = exitInfo;

    return isNodeRemoved; // Retorna o status da remoção
}

// Função para liberar a memória de todos os nós da árvore 2-3
void TreeNode23_cleanup(TreeNode23 **root)
{
    if (*root != NULL) // Verifica se o nó atual não é nulo
    {
        TreeNode23_cleanup(&((*root)->left));   // Limpa recursivamente o filho à esquerda
        TreeNode23_cleanup(&((*root)->center)); // Limpa recursivamente o filho central

        if ((*root)->n_infos == 2) // Se o nó possui dois blocos de informações
            TreeNode23_cleanup(&((*root)->right)); // Limpa recursivamente o filho à direita

        free_nodo(root); // Libera o nó atual
    }
}


// Insere um novo nó na árvore 2-3
TreeNode23 *TreeNode23_insertNode(TreeNode23 **root, Info info, TreeNode23 *parentNode, Info *up)
{
    TreeNode23 *largestNode = NULL; // Inicializa o maior nó como NULL

    if (*root == NULL) // Caso a raiz seja nula (árvore vazia)
        *root = Create_nodo(info, NULL, NULL); // Cria o primeiro nó da árvore
    else
    {
        if (isLeaf(**root)) // Verifica se o nó atual é uma folha
        {
            if ((*root)->n_infos == 1) // Caso o nó tenha apenas uma informação
                add_info(*root, info, NULL); // Adiciona a nova informação no nó
            else // Caso o nó esteja cheio (duas informações)
            {
                largestNode = SplitNode(*root, info, up, NULL); // Divide o nó em dois
                if (parentNode == NULL) // Se não houver nó pai, cria um novo nó raiz
                {
                    *root = Create_nodo(*up, *root, largestNode); // Promove a informação para a raiz
                    largestNode = NULL; // Limpa o maior nó
                }
            }
        }
        else // Caso o nó não seja uma folha
        {
            // Decide qual filho será explorado com base no valor da nova informação
            if (info.num_start < (*root)->info1.num_start)
                largestNode = TreeNode23_insertNode(&((*root)->left), info, *root, up);
            else if ((*root)->n_infos == 1 || info.num_start < (*root)->info2.num_start)
                largestNode = TreeNode23_insertNode(&((*root)->center), info, *root, up);
            else
                largestNode = TreeNode23_insertNode(&((*root)->right), info, *root, up);

            // Caso haja um maior nó resultante da operação
            if (largestNode != NULL)
            {
                if ((*root)->n_infos == 1) // Se o nó atual tiver apenas uma informação
                {
                    add_info(*root, *up, largestNode); // Adiciona a informação ao nó atual
                    largestNode = NULL; // Limpa o maior nó
                }
                else // Caso o nó atual já esteja cheio
                {
                    Info promove_aux;
                    largestNode = SplitNode(*root, *up, &promove_aux, largestNode); // Divide o nó
                    *up = promove_aux; // Atualiza a informação promovida
                    if (parentNode == NULL) // Caso não haja nó pai
                    {
                        *root = Create_nodo(promove_aux, *root, largestNode); // Cria um novo nó raiz
                        largestNode = NULL; // Limpa o maior nó
                    }
                }
            }
        }
    }

    return largestNode; // Retorna o maior nó criado ou NULL
}

// Insere uma nova informação na árvore 2-3
TreeNode23 *TreeNode23_insert(TreeNode23 **root, Info info)
{
    Info up; // Variável para armazenar a informação promovida
    return TreeNode23_insertNode(root, info, NULL, &up); // Chama a função auxiliar de inserção
}

// Realiza o balanceamento da árvore 2-3 após uma operação
int balanceTree(TreeNode23 **root, TreeNode23 *leftChild, TreeNode23 **filho2, Info info, TreeNode23 **largestNode)
{
    int isBalanced = 0; // Inicializa o status de balanceamento como não balanceado

    if (*filho2 == NULL || (*filho2)->n_infos == 0) // Verifica se o filho 2 está vazio ou não possui informações
    {
        if (*filho2 != NULL) // Libera o filho 2 se ele for inválido
            free_nodo(filho2);

        *largestNode = no23_merge(leftChild, info, *largestNode, root); // Mescla os nós
        isBalanced = 1; // Marca a árvore como balanceada
    }

    return isBalanced; // Retorna o status de balanceamento
}

// Ajusta o balanceamento da árvore 2-3 após uma remoção
int TreeNode23_adjustBalance(TreeNode23 **root, int info, TreeNode23 **largestNode)
{
    int isBalanced = 0; // Inicializa o status de balanceamento como não balanceado

    if (*root != NULL) // Verifica se o nó atual não é nulo
    {
        if (!isLeaf(**root)) // Verifica se o nó atual não é uma folha
        {
            // Decide qual filho será ajustado com base na informação fornecida
            if (info < (*root)->info1.num_start)
                isBalanced = TreeNode23_adjustBalance(&((*root)->left), info, largestNode);
            else if ((*root)->n_infos == 1 || info < (*root)->info2.num_start)
            {
                if ((*root)->left->n_infos == 2 && !confirm_remove((*root)->center))
                    isBalanced = -1; // Indica desbalanceamento
                else
                    isBalanced = TreeNode23_adjustBalance(&((*root)->center), info, largestNode);
            }
            else
            {
                if ((*root)->center->n_infos == 2 && !confirm_remove((*root)->right))
                    isBalanced = -1; // Indica desbalanceamento
                else
                    isBalanced = TreeNode23_adjustBalance(&((*root)->right), info, largestNode);
            }

            // Realiza o balanceamento, se necessário
            if (isBalanced != -1)
            {
                if ((*root)->n_infos == 1)
                    isBalanced = balanceTree(root, (*root)->left, &((*root)->center), (*root)->info1, largestNode);
                else if ((*root)->n_infos == 2)
                    isBalanced = balanceTree(root, (*root)->center, &((*root)->right), (*root)->info2, largestNode);
            }
        }
    }

    return isBalanced; // Retorna o status de balanceamento
}

// Exibe informações detalhadas de um nó
void showNodeInfo23(Info node)
{
    if (node.num_start > node.num_end) // Verifica se o intervalo do nó é inválido
    {
        printf("Erro: Intervalo invalido no no [%d] até [%d].\n", node.num_start, node.num_end);
        return;
    }

    // Exibe informações detalhadas sobre o bloco
    printf("Bloco de [%d] até [%d] - Status: %s\n",
           node.num_start,
           node.num_end,
           node.status == ALLOCATED_STATUS_FREE ? "Livre" : node.status == STATUS_OCCUPIED ? "Ocupado" : "Desconhecido");

    printf("Informacoes adicionais:\n");
    printf("  Inicio: %d\n", node.num_start);
    printf("  Fim: %d\n", node.num_end);
    printf("  Status: %s\n", node.status == ALLOCATED_STATUS_FREE ? "Livre" : node.status == STATUS_OCCUPIED ? "Ocupado" : "Desconhecido");

    if (node.status != ALLOCATED_STATUS_FREE && node.status != STATUS_OCCUPIED)
    {
        printf("  Aviso: Status desconhecido encontrado no no\n");
    }
}

// Percorre e imprime a árvore 2-3 em ordem
void TreeNode23_print_in_order(TreeNode23 *root)
{
    if (root != NULL)
    {
        TreeNode23_print_in_order(root->left); // Percorre o lado esquerdo
        printf("[1º] ");
        showNodeInfo23(root->info1); // Exibe informações do primeiro bloco
        TreeNode23_print_in_order(root->center); // Percorre o centro

        if (root->n_infos == 2) // Caso o nó possua dois blocos
        {
            printf("[2º] ");
            showNodeInfo23(root->info2); // Exibe informações do segundo bloco
            TreeNode23_print_in_order(root->right); // Percorre o lado direito
        }
    }
}



