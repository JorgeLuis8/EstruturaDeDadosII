#include <stdio.h>
#include <stdlib.h>
#include "matricula.h"


short maior_no_mat(short a, short b)
{
    return (a > b) ? a : b;
}

short altura_do_no_mat(arvore_matricula *no)
{
    if (no == NULL)
    {
        return -1;
    }
    return no->altura;
}

short fator_balanceamento_mat(arvore_matricula *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return altura_do_no_mat(no->esq) - altura_do_no_mat(no->dir);
}

 arvore_matricula *rotar_esquerda_mat(arvore_matricula *no)
{
    arvore_matricula *aux, *aux1;

    aux = no->dir;
    aux1 = aux->esq;

    aux->esq = no;
    no->dir = aux1;

    no->altura = maior_no_mat(altura_do_no_mat(no->esq), altura_do_no_mat(no->dir)) + 1;
    aux->altura = maior_no_mat(altura_do_no_mat(aux->esq), altura_do_no_mat(aux->dir)) + 1;

    return aux;
}

arvore_matricula *rotar_direita_mat(arvore_matricula *no)
{
    arvore_matricula *aux, *aux1;

    aux = no->esq;
    aux1 = aux->dir;

    aux->dir = no;
    no->esq = aux1;

    no->altura = maior_no_mat(altura_do_no_mat(no->esq), altura_do_no_mat(no->dir)) + 1;
    aux->altura = maior_no_mat(altura_do_no_mat(aux->esq), altura_do_no_mat(aux->dir)) + 1;

    return aux;
}

arvore_matricula *rotar_direita_esquerda_mat(arvore_matricula *no)
{
    no->dir = rotar_direita_mat(no->dir);
    return rotar_esquerda_mat(no);
}

 arvore_matricula *rotar_esquerda_direita_mat(arvore_matricula *no)
{
    no->esq = rotar_esquerda_mat(no->esq);
    return rotar_direita_mat(no);
}

arvore_matricula *balencar_arvore_mat(arvore_matricula *raiz)
{
    short fb = fator_balanceamento_mat(raiz);

    if (fb < -1 && fator_balanceamento_mat(raiz->dir) <= 0)
    {
        raiz = rotar_esquerda_mat(raiz);
    }
    else if (fb > 1 && fator_balanceamento_mat(raiz->esq) >= 0)
    {
        raiz = rotar_direita_mat(raiz);
    }
    else if (fb > 1 && fator_balanceamento_mat(raiz->esq) < 0)
    {
        raiz = rotar_esquerda_direita_mat(raiz);
    }
    else if (fb < -1 && fator_balanceamento_mat(raiz->dir) > 0)
    {
        raiz = rotar_direita_esquerda_mat(raiz);
    }
    return raiz;
}


arvore_matricula *criar_matricula()
{
    arvore_matricula *no = (arvore_matricula *)malloc(sizeof(arvore_matricula));
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 0;
    return no;
}

arvore_matricula *inserir_matriculas(arvore_matricula *raiz, arvore_matricula *no) {
    if (raiz == NULL) {
        // Se a árvore estiver vazia, o novo nó se torna a raiz
        raiz = no;
    } else {
        // Comparar o código da disciplina para decidir a posição
        if (no->codigo_disciplina < raiz->codigo_disciplina) {
            // Inserir à esquerda
            raiz->esq = inserir_matriculas(raiz->esq, no);
        } else if (no->codigo_disciplina > raiz->codigo_disciplina) {
            // Inserir à direita
            raiz->dir = inserir_matriculas(raiz->dir, no);
        }
        // Se o código da disciplina for igual, você pode definir uma política para lidar com duplicatas,
        // mas neste caso estamos assumindo que não haverá duplicatas na árvore.
    }

    // Atualizar a altura do nó atual
    raiz->altura = maior_no_mat(altura_do_no_mat(raiz->esq), altura_do_no_mat(raiz->dir)) + 1;
    raiz = balencar_arvore_mat(raiz); // Balancear a árvore
    return raiz;
}



void imprimir_matricula(arvore_matricula *raiz)
{
    if (raiz != NULL)
    {
        printf("Codigo da disciplina: %d\n", raiz->codigo_disciplina);

        imprimir_matricula(raiz->esq); // Corrigido
        imprimir_matricula(raiz->dir); // Corrigido
    }
}

arvore_matricula *buscar_matricula(arvore_matricula *raiz, int codigo_disciplina)
{
    arvore_matricula *aux = NULL;
    if (raiz != NULL)
    {
        if (codigo_disciplina == raiz->codigo_disciplina)
        {
            aux = raiz;
        }
        else if (codigo_disciplina < raiz->codigo_disciplina)
        {
            aux = buscar_matricula(raiz->esq, codigo_disciplina); // Corrigido
        }
        else
        {
            aux = buscar_matricula(raiz->dir, codigo_disciplina); // Corrigido
        }
    }
    return aux;
}



arvore_matricula *remover_matricula(arvore_matricula *raiz, int codigo_disciplina)
{
    // Busca o nó a ser removido
    if (raiz != NULL) 
    {
        if (codigo_disciplina < raiz->codigo_disciplina)
        {
            raiz->esq = remover_matricula(raiz->esq, codigo_disciplina);
        }
        else if (codigo_disciplina > raiz->codigo_disciplina)
        {
            raiz->dir = remover_matricula(raiz->dir, codigo_disciplina);
        }
        else // Encontrou o nó a ser removido
        {
            // Caso 1: Nó com apenas um filho ou nenhum
            if (raiz->esq == NULL) 
            {
                arvore_matricula *temp = raiz->dir; // Salva o filho direito
                free(raiz); // Libera a memória do nó
                raiz = temp; // Atualiza a raiz para o filho direito
            } 
            else if (raiz->dir == NULL) 
            {
                arvore_matricula *temp = raiz->esq; // Salva o filho esquerdo
                free(raiz); // Libera a memória do nó
                raiz = temp; // Atualiza a raiz para o filho esquerdo
            }
            else // Caso 2: Nó com dois filhos
            {
                // Encontrar o menor nó na subárvore da direita
                arvore_matricula *temp = raiz->dir;
                while (temp->esq != NULL)
                {
                    temp = temp->esq; // Encontra o menor nó na subárvore direita
                }

                // Substitui o código do nó a ser removido pelo menor nó da subárvore da direita
                raiz->codigo_disciplina = temp->codigo_disciplina;

                // Remove o menor nó da subárvore da direita
                raiz->dir = remover_matricula(raiz->dir, temp->codigo_disciplina);
            }
        }

        // Atualizar a altura do nó atual, se raiz ainda é válida
        if (raiz != NULL)
        {
            raiz->altura = maior_no_mat(altura_do_no_mat(raiz->esq), altura_do_no_mat(raiz->dir)) + 1;

            // Balancear a árvore
            raiz = balencar_arvore_mat(raiz);
        }
    }

    return raiz; // Retorna a raiz balanceada apenas no final
}

