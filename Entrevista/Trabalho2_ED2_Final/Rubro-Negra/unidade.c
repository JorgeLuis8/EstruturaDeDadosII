#include <stdio.h>
#include <stdlib.h>
#include "unidade.h"

// Função para remover uma unidade da lista
Unit *remove_unit(Unit *unitList, int unitValue) {
    Unit *aux = unitList;       // Ponteiro auxiliar para percorrer a lista
    Unit *ant = NULL;           // Ponteiro para o nó anterior
    Unit *unitListHead = unitList; // Cabeça da lista

    // Percorre a lista até encontrar a unidade desejada ou chegar ao final
    while (aux != NULL && aux->unitValue != unitValue) {
        ant = aux;
        aux = aux->nextNode;
    }

    if (aux != NULL) { // Se a unidade foi encontrada
        if (ant == NULL) { // Caso a unidade seja a cabeça da lista
            unitListHead = aux->nextNode; // Atualiza a cabeça para o próximo nó
        } else { // Caso contrário, desconecta o nó encontrado
            ant->nextNode = aux->nextNode;
        }
        free(aux); // Libera a memória do nó removido
    }

    return unitListHead; // Retorna a cabeça atualizada da lista
}

// Função para encontrar uma unidade específica na lista
Unit *find_unit(Unit *unitList, int unit) {
    Unit *aux = unitList; // Ponteiro auxiliar para percorrer a lista

    // Percorre a lista até encontrar a unidade desejada ou chegar ao final
    while (aux != NULL && aux->unitValue != unit) {
        aux = aux->nextNode;
    }

    return aux; // Retorna o nó encontrado ou NULL se não existir
}

// Função para imprimir todas as unidades na lista
void print_units(Unit *unitList) {
    Unit *aux = unitList; // Ponteiro auxiliar para percorrer a lista
    while (aux != NULL) {
        printf("Unidade: %d\n", aux->unitValue); // Imprime o valor da unidade
        aux = aux->nextNode; // Avança para o próximo nó
    }
}

// Função para criar uma nova unidade
Unit *create_unit(int unit) {
    Unit *new_unit = (Unit *)malloc(sizeof(Unit)); // Aloca memória para a nova unidade
    if (new_unit != NULL) { // Verifica se a alocação foi bem-sucedida
        new_unit->unitValue = unit; // Define o valor da unidade
        new_unit->nextNode = NULL; // Inicializa o próximo nó como NULL
    }
    return new_unit; // Retorna o ponteiro para a nova unidade
}

// Função para inserir uma unidade em ordem crescente na lista
Unit *insert_unit_sorted(Unit *unitList, Unit *new_unit) {
    Unit *aux = unitList; // Ponteiro auxiliar para a cabeça da lista

    if (unitList == NULL) { // Caso a lista esteja vazia
        new_unit->nextNode = NULL; // Define o próximo nó como NULL
        aux = new_unit; // O novo nó se torna a cabeça da lista
    } else {
        Unit *anterior = NULL; // Ponteiro para o nó anterior
        Unit *atual = unitList; // Ponteiro para o nó atual

        // Percorre a lista até encontrar a posição correta
        while (atual != NULL && atual->unitValue < new_unit->unitValue) {
            anterior = atual;
            atual = atual->nextNode;
        }

        if (anterior == NULL) { // Caso o novo nó seja o menor e deva ser a nova cabeça
            new_unit->nextNode = unitList; // Conecta o novo nó ao início da lista
            aux = new_unit; // Atualiza a cabeça da lista
        } else { // Caso o novo nó seja inserido no meio ou no final
            anterior->nextNode = new_unit; // Conecta o nó anterior ao novo nó
            new_unit->nextNode = atual; // Conecta o novo nó ao próximo nó
        }
    }

    return aux; // Retorna a cabeça da lista atualizada
}

// Função para liberar a memória de toda a lista
void free_list(Unit *unitList) {
    Unit *atual = unitList; // Ponteiro para o nó atual
    while (atual != NULL) {
        Unit *temp = atual; // Armazena o nó atual
        atual = atual->nextNode; // Avança para o próximo nó
        free(temp); // Libera o nó armazenado
    }
}











