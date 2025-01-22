#include <stdio.h>
#include <stdlib.h>
#include "23.h"

int initialize_memory_blocks(TreeNode23 **memory_structure, int max_capacity)
{
    int current_state; // Estado inicial do bloco (disponível ou ocupado)

    // Configuração do estado inicial do bloco
    do {
        printf("\n=== Configuração do Bloco Inicial ===\n");
        printf("Escolha o estado do bloco inicial:\n");
        printf("%d -> Disponível\n", ALLOCATED_STATUS_FREE);
        printf("%d -> Ocupado\n", STATUS_OCCUPIED);
        printf("Digite sua escolha: ");
        scanf("%d", &current_state);
        while (getchar() != '\n'); // Limpa o buffer de entrada
        if (current_state != ALLOCATED_STATUS_FREE && current_state != STATUS_OCCUPIED) {
            printf("\n[Erro] Escolha inválida. Por favor, tente novamente.\n");
        }
    } while (current_state != ALLOCATED_STATUS_FREE && current_state != STATUS_OCCUPIED);

    Info infoBlock; // Estrutura para armazenar as informações do bloco
    printf("\n=== Inicialização dos Blocos ===\n");
    printf("Para finalizar digite 1048575 como endereço final.\n");

    // Define o endereço inicial do primeiro bloco
    do {
        printf("\n>>> Insira o endereço inicial do infoBlock: ");
        scanf("%d", &infoBlock.num_start);
        while (getchar() != '\n');
        if (infoBlock.num_start < 0 || infoBlock.num_start >= max_capacity) {
            printf("\n[Erro] O endereço inicial deve estar entre 0 e %d.\n", max_capacity - 1);
        }
    } while (infoBlock.num_start < 0 || infoBlock.num_start >= max_capacity);

    int endereco_minimo = infoBlock.num_start; // Salva o menor endereço inicial

    // Inicializa os blocos de memória na árvore 2-3
    do {
        infoBlock.status = current_state; // Define o estado atual do bloco

        // Define o endereço final do bloco
        do {
            printf("\n>>> Insira o endereço final do infoBlock (deve ser >= %d): ", infoBlock.num_start);
            scanf("%d", &infoBlock.num_end);
            while (getchar() != '\n');
            if (infoBlock.num_end < infoBlock.num_start || infoBlock.num_end >= max_capacity) {
                printf("\n[Erro] O endereço final deve estar entre %d e %d.\n", infoBlock.num_start, max_capacity - 1);
            }
        } while (infoBlock.num_end < infoBlock.num_start || infoBlock.num_end >= max_capacity);

        // Insere o bloco na estrutura de memória (árvore 2-3)
        TreeNode23_insert(memory_structure, infoBlock);

        // Atualiza o início do próximo bloco e alterna o estado
        infoBlock.num_start = infoBlock.num_end + 1;
        current_state = !current_state;
    } while (infoBlock.num_end < (max_capacity - 1));

    printf("\n[Sucesso] Blocos inicializados com sucesso!\n");
    return endereco_minimo; // Retorna o menor endereço inicial
}

void merge_no(TreeNode23 **root, int *num_end, int limite, int valor_remover)
{
    *num_end = limite; // Atualiza o endereço final para o limite
    TreeNode23_remove(root, valor_remover); // Remove o valor especificado da árvore
}


TreeNode23 *find_smallest_block(TreeNode23 **treeRoot, TreeNode23 *nodo, Info *data_info, Info **minimum_value)
{
    TreeNode23 *smallest_block, *temporary_parent;
    *minimum_value = NULL; // Inicializa o ponteiro para o menor valor como NULL

    if (isLeaf(*nodo)) // Se o nó atual é uma folha
    {
        if (nodo->info1.num_start != data_info->num_start) {
            smallest_block = nodo; // Define o nó atual como o menor bloco
        } else {
            smallest_block = Find_smallest_parent_node(*treeRoot, data_info->num_start); // Encontra o menor nó pai
        }

        if (smallest_block != NULL) // Verifica se encontrou um bloco válido
        {
            if (smallest_block->n_infos == 2 && smallest_block->info2.num_start < data_info->num_start) {
                *minimum_value = &(smallest_block->info2); // Define o menor valor como info2
            } else {
                *minimum_value = &(smallest_block->info1); // Define o menor valor como info1
            }
        }
    }
    else if (nodo->info1.num_start == data_info->num_start) {
        smallest_block = Find_largest_child_node(nodo->left, &temporary_parent, minimum_value); // Busca o maior filho à esquerda
    } else {
        smallest_block = Find_largest_child_node(nodo->center, &temporary_parent, minimum_value); // Busca o maior filho no centro
    }

    return smallest_block; // Retorna o menor bloco encontrado
}


TreeNode23 *find_largest_block(TreeNode23 **treeRoot, TreeNode23 *nodo, Info *data_info, Info **largest_value_pointer)
{
    TreeNode23 *largest_block, *temporary_parent;
    *largest_value_pointer = NULL; // Inicializa o ponteiro para o maior valor como NULL

    if (isLeaf(*nodo)) // Se o nó atual é uma folha
    {
        if (nodo->n_infos == 2 && nodo->info1.num_start == data_info->num_start) {
            largest_block = nodo; // Define o nó atual como o maior bloco
        } else {
            largest_block = Find_max_parent_node(*treeRoot, data_info->num_start); // Encontra o maior nó pai
        }

        if (largest_block != NULL) // Verifica se encontrou um bloco válido
        {
            if (largest_block->info1.num_start > data_info->num_start) {
                *largest_value_pointer = &(largest_block->info1); // Define o maior valor como info1
            } else {
                *largest_value_pointer = &(largest_block->info2); // Define o maior valor como info2
            }
        }
    }
    else // Caso o nó atual não seja folha
    {
        if (nodo->info1.num_start == data_info->num_start) {
            largest_block = Find_min_child_node(nodo->center, &temporary_parent); // Busca o menor filho no centro
        } else {
            largest_block = Find_min_child_node(nodo->right, &temporary_parent); // Busca o menor filho à direita
        }

        if (largest_block != NULL) {
            *largest_value_pointer = &(largest_block->info1); // Define o maior valor como info1
        }
    }

    return largest_block; // Retorna o maior bloco encontrado
}

