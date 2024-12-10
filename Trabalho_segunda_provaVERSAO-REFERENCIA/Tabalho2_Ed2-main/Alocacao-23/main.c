#include "arv-23.c"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MEMORY_SIZE (1024 * 1024) // Tamanho total da memoria (1MB por bloco)

// Declaracao das funcoes utilizadas
void concatenar_nos(Memory **root);
void alocar_nos(Memory **root, int quantidade_blocos);
void cadastrar_nos(Memory **root);
void exibir_estado(Memory *root);

// Funcao para concatenar nos adjacentes do mesmo status
void concatenar_nos(Memory **root)
{
    if (!root || !(*root))
    {
        return;
    }

    Memory *node = *root;
    if (isLeaf(node))
    {
        // Concatenar nos em folhas
        if (node->numKeys == 2)
        {
            if (node->info1->status == node->info2->status)
            {
                // Mesclar os dois nos
                node->info1->end = node->info2->end;
                free(node->info2);
                node->info2 = NULL;
                node->numKeys = 1;
            }
        }
    }
    else
    {
        // Concatenar recursivamente nos filhos
        concatenar_nos(&node->left);
        concatenar_nos(&node->center);
        if (node->numKeys == 2)
        {
            concatenar_nos(&node->right);
        }
    }
}

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

// Funcao para alocar nos
void alocar_nos(Memory **root, int quantidade_blocos)
{
    if (!root || !(*root))
    {
        printf("Erro: Nenhuma memoria cadastrada.\n");
        return;
    }

    // Buscar um nó que tenha espaço suficiente
    Memory *node = FindSpace(*root, quantidade_blocos);
    if (!node)
    {
        printf("Erro: Nao ha blocos livres suficientes para alocar.\n");
        return;
    }

    // Determinar qual bloco será alocado
    Info *targetInfo = NULL;
    if (node->info1->status == FREE && (node->info1->end - node->info1->start + 1) >= quantidade_blocos)
    {
        targetInfo = node->info1;
    }
    else if (node->numKeys == 2 && node->info2->status == FREE &&
             (node->info2->end - node->info2->start + 1) >= quantidade_blocos)
    {
        targetInfo = node->info2;
    }

    if (!targetInfo)
    {
        printf("Erro interno: Não foi possível encontrar um bloco adequado.\n");
        return;
    }

    // Atualizar o bloco encontrado
    int espacoDisponivel = targetInfo->end - targetInfo->start + 1;
    if (espacoDisponivel > quantidade_blocos)
    {
        // Caso o nó tenha mais espaço do que o necessário, dividir
        int novo_inicio = targetInfo->start + quantidade_blocos;

        // Criar um novo bloco livre para os blocos restantes
        Info *novo_info = CreateInfo(novo_inicio, targetInfo->end, FREE);
        targetInfo->end = novo_inicio - 1;

        // Inserir o novo bloco na árvore
        AddInfo(root, novo_info, NULL);
    }

    // Alterar o status do nó alocado para "Ocupado"
    targetInfo->status = OCCUPIED;

    printf("Blocos alocados: Inicio = %d, Fim = %d\n", targetInfo->start, targetInfo->end);

    // Concatenar nós adjacentes, se necessário
    concatenar_nos(root);
}

// Funcao para exibir o estado da memoria
void exibir_estado(Memory *root)
{
    printf("\nEstado atual da memoria:\n");
    if (root)
    {
        DisplayInfos(root);
    }
    else
    {
        printf("Nenhum no cadastrado.\n");
    }
}

// Funcao principal com menu interativo
int main()
{
    setlocale(LC_ALL, "");
    Memory *root = NULL;
    int opcao;

    while (1)
    {
        printf("\nMenu de Cadastro de Nos:\n");
        printf("1. Cadastrar nos\n");
        printf("2. Exibir estado da memoria\n");
        printf("3. Alocar blocos\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrar_nos(&root);
            break;
        case 2:
            exibir_estado(root);
            break;
        case 3:
        {
            printf("Informe a quantidade de blocos a alocar: ");
            int quantidade_blocos;
            scanf("%d", &quantidade_blocos);
            alocar_nos(&root, quantidade_blocos);
            break;
        }

        case 4:
            printf("Saindo do programa...\n");
            return 0;
        default:
            printf("Opcao invalida, tente novamente.\n");
        }
    }

    return 0;
}
