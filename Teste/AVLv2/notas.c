#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "notas.h"

// Função que retorna o maior de dois valores do tipo 'short'.
// Esta função utiliza o operador ternário para comparar os dois valores
// fornecidos como argumentos 'a' e 'b'.
// Se 'a' for maior que 'b', a função retorna 'a'; caso contrário, retorna 'b'.
short maior_no_nota(short a, short b)
{
    return (a > b) ? a : b; // Retorna o maior valor entre 'a' e 'b'.
}

// Função que retorna a altura de um nó da árvore de notas.
// Recebe um ponteiro para um nó do tipo 'arvore_notas' como argumento.
// Se o nó for NULL, a função retorna -1, indicando que a altura de um nó
// inexistente é -1 (comum em árvores para representar a ausência de nó).
// Caso contrário, retorna a altura do nó, que é armazenada no campo 'altura'.
short altura_do_no_nota(arvore_notas *no)
{
    short altura; // Variável para armazenar a altura do nó.

    if (no == NULL) // Verifica se o nó é NULL.
    {
        altura = -1; // Se for NULL, a altura é -1.
    }
    else
    {
        altura = no->altura; // Caso contrário, obtém a altura do nó.
    }

    return altura; // Retorna a altura do nó.
}

// Função que calcula o fator de balanceamento de um nó da árvore de notas.
// O fator de balanceamento é a diferença entre a altura da subárvore esquerda
// e a altura da subárvore direita de um nó.
// Se o nó for NULL, o fator de balanceamento será 0.
// Caso contrário, calcula-se a altura da subárvore esquerda e a da subárvore direita
// e a diferença entre elas é retornada como o fator de balanceamento.
short fator_balanceamento_nota(arvore_notas *no)
{
    short fb = 0; // Variável para armazenar o fator de balanceamento.

    if (no != NULL) // Verifica se o nó não é NULL.
    {
        // Calcula o fator de balanceamento como a diferença entre as alturas
        // das subárvores esquerda e direita.
        fb = altura_do_no_nota(no->esq) - altura_do_no_nota(no->dir);
    }

    return fb; // Retorna o fator de balanceamento.
}

// Função que realiza uma rotação à esquerda em um nó da árvore de notas.
// Esta operação é utilizada para reequilibrar a árvore quando a subárvore direita
// de um nó se torna mais alta que a subárvore esquerda, geralmente durante a
// inserção de um novo nó na árvore.
//
// Parâmetros:
// - no: ponteiro para o nó que será rotacionado à esquerda.
//
// Retorna:
// - Um ponteiro para o novo nó raiz da subárvore após a rotação.
arvore_notas *rotar_esquerda_nota(arvore_notas *no)
{
    arvore_notas *aux, *aux1; // Ponteiros auxiliares para realizar a rotação.

    aux = no->dir;   // O nó à direita do nó atual se torna o novo nó raiz.
    aux1 = aux->esq; // O filho esquerdo do novo nó raiz é armazenado para realocar.

    aux->esq = no;  // O nó atual se torna o filho esquerdo do novo nó raiz.
    no->dir = aux1; // O filho esquerdo do novo nó raiz se torna o novo filho direito do nó atual.

    // Atualiza a altura do nó atual e do novo nó raiz após a rotação.
    no->altura = maior_no_nota(altura_do_no_nota(no->esq), altura_do_no_nota(no->dir)) + 1;
    aux->altura = maior_no_nota(altura_do_no_nota(aux->esq), altura_do_no_nota(aux->dir)) + 1;

    return aux; // Retorna o novo nó raiz da subárvore.
}

// Função que realiza uma rotação à direita em um nó da árvore de notas.
// Esta operação é utilizada para reequilibrar a árvore quando a subárvore esquerda
// de um nó se torna mais alta que a subárvore direita, geralmente durante a
// inserção de um novo nó na árvore.
//
// Parâmetros:
// - no: ponteiro para o nó que será rotacionado à direita.
//
// Retorna:
// - Um ponteiro para o novo nó raiz da subárvore após a rotação.
arvore_notas *rotar_direita_nota(arvore_notas *no)
{
    arvore_notas *aux, *aux1; // Ponteiros auxiliares para realizar a rotação.

    aux = no->esq;   // O nó à esquerda do nó atual se torna o novo nó raiz.
    aux1 = aux->dir; // O filho direito do novo nó raiz é armazenado para realocar.

    aux->dir = no;  // O nó atual se torna o filho direito do novo nó raiz.
    no->esq = aux1; // O filho direito do novo nó raiz se torna o novo filho esquerdo do nó atual.

    // Atualiza a altura do nó atual e do novo nó raiz após a rotação.
    no->altura = maior_no_nota(altura_do_no_nota(no->esq), altura_do_no_nota(no->dir)) + 1;
    aux->altura = maior_no_nota(altura_do_no_nota(aux->esq), altura_do_no_nota(aux->dir)) + 1;

    return aux; // Retorna o novo nó raiz da subárvore.
}

