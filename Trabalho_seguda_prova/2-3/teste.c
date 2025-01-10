#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "portugues.c"
#include "ingles.c"
#include "unidade.c"


void test_remove_english_word() {
    PortugueseTree *rootNode = NULL;

    // Inserir palavras e traduções
    insertPortugueseTerm(&rootNode, "carro", "Car", 1);
    insertPortugueseTerm(&rootNode, "teia", "Web", 1);
    insertPortugueseTerm(&rootNode, "ventilador", "Fan", 1);

    // Remover "Fan"
    int result = Remove_english_word_from_unit(&rootNode, "Fan", 1);
    if (result) {
        printf("Remoção bem-sucedida.\n");
    } else {
        printf("Falha na remoção.\n");
    }

    // Verificar estado da árvore após remoção
    print_tree23(rootNode);

    // Liberar memória
    deallocateTree(&rootNode);
}

int main() {
    test_remove_english_word();
    return 0;
}