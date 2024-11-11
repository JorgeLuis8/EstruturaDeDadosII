#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclua os cabeçalhos das suas árvores 2-3 e binária
#include "arv_portugues-23.c"
#include "arv_ingles-binaria.c"

// Função auxiliar para criar uma estrutura `Info` com uma palavra em português

// Função para imprimir as traduções em ordem com separação por vírgula


// Função para imprimir a estrutura `Info` com unidade e suas traduções


// Função principal para imprimir a árvore 2-3 por unidade


int main() {
    Tree23Node *arvore = NULL;

    // Criação de exemplos para unidade 1
    Info busInfo = criarInfo("onibus", 1);
    adicionarTraducao(&busInfo, "Bus", 1);
    adicionarTraducao(&busInfo, "Coach", 1); // Outra tradução
    inserirValorArvore(&arvore, busInfo);

    Info bugInfo = criarInfo("inseto", 1);
    adicionarTraducao(&bugInfo, "Bug", 1);
    inserirValorArvore(&arvore, bugInfo);

    Info systemInfo = criarInfo("sistema", 1);
    adicionarTraducao(&systemInfo, "System", 1);
    inserirValorArvore(&arvore, systemInfo);

    // Criação de exemplos para unidade 2
    Info bikeInfo = criarInfo("bicicleta", 2);
    adicionarTraducao(&bikeInfo, "Bicycle", 2);
    inserirValorArvore(&arvore, bikeInfo);

    // Imprime a árvore 2-3 organizada por unidade
    imprimirArvorePorUnidade(arvore);

    // Limpa a árvore e libera a memória
    limparArvore(&arvore);
    printf("\nA árvore foi limpa.\n");

    return 0;
}
