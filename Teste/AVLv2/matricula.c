#include <stdio.h>
#include <stdlib.h>
#include "matricula.h"

// Função que retorna o maior valor entre dois números do tipo short
short maior_no_mat(short a, short b)
{
    // 1. Compara os dois valores recebidos como parâmetros (a e b).
    // 2. Retorna o valor maior usando o operador ternário.
    //    - Se a é maior que b, retorna a.
    //    - Caso contrário, retorna b.
    return (a > b) ? a : b;
}


// Função que retorna a altura de um nó em uma árvore de matrículas
short altura_do_no_mat(arvore_matricula *no)
{
    short altura; // Declaração da variável para armazenar a altura

    // 1. Verifica se o nó passado como parâmetro é nulo.
    if (no == NULL)
    {
        // 2. Se o nó é nulo, atribui -1 à variável altura.
        //    - Isso indica que a altura de um nó nulo é considerada -1.
        altura = -1;
    }
    else
    {
        // 3. Se o nó não é nulo, atribui a altura do nó à variável altura.
        altura = no->altura;
    }

    // 4. Retorna a altura do nó.
    return altura;
}

// Função que calcula o fator de balanceamento de um nó em uma árvore de matrículas
short fator_balanceamento_mat(arvore_matricula *no)
{
    short fb = 0; // Declaração da variável para armazenar o fator de balanceamento

    // 1. Verifica se o nó passado como parâmetro não é nulo.
    if (no != NULL)
    {
        // 2. Calcula o fator de balanceamento:
        //    - O fator de balanceamento é a diferença entre a altura da subárvore esquerda
        //      e a altura da subárvore direita do nó.
        fb = altura_do_no_mat(no->esq) - altura_do_no_mat(no->dir);
    }

    // 3. Retorna o fator de balanceamento.
    return fb;
}


// Função que realiza uma rotação à esquerda em um nó da árvore de matrículas
arvore_matricula *rotar_esquerda_mat(arvore_matricula *no)
{
    arvore_matricula *aux, *aux1; // Declaração de ponteiros auxiliares

    // 1. O nó à direita do nó atual (no) se torna o novo nó "aux".
    aux = no->dir;

    // 2. O filho à esquerda do novo nó "aux" será armazenado em "aux1".
    aux1 = aux->esq;

    // 3. Realiza a rotação:
    //    - O novo nó "aux" passa a ser a raiz da subárvore.
    aux->esq = no; // O nó atual (no) agora é o filho esquerdo de aux.

    // 4. Atualiza o filho direito do nó atual (no) para o filho esquerdo de aux.
    no->dir = aux1;

    // 5. Atualiza a altura do nó atual (no):
    no->altura = maior_no_mat(altura_do_no_mat(no->esq), altura_do_no_mat(no->dir)) + 1;

    // 6. Atualiza a altura do novo nó (aux):
    aux->altura = maior_no_mat(altura_do_no_mat(aux->esq), altura_do_no_mat(aux->dir)) + 1;

    // 7. Retorna o novo nó (aux), que se tornou a raiz da subárvore após a rotação.
    return aux;
}


// Função que realiza uma rotação à direita em um nó da árvore de matrículas
arvore_matricula *rotar_direita_mat(arvore_matricula *no)
{
    arvore_matricula *aux, *aux1; // Declaração de ponteiros auxiliares

    // 1. O nó à esquerda do nó atual (no) se torna o novo nó "aux".
    aux = no->esq;

    // 2. O filho à direita do novo nó "aux" será armazenado em "aux1".
    aux1 = aux->dir;

    // 3. Realiza a rotação:
    //    - O novo nó "aux" passa a ser a raiz da subárvore.
    aux->dir = no; // O nó atual (no) agora é o filho direito de aux.

    // 4. Atualiza o filho esquerdo do nó atual (no) para o filho direito de aux.
    no->esq = aux1;

    // 5. Atualiza a altura do nó atual (no):
    no->altura = maior_no_mat(altura_do_no_mat(no->esq), altura_do_no_mat(no->dir)) + 1;

    // 6. Atualiza a altura do novo nó (aux):
    aux->altura = maior_no_mat(altura_do_no_mat(aux->esq), altura_do_no_mat(aux->dir)) + 1;

    // 7. Retorna o novo nó (aux), que se tornou a raiz da subárvore após a rotação.
    return aux;
}


