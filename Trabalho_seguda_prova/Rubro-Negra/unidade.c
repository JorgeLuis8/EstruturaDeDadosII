#include <stdio.h>
#include <stdlib.h>
#include "unidade.h"

Unit *remove_unit(Unit *lista, int valor) {
    Unit *aux = lista;
    Unit *ant = NULL;
    Unit *resultado = lista;  

    while (aux != NULL && aux->unidade != valor) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux != NULL) {
        if (ant == NULL) {
            resultado = aux->prox;
        } else {
            ant->prox = aux->prox;
        }
        free(aux);
    }

    return resultado;
}

Unit *find_unit(Unit *lista, int valor) {
    Unit *aux = lista;

    while (aux != NULL && aux->unidade != valor) {
        aux = aux->prox;
    }

    return aux;
}

void print_units(Unit *lista) {
    Unit *aux = lista;
    while (aux != NULL) {
        printf("Unidade: %d\n", aux->unidade);
        aux = aux->prox;
    }
}

// Função para criar um novo nó de Unidade.
Unit *create_unit(int valor) {
    Unit *nova_unidade = (Unit *)malloc(sizeof(Unit));
    if (nova_unidade != NULL) {
        nova_unidade->unidade = valor;
        nova_unidade->prox = NULL;
    }
    return nova_unidade;
}

// Função para inserir uma nova unidade ordenada.
Unit *insert_unit_sorted(Unit *lista, Unit *novo_no) {
    Unit *aux = lista;

    if (lista == NULL) {
        // Caso a lista esteja vazia, o novo nó se torna o primeiro.
        novo_no->prox = NULL;
        aux = novo_no;
    } else {
        Unit *anterior = NULL;
        Unit *atual = lista;

        // Percorre a lista para encontrar a posição correta (ordem crescente de "unidade").
        while (atual != NULL && atual->unidade < novo_no->unidade) {
            anterior = atual;
            atual = atual->prox;
        }

        if (anterior == NULL) {
            // Insere o novo nó no início da lista.
            novo_no->prox = lista;
            aux = novo_no;
        } else {
            // Insere o novo nó no meio ou no final da lista.
            anterior->prox = novo_no;
            novo_no->prox = atual;
        }
    }

    return aux;
}

// Função para liberar a memória da lista.
void free_list(Unit *lista) {
    Unit *atual = lista;
    while (atual != NULL) {
        Unit *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}
