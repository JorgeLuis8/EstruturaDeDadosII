#include <stdio.h>
#include <stdlib.h>
#include "unidade.h"

Unit *remove_unit(Unit *lista, int valor) {
    Unit *aux = lista;       // Ponteiro para percorrer a lista
    Unit *ant = NULL;        // Ponteiro para o nó anterior
    Unit *resultado = lista; // Cabeça da lista, pode mudar se o primeiro nó for removido

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
    Unit *head = lista;  // Aponta para o início da lista
    Unit *anterior = NULL;
    Unit *atual = lista;

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
void free_list(Unit *lista) {
    Unit *atual = lista;
    while (atual != NULL) {
        Unit *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}
