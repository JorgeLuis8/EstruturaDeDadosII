#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv23.c"
#include "ingles_arv.c"
// #include "arvbin.h"

int inserirPalavraPortugues(Arv_pt **arvore, char *palavraPortugues, char *palavraIngles, int unidade) {
    Info promove;
    Arv_pt *pai = NULL;
    int inseriu;

    // Busca a palavra na árvore
    Arv_pt *noExistente = NULL;
    noExistente =  BuscarNoPorPalavra(arvore, palavraPortugues);

    if (noExistente != NULL) {
        printf("A palavra já existe. Adicionando tradução...\n");
        AdicionarTraducaoNo(noExistente, palavraPortugues, palavraIngles, unidade);
        inseriu = 1;
    } else {
        Info novoInfo = CriarInfo(palavraPortugues, palavraIngles, unidade);
        InserirInfoArvore23(arvore, &novoInfo, &promove, &pai);
        inseriu = 0;
    }
    return inseriu;
}

void carregarArquivo(const char *nomeArquivo, Arv_pt **arvore)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];

    int unidadeAtual = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        linha[strcspn(linha, "\n")] = 0;

        if (linha[0] == '%')
        {
            // Atualiza a unidade corretamente
            sscanf(linha, "%% Unidade %d", &unidadeAtual);
        }
        else
        {
            char palavraIngles[50], traducoesPortugues[200];
            sscanf(linha, "%[^:]: %[^;]", palavraIngles, traducoesPortugues);
            printf("Lendo: Palavra Inglês = '%s', Traduções: '%s'\n", palavraIngles, traducoesPortugues);
            
            char *traducaoPortugues = strtok(traducoesPortugues, ",;");
            while(traducaoPortugues != NULL)
            {
                while (*traducaoPortugues == ' ') 
                    traducaoPortugues++;

                inserirPalavraPortugues(arvore, traducaoPortugues, palavraIngles, unidadeAtual);
                traducaoPortugues = strtok(NULL, ",;");    
            }
            
        }
    }

    fclose(arquivo);
    printf("Arquivo '%s' carregado com sucesso!\n", nomeArquivo);
}


int main()
{
    Arv_pt *raiz = NULL;
    carregarArquivo("C:/Users/jorge/OneDrive/Documentos/GitHub/EstruturaDeDadosII/Trabalho_segunda_provaVERSAO-REFERENCIA/Tabalho2_Ed2-main/trabalhoEd2.txt", &raiz);
    
    printf("\n--------------------------------------------------------------- \n");
    printf("Árvore 2-3 carregada:\n");
    ExibirArvore23(raiz);

    printf("\n--------------------------------------------------------------- \n");
    printf("\nPalavras da unidade 1: \n");
    ImprimirPorUnidade(raiz, 1);

    printf("\n--------------------------------------------------------------- \n");


    ExibirTraducoesPortugues(&raiz, "bicicleta");

    printf("\n--------------------------------------------------------------- \n");

    RemoverTraducoesInglesNaUnidade(&raiz, "Coller", 1);
   
    printf("\n--------------------------------------------------------------- \n");

    RemoverPalavraArvore23(&raiz, "bicicleta");

    printf("\nPalavras apos remoção: \n\n");

    ExibirArvore23(raiz);



    // freeTree(raiz);

    return 0;
}