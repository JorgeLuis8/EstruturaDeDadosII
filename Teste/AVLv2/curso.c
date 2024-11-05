#include "curso.h"
#include "disciplinas.h"
#include "Alunos.h"
#include <stdlib.h>
#include <stdio.h>

short maior_no_curso(short a, short b)
{
    // Verifica se 'a' é maior que 'b'
    // Se verdadeiro, retorna 'a'; caso contrário, retorna 'b'
    return (a > b) ? a : b; 
}


short altura_do_no_curso(Arvore_curso *no)
{
    short altura; // Declara uma variável para armazenar a altura do nó

    // Verifica se o nó é nulo
    if (no == NULL)
    {
        // Se o nó for nulo, a altura é -1 (indicando que não há árvore)
        altura = -1; 
    }
    else
    {
        // Se o nó não for nulo, armazena a altura do nó na variável 'altura'
        altura = no->altura; 
    }

    // Retorna a altura do nó
    return altura; 
}


short fator_balanceamento_curso(Arvore_curso *no)
{
    short fb = 0; // Inicializa a variável fb para armazenar o fator de balanceamento

    // Verifica se o nó não é nulo
    if (no != NULL)
    {
        // Calcula o fator de balanceamento como a diferença entre a altura da subárvore esquerda e a altura da subárvore direita
        fb = altura_do_no_curso(no->esq) - altura_do_no_curso(no->dir);
    }

    // Retorna o fator de balanceamento
    return fb; 
}


Arvore_curso *rotar_esquerda_curso(Arvore_curso *no)
{
    Arvore_curso *aux, *aux1;

    // 1. Armazena o filho à direita do nó atual (no) em aux
    aux = no->dir; 

    // 2. Armazena o filho à esquerda de aux em aux1
    aux1 = aux->esq; 

    // 3. Realiza a rotação à esquerda
    // O filho à direita (aux) se torna a nova raiz da subárvore
    aux->esq = no; 
    // O filho à esquerda de aux se torna o novo filho à direita de no
    no->dir = aux1; 

    // 4. Atualiza a altura do nó atual (no)
    // A altura do nó atual é definida como a altura máxima entre suas subárvores + 1
    no->altura = maior_no_curso(altura_do_no_curso(no->esq), altura_do_no_curso(no->dir)) + 1; 

    // 5. Atualiza a altura do novo nó (aux) que se tornou a nova raiz
    // A altura é atualizada da mesma forma
    aux->altura = maior_no_curso(altura_do_no_curso(aux->esq), altura_do_no_curso(aux->dir)) + 1; 

    // 6. Retorna o novo nó (aux), que agora é a raiz da subárvore rotacionada
    return aux; 
}


Arvore_curso *rotar_direita_curso(Arvore_curso *no)
{
    Arvore_curso *aux, *aux1;

    // 1. Armazena o filho à esquerda do nó atual (no) em aux
    aux = no->esq; 

    // 2. Armazena o filho à direita de aux em aux1
    aux1 = aux->dir; 

    // 3. Realiza a rotação à direita
    // O filho à esquerda (aux) se torna a nova raiz da subárvore
    aux->dir = no; 
    // O filho à direita de aux se torna o novo filho à esquerda de no
    no->esq = aux1; 

    // 4. Atualiza a altura do nó atual (no)
    // A altura do nó atual é definida como a altura máxima entre suas subárvores + 1
    no->altura = maior_no_curso(altura_do_no_curso(no->esq), altura_do_no_curso(no->dir)) + 1; 

    // 5. Atualiza a altura do novo nó (aux) que se tornou a nova raiz
    // A altura é atualizada da mesma forma
    aux->altura = maior_no_curso(altura_do_no_curso(aux->esq), altura_do_no_curso(aux->dir)) + 1; 

    // 6. Retorna o novo nó (aux), que agora é a raiz da subárvore rotacionada
    return aux; 
}


