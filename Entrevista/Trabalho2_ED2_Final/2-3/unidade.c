#include <stdio.h>   // Inclui as funções padrão de entrada e saída.
#include <stdlib.h>  // Inclui as funções para alocação e liberação de memória.
#include "unidade.h" // Inclui o cabeçalho com as definições da estrutura `Unit`.

// Função para remover uma unidade da lista encadeada.
int remove_unit(Unit **lista, int nome) {
    int confirmacao = 0; // Inicializa a variável de confirmação como 0 (não encontrado).

    if (*lista) { // Verifica se a lista não está vazia.
        if ((*lista)->unitValue == nome) { // Verifica se o valor da unidade atual corresponde ao valor a ser removido.
            Unit *aux = *lista; // Salva o nó atual em uma variável auxiliar.
            *lista = (*lista)->nextNode; // Avança para o próximo nó.
            free(aux); // Libera a memória do nó removido.
            confirmacao = 1; // Define confirmação como 1 (unidade encontrada e removida).
        } else { 
            // Chama a função recursivamente para remover o nó em nós subsequentes.
            confirmacao = remove_unit(&(*lista)->nextNode, nome);
        }
    }

    return confirmacao; // Retorna 1 se a unidade foi removida, ou 0 caso contrário.
}

// Função para buscar uma unidade na lista encadeada.
Unit *find_unit(Unit *unitList, int unitValue) {
    Unit *aux = unitList; // Inicializa um ponteiro auxiliar para percorrer a lista.

    // Percorre a lista até encontrar o valor ou chegar ao final.
    while (aux != NULL && aux->unitValue != unitValue) {
        aux = aux->nextNode; // Avança para o próximo nó.
    }

    return aux; // Retorna o nó encontrado ou NULL se não for encontrado.
}

// Função para imprimir os valores das unidades na lista.
void print_units(Unit *unitList) {
    Unit *aux = unitList; // Inicializa um ponteiro auxiliar para percorrer a lista.
    while (aux != NULL) { // Itera sobre a lista até o final.
        printf("Unidade: %d\n", aux->unitValue); // Imprime o valor da unidade atual.
        aux = aux->nextNode; // Avança para o próximo nó.
    }
}

// Função para criar uma nova unidade.
Unit *create_unit(int unitValue) {
    // Aloca memória para uma nova unidade.
    Unit *nova_unidade = (Unit *)malloc(sizeof(Unit));
    if (nova_unidade != NULL) { // Verifica se a alocação foi bem-sucedida.
        nova_unidade->unitValue = unitValue; // Atribui o valor da unidade.
        nova_unidade->nextNode = NULL; // Inicializa o próximo nó como NULL.
    }
    return nova_unidade; // Retorna o ponteiro para a nova unidade criada.
}

// Função para inserir uma unidade de forma ordenada na lista.
Unit *insert_unit_sorted(Unit *unitList, Unit *new_unit) {
    Unit *head = unitList; // Ponteiro para a cabeça da lista.
    Unit *previousUnit = NULL; // Ponteiro para o nó anterior.
    Unit *currentUnit = unitList; // Ponteiro para o nó atual.

    if (unitList == NULL) { // Caso a lista esteja vazia.
        new_unit->nextNode = NULL; // Define o próximo nó como NULL.
        head = new_unit; // Define o novo nó como a cabeça da lista.
    } else {
        // Percorre a lista até encontrar a posição correta para inserir.
        while (currentUnit != NULL && currentUnit->unitValue < new_unit->unitValue) {
            previousUnit = currentUnit; // Atualiza o nó anterior.
            currentUnit = currentUnit->nextNode; // Avança para o próximo nó.
        }

        // Verifica se o valor já existe na lista.
        if (currentUnit != NULL && currentUnit->unitValue == new_unit->unitValue) {
            free(new_unit); // Libera a memória da nova unidade (não duplicar valores).
        } else if (previousUnit == NULL) { // Caso a nova unidade deva ser a primeira da lista.
            new_unit->nextNode = unitList; // Define o próximo nó como a cabeça atual.
            head = new_unit; // Atualiza a cabeça da lista.
        } else { 
            // Insere o novo nó entre o nó anterior e o nó atual.
            previousUnit->nextNode = new_unit;
            new_unit->nextNode = currentUnit;
        }
    }

    return head; // Retorna o ponteiro para a cabeça da lista.
}

// Função para liberar toda a memória alocada para a lista.
void free_list(Unit *unitList) {
    Unit *currentUnit = unitList; // Ponteiro para percorrer a lista.
    while (currentUnit != NULL) { // Itera até o final da lista.
        Unit *temp = currentUnit; // Salva o nó atual em uma variável temporária.
        currentUnit = currentUnit->nextNode; // Avança para o próximo nó.
        free(temp); // Libera a memória do nó atual.
    }
}
