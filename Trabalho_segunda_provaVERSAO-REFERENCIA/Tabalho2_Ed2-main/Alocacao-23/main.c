#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "arv-23.c" // Inclui a implementacao da arvore 2-3

#define MEMORY_SIZE (1024 * 1024) // Tamanho total da memoria (1MB por bloco)

// Funcao para cadastrar os nos da arvore
void cadastrar_nos(Memory **root)
{
    int start = 0, end, status;

    // Cadastro do primeiro no
    printf("Informe o status do primeiro no (1 para Livre, 0 para Ocupado): ");
    scanf("%d", &status);

    printf("Informe o endereco inicial do primeiro no: ");
    scanf("%d", &start);

    printf("Informe o endereco final do primeiro no (maximo %d): ", MEMORY_SIZE);
    scanf("%d", &end);

    if (end < start || end > MEMORY_SIZE)
    {
        printf("Endereco final invalido. O programa sera encerrado.\n");
        return;
    }

    // Criar o primeiro no
    Info *info = CreateInfo(start, end, status);
    if (!info)
    {
        printf("Erro ao alocar memoria para o no inicial.\n");
        return;
    }

    *root = createNode(info, NULL, NULL);
    if (!*root)
    {
        printf("Erro ao criar o no inicial.\n");
        free(info);
        return;
    }

    // Cadastro dos nos subsequentes
    while (end < MEMORY_SIZE)
    {
        start = end + 1; // Proximo bloco comeca logo apos o final do anterior
        printf("Informe o endereco final do proximo no (maximo %d para terminar): ", MEMORY_SIZE);
        scanf("%d", &end);

        if (end < start || end > MEMORY_SIZE)
        {
            printf("Endereco final invalido.\n");
            int escolha;
            printf("Deseja tentar novamente (1) ou voltar ao menu principal (2)? ");
            scanf("%d", &escolha);
            if (escolha == 2)
            {
                break; // Voltar ao menu principal
            }
            else
            {
                continue; // Tentar novamente
            }
        }

        // Alternar status entre Livre e Ocupado
        status = (status == FREE) ? OCCUPIED : FREE;

        // Criar o novo no
        info = CreateInfo(start, end, status);
        if (!info)
        {
            printf("Erro ao alocar memoria para o proximo no.\n");
            break;
        }

        // Inserir na arvore 2-3
        int flag = 0;
        Insert23(root, NULL, NULL, start, end, status, &flag);
        if (!flag)
        {
            printf("Erro ao inserir no na arvore.\n");
            free(info);
            break;
        }

        if (end == MEMORY_SIZE)
        {
            printf("Cadastro de nos concluido.\n");
            break;
        }
    }
}
void concatenar_nos(Memory **root)
{
    if (!root || !(*root))
        return;

    Memory *node = *root;

    // Se o nó é folha, tenta concatenar os blocos adjacentes
    if (isLeaf(node))
    {
        if (node->numKeys == 2)
        {
            // Se os dois blocos possuem o mesmo status, concatenar
            if (node->info1->status == node->info2->status)
            {
                node->info1->end = node->info2->end; // Atualiza o final do primeiro bloco
                free(node->info2);                   // Libera o segundo bloco
                node->info2 = NULL;                  // Remove o segundo bloco
                node->numKeys = 1;                   // Atualiza o número de chaves
            }
        }
    }
    else
    {
        // Recursivamente aplica a concatenação nos filhos
        concatenar_nos(&node->left);
        concatenar_nos(&node->center);

        if (node->numKeys == 2)
        {
            concatenar_nos(&node->right);
        }
    }
}