Arvore_curso *rotar_direita_esquerda_curso(Arvore_curso *no)
{
    // 1. Realiza uma rotação à direita no filho à direita do nó atual (no)
    // Isso prepara o nó para a rotação à esquerda que será feita em seguida
    no->dir = rotar_direita_curso(no->dir); 

    // 2. Realiza uma rotação à esquerda no nó atual (no)
    // A rotação à esquerda agora se torna a nova raiz da subárvore
    return rotar_esquerda_curso(no); 
}

Arvore_curso *rotar_esquerda_direita_curso(Arvore_curso *no)
{
    // 1. Realiza uma rotação à esquerda no filho à esquerda do nó atual (no)
    // Isso prepara o nó para a rotação à direita que será feita em seguida
    no->esq = rotar_esquerda_curso(no->esq); 

    // 2. Realiza uma rotação à direita no nó atual (no)
    // A rotação à direita agora se torna a nova raiz da subárvore
    return rotar_direita_curso(no); 
}
Arvore_curso *balencar_arvore_curso(Arvore_curso *raiz)
{
    // 1. Calcula o fator de balanceamento da árvore a partir da raiz
    short fb = fator_balanceamento_curso(raiz);

    // 2. Verifica se a árvore está desbalanceada para o lado direito
    if (fb < -1 && fator_balanceamento_curso(raiz->dir) <= 0)
    {
        // 2.1. Caso de desbalanceamento à direita: realiza rotação à esquerda
        raiz = rotar_esquerda_curso(raiz);
    }
    // 3. Verifica se a árvore está desbalanceada para o lado esquerdo
    else if (fb > 1 && fator_balanceamento_curso(raiz->esq) >= 0)
    {
        // 3.1. Caso de desbalanceamento à esquerda: realiza rotação à direita
        raiz = rotar_direita_curso(raiz);
    }
    // 4. Verifica o caso de desbalanceamento à esquerda, onde o filho à esquerda é desbalanceado para a direita
    else if (fb > 1 && fator_balanceamento_curso(raiz->esq) < 0)
    {
        // 4.1. Realiza uma rotação à esquerda no filho à esquerda, seguida de rotação à direita
        raiz = rotar_esquerda_direita_curso(raiz);
    }
    // 5. Verifica o caso de desbalanceamento à direita, onde o filho à direita é desbalanceado para a esquerda
    else if (fb < -1 && fator_balanceamento_curso(raiz->dir) > 0)
    {
        // 5.1. Realiza uma rotação à direita no filho à direita, seguida de rotação à esquerda
        raiz = rotar_direita_esquerda_curso(raiz);
    }

    // 6. Retorna a nova raiz da árvore balanceada
    return raiz;
}

Arvore_curso *criar_curso()
{
    Arvore_curso *curso = (Arvore_curso *)malloc(sizeof(Arvore_curso));
    if (curso == NULL)
    {
        printf("Erro ao alocar memória para o curso\n");
        exit(1);
    }
    curso->raiz_disciplinas = NULL;
    curso->esq = NULL;
    curso->dir = NULL;
    curso->altura = 0;
    return curso;
}

Arvore_curso *inserir_curso(Arvore_curso *raiz, Arvore_curso *no)
{
    // 1. Verifica se a raiz está vazia (árvore vazia)
    if (raiz == NULL)
    {
        // 1.1. Se estiver vazia, o novo nó se torna a raiz
        raiz = no;
    }
    else
    {
        // 2. Compara o código do novo nó com o da raiz
        if (no->codigo < raiz->codigo)
        {
            // 2.1. Se o código do novo nó for menor, insere na subárvore esquerda
            raiz->esq = inserir_curso(raiz->esq, no);
        }
        else
        {
            // 2.2. Se o código do novo nó for maior ou igual, insere na subárvore direita
            raiz->dir = inserir_curso(raiz->dir, no);
        }
    }
    
    // 3. Após a inserção, a árvore pode estar desbalanceada, então chamamos a função de balanceamento
    raiz = balencar_arvore_curso(raiz);

    // 4. Atualiza a altura do nó atual
    raiz->altura = maior_no_curso(altura_do_no_curso(raiz->esq), altura_do_no_curso(raiz->dir)) + 1;

    // 5. Retorna a nova raiz (que pode ser diferente se houve rotação)
    return raiz;
}


