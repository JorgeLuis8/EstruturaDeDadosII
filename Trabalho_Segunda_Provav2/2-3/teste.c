#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "arv_portugues-23.c"
#include "arv_ingles-binaria.c"

// Função para obter o tempo em milissegundos no Windows
double get_milliseconds() {
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (double)(counter.QuadPart * 1000.0) / frequency.QuadPart;
}

// Função para carregar 30 palavras fixas na árvore 2-3
void carregarDadosExemplo(Tree23Node **arvore) {
    Info palavra;
    const char *ingles[30] = {
        "bus", "bug", "bike", "cooler", "network", "system", "issue", "computer", "friendship", "phone",
        "book", "family", "car", "road", "nature", "work", "knowledge", "science", "sport", "culture",
        "medicine", "art", "education", "math", "physics", "chemistry", "music", "movie", "city", "food"
    };
    const char *portugues[30] = {
        "ônibus", "inseto", "bicicleta", "ventilador", "rede", "sistema", "problema", "computador", "amizade", "telefone",
        "livro", "família", "carro", "estrada", "natureza", "trabalho", "conhecimento", "ciência", "esporte", "cultura",
        "medicina", "arte", "educação", "matemática", "física", "química", "música", "filme", "cidade", "comida"
    };

    for (int i = 0; i < 30; i++) {
        strcpy(palavra.portugueseWord, portugues[i]);
        palavra.unit = 1;  // Unidade fixa para o exemplo
        palavra.englishTreeRoot = NULL;
        palavra.englishTreeRoot = insertEnglishWord(palavra.englishTreeRoot, ingles[i], 1);
        inserirValorArvore(arvore, palavra);
    }
}

// Função auxiliar para buscar uma palavra e mostrar o caminho percorrido
Tree23Node* buscarComCaminho(Tree23Node *arvore, const char *palavra, int *niveisPercorridos) {
    Tree23Node *atual = arvore;
    *niveisPercorridos = 0;

    while (atual != NULL) {
        (*niveisPercorridos)++;
        if (estaNodo(atual, palavra)) {
            return atual;
        }
        if (strcmp(palavra, atual->info1.portugueseWord) < 0) {
            atual = atual->left;
        } else if (atual->nInfos == 2 && strcmp(palavra, atual->info2.portugueseWord) < 0) {
            atual = atual->middle;
        } else {
            atual = atual->right;
        }
    }
    return NULL;
}

int main() {
    Tree23Node *arvore = NULL;
    carregarDadosExemplo(&arvore); // Carrega a árvore com 30 palavras fixas

    const char *palavras[30] = {
        "ônibus", "inseto", "bicicleta", "ventilador", "rede", 
        "sistema", "problema", "computador", "amizade", "telefone", 
        "livro", "família", "carro", "estrada", "natureza", 
        "trabalho", "conhecimento", "ciência", "esporte", "cultura", 
        "medicina", "arte", "educação", "matemática", "física", 
        "química", "música", "filme", "cidade", "comida"
    };

    const int num_execucoes = 100000;  // Aumente significativamente para capturar tempos maiores

    // Variáveis para análise do tempo em milissegundos
    double tempos[30];
    int niveisPercorridos[30];
    int sucesso = 0;

    for (int i = 0; i < 30; i++) {
        double tempoTotal = 0;
        int nivel = 0;
        Tree23Node *resultado = NULL;

        // Executa a busca múltiplas vezes para calcular uma média mais precisa
        for (int j = 0; j < num_execucoes; j++) {
            nivel = 0;
            double inicio = get_milliseconds();
            resultado = buscarComCaminho(arvore, palavras[i], &nivel);
            double fim = get_milliseconds();

            tempoTotal += (fim - inicio);
        }

        double tempoMedio = tempoTotal / num_execucoes;  // Média do tempo para `num_execucoes`
        tempos[i] = tempoMedio;
        niveisPercorridos[i] = nivel;
    }

    // Exibe o caminho percorrido e o tempo médio para cada palavra
    printf("Resultados:\n");
    for (int i = 0; i < 30; i++) {
        printf("Palavra: '%s', Níveis percorridos: %d, Tempo médio: %.6f ms\n", 
               palavras[i], niveisPercorridos[i], tempos[i]);
    }

    limparArvore(&arvore);

    return 0;
}
