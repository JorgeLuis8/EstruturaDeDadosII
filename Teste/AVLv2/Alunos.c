#include "Alunos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Aluno *criar_aluno()
{
    // Aloca memória para um novo aluno. "malloc" tenta reservar espaço na memória
    // para o tipo "Aluno" e retorna um ponteiro para esse espaço.
    Aluno *a = (Aluno *)malloc(sizeof(Aluno));
    
    // Verifica se a alocação de memória falhou, o que significa que "a" é NULL.
    // Se não houver memória suficiente, exibe uma mensagem de erro e encerra o programa.
    if (a == NULL)
    {
        printf("Erro ao alocar aluno\n");
        exit(1);
    }

    // Inicializa o ponteiro para a raiz da árvore de notas do aluno como NULL,
    // indicando que o aluno ainda não possui nenhuma nota cadastrada.
    a->raiz_notas = NULL;

    // Inicializa o ponteiro para a raiz da árvore de matrículas do aluno como NULL,
    // indicando que o aluno ainda não possui nenhuma matrícula em disciplinas.
    a->raiz_matriculas = NULL;

    // Inicializa o ponteiro "prox" como NULL, o que indica que este aluno ainda
    // não está conectado a nenhum outro aluno em uma lista encadeada.
    a->prox = NULL;

    // Retorna o ponteiro para o aluno recém-criado com todos os campos inicializados.
    return a;
}


Aluno *inserir_aluno(Aluno *aluno, Aluno *no)
{
    // Declara um ponteiro auxiliar que aponta para o início da lista.
    Aluno *aux = aluno;

    // Caso a lista de alunos esteja vazia (aluno == NULL),
    // insere o novo aluno (no) como o primeiro elemento da lista.
    if (aluno == NULL)
    {
        no->prox = NULL; // Define o próximo do novo aluno como NULL, pois ele será o único na lista.
        aux = no;        // Atualiza o ponteiro auxiliar para apontar para o novo aluno.
    }
    else
    {
        // Se a lista não estiver vazia, declara ponteiros para navegar na lista:
        // "anterior" será usado para guardar o elemento anterior ao que estamos inserindo,
        // e "atual" para percorrer os elementos da lista.
        Aluno *anterior = NULL;
        Aluno *atual = aluno;

        // Percorre a lista até encontrar a posição correta para inserir o novo aluno,
        // mantendo a lista em ordem alfabética. A comparação é feita pelo nome do aluno.
        while (atual != NULL && strcmp(atual->nome, no->nome) < 0)
        {
            anterior = atual;     // Move o ponteiro anterior para o elemento atual.
            atual = atual->prox;  // Move o ponteiro atual para o próximo elemento da lista.
        }

        // Se o novo aluno deve ser inserido no início da lista (anterior == NULL),
        // o novo aluno aponta para o primeiro elemento atual da lista.
        if (anterior == NULL)
        {
            no->prox = aluno; // Define o próximo do novo aluno como o atual início da lista.
            aux = no;         // Atualiza o ponteiro auxiliar para apontar para o novo aluno.
        }
        else
        {
            // Caso contrário, insere o novo aluno entre "anterior" e "atual".
            // "anterior" aponta para o novo aluno, e o novo aluno aponta para "atual".
            anterior->prox = no;
            no->prox = atual;
        }
    }

    // Retorna o ponteiro para o início da lista, que pode ter sido atualizado.
    return aux;
}


Aluno *remover_aluno(Aluno *aluno, int matricula)
{
    // Define um ponteiro auxiliar para percorrer a lista, iniciando do primeiro aluno.
    Aluno *aux = aluno;
    // Define um ponteiro para o elemento anterior ao que será removido, iniciando como NULL.
    Aluno *ant = NULL;
    // Define um ponteiro para armazenar o início da lista, que será retornado ao final.
    Aluno *resultado = aluno;

    // Percorre a lista até encontrar o aluno com a matrícula desejada ou até o final da lista.
    while (aux != NULL && aux->matricula != matricula)
    {
        ant = aux;       // Atualiza o ponteiro "ant" para o elemento atual.
        aux = aux->prox; // Move o ponteiro "aux" para o próximo elemento da lista.
    }

    // Verifica se encontrou o aluno com a matrícula especificada.
    if (aux != NULL)
    {
        // Caso o aluno a ser removido seja o primeiro da lista.
        if (ant == NULL)
        {
            resultado = aux->prox; // Atualiza o início da lista para o próximo elemento.
        }
        else
        {
            // Caso o aluno esteja no meio ou no final da lista, ajusta o ponteiro
            // "prox" do elemento anterior para pular o elemento a ser removido.
            ant->prox = aux->prox;
        }
        // Libera a memória do aluno que foi removido.
        free(aux);
    }

    // Retorna o ponteiro para o início da lista, que pode ter sido atualizado.
    return resultado;
}


Aluno *buscar_aluno(Aluno *aluno, int matricula)
{
    Aluno *aux = aluno;

    while (aux != NULL && aux->matricula != matricula)
    {
        aux = aux->prox;
    }

    return aux;
}

void imprimir_alunos(Aluno *aluno, int codigo_curso)
{
    Aluno *aux = aluno;
    while (aux != NULL)
    {
        if (aux->codigo_curso == codigo_curso)
        {
            printf("Matricula: %d\n", aux->matricula);
            printf("Nome: %s\n", aux->nome);
            printf("Codigo do curso: %d\n", aux->codigo_curso);
        }
        aux = aux->prox;
    }
}

int verificar_matricula_disciplinas(Aluno *raiz_alunos, int codigo_disciplina)
{
    int encontrado = 0;

    for (Aluno *atual = raiz_alunos; atual != NULL; atual = atual->prox)
    {
        arvore_matricula *matricula = buscar_matricula(atual->raiz_matriculas, codigo_disciplina);
        if (matricula != NULL)
        {
            encontrado = 1;
        }
    }

    return encontrado;
}
