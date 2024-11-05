#include "disciplinas.h"
#include <stdio.h>
#include <stdlib.h>

arvore_disciplinas *criar_disciplina()
{
    // Aloca memória para uma nova disciplina, usando "malloc" para reservar espaço
    // suficiente para a estrutura "arvore_disciplinas" e retorna um ponteiro para ela.
    arvore_disciplinas *disciplina = (arvore_disciplinas *)malloc(sizeof(arvore_disciplinas));

    // Verifica se a alocação de memória foi bem-sucedida.
    // Caso contrário, exibe uma mensagem de erro e encerra o programa.
    if (disciplina == NULL)
    {
        printf("Erro ao alocar memória para a disciplina\n");
        exit(1);
    }

    // Inicializa os ponteiros "esq" e "dir" como NULL, indicando que esta disciplina
    // não possui filhos à esquerda nem à direita na árvore.
    disciplina->esq = NULL;
    disciplina->dir = NULL;

    // Retorna o ponteiro para a nova disciplina, com todos os campos inicializados.
    return disciplina;
}


arvore_disciplinas *inserir_disciplina(arvore_disciplinas *raiz, arvore_disciplinas *no)
{
    // Verifica se a raiz da árvore (ou subárvore) é NULL.
    // Se for, o novo nó se torna a raiz da árvore.
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        // Se o código da nova disciplina é menor que o código da raiz,
        // insere o novo nó na subárvore esquerda.
        if (no->codigo < raiz->codigo)
        {
            raiz->esq = inserir_disciplina(raiz->esq, no);
        }
        // Caso contrário, insere o novo nó na subárvore direita.
        else
        {
            raiz->dir = inserir_disciplina(raiz->dir, no);
        }
    }

    // Retorna o ponteiro para a raiz da árvore, possivelmente atualizado.
    return raiz;
}

arvore_disciplinas *buscar_disciplina(arvore_disciplinas *raiz, int codigo)
{
    arvore_disciplinas *aux = NULL;
    if (raiz != NULL)
    {
        if (codigo == raiz->codigo)
        {
            aux = raiz;
        }
        else
        {
            if (codigo < raiz->codigo)
            {
                aux = buscar_disciplina(raiz->esq, codigo);
            }
            else
            {
                aux = buscar_disciplina(raiz->dir, codigo);
            }
        }
    }
    return aux;
}

arvore_disciplinas *remover_disciplina(arvore_disciplinas *raiz, int codigo)
{
    // Verifica se a árvore (ou subárvore) não está vazia.
    if (raiz != NULL)
    {
        // Se o código da disciplina a ser removida é menor que o código da raiz,
        // faz a chamada recursiva para a subárvore esquerda.
        if (codigo < raiz->codigo)
        {
            raiz->esq = remover_disciplina(raiz->esq, codigo);
        }
        // Se o código da disciplina a ser removida é maior que o código da raiz,
        // faz a chamada recursiva para a subárvore direita.
        else if (codigo > raiz->codigo)
        {
            raiz->dir = remover_disciplina(raiz->dir, codigo);
        }
        // Caso contrário, encontrou o nó a ser removido.
        else
        {
            // Caso 1: O nó não possui filhos (é uma folha).
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);  // Libera a memória do nó.
                raiz = NULL; // Define o ponteiro para NULL, removendo o nó da árvore.
            }
            // Caso 2: O nó possui apenas um filho à direita.
            else if (raiz->esq == NULL)
            {
                arvore_disciplinas *aux = raiz; // Salva o nó atual em uma variável auxiliar.
                raiz = raiz->dir;               // Substitui o nó atual pelo seu filho à direita.
                free(aux);                      // Libera a memória do nó removido.
            }
            // Caso 2: O nó possui apenas um filho à esquerda.
            else if (raiz->dir == NULL)
            {
                arvore_disciplinas *aux = raiz; // Salva o nó atual em uma variável auxiliar.
                raiz = raiz->esq;               // Substitui o nó atual pelo seu filho à esquerda.
                free(aux);                      // Libera a memória do nó removido.
            }
            // Caso 3: O nó possui dois filhos.
            else
            {
                // Encontra o maior valor na subárvore esquerda (prédecessor).
                arvore_disciplinas *aux = raiz->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir;
                }
                // Copia o valor do curso encontrado para o nó atual.
                raiz->codigo = aux->codigo;
                // Remove o curso duplicado na subárvore esquerda.
                raiz->esq = remover_disciplina(raiz->esq, aux->codigo);
            }
        }
    }
    // Retorna a raiz (possivelmente atualizada) da árvore.
    return raiz;
}


void imprimir_disciplinas(arvore_disciplinas *raiz)
{
    if (raiz != NULL)
    {
        imprimir_disciplinas(raiz->esq);
        printf("Codigo: %d\n", raiz->codigo);
        printf("Nome: %s\n", raiz->nome);
        printf("\n");
        imprimir_disciplinas(raiz->dir);
    }
}

void liberar_disciplinas(arvore_disciplinas *raiz)
{
    if (raiz != NULL)
    {
        liberar_disciplinas(raiz->esq);
        liberar_disciplinas(raiz->dir);
        free(raiz);
    }
}
void imprimir_disciplinas_periodo(arvore_disciplinas *raiz, int periodo)
{
    if (raiz != NULL)
    {
        imprimir_disciplinas_periodo(raiz->esq, periodo);
        if (raiz->periodo == periodo)
        {
            printf("Codigo: %d\n", raiz->codigo);
            printf("Nome: %s\n", raiz->nome);
            printf("\n");
        }
        imprimir_disciplinas_periodo(raiz->dir, periodo);
    }
}

void imprimir_historico_disciplinas(arvore_notas *raiz_notas, arvore_disciplinas *raiz_disciplinas)
{
    if (raiz_disciplinas != NULL)
    {

        arvore_notas *nota = buscar_notas(raiz_notas, raiz_disciplinas->codigo);
        if (nota != NULL)
        {
            printf("Disciplina: %s\n", raiz_disciplinas->nome);
            printf("Nota: %.2f\n", nota->nota_final);
            printf("Semestre cursado: %s\n", nota->semestre_cursado);
            printf("Carga horaria: %d\n", raiz_disciplinas->carga_horaria);
            printf("Periodo: %d\n", raiz_disciplinas->periodo);
            printf("\n");
        }

        imprimir_historico_disciplinas(raiz_notas, raiz_disciplinas->esq);

        imprimir_historico_disciplinas(raiz_notas, raiz_disciplinas->dir);
    }
}