// Função que realiza uma rotação dupla (direita seguida de esquerda) em um nó da árvore de notas.
// Esta operação é utilizada para reequilibrar a árvore quando a subárvore direita do nó
// se torna mais alta, e a subárvore esquerda do filho direito é maior, indicando a necessidade
// de um ajuste mais complexo na estrutura da árvore.
//
// Parâmetros:
// - no: ponteiro para o nó que será rotacionado.
//
// Retorna:
// - Um ponteiro para o novo nó raiz da subárvore após a rotação dupla.
arvore_notas *rotar_direita_esquerda_nota(arvore_notas *no)
{
    no->dir = rotar_direita_nota(no->dir); // Realiza uma rotação à direita na subárvore direita do nó.
    return rotar_esquerda_nota(no);        // Realiza uma rotação à esquerda no nó atual após a rotação direita.
}

// Função que realiza uma rotação dupla (esquerda seguida de direita) em um nó da árvore de notas.
// Esta operação é utilizada para reequilibrar a árvore quando a subárvore esquerda do nó
// se torna mais alta, e a subárvore direita do filho esquerdo é maior, indicando a necessidade
// de um ajuste mais complexo na estrutura da árvore.
//
// Parâmetros:
// - no: ponteiro para o nó que será rotacionado.
//
// Retorna:
// - Um ponteiro para o novo nó raiz da subárvore após a rotação dupla.
arvore_notas *rotar_esquerda_direita_nota(arvore_notas *no)
{
    no->esq = rotar_esquerda_nota(no->esq); // Realiza uma rotação à esquerda na subárvore esquerda do nó.
    return rotar_direita_nota(no);          // Realiza uma rotação à direita no nó atual após a rotação esquerda.
}

// Função que balanceia a árvore de notas após uma operação de inserção ou remoção.
// Esta função verifica o fator de balanceamento do nó raiz e executa as rotações
// necessárias para manter a árvore balanceada, utilizando as regras de balanceamento
// das árvores AVL.
//
// Parâmetros:
// - raiz: ponteiro para o nó raiz da árvore a ser balanceada.
//
// Retorna:
// - Um ponteiro para o novo nó raiz da árvore balanceada após as rotações.
arvore_notas *balencar_arvore_nota(arvore_notas *raiz)
{
    short fb = fator_balanceamento_nota(raiz); // Calcula o fator de balanceamento do nó raiz.

    // Se o fator de balanceamento for negativo e o fator da subárvore direita for 0 ou negativo,
    // realiza uma rotação à esquerda.
    if (fb < -1 && fator_balanceamento_nota(raiz->dir) <= 0)
    {
        raiz = rotar_esquerda_nota(raiz);
    }
    // Se o fator de balanceamento for positivo e o fator da subárvore esquerda for 0 ou positivo,
    // realiza uma rotação à direita.
    else if (fb > 1 && fator_balanceamento_nota(raiz->esq) >= 0)
    {
        raiz = rotar_direita_nota(raiz);
    }
    // Se o fator de balanceamento for positivo e o fator da subárvore esquerda for negativo,
    // realiza uma rotação dupla: esquerda e depois direita.
    else if (fb > 1 && fator_balanceamento_nota(raiz->esq) < 0)
    {
        raiz = rotar_esquerda_direita_nota(raiz);
    }
    // Se o fator de balanceamento for negativo e o fator da subárvore direita for positivo,
    // realiza uma rotação dupla: direita e depois esquerda.
    else if (fb < -1 && fator_balanceamento_nota(raiz->dir) > 0)
    {
        raiz = rotar_direita_esquerda_nota(raiz);
    }

    return raiz; // Retorna o novo nó raiz da árvore balanceada.
}

// Função para criar um novo nó da árvore de notas.
// Esta função aloca memória para um novo nó da árvore do tipo 'arvore_notas',
// inicializa os ponteiros 'esq' e 'dir' como NULL, e define a altura como 0.
// Retorna um ponteiro para o novo nó criado.
arvore_notas *criar_nota()
{
    arvore_notas *no = (arvore_notas *)malloc(sizeof(arvore_notas)); // Aloca memória para um novo nó.
    no->esq = NULL;                                                  // Inicializa o ponteiro esquerdo como NULL.
    no->dir = NULL;                                                  // Inicializa o ponteiro direito como NULL.
    no->altura = 0;                                                  // Define a altura do nó como 0.
    return no;                                                       // Retorna o ponteiro para o novo nó criado.
}

