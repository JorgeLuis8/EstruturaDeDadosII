#include <stdio.h>
#include <stdlib.h>
#include "23.h"

int TreeNode23_remove_internal_node(TreeNode23 **treeSource, TreeNode23 *root, Info *info, TreeNode23 *leftChild, TreeNode23 *rightChild, TreeNode23 **maxNode)
{
    int isRemoved;                     // Flag para indicar se o nó foi removido com sucesso
    TreeNode23 *childNode, *parentNode; // Ponteiros auxiliares para o nó filho e pai
    Info *child_info;                  // Informação associada ao nó filho

    parentNode = root; // Define o nó atual como o nó pai

    // Encontra o maior nó na subárvore esquerda
    childNode = Find_largest_child_node(leftChild, &parentNode, &child_info);

    if (childNode->n_infos == 2) // Caso o nó filho tenha duas informações
    {
        *info = *child_info;       // Copia a informação do nó filho para o nó pai
        childNode->n_infos = 1;    // Reduz a quantidade de informações do nó filho para 1
    }
    else // Caso o nó filho tenha apenas uma informação
    {
        // Busca o menor nó na subárvore direita e realiza o movimento de onda
        childNode = Find_min_child_node(rightChild, &parentNode);
        isRemoved = wave_movement(childNode->info1, info, parentNode, treeSource, &childNode, maxNode, RemoveNodeFrom23Tree);
    }

    return isRemoved; // Retorna o status da remoção
}


int TreeNode23_delete_internal_node(TreeNode23 **treeSource, TreeNode23 *root, Info *info, TreeNode23 *leftChild, TreeNode23 *rightChild, TreeNode23 **maxNode)
{
    int isRemoved;                     // Flag para indicar se o nó foi removido com sucesso
    TreeNode23 *childNode, *parentNode; // Ponteiros auxiliares para o nó filho e pai
    Info *child_info;                  // Informação associada ao nó filho

    parentNode = root; // Define o nó atual como o nó pai

    // Encontra o menor nó na subárvore esquerda
    childNode = Find_min_child_node(leftChild, &parentNode);

    if (childNode->n_infos == 2) // Caso o nó filho tenha duas informações
    {
        *info = childNode->info1;       // Copia a primeira informação do nó filho para o nó pai
        childNode->info1 = childNode->info2; // Move a segunda informação para a primeira posição
        childNode->n_infos = 1;         // Reduz a quantidade de informações do nó filho para 1
    }
    else // Caso o nó filho tenha apenas uma informação
    {
        // Busca o maior nó na subárvore direita e realiza o movimento de onda
        childNode = Find_largest_child_node(rightChild, &parentNode, &child_info);
        isRemoved = wave_movement(*child_info, info, parentNode, treeSource, &childNode, maxNode, TreeNode23_Delete);
    }

    return isRemoved; // Retorna o status da remoção
}


