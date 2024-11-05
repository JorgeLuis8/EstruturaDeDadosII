#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "notas.h"

struct arvore_notas;

arvore_notas *criar_nota()
{
    arvore_notas *no = (arvore_notas *)malloc(sizeof(arvore_notas));
    no->esq = NULL;
    no->dir = NULL;
    return no;
}
arvore_notas *inserir_nota(arvore_notas *raiz, arvore_notas *no)
{
    if (raiz == NULL)
    {
        raiz = no; // Se a raiz está vazia, atribui o novo nó
    }
    else
    {
        if (no->codigo_disciplina < raiz->codigo_disciplina)
        {
            if (raiz->esq == NULL)
            {
                raiz->esq = no; // Insere à esquerda se não há nó
            }
            else
            {
                raiz->esq = inserir_nota(raiz->esq, no); // Chama recursivamente para a esquerda
            }
        }
        else
        {
            if (raiz->dir == NULL)
            {
                raiz->dir = no; // Insere à direita se não há nó
            }
            else
            {
                raiz->dir = inserir_nota(raiz->dir, no); // Chama recursivamente para a direita
            }
        }
    }

    return raiz; // Retorna a raiz da árvore
}


void imprimir_notas(arvore_notas *raiz)
{
    if (raiz != NULL)
    {
        printf("Codigo da disciplina: %d\n", raiz->codigo_disciplina);
        printf("Semestre cursado: %s\n", raiz->semestre_cursado);
        printf("Nota Final: %.2f\n", raiz->nota_final);
        imprimir_notas(raiz->esq);
        imprimir_notas(raiz->dir);
    }
}

arvore_notas *buscar_notas(arvore_notas *raiz, int codigo_disciplina)
{
    arvore_notas *aux = NULL;
    if (raiz != NULL)
    {
        {
            if (codigo_disciplina == raiz->codigo_disciplina)
            {
                aux = raiz;
            }
            else
            {
                if (codigo_disciplina < raiz->codigo_disciplina)
                {
                    aux = buscar_notas(raiz->esq, codigo_disciplina);
                }
                else
                {
                    aux = buscar_notas(raiz->dir, codigo_disciplina);
                }
            }
        }
    }
    return aux;
}

arvore_notas *remover_nota(arvore_notas *raiz, int codigo_disciplina)
{
    // Verifica se a raiz da árvore não é nula
    if (raiz != NULL)
    {
        // Se o código da disciplina a ser removida é menor que o código do nó atual,
        // busca na subárvore esquerda.
        if (codigo_disciplina < raiz->codigo_disciplina)
        {
            raiz->esq = remover_nota(raiz->esq, codigo_disciplina);
        }
        // Se o código da disciplina a ser removida é maior que o código do nó atual,
        // busca na subárvore direita.
        else if (codigo_disciplina > raiz->codigo_disciplina)
        {
            raiz->dir = remover_nota(raiz->dir, codigo_disciplina);
        }
        // Caso encontrado: o código da disciplina é igual ao código do nó atual.
        else
        {
            // Caso 1: O nó a ser removido é uma folha (não tem filhos).
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);  // Libera a memória do nó.
                raiz = NULL; // Define a raiz como nula.
            }
            // Caso 2: O nó a ser removido tem apenas filho à direita.
            else if (raiz->esq == NULL)
            {
                arvore_notas *aux = raiz; // Armazena o nó a ser removido.
                raiz = raiz->dir;         // A raiz passa a ser seu filho à direita.
                free(aux);                // Libera a memória do nó removido.
            }
            // Caso 3: O nó a ser removido tem apenas filho à esquerda.
            else if (raiz->dir == NULL)
            {
                arvore_notas *aux = raiz; // Armazena o nó a ser removido.
                raiz = raiz->esq;         // A raiz passa a ser seu filho à esquerda.
                free(aux);                // Libera a memória do nó removido.
            }
            // Caso 4: O nó a ser removido tem dois filhos.
            else
            {
                // Encontra o maior nó na subárvore esquerda.
                arvore_notas *aux = raiz->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir; // Vai para o nó mais à direita na subárvore esquerda.
                }
                // Copia o código da disciplina do nó encontrado para o nó a ser removido.
                raiz->codigo_disciplina = aux->codigo_disciplina;
                // Remove o nó que tinha o código da disciplina copiado.
                raiz->esq = remover_nota(raiz->esq, aux->codigo_disciplina);
            }
        }
    }
    return raiz; // Retorna a raiz atualizada da árvore.
}


void imprimir_notas_periodo(arvore_notas *raiz_notas, int periodo)
{
    if (raiz_notas != NULL)
    {
        imprimir_notas_periodo(raiz_notas->esq, periodo);
        if (raiz_notas->semestre_cursado[5] == periodo + '0')
        {
            printf("Codigo da disciplina: %d\n", raiz_notas->codigo_disciplina);
            printf("Semestre cursado: %s\n", raiz_notas->semestre_cursado);
            printf("Nota Final: %f\n", raiz_notas->nota_final);
        }
        imprimir_notas_periodo(raiz_notas->dir, periodo);
    }
}

arvore_notas *buscar_nota_periodo(arvore_notas *raiz, int periodo)
{
    arvore_notas *aux = NULL;
    if (raiz != NULL)
    {
        aux = buscar_nota_periodo(raiz->esq, periodo);
        if (raiz->semestre_cursado[5] == periodo + '0')
        {
            aux = raiz;
        }
        if (aux == NULL)
        {
            aux = buscar_nota_periodo(raiz->dir, periodo);
        }
    }
    return aux;
}