// Função que insere um novo nó na árvore de notas, garantindo que a árvore
// permaneça balanceada após a inserção. A inserção é realizada de acordo com
// o valor do código da disciplina, que determina a posição do novo nó na árvore.
//
// Parâmetros:
// - raiz: ponteiro para o nó raiz da árvore onde o novo nó será inserido.
// - no: ponteiro para o nó que será inserido na árvore.
//
// Retorna:
// - Um ponteiro para o novo nó raiz da árvore após a inserção e balanceamento.
arvore_notas *inserir_nota(arvore_notas *raiz, arvore_notas *no)
{
    // Se a raiz for NULL, significa que a árvore está vazia e o novo nó se torna a raiz.
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        // Compara o código da disciplina do novo nó com o da raiz
        // para determinar em qual subárvore inserir o novo nó.
        if (no->codigo_disciplina < raiz->codigo_disciplina)
        {
            // Insere na subárvore esquerda se o código da disciplina for menor.
            raiz->esq = inserir_nota(raiz->esq, no);
        }
        else
        {
            // Caso contrário, insere na subárvore direita.
            raiz->dir = inserir_nota(raiz->dir, no);
        }
    }

    // Após a inserção, balanceia a árvore.
    raiz = balencar_arvore_nota(raiz);

    // Atualiza a altura do nó raiz após a inserção e balanceamento.
    raiz->altura = maior_no_nota(altura_do_no_nota(raiz->esq), altura_do_no_nota(raiz->dir)) + 1;

    return raiz; // Retorna o novo nó raiz da árvore.
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

// Função que remove um nó da árvore de notas com base no código da disciplina,
// garantindo que a árvore permaneça balanceada após a remoção. A função utiliza
// as regras de uma árvore binária de busca para localizar e remover o nó.
//
// Parâmetros:
// - raiz: ponteiro para o nó raiz da árvore onde o nó será removido.
// - codigo_disciplina: o código da disciplina do nó a ser removido.
//
// Retorna:
// - Um ponteiro para o novo nó raiz da árvore após a remoção e balanceamento.
arvore_notas *remover_nota(arvore_notas *raiz, int codigo_disciplina)
{
    if (raiz != NULL) // Verifica se a árvore não está vazia.
    {
        // Se o código da disciplina a ser removido for menor que o da raiz,
        // busca na subárvore esquerda.
        if (codigo_disciplina < raiz->codigo_disciplina)
        {
            raiz->esq = remover_nota(raiz->esq, codigo_disciplina);
        }
        // Se o código da disciplina for maior, busca na subárvore direita.
        else if (codigo_disciplina > raiz->codigo_disciplina)
        {
            raiz->dir = remover_nota(raiz->dir, codigo_disciplina);
        }
        // Se o código da disciplina for igual, encontramos o nó a ser removido.
        else
        {
            // Caso 1: O nó a ser removido não tem filho à esquerda.
            if (raiz->esq == NULL)
            {
                arvore_notas *temp = raiz->dir; // Armazena o filho direito.
                free(raiz);                     // Libera a memória do nó atual.
                raiz = temp;                    // Retorna o filho direito como nova raiz.
            }
            // Caso 2: O nó a ser removido não tem filho à direita.
            else if (raiz->dir == NULL)
            {
                arvore_notas *temp = raiz->esq; // Armazena o filho esquerdo.
                free(raiz);                     // Libera a memória do nó atual.
                raiz = temp;                    // Retorna o filho esquerdo como nova raiz.
            }
            // Caso 3: O nó a ser removido tem ambos os filhos.
            else
            {
                // Encontra o menor nó na subárvore direita (sucessor).
                arvore_notas *temp = raiz->dir;
                while (temp->esq != NULL)
                {
                    temp = temp->esq;
                }

                // Substitui o código da disciplina do nó a ser removido
                // pelo código do sucessor.
                raiz->codigo_disciplina = temp->codigo_disciplina;

                // Remove o sucessor encontrado da subárvore direita.
                raiz->dir = remover_nota(raiz->dir, temp->codigo_disciplina);
            }
        }

        // Atualiza a altura do nó raiz após a remoção, se a raiz não for NULL.
        if (raiz != NULL)
        {
            raiz->altura = maior_no_nota(altura_do_no_nota(raiz->esq), altura_do_no_nota(raiz->dir)) + 1;

            // Balanceia a árvore após a remoção.
            raiz = balencar_arvore_nota(raiz);
        }
    }

    return raiz; // Retorna o novo nó raiz da árvore.
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
int contar_nos(arvore_notas *raiz)
{
    int cont = 0;
    // Alterada a condição para contar apenas se ambos os filhos são NULL
    if (raiz != NULL)
    { // Adicionei uma verificação para garantir que a raiz não seja NULL
        if (raiz->esq != NULL || raiz->dir != NULL)
        {
            cont++; // Conta se o nó não tem filhos
        }
        cont += contar_nos(raiz->dir);
        cont += contar_nos(raiz->esq);
    }
    return cont;
}
