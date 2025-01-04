#include "arvbin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unidade.h"

Inglesbin *createNode(const char *palavraIng, int unidade) {
    Inglesbin *novoNo = (Inglesbin *)malloc(sizeof(Inglesbin));
    if (novoNo == NULL) {
        printf("Erro: Falha ao alocar memória para o nó.\n");
        return NULL;
    }

    novoNo->palavraIngles = strdup(palavraIng); // Copia segura da string
    if (novoNo->palavraIngles == NULL) {
        printf("Erro: Falha ao alocar memória para a palavra '%s'.\n", palavraIng);
        free(novoNo);
        return NULL;
    }

    novoNo->unidades = criar_unidade(unidade); // Inicializa a lista de unidades
    novoNo->esq = novoNo->dir = NULL; // Inicializa filhos
    return novoNo;
}


// Função para inserir uma palavra em inglês na arvore binaria de busca
Inglesbin *insertpalavraIngles(Inglesbin *root, const char *palavraIngles, int unidade) {
    Inglesbin *result;

    if (root == NULL) {
        // Cria um novo nó para a palavra em inglês e adiciona a unidade à lista
        result = createNode(palavraIngles, unidade);
    } else {
        // Se a palavra em inglês já existe, adiciona a unidade à lista ordenada
        if (strcmp(palavraIngles, root->palavraIngles) == 0) {
            root->unidades = adicionar_unidade_ordenada(root->unidades, criar_unidade(unidade));
            result = root;
        } else {
            // Caso contrário, insere recursivamente na árvore binária
            if (strcmp(palavraIngles, root->palavraIngles) < 0) {
                root->esq = insertpalavraIngles(root->esq, palavraIngles, unidade);
            } else {
                root->dir = insertpalavraIngles(root->dir, palavraIngles, unidade);
            }
            result = root;
        }
    }

    return result;
}

void adicionarTraducaoEmIngles(Info *info, const char *palavraIng, int unidade) {
    if (!info || !palavraIng) {
        printf("Erro: Info ou palavra em inglês inválida.\n");
        return;
    }

    // Verifica se a árvore binária de traduções em inglês está vazia
    if (info->palavraIngles == NULL) {
        // Se a árvore estiver vazia, cria a palavra em inglês com a unidade associada
        info->palavraIngles = createNode(palavraIng, unidade);
        if (!info->palavraIngles) {
            printf("Erro: Falha ao criar nó para a palavra '%s'.\n", palavraIng);
            return;
        }
    } else {
        // Se a árvore não estiver vazia, insere a palavra em inglês de maneira ordenada na árvore
        Inglesbin *novaRaiz = insertpalavraIngles(info->palavraIngles, palavraIng, unidade);
        if (novaRaiz == NULL) {
            printf("Erro: Falha ao inserir palavra '%s' na árvore binária.\n", palavraIng);
            return;
        }
        info->palavraIngles = novaRaiz; // Atualiza a raiz da árvore
    }

    // Agora associa a unidade à palavra em inglês, garantindo a ordem das unidades
    Unidade *novaUnidade = criar_unidade(unidade);
    if (!novaUnidade) {
        printf("Erro: Falha ao criar unidade %d para a palavra '%s'.\n", unidade, palavraIng);
        return;
    }

    info->palavraIngles->unidades = adicionar_unidade_ordenada(info->palavraIngles->unidades, novaUnidade);
    if (!info->palavraIngles->unidades) {
        printf("Erro: Falha ao associar unidade %d à palavra '%s'.\n", unidade, palavraIng);
    }
}



void printBinaryTree(Inglesbin *root)
{
    if (root != NULL)
    {
        // Percorre a árvore à esquerda
        printBinaryTree(root->esq);
        
        // Imprime a palavra em inglês e as unidades associadas
        printf("\nPalavra em Inglês: %s\n", root->palavraIngles);
        
        // Imprime as unidades associadas a essa palavra em inglês
        if (root->unidades != NULL) {
            printf("Unidades associadas: ");
            imprimir_unidades(root->unidades);  // Usa a função 'imprimir_unidades' para imprimir as unidades
        }
        else {
            printf("Nenhuma unidade associada.\n");
        }
        
        // Percorre a árvore à direita
        printBinaryTree(root->dir);
    }
}


int ehFolhas(Inglesbin *raiz){
    return (raiz->esq == NULL && raiz->dir == NULL);
}

Inglesbin *soUmFilho(Inglesbin *raiz){
    Inglesbin *aux;
    aux = NULL;

    if (raiz->dir == NULL)
    {
        aux = raiz->esq;
    }
    else if (raiz->esq == NULL)
    {
        aux = raiz->dir;
    }

    return aux;
}

Inglesbin *menorFilho(Inglesbin *raiz){
    Inglesbin *aux;
    aux = raiz;

    if (raiz)
    {
        if (raiz->esq)
            aux = menorFilho(raiz->esq);
    }

    return aux;
}