void alocar_blocos(Memory **root, int quantidade_blocos)
{
    Memory *node = NULL;
    Info *targetInfo = NULL;

    if (root && *root)
    {
        // Buscar um nó que tenha espaço suficiente
        node = FindSpace(*root, quantidade_blocos);

        if (node)
        {
            // Determinar qual bloco será alocado
            if (node->info1->status == FREE && (node->info1->end - node->info1->start + 1) >= quantidade_blocos)
            {
                targetInfo = node->info1;
            }
            else if (node->numKeys == 2 && node->info2->status == FREE &&
                     (node->info2->end - node->info2->start + 1) >= quantidade_blocos)
            {
                targetInfo = node->info2;
            }

            if (targetInfo)
            {
                // Atualizar o bloco encontrado
                int espacoDisponivel = targetInfo->end - targetInfo->start + 1;
                if (espacoDisponivel > quantidade_blocos)
                {
                    int novo_inicio = targetInfo->start + quantidade_blocos;

                    // Criar novo bloco livre para o espaço restante
                    Info *novo_info = CreateInfo(novo_inicio, targetInfo->end, FREE);
                    targetInfo->end = novo_inicio - 1;

                    // Inserir novo bloco na árvore
                    int flag = 0;
                    Insert23(root, NULL, NULL, novo_info->start, novo_info->end, FREE, &flag);
                }

                // Alterar o status para ocupado
                targetInfo->status = OCCUPIED;

                printf("Blocos alocados: Inicio = %d, Fim = %d\n", targetInfo->start, targetInfo->end);

                // Concatenar nós adjacentes
                concatenar_nos(root);
            }
            else
            {
                printf("Erro interno: Nao foi possivel encontrar um bloco adequado.\n");
            }
        }
        else
        {
            printf("Erro: Nao ha blocos livres suficientes para alocar.\n");
        }
    }
    else
    {
        printf("Erro: Nenhuma memoria cadastrada.\n");
    }
}
void liberar_blocos(Memory **root, int inicio, int quantidade_blocos)
{
    if (!root || !(*root))
    {
        printf("Erro: Nenhuma memoria cadastrada.\n");
        return;
    }

    Memory *node = *root;
    Info *targetInfo = NULL;
    int encontrado = 0; // Flag para determinar se o bloco foi encontrado

    // Procurar o bloco que contém o intervalo solicitado
    while (node != NULL && !encontrado)
    {
        if (isLeaf(node))
        {
            if (inicio >= node->info1->start && inicio <= node->info1->end)
            {
                targetInfo = node->info1;
                encontrado = 1; // Bloco encontrado
            }
            else if (node->numKeys == 2 && inicio >= node->info2->start && inicio <= node->info2->end)
            {
                targetInfo = node->info2;
                encontrado = 1; // Bloco encontrado
            }
        }
        else
        {
            if (inicio < node->info1->start)
            {
                node = node->left;
            }
            else if (node->numKeys == 1 || inicio < node->info2->start)
            {
                node = node->center;
            }
            else
            {
                node = node->right;
            }
        }
    }

    if (!encontrado || !targetInfo)
    {
        printf("Erro: Nao foi encontrado nenhum bloco contendo o endereco informado.\n");
        return;
    }

    // Determinar o tamanho do bloco e ajustar a árvore
    int tamanho_bloco = targetInfo->end - targetInfo->start + 1;

    if (quantidade_blocos > tamanho_bloco)
    {
        printf("Erro: A quantidade de blocos a liberar excede o tamanho do bloco encontrado.\n");
        return;
    }

    if (quantidade_blocos == tamanho_bloco)
    {
        // Caso o tamanho do bloco seja exatamente o solicitado
        targetInfo->status = FREE;
    }
    else
    {
        // Caso o bloco precise ser dividido
        int novo_inicio = inicio + quantidade_blocos;

        // Criar um novo bloco ocupado para o restante
        Info *novo_info_ocupado = CreateInfo(novo_inicio, targetInfo->end, targetInfo->status);
        if (!novo_info_ocupado)
        {
            printf("Erro: Falha ao alocar memoria para o novo bloco.\n");
            return;
        }

        targetInfo->end = inicio - 1;

        // Atualizar o bloco original como livre
        targetInfo->status = FREE;

        // Inserir o novo bloco na árvore
        int flag = 0;
        Insert23(root, NULL, NULL, novo_info_ocupado->start, novo_info_ocupado->end, novo_info_ocupado->status, &flag);
        if (!flag)
        {
            printf("Erro: Falha ao inserir o novo bloco na arvore.\n");
            free(novo_info_ocupado);
            return;
        }
    }

    // Concatenar nós adjacentes após a liberação
    concatenar_nos(root);

    printf("Blocos liberados: Inicio = %d, Quantidade = %d\n", inicio, quantidade_blocos);
}


// Funcao principal com menu interativo
int main()
{
    setlocale(LC_ALL, "PT-BR"); // Permite usar caracteres regionais
    Memory *root = NULL;   // Raiz da arvore
    int opcao;
    int quantidade_blocos;
    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Cadastrar nos\n");
        printf("2. Exibir estado da memoria\n");
        printf("3. Alocar blocos\n");
        printf("4. Liberar blocos\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrar_nos(&root);
            break;
        case 2:
            printf("\nEstado atual da memoria:\n");
            if (root)
            {
                DisplayInfos(root);
            }
            else
            {
                printf("Nenhum no cadastrado.\n");
            }
            break;
        case 3:
            printf("Informe a quantidade de blocos a alocar: ");
            scanf("%d", &quantidade_blocos);
            alocar_blocos(&root, quantidade_blocos);
            break;
        case 4:
            printf("Informe o endereco inicial do bloco a ser liberado: ");
            int inicio;
            scanf("%d", &inicio);
            printf("Informe a quantidade de blocos a liberar: ");
            
            scanf("%d", &quantidade_blocos);
            liberar_blocos(&root, inicio, quantidade_blocos);
            break;

        case 5:
            printf("Saindo do programa...\n");
            return 0;
        default:
            printf("Opcao invalida, tente novamente.\n");
        }
    }

    return 0;
}
