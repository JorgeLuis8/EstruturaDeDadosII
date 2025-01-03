#include <stdio.h>
#include <stdlib.h>
#include "unidade.h"

Unidade *remover_unidade(Unidade *lista, int valor) {
    Unidade *aux = lista;       // Ponteiro para percorrer a lista
    Unidade *ant = NULL;        // Ponteiro para o nó anterior
    Unidade *resultado = lista; // Cabeça da lista, pode mudar se o primeiro nó for removido

    // Percorre a lista até encontrar o nó com o valor ou o final da lista
    while (aux != NULL && aux->unidade != valor) {
        ant = aux;
        aux = aux->prox;
    }

    // Se encontrou o nó, remove-o
    if (aux != NULL) {
        if (ant == NULL) {
            // Se o nó a ser removido é o primeiro
            resultado = aux->prox;
        } else {
            // Se o nó está no meio ou no final
            ant->prox = aux->prox;
        }
        free(aux); // Libera a memória do nó removido
    }

    return resultado; // Retorna a nova cabeça da lista
}


Unidade *buscar_unidade(Unidade *lista, int valor) {
    Unidade *aux = lista;

    while (aux != NULL && aux->unidade != valor) {
        aux = aux->prox;
    }

    return aux;
}

void imprimir_unidades(Unidade *lista) {
    Unidade *aux = lista;
    while (aux != NULL) {
        printf("Unidade: %d\n", aux->unidade);
        aux = aux->prox;
    }
}

// Função para criar um novo nó de Unidade.
Unidade *criar_unidade(int valor) {
    Unidade *nova_unidade = (Unidade *)malloc(sizeof(Unidade));
    if (nova_unidade != NULL) {
        nova_unidade->unidade = valor;
        nova_unidade->prox = NULL;
    }
    return nova_unidade;
}

// Função para inserir uma nova unidade ordenada.
Unidade *adicionar_unidade_ordenada(Unidade *lista, Unidade *novo_no) {
    Unidade *head = lista;  // Aponta para o início da lista
    Unidade *anterior = NULL;
    Unidade *atual = lista;

    if (lista == NULL) {
        // Lista vazia, adiciona como primeiro elemento
        printf("Adicionando unidade %d como a primeira na lista.\n", novo_no->unidade);
        novo_no->prox = NULL;
        head = novo_no;
    } else {
        // Percorre a lista até encontrar a posição correta ou verificar duplicata
        while (atual != NULL && atual->unidade < novo_no->unidade) {
            anterior = atual;
            atual = atual->prox;
        }

        // Verifica se a unidade já existe
        if (atual != NULL && atual->unidade == novo_no->unidade) {
            printf("Unidade %d já existe na lista. Ignorando.\n", novo_no->unidade);
            free(novo_no);
        } else if (anterior == NULL) {
            // Adiciona no início da lista
            novo_no->prox = lista;
            head = novo_no;
            printf("Unidade %d adicionada no início da lista.\n", novo_no->unidade);
        } else {
            // Adiciona no meio ou no final
            anterior->prox = novo_no;
            novo_no->prox = atual;
            printf("Unidade %d adicionada na lista.\n", novo_no->unidade);
        }
    }

    return head;  // Sempre retorna o início da lista
}



// Função para liberar a memória da lista.
void liberar_lista(Unidade *lista) {
    Unidade *atual = lista;
    while (atual != NULL) {
        Unidade *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}
