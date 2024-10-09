#include "disciplinas.h"
#include <stdio.h>
#include <stdlib.h>


short maior_no_disc(short a, short b)
{
    return (a > b) ? a : b;
}

short altura_do_no_disc(arvore_disciplinas *no)
{
    if (no == NULL)
    {
        return -1;
    }
    return no->altura;
}

short fator_balanceamento_disc(arvore_disciplinas *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return altura_do_no_disc(no->esq) - altura_do_no_disc(no->dir);
}

 arvore_disciplinas *rotar_esquerda_disc(arvore_disciplinas *no)
{
    arvore_disciplinas *aux, *aux1;

    aux = no->dir;
    aux1 = aux->esq;

    aux->esq = no;
    no->dir = aux1;

    no->altura = maior_no_disc(altura_do_no_disc(no->esq), altura_do_no_disc(no->dir)) + 1;
    aux->altura = maior_no_disc(altura_do_no_disc(aux->esq), altura_do_no_disc(aux->dir)) + 1;

    return aux;
}

arvore_disciplinas *rotar_direita_disc(arvore_disciplinas *no)
{
    arvore_disciplinas *aux, *aux1;

    aux = no->esq;
    aux1 = aux->dir;

    aux->dir = no;
    no->esq = aux1;

    no->altura = maior_no_disc(altura_do_no_disc(no->esq), altura_do_no_disc(no->dir)) + 1;
    aux->altura = maior_no_disc(altura_do_no_disc(aux->esq), altura_do_no_disc(aux->dir)) + 1;

    return aux;
}

arvore_disciplinas *rotar_direita_esquerda_disc(arvore_disciplinas *no)
{
    no->dir = rotar_direita_disc(no->dir);
    return rotar_esquerda_disc(no);
}

 arvore_disciplinas *rotar_esquerda_direita_disc(arvore_disciplinas *no)
{
    no->esq = rotar_esquerda_disc(no->esq);
    return rotar_direita_disc(no);
}

arvore_disciplinas *balencar_arvore_disc(arvore_disciplinas *raiz)
{
    short fb = fator_balanceamento_disc(raiz);

    if (fb < -1 && fator_balanceamento_disc(raiz->dir) <= 0)
    {
        raiz = rotar_esquerda_disc(raiz);
    }
    else if (fb > 1 && fator_balanceamento_disc(raiz->esq) >= 0)
    {
        raiz = rotar_direita_disc(raiz);
    }
    else if (fb > 1 && fator_balanceamento_disc(raiz->esq) < 0)
    {
        raiz = rotar_esquerda_direita_disc(raiz);
    }
    else if (fb < -1 && fator_balanceamento_disc(raiz->dir) > 0)
    {
        raiz = rotar_direita_esquerda_disc(raiz);
    }
    return raiz;
}

arvore_disciplinas *criar_disciplina()
{
    arvore_disciplinas *disciplina = (arvore_disciplinas *)malloc(sizeof(arvore_disciplinas));
    if (disciplina == NULL)
    {
        printf("Erro ao alocar memória para a disciplina\n");
        exit(1);
    }
    disciplina->esq = NULL;
    disciplina->dir = NULL;
    disciplina->altura = 0;
    return disciplina;
}

arvore_disciplinas *inserir_disciplina(arvore_disciplinas *raiz, arvore_disciplinas *no)
{
    
    if (raiz == NULL)
    {
        raiz = no;
    }
    else
    {
        if (no->codigo < raiz->codigo)
        {
            raiz->esq = inserir_disciplina(raiz->esq, no);
        }
        else
        {
            raiz->dir = inserir_disciplina(raiz->dir, no);
        }
    }
    raiz->altura = maior_no_disc(altura_do_no_disc(raiz->esq), altura_do_no_disc(raiz->dir)) + 1;
    raiz = balencar_arvore_disc(raiz);
    
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
    // Localiza o nó a ser removido
    if (raiz != NULL)
    {
        if (codigo < raiz->codigo)
        {
            raiz->esq = remover_disciplina(raiz->esq, codigo);
        }
        else if (codigo > raiz->codigo)
        {
            raiz->dir = remover_disciplina(raiz->dir, codigo);
        }
        else // Caso encontrado (nó a ser removido)
        {
            // Caso 1: Nó com apenas um filho ou nenhum
            if (raiz->esq == NULL)
            {
                arvore_disciplinas *temp = raiz->dir; // Salva o filho direito
                free(raiz); // Libera a memória do nó
                raiz = temp; // Atualiza a raiz para o filho direito
            }
            else if (raiz->dir == NULL)
            {
                arvore_disciplinas *temp = raiz->esq; // Salva o filho esquerdo
                free(raiz); // Libera a memória do nó
                raiz = temp; // Atualiza a raiz para o filho esquerdo
            }
            else // Caso 2: Nó com dois filhos
            {
                // Obter o sucessor (menor nó da subárvore direita)
                arvore_disciplinas *temp = raiz->dir;
                while (temp->esq != NULL)
                {
                    temp = temp->esq; // Encontra o menor nó na subárvore direita
                }

                // Substitui o valor do nó a ser removido pelo valor do sucessor
                raiz->codigo = temp->codigo;

                // Remove o sucessor
                raiz->dir = remover_disciplina(raiz->dir, temp->codigo);
            }
        }

        // Atualizar a altura do nó atual
        if (raiz != NULL) // Verifica se a raiz ainda é válida
        {
            raiz->altura = maior_no_disc(altura_do_no_disc(raiz->esq), altura_do_no_disc(raiz->dir)) + 1;

            // Balancear a árvore
            raiz = balencar_arvore_disc(raiz);
        }
    }

    return raiz; // Retorna a raiz balanceada apenas no final
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
void imprimir_disciplinas_periodo(arvore_disciplinas *raiz, int periodo){
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
        // Imprimir as notas da disciplina
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

        // Imprimir as disciplinas do lado esquerdo
        imprimir_historico_disciplinas(raiz_notas, raiz_disciplinas->esq);

        // Imprimir as disciplinas do lado direito
        imprimir_historico_disciplinas(raiz_notas, raiz_disciplinas->dir);
    }
}