void adjust_node_in_tree(TreeNode23 **treeRoot, TreeNode23 *current_node, Info *current_info, int size)
{
    TreeNode23 *smallest_block;
    Info *smallest_data = NULL;

    // Encontra o menor bloco associado ao nó atual
    smallest_block = find_smallest_block(treeRoot, current_node, current_info, &smallest_data);

    // Caso o tamanho desejado seja menor que o espaço disponível no bloco atual
    if (size < (current_info->num_end - current_info->num_start + 1)) {
        if (smallest_block == NULL) { // Caso não haja um bloco menor disponível
            Info novo_dado;
            // Cria um novo bloco com o tamanho especificado
            novo_dado.num_start = current_info->num_start;
            novo_dado.num_end = current_info->num_start + size - 1;
            novo_dado.status = !(current_info->status); // Alterna o status do bloco

            current_info->num_start += size; // Ajusta o início do bloco atual
            TreeNode23_insert(treeRoot, novo_dado); // Insere o novo bloco na árvore
        } else {
            // Ajusta o tamanho do menor bloco e do bloco atual
            smallest_data->num_end += size;
            current_info->num_start += size;
        }
    } else { // Caso o tamanho desejado seja maior ou igual ao espaço disponível
        TreeNode23 *largest_block;
        Info *largest_item = NULL;

        // Encontra o maior bloco associado ao nó atual
        largest_block = find_largest_block(treeRoot, current_node, current_info, &largest_item);

        // Caso não haja blocos menores ou maiores disponíveis
        if (smallest_block == NULL && largest_block == NULL) {
            current_info->status = !(current_info->status); // Alterna o status do bloco atual
        } else {
            if (smallest_block == NULL) { // Caso não haja blocos menores disponíveis
                current_info->status = !(current_info->status); // Alterna o status
                // Mescla o bloco atual com o maior bloco
                merge_no(treeRoot, &(current_info->num_end), largest_item->num_end, largest_item->num_start);
            } else if (largest_block == NULL) { // Caso não haja blocos maiores disponíveis
                // Mescla o menor bloco com o bloco atual
                merge_no(treeRoot, &(smallest_data->num_end), current_info->num_end, current_info->num_start);
            } else { // Caso existam blocos menores e maiores disponíveis
                int remover_endereco = largest_item->num_start; // Salva o endereço do maior bloco
                // Mescla o menor bloco com o maior bloco
                merge_no(treeRoot, &(smallest_data->num_end), largest_item->num_end, current_info->num_start);
                TreeNode23_remove(treeRoot, remover_endereco); // Remove o maior bloco da árvore
            }
        }
    }
}

TreeNode23 *search_node(TreeNode23 **treeRoot, int quantity, int status, Info **selected_info)
{
    TreeNode23 *node;

    if (*treeRoot != NULL) { // Verifica se a árvore não está vazia
        // Busca recursivamente no lado esquerdo da árvore
        node = search_node(&((*treeRoot)->left), quantity, status, selected_info);

        if (*selected_info == NULL) { // Verifica se o bloco já foi encontrado
            // Verifica o primeiro bloco de informações no nó atual
            if ((*treeRoot)->info1.status == status &&
                ((*treeRoot)->info1.num_end - (*treeRoot)->info1.num_start + 1) >= quantity) {
                *selected_info = &((*treeRoot)->info1); // Define o bloco selecionado
                node = *treeRoot; // Salva o nó atual
            } else {
                // Busca recursivamente no centro da árvore
                node = search_node(&((*treeRoot)->center), quantity, status, selected_info);

                if ((*treeRoot)->n_infos == 2) { // Caso o nó tenha dois blocos de informações
                    // Verifica o segundo bloco de informações
                    if ((*treeRoot)->info2.status == status &&
                        ((*treeRoot)->info2.num_end - (*treeRoot)->info2.num_start + 1) >= quantity) {
                        *selected_info = &((*treeRoot)->info2); // Define o bloco selecionado
                        node = *treeRoot; // Salva o nó atual
                    } else if (*selected_info == NULL) {
                        // Busca recursivamente no lado direito da árvore
                        node = search_node(&((*treeRoot)->right), quantity, status, selected_info);
                    }
                }
            }
        }
    } else {
        *selected_info = NULL; // Define o bloco selecionado como nulo se não encontrar
    }

    return node; // Retorna o nó encontrado ou NULL
}

int manage_memory_block(TreeNode23 **treeRoot, int size, int estado_atual)
{
    Info *target_block = NULL; // Bloco alvo para a operação
    // Procura um nó que atenda aos critérios de tamanho e estado
    TreeNode23 *nodo_alvo = search_node(treeRoot, size, estado_atual, &target_block);

    if (target_block != NULL) { // Verifica se um bloco foi encontrado
        printf("\nDetalhes do infoBlock selecionado:\n");
        showNodeInfo23(*target_block); // Exibe informações do bloco encontrado
        adjust_node_in_tree(treeRoot, nodo_alvo, target_block, size); // Ajusta o nó na árvore
    } else {
        // Exibe mensagem caso nenhum bloco atenda aos critérios
        printf("\nNão foram encontrados blocos disponíveis com o critério especificado.\n");
    }

    return 1; // Retorna sucesso
}