int removerPalavraIngles(Inglesbin **raiz, const char *palavra) {
    Inglesbin *endFilho = NULL;
    int existe = 0;

    if (*raiz) {
        if (strcmp(palavra, (*raiz)->palavraIngles) == 0) {
            Inglesbin *aux = *raiz;
            existe = 1;

            if (ehFolhas(*raiz)) { 
                // Caso nó folha
                free(aux->palavraIngles); // Libera a string
                free(aux);
                *raiz = NULL;
            } else if ((endFilho = soUmFilho(*raiz)) != NULL) {
                // Caso nó tenha apenas um filho
                free(aux->palavraIngles); // Libera a string
                free(aux);
                *raiz = endFilho;
            } else {
                // Caso nó tenha dois filhos
                endFilho = menorFilho((*raiz)->dir);
                if (endFilho && endFilho->palavraIngles) {
                    free((*raiz)->palavraIngles); // Libera a string existente
                    (*raiz)->palavraIngles = strdup(endFilho->palavraIngles); // Copia a palavra do menor filho
                    (*raiz)->unidades = endFilho->unidades; // Transfere a unidade
                    removerPalavraIngles(&(*raiz)->dir, endFilho->palavraIngles); // Remove o nó substituído
                }
            }
        } else if (strcmp(palavra, (*raiz)->palavraIngles) < 0) {
            // Busca na subárvore esquerda
            existe = removerPalavraIngles(&(*raiz)->esq, palavra);
        } else {
            // Busca na subárvore direita
            existe = removerPalavraIngles(&(*raiz)->dir, palavra);
        }
    }

    return existe;
}






void free_arvore_binaria(Inglesbin *raiz) {
    if (raiz != NULL) {
        // Debug: Log the word being freed
        printf("Liberando nó da árvore binária com palavra: %s\n", raiz->palavraIngles);

        // Recursively free left and right subtrees
        free_arvore_binaria(raiz->esq);
        free_arvore_binaria(raiz->dir);

        // Free associated list of units
        liberar_lista(raiz->unidades);

        // Free the English word
        free(raiz->palavraIngles);

        // Free the node itself
        free(raiz);
    }
}

void imprimirTraducoes(Inglesbin *node, int unidade, const char *palavraPortugues)
{
    if (node)
    {
        // Percorre a subárvore esquerda
        imprimirTraducoes(node->esq, unidade, palavraPortugues);

        // Verifica se a unidade está associada à palavra em inglês
        if (buscar_unidade(node->unidades, unidade)) // Verifica se a unidade existe na lista
        {
            printf("Palavra em Português: %s\n", palavraPortugues);
            printf("Tradução em Inglês: %s\n", node->palavraIngles);
        }

        // Percorre a subárvore direita
        imprimirTraducoes(node->dir, unidade, palavraPortugues);
    }
}

Inglesbin *buscarPalavraIngles(Inglesbin *raiz, const char *palavraIngles) {
    Inglesbin *resultado = NULL;

    if (raiz != NULL) {
        int comparacao = strcmp(palavraIngles, raiz->palavraIngles);

        if (comparacao == 0) {
            resultado = raiz; // Palavra encontrada
        } else if (comparacao < 0) {
            resultado = buscarPalavraIngles(raiz->esq, palavraIngles);
        } else {
            resultado = buscarPalavraIngles(raiz->dir, palavraIngles);
        }
    }

    return resultado;
}


void BuscarPalavraIngles(Portugues23 **raiz, char *palavraIngles, int unidade, Portugues23 **pai)
{
    if (*raiz != NULL)
    {
        // Verifica na subárvore esquerda
        BuscarPalavraIngles(&(*raiz)->esq, palavraIngles, unidade, pai);

        // Verifica no primeiro elemento do nó
        if ((*raiz)->info1.palavraIngles != NULL)
        {
            Inglesbin *traducaoEncontrada = buscarPalavraIngles((*raiz)->info1.palavraIngles, palavraIngles);
            if (traducaoEncontrada != NULL && buscar_unidade(traducaoEncontrada->unidades, unidade))
            {
                printf("Palavra em Inglês: %s encontrada na Unidade: %d\n", palavraIngles, unidade);
            }
        }

        // Verifica na subárvore central
        BuscarPalavraIngles(&(*raiz)->cent, palavraIngles, unidade, raiz);

        // Se o nó tem dois elementos, verifica o segundo
        if ((*raiz)->nInfos == 2 && (*raiz)->info2.palavraIngles != NULL)
        {
            Inglesbin *traducaoEncontrada = buscarPalavraIngles((*raiz)->info2.palavraIngles, palavraIngles);
            if (traducaoEncontrada != NULL && buscar_unidade(traducaoEncontrada->unidades, unidade))
            {
                printf("Palavra em Inglês: %s encontrada na Unidade: %d\n", palavraIngles, unidade);
            }
        }

        // Verifica na subárvore direita
        if ((*raiz)->nInfos == 2)
        {
            BuscarPalavraIngles(&(*raiz)->dir, palavraIngles, unidade, raiz);
        }
    }
}

void exibirTraducoesIngles(Inglesbin *raiz)
{
    if (raiz)
    {
        // Percorre a subárvore esquerda
        exibirTraducoesIngles(raiz->esq);

        // Exibe a tradução em inglês
        printf("- %s\n", raiz->palavraIngles);

        // Percorre a subárvore direita
        exibirTraducoesIngles(raiz->dir);
    }
}