// Função que realiza uma rotação dupla: primeiro à direita, depois à esquerda
arvore_matricula *rotar_direita_esquerda_mat(arvore_matricula *no)
{
    // 1. Realiza uma rotação à direita no filho direito do nó atual (no).
    // Isso corrige o desbalanceamento que ocorre quando o filho direito de 'no' é mais alto.
    no->dir = rotar_direita_mat(no->dir);

    // 2. Realiza uma rotação à esquerda no nó atual (no).
    // Após a rotação à direita no filho direito, agora rotacionamos o nó atual para restaurar o balanceamento.
    return rotar_esquerda_mat(no);
}


// Função que realiza uma rotação dupla: primeiro à esquerda, depois à direita
arvore_matricula *rotar_esquerda_direita_mat(arvore_matricula *no)
{
    // 1. Realiza uma rotação à esquerda no filho esquerdo do nó atual (no).
    // Isso corrige o desbalanceamento que ocorre quando o filho esquerdo de 'no' é mais alto.
    no->esq = rotar_esquerda_mat(no->esq);

    // 2. Realiza uma rotação à direita no nó atual (no).
    // Após a rotação à esquerda no filho esquerdo, agora rotacionamos o nó atual para restaurar o balanceamento.
    return rotar_direita_mat(no);
}


// Função que balanceia a árvore AVL de matrículas
arvore_matricula *balencar_arvore_mat(arvore_matricula *raiz)
{
    // 1. Calcula o fator de balanceamento da raiz.
    short fb = fator_balanceamento_mat(raiz);

    // 2. Verifica se a árvore está desbalanceada para a direita.
    if (fb < -1 && fator_balanceamento_mat(raiz->dir) <= 0)
    {
        // Caso simples: rotação à esquerda
        raiz = rotar_esquerda_mat(raiz);
    }
    // 3. Verifica se a árvore está desbalanceada para a esquerda.
    else if (fb > 1 && fator_balanceamento_mat(raiz->esq) >= 0)
    {
        // Caso simples: rotação à direita
        raiz = rotar_direita_mat(raiz);
    }
    // 4. Verifica o caso esquerdo-direita.
    else if (fb > 1 && fator_balanceamento_mat(raiz->esq) < 0)
    {
        // Caso duplo: rotação à esquerda no filho esquerdo, seguida de rotação à direita
        raiz = rotar_esquerda_direita_mat(raiz);
    }
    // 5. Verifica o caso direito-esquerdo.
    else if (fb < -1 && fator_balanceamento_mat(raiz->dir) > 0)
    {
        // Caso duplo: rotação à direita no filho direito, seguida de rotação à esquerda
        raiz = rotar_direita_esquerda_mat(raiz);
    }
    
    // 6. Retorna a raiz da árvore balanceada.
    return raiz;
}

// Função que cria um novo nó para a árvore AVL de matrículas
arvore_matricula *criar_matricula()
{
    // 1. Aloca memória para um novo nó da árvore.
    arvore_matricula *no = (arvore_matricula *)malloc(sizeof(arvore_matricula));
    
    // 2. Verifica se a alocação foi bem-sucedida.
    if (no == NULL)
    {
        printf("Erro ao alocar memória para a matrícula\n");
        exit(1); // Finaliza o programa em caso de falha na alocação.
    }
    
    // 3. Inicializa os ponteiros esquerdo e direito como NULL.
    no->esq = NULL;
    no->dir = NULL;
    
    // 4. Inicializa a altura do nó como 0.
    no->altura = 0;

    // 5. Retorna o ponteiro para o novo nó criado.
    return no;
}


