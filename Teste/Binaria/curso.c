#include "curso.h"
#include "disciplinas.h"
#include "alunos.h"
#include <stdlib.h>
#include <stdio.h>

Arvore_curso *criar_curso()
{
    // Aloca memória para um novo curso, usando "malloc" para reservar o espaço necessário
    // para a estrutura "Arvore_curso" e retorna um ponteiro para esse espaço.
    Arvore_curso *curso = (Arvore_curso *)malloc(sizeof(Arvore_curso));

    // Verifica se a alocação de memória foi bem-sucedida.
    // Caso contrário, exibe uma mensagem de erro e encerra o programa.
    if (curso == NULL)
    {
        printf("Erro ao alocar memória para o curso\n");
        exit(1);
    }

    // Inicializa o ponteiro "raiz_disciplinas" como NULL,
    // indicando que o curso ainda não possui disciplinas cadastradas.
    curso->raiz_disciplinas = NULL;

    // Inicializa os ponteiros "esq" e "dir" como NULL,
    // indicando que o curso não possui filhos à esquerda nem à direita na árvore.
    curso->esq = NULL;
    curso->dir = NULL;

    // Retorna o ponteiro para o novo curso, com todos os campos inicializados.
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
    // Caso a árvore (ou subárvore) esteja vazia, o nó a ser inserido se torna a nova raiz.
    if (curso == NULL)
    {
        curso = no; // Define o nó como a raiz da subárvore.
    }
    else
    {
        // Se o código do novo curso for menor que o código do curso atual,
        // a função insere o nó na subárvore esquerda.
        if (no->codigo < curso->codigo)
        {
            curso->esq = inserir_curso(curso->esq, no);
        }
        else
        {
            // Caso contrário, insere o nó na subárvore direita.
            curso->dir = inserir_curso(curso->dir, no);
        }
    }
    
    // Retorna o ponteiro para a raiz da árvore ou subárvore, que pode ter sido atualizado.
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

Arvore_curso *buscar_curso(Arvore_curso *curso, int codigo)
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
    // Verifica se a árvore (ou subárvore) não está vazia.
    if (curso != NULL)
    {
        // Se o código do curso a ser removido é menor que o código do curso atual,
        // faz a chamada recursiva para remover o curso na subárvore esquerda.
        if (codigo < curso->codigo)
        {
            curso->esq = remover_curso(curso->esq, codigo);
        }
        // Se o código do curso a ser removido é maior que o código do curso atual,
        // faz a chamada recursiva para remover o curso na subárvore direita.
        else if (codigo > curso->codigo)
        {
            curso->dir = remover_curso(curso->dir, codigo);
        }
        // Caso contrário, encontrou o nó a ser removido.
        else
        {
            // Caso 1: O nó não possui filhos (é uma folha).
            if (curso->esq == NULL && curso->dir == NULL)
            {
                free(curso);  // Libera a memória do nó.
                curso = NULL; // Define o ponteiro para NULL, removendo o nó da árvore.
            }
            // Caso 2: O nó possui apenas um filho à direita.
            else if (curso->esq == NULL)
            {
                Arvore_curso *aux = curso; // Salva o nó atual em uma variável auxiliar.
                curso = curso->dir;        // Substitui o nó atual pelo seu filho à direita.
                free(aux);                 // Libera a memória do nó removido.
            }
            // Caso 2: O nó possui apenas um filho à esquerda.
            else if (curso->dir == NULL)
            {
                Arvore_curso *aux = curso; // Salva o nó atual em uma variável auxiliar.
                curso = curso->esq;        // Substitui o nó atual pelo seu filho à esquerda.
                free(aux);                 // Libera a memória do nó removido.
            }
            // Caso 3: O nó possui dois filhos.
            else
            {
                // Encontra o maior valor na subárvore esquerda (prédecessor) para substituir o nó.
                Arvore_curso *aux = curso->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir;
                }
                // Copia o valor do curso encontrado para o nó atual.
                curso->codigo = aux->codigo;
                // Remove o curso duplicado na subárvore esquerda.
                curso->esq = remover_curso(curso->esq, aux->codigo);
            }
        }
    }
    // Retorna a raiz (possivelmente atualizada) da árvore.
    return curso;
}


void imprimir_historico(Aluno *aluno, Arvore_curso *raiz_cursos)
{

    Arvore_curso *curso = buscar_curso(raiz_cursos, aluno->codigo_curso);
    if (curso == NULL)
    {
        printf("Curso nao encontrado.\n");
        return;
    }

    printf("Curso: %s\n", curso->nome);

    imprimir_historico_disciplinas(aluno->raiz_notas, curso->raiz_disciplinas);
}