int RemoveNodeFrom23Tree(TreeNode23 **root, int info, TreeNode23 *parentNode, TreeNode23 **treeSource, TreeNode23 **maxNode)
{
    int isRemoved = 0; // Flag para indicar se o nó foi removido

    if (*root != NULL) // Verifica se o nó atual não é nulo
    {
        int info1 = isInfo1(**root, info); // Verifica se a informação está na primeira posição
        int info2 = isInfo2(**root, info); // Verifica se a informação está na segunda posição

        if (info1 || info2) // Se a informação está no nó atual
        {
            isRemoved = 1; // Marca que a remoção foi realizada
            if (isLeaf(**root)) // Se o nó é uma folha
            {
                if ((*root)->n_infos == 2) // Caso o nó tenha duas informações
                {
                    if (info1)
                        (*root)->info1 = (*root)->info2; // Move a segunda informação para a primeira posição

                    (*root)->n_infos = 1; // Reduz a quantidade de informações do nó para 1
                }
                else // Caso o nó tenha apenas uma informação
                {
                    if (parentNode == NULL) // Se não há nó pai
                        free_nodo(root);    // Libera o nó atual
                    else
                    {
                        TreeNode23 *parent_node_aux; // Nó auxiliar para o pai
                        Info parent_info;

                        // Verifica qual filho do nó pai está sendo removido
                        if (*root == parentNode->left || (parentNode->n_infos == 2 && *root == parentNode->center))
                        {
                            parent_node_aux = Find_parent_node(*treeSource, parentNode->info1.num_start);

                            if (*root == parentNode->left)
                                parent_info = parentNode->info1;
                            else
                                parent_info = parentNode->info2;

                            isRemoved = wave_movement(parent_info, &((*root)->info1), parent_node_aux, treeSource, &parentNode, maxNode, RemoveNodeFrom23Tree);
                        }
                        else
                        {
                            parent_node_aux = Find_max_parent_node(*treeSource, (*root)->info1.num_start);

                            TreeNode23 *smaller_parent = Find_smallest_parent_with_two_info(*treeSource, (*root)->info1.num_start);

                            if (parent_node_aux != NULL)
                            {
                                if (parent_node_aux->info1.num_start > (*root)->info1.num_start)
                                    parent_info = parent_node_aux->info1;
                                else
                                    parent_info = parent_node_aux->info2;
                            }

                            int height_of_smaller_parent = height_size(smaller_parent);
                            int parent_node_height = height_size(parent_node_aux);

                            if (parent_node_aux == NULL || (parent_node_aux != parentNode && smaller_parent != NULL && height_of_smaller_parent <= parent_node_height && parent_info.num_start > smaller_parent->info2.num_start))
                            {
                                *maxNode = parentNode; // Define o nó máximo como o nó pai
                                (*root)->n_infos = 0; // Remove todas as informações do nó
                                isRemoved = -1; // Indica que a remoção foi finalizada
                            }
                            else
                            {
                                TreeNode23 *avo = Find_parent_node(*treeSource, parent_info.num_start); // Encontra o avô do nó atual
                                isRemoved = wave_movement(parent_info, &((*root)->info1), avo, treeSource, &parent_node_aux, maxNode, RemoveNodeFrom23Tree);
                            }
                        }
                    }
                }
            }
            else if (info2) // Se a informação está na segunda posição
                isRemoved = TreeNode23_remove_internal_node(treeSource, *root, &((*root)->info2), (*root)->center, (*root)->right, maxNode);
            else if (info1) // Se a informação está na primeira posição
                isRemoved = TreeNode23_remove_internal_node(treeSource, *root, &((*root)->info1), (*root)->left, (*root)->center, maxNode);
        }
        else // Caso a informação não esteja no nó atual, continua a busca recursivamente
        {
            if (info < (*root)->info1.num_start)
                isRemoved = RemoveNodeFrom23Tree(&(*root)->left, info, *root, treeSource, maxNode);
            else if ((*root)->n_infos == 1 || info < (*root)->info2.num_start)
                isRemoved = RemoveNodeFrom23Tree(&(*root)->center, info, *root, treeSource, maxNode);
            else
                isRemoved = RemoveNodeFrom23Tree(&(*root)->right, info, *root, treeSource, maxNode);
        }
    }
    return isRemoved; // Retorna o status da remoção
}


int TreeNode23_Delete(TreeNode23 **root, int info, TreeNode23 *parentNode, TreeNode23 **treeSource, TreeNode23 **maxNode)
{
    int isRemoved = 0; // Flag para indicar se o nó foi removido com sucesso

    if (*root != NULL) // Verifica se o nó atual não é nulo
    {
        // Verifica se o valor a ser removido está no nó atual
        int info1 = isInfo1(**root, info);
        int info2 = isInfo2(**root, info);

        if (info1 || info2) // Se o valor foi encontrado no nó atual
        {
            isRemoved = 1; // Marca que o valor foi removido
            if (isLeaf(**root)) // Se o nó é uma folha
            {
                if ((*root)->n_infos == 2) // Caso o nó tenha duas informações
                {
                    if (info1)
                        (*root)->info1 = (*root)->info2; // Move a segunda informação para a primeira posição

                    (*root)->n_infos = 1; // Reduz o número de informações no nó para 1
                }
                else // Caso o nó tenha apenas uma informação
                {
                    if (parentNode == NULL) // Se o nó não possui pai (é a raiz)
                        free_nodo(root); // Libera o nó atual
                    else // Caso contrário, ajusta o balanceamento da árvore
                    {
                        TreeNode23 *parent_node_aux;
                        Info parent_info;

                        // Identifica o nó pai e ajusta o balanceamento dependendo do filho removido
                        if (*root == parentNode->center || (parentNode->n_infos == 2 && *root == parentNode->right))
                        {
                            parent_node_aux = Find_parent_node(*treeSource, parentNode->info1.num_start);

                            if (*root == parentNode->center)
                                parent_info = parentNode->info1;
                            else
                                parent_info = parentNode->info2;

                            isRemoved = wave_movement(parent_info, &((*root)->info1), parent_node_aux, treeSource, &parentNode, maxNode, TreeNode23_Delete);
                        }
                        else
                        {
                            parent_node_aux = Find_smallest_parent_node(*treeSource, (*root)->info1.num_start);
                            TreeNode23 *smaller_parent = Find_smallest_parent_with_two_info(*treeSource, (*root)->info1.num_start);
                            TreeNode23 *avo;

                            if (parent_node_aux == NULL || (parent_node_aux != parentNode && smaller_parent != NULL))
                            {
                                isRemoved = -1;
                                *maxNode = parentNode;
                            }
                            else
                            {
                                if (parent_node_aux->n_infos == 2 && parent_node_aux->info2.num_start < (*root)->info1.num_start)
                                    parent_info = parent_node_aux->info2;
                                else
                                    parent_info = parent_node_aux->info1;

                                avo = Find_parent_node(*treeSource, parent_info.num_start);
                                isRemoved = wave_movement(parent_info, &((*root)->info1), avo, treeSource, &parent_node_aux, maxNode, TreeNode23_Delete);
                            }
                        }
                    }
                }
            }
            else if (info2) // Caso o valor esteja na segunda posição
                isRemoved = TreeNode23_delete_internal_node(treeSource, *root, &((*root)->info2), (*root)->right, (*root)->center, maxNode);
            else if (info1) // Caso o valor esteja na primeira posição
                isRemoved = TreeNode23_delete_internal_node(treeSource, *root, &((*root)->info1), (*root)->center, (*root)->left, maxNode);
        }
        else // Caso o valor não esteja no nó atual
        {
            // Navega recursivamente para encontrar o valor na subárvore correta
            if (info < (*root)->info1.num_start)
                isRemoved = TreeNode23_Delete(&(*root)->left, info, *root, treeSource, maxNode);
            else if ((*root)->n_infos == 1 || info < (*root)->info2.num_start)
                isRemoved = TreeNode23_Delete(&(*root)->center, info, *root, treeSource, maxNode);
            else
                isRemoved = TreeNode23_Delete(&(*root)->right, info, *root, treeSource, maxNode);
        }
    }
    return isRemoved; // Retorna o status da remoção
}

int TreeNode23_remove(TreeNode23 **root, int info)
{
    TreeNode23 *maxNode, *junction_position;
    int isRemoved = RemoveNodeFrom23Tree(root, info, NULL, root, &junction_position);

    if (isRemoved == -1) // Caso a remoção tenha causado um desbalanceamento
    {
        isRemoved = 1; // Marca a remoção como bem-sucedida
        Info junction_value = *(getMaxNodeInfo(junction_position)); // Obtém o maior valor no nó de junção
        maxNode = NULL;

        // Ajusta o balanceamento da árvore
        int adjusted_balance_status = TreeNode23_adjustBalance(root, junction_value.num_start, &maxNode);

        if (adjusted_balance_status == -1) // Caso o balanceamento falhe
        {
            TreeNode23 *parentNode;
            Info *enterAux;
            parentNode = Find_parent_node(*root, junction_value.num_start);

            if (isInfo1(*junction_position, junction_value.num_start))
                enterAux = &(junction_position->center->info1); // Ajusta o ponteiro auxiliar
            else
                enterAux = &(junction_position->right->info1);

            adjusted_balance_status = wave_movement(junction_value, enterAux, parentNode, root, &junction_position, &junction_position, TreeNode23_Delete);

            if (adjusted_balance_status == -1) // Caso o ajuste falhe novamente
            {
                junction_value = junction_position->info1;
                parentNode = Find_parent_node(*root, junction_value.num_start);
                adjusted_balance_status = wave_movement(junction_value, &(junction_position->left->info1), parentNode, root, &junction_position, &junction_position, RemoveNodeFrom23Tree);

                junction_value = *(getMaxNodeInfo(junction_position)); // Obtém o maior valor atualizado
                maxNode = NULL;
                adjusted_balance_status = TreeNode23_adjustBalance(root, junction_value.num_start, &maxNode);
            }
        }

        // Se a raiz foi removida, redefine a raiz para o nó máximo
        if (*root == NULL)
            *root = maxNode;
    }

    return isRemoved; // Retorna o status da remoção
}
