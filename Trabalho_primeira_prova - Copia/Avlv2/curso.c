#include "curso.h"
#include "disciplinas.h"
#include "alunos.h"
#include <stdlib.h>
#include <stdio.h>


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
    return curso;
}

void ler_dados_curso(Arvore_curso *curso)
{
    printf("Digite o codigo do curso: ");
    scanf("%d", &curso->codigo);

    printf("Digite o nome do curso: ");
    scanf(" %[^\n]", curso->nome);

    printf("Digite o periodo do curso: ");
    scanf("%d", &curso->periodo);
}

Arvore_curso *inserir_curso(Arvore_curso *curso, Arvore_curso *no)
{
    if (curso == NULL)
    {
        curso = no;
    }
    else
    {
        if (no->codigo < curso->codigo)
        {
            curso->esq = inserir_curso(curso->esq, no);
        }
        else
        {
            curso->dir = inserir_curso(curso->dir, no);
        }
    }
    curso->altura = maior_no_curso(altura_do_no_curso(curso->esq), altura_do_no_curso(curso->dir)) + 1;
    curso = balancear_arvore_curso(curso);
    return curso;
}

void imprimir_cursos(Arvore_curso *curso)
{
    if (curso != NULL)
    {
        imprimir_cursos(curso->esq);
        printf("Codigo: %d\n", curso->codigo);
        printf("Nome: %s\n", curso->nome);
        printf("Periodo: %d\n", curso->periodo);
        printf("\n");
        imprimir_cursos(curso->dir);
    }
}

Arvore_curso *buscar_curso (Arvore_curso *curso, int codigo)
{
    Arvore_curso *aux = NULL;
    if (curso != NULL)
    {
        if (codigo == curso->codigo)
        {
            aux = curso;
        }
        else
        {
            if (codigo < curso->codigo)
            {
                aux = buscar_curso(curso->esq, codigo);
            }
            else
            {
                aux = buscar_curso(curso->dir, codigo);
            }
        }
    }
    return aux;
}

Arvore_curso *remover_curso(Arvore_curso *curso, int codigo)
{
    if (curso != NULL)
    {
        if (codigo < curso->codigo)
        {
            curso->esq = remover_curso(curso->esq, codigo);
        }
        else if (codigo > curso->codigo)
        {
            curso->dir = remover_curso(curso->dir, codigo);
        }
        else
        {
            if (curso->esq == NULL && curso->dir == NULL)
            {
                free(curso);
                curso = NULL;
            }
            else if (curso->esq == NULL)
            {
                Arvore_curso *aux = curso;
                curso = curso->dir;
                free(aux);
            }
            else if (curso->dir == NULL)
            {
                Arvore_curso *aux = curso;
                curso = curso->esq;
                free(aux);
            }
            else
            {
                Arvore_curso *aux = curso->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir;
                }
                curso->codigo = aux->codigo;
                curso->esq = remover_curso(curso->esq, aux->codigo);
            }
        }
    }
    curso->altura = maior_no_curso(altura_do_no_curso(curso->esq), altura_do_no_curso(curso->dir)) + 1;
    curso = balancear_arvore_curso(curso);
    return curso;


}

void imprimir_historico(Aluno *aluno, Arvore_curso *raiz_cursos)
{
    // Buscar o curso do aluno
    Arvore_curso *curso = buscar_curso(raiz_cursos, aluno->codigo_curso);
    if (curso == NULL)
    {
        printf("Curso nao encontrado.\n");
        return;
    }

    // Imprimir o nome do curso
    printf("Curso: %s\n", curso->nome);

    // Imprimir as disciplinas e notas do aluno
    imprimir_historico_disciplinas(aluno->raiz_notas, curso->raiz_disciplinas);
}

short maior_no_curso(short a, short b)
{
    return (a > b) ? a : b;
}

short altura_do_no_curso(Arvore_curso *no)
{
    short altura;

    if (no == NULL)
    {
        altura = -1;
    }
    else
    {
        altura = no->altura;
    }

    return altura;
}

short fator_balanceamento_curso(Arvore_curso *no)
{
    short fb = 0;

    if (no != NULL)
    {
        fb = altura_do_no_curso(no->esq) - altura_do_no_curso(no->dir);
    }

    return fb;
}

Arvore_curso *rotar_esquerda_curso(Arvore_curso *no)
{
    Arvore_curso *aux, *aux1;

    aux = no->dir;
    aux1 = aux->esq;

    aux->esq = no;
    no->dir = aux1;

    no->altura = maior_no_curso(altura_do_no_curso(no->esq), altura_do_no_curso(no->dir)) + 1;
    aux->altura = maior_no_curso(altura_do_no_curso(aux->esq), altura_do_no_curso(aux->dir)) + 1;

    return aux;
}

Arvore_curso *rotar_direita_curso(Arvore_curso *no)
{
    Arvore_curso *aux, *aux1;

    aux = no->esq;
    aux1 = aux->dir;

    aux->dir = no;
    no->esq = aux1;

    no->altura = maior_no_curso(altura_do_no_curso(no->esq), altura_do_no_curso(no->dir)) + 1;
    aux->altura = maior_no_curso(altura_do_no_curso(aux->esq), altura_do_no_curso(aux->dir)) + 1;

    return aux;
}

Arvore_curso *rotar_direita_esquerda_podcast(Arvore_curso *no)
{
    no->dir = rotar_direita_curso(no->dir);
    return rotar_esquerda_curso(no);
}

Arvore_curso *rotar_esquerda_direita_curso(Arvore_curso *no)
{
    no->esq = rotar_esquerda_curso(no->esq);
    return rotar_direita_curso(no);
}

Arvore_curso *balencar_arvore_curso(Arvore_curso *raiz)
{
    short fb = fator_balanceamento_curso(raiz);

    if (fb < -1 && fator_balanceamento_curso(raiz->dir) <= 0)
    {
        raiz = rotar_esquerda_curso(raiz);
    }
    else if (fb > 1 && fator_balanceamento_curso(raiz->esq) >= 0)
    {
        raiz = rotar_direita_curso(raiz);
    }
    else if (fb > 1 && fator_balanceamento_curso(raiz->esq) < 0)
    {
        raiz = rotar_esquerda_direita_curso(raiz);
    }
    else if (fb < -1 && fator_balanceamento_curso(raiz->dir) > 0)
    {
        raiz = rotar_direita_esquerda_curso(raiz);
    }
    return raiz;
}