void imprimir_cursos(Arvore_curso *raiz)
{
    if (raiz != NULL)
    {
        imprimir_cursos(raiz->esq);
        printf("Codigo: %d\n", raiz->codigo);
        printf("Nome: %s\n", raiz->nome);
        printf("Periodo: %d\n", raiz->periodo);
        printf("\n");
        imprimir_cursos(raiz->dir);
    }
}

Arvore_curso *buscar_curso(Arvore_curso *raiz, int codigo)
{
    Arvore_curso *aux = NULL;
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
                aux = buscar_curso(raiz->esq, codigo);
            }
            else
            {
                aux = buscar_curso(raiz->dir, codigo);
            }
        }
    }
    return aux;
}

Arvore_curso *remover_curso(Arvore_curso *raiz, int codigo)
{
    // 1. Verifica se a raiz não é nula (árvore não está vazia)
    if (raiz != NULL)
    {
        // 2. Compara o código a ser removido com o código da raiz
        if (codigo < raiz->codigo)
        {
            // 2.1. Se o código for menor, chama a função recursivamente na subárvore esquerda
            raiz->esq = remover_curso(raiz->esq, codigo);
        }
        else if (codigo > raiz->codigo)
        {
            // 2.2. Se o código for maior, chama a função recursivamente na subárvore direita
            raiz->dir = remover_curso(raiz->dir, codigo);
        }
        else // 3. Caso em que o código a ser removido é encontrado
        {
            // 3.1. Caso 1: O nó é uma folha (sem filhos)
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz); // Libera a memória do nó
                raiz = NULL; // Define a raiz como nula
            }
            // 3.2. Caso 2: O nó tem apenas um filho à direita
            else if (raiz->esq == NULL)
            {
                Arvore_curso *aux = raiz; // Salva o nó a ser removido
                raiz = raiz->dir; // Move a raiz para o filho à direita
                free(aux); // Libera a memória do nó removido
            }
            // 3.3. Caso 3: O nó tem apenas um filho à esquerda
            else if (raiz->dir == NULL)
            {
                Arvore_curso *aux = raiz; // Salva o nó a ser removido
                raiz = raiz->esq; // Move a raiz para o filho à esquerda
                free(aux); // Libera a memória do nó removido
            }
            // 3.4. Caso 4: O nó tem dois filhos
            else
            {
                // 3.4.1. Encontra o maior nó na subárvore esquerda
                Arvore_curso *aux = raiz->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir; // Vai para o maior nó
                }
                // 3.4.2. Substitui o código do nó atual pelo código do maior nó encontrado
                raiz->codigo = aux->codigo;
                // 3.4.3. Remove o maior nó da subárvore esquerda
                raiz->esq = remover_curso(raiz->esq, aux->codigo);
            }
        }

        // 4. Após a remoção, atualiza a altura e balanceia a árvore
        if (raiz != NULL)
        {
            // 4.1. Atualiza a altura do nó atual
            raiz->altura = maior_no_curso(altura_do_no_curso(raiz->esq), altura_do_no_curso(raiz->dir)) + 1;
            // 4.2. Balanceia a árvore após a remoção
            raiz = balencar_arvore_curso(raiz);
        }
    }
    // 5. Retorna a nova raiz (que pode ter mudado após a remoção)
    return raiz;
}


void imprimir_historico(Aluno *aluno, Arvore_curso *raiz_cursos)
{
    Arvore_curso *curso = buscar_curso(raiz_cursos, aluno->codigo_curso);
    if (curso == NULL)
    {
        printf("Curso nao encontrado.\n");
    }

    printf("Curso: %s\n", curso->nome);

    imprimir_historico_disciplinas(aluno->raiz_notas, curso->raiz_disciplinas);
}