// Função que insere um novo nó (matrícula) na árvore AVL de matrículas
arvore_matricula *inserir_matriculas(arvore_matricula *raiz, arvore_matricula *no)
{
    // 1. Se a raiz é NULL, significa que a árvore está vazia, então insere o novo nó.
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        // 2. Compara o código da disciplina do novo nó com o da raiz.
        if (no->codigo_disciplina < raiz->codigo_disciplina)
        {
            // 3. Se o código da disciplina do novo nó é menor, insere na subárvore esquerda.
            raiz->esq = inserir_matriculas(raiz->esq, no);
        }
        else if (no->codigo_disciplina > raiz->codigo_disciplina)
        {
            // 4. Se o código da disciplina do novo nó é maior, insere na subárvore direita.
            raiz->dir = inserir_matriculas(raiz->dir, no);
        }
        // Caso em que o código da disciplina já existe na árvore não é tratado aqui, assumindo que não se inserem duplicatas.
    }

    // 5. Atualiza a altura do nó raiz.
    raiz->altura = maior_no_mat(altura_do_no_mat(raiz->esq), altura_do_no_mat(raiz->dir)) + 1;

    // 6. Rebalanceia a árvore, se necessário.
    raiz = balencar_arvore_mat(raiz);

    // 7. Retorna o ponteiro para a raiz (que pode ter mudado se o nó foi rebalanceado).
    return raiz;
}


void imprimir_matricula(arvore_matricula *raiz)
{
    if (raiz != NULL)
    {
        printf("Codigo da disciplina: %d\n", raiz->codigo_disciplina);

        imprimir_matricula(raiz->esq);
        imprimir_matricula(raiz->dir);
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
            aux = buscar_matricula(raiz->esq, codigo_disciplina);
        }
        else
        {
            aux = buscar_matricula(raiz->dir, codigo_disciplina);
        }
    }
    return aux;
}

arvore_matricula *remover_matricula(arvore_matricula *raiz, int codigo_disciplina)
{
    // 1. Se a raiz não é NULL, continua o processo de remoção.
    if (raiz != NULL)
    {
        // 2. Compara o código da disciplina a ser removido com o código do nó raiz.
        if (codigo_disciplina < raiz->codigo_disciplina)
        {
            // 3. Se o código da disciplina é menor, chama a remoção na subárvore esquerda.
            raiz->esq = remover_matricula(raiz->esq, codigo_disciplina);
        }
        else if (codigo_disciplina > raiz->codigo_disciplina)
        {
            // 4. Se o código da disciplina é maior, chama a remoção na subárvore direita.
            raiz->dir = remover_matricula(raiz->dir, codigo_disciplina);
        }
        else
        {
            // 5. Aqui, encontramos o nó que deve ser removido.

            // Caso 1: O nó não tem filhos (nó folha).
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);
                raiz = NULL; // A raiz agora se torna NULL.
            }
            // Caso 2: O nó tem apenas um filho (subárvore).
            else if (raiz->esq == NULL)
            {
                arvore_matricula *temp = raiz->dir; // Salva o filho à direita.
                free(raiz); // Libera o nó atual.
                raiz = temp; // A raiz agora aponta para o filho.
            }
            else if (raiz->dir == NULL)
            {
                arvore_matricula *temp = raiz->esq; // Salva o filho à esquerda.
                free(raiz);
                raiz = temp;
            }
            // Caso 3: O nó tem dois filhos.
            else
            {
                // 6. Encontra o nó sucessor (menor na subárvore direita).
                arvore_matricula *temp = raiz->dir;
                while (temp->esq != NULL)
                {
                    temp = temp->esq; // Navega até o nó mais à esquerda.
                }

                // 7. Substitui o código da disciplina do nó atual pelo sucessor.
                raiz->codigo_disciplina = temp->codigo_disciplina;

                // 8. Remove o sucessor da subárvore direita.
                raiz->dir = remover_matricula(raiz->dir, temp->codigo_disciplina);
            }
        }

        // 9. Após a remoção, atualiza a altura do nó raiz, se ele não for NULL.
        if (raiz != NULL)
        {
            raiz->altura = maior_no_mat(altura_do_no_mat(raiz->esq), altura_do_no_mat(raiz->dir)) + 1;

            // 10. Rebalanceia a árvore após a remoção.
            raiz = balencar_arvore_mat(raiz);
        }
    }

    // 11. Retorna a nova raiz da árvore (que pode ter mudado).
    return raiz;
}
