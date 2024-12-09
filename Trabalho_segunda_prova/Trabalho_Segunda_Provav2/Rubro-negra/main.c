#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv-ingles-bin.c"
#include "arv-portugues.c"
// #include "arvbin.h"

int inserirPalavraPortugues(PortuguesRB **arvore, char *palavraPortugues, char *palavraIngles, int unidade) {
    int inseriu = 0;

    // Busca a palavra na árvore
    PortuguesRB *noExistente = NULL;
    noExistente =  BuscarPalavra(arvore, palavraPortugues);

    if (noExistente != NULL) {
        printf("A palavra já existe. Adicionando tradução...\n");
        adicionarTraducaoEmIngles(noExistente, palavraIngles, unidade);
        inseriu = 1;
    } else {
        Info novoInfo = CriarInfo(palavraPortugues, palavraIngles, unidade);
        inserirArvRB(arvore, &novoInfo);
        inseriu = 1;
    }
    return inseriu;
}

void carregarArquivo(const char *nomeArquivo, PortuguesRB **arvore)
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

                // Info novoInfo = criaInfo(traducaoPortugues, palavraIngles, unidadeAtual);
                // inserirArvRB(arvore, &novoInfo);
                traducaoPortugues = strtok(NULL, ",;");    
            }
            
        }
    }

    fclose(arquivo);
    printf("Arquivo '%s' carregado com sucesso!\n", nomeArquivo);
}


int main()
{

    PortuguesRB *raiz = NULL;

    carregarArquivo("/mnt/c/Users/Rayssa Alves/Documents/trabalho_ed2/Tabalho2_Ed2/trabalhoEd2.txt", &raiz);

    // Info info1 = criaInfo("casa", 1);
    // Info info2 = criaInfo("livro", 2);
    // Info info3 = criaInfo("carro", 3);
    // Info info4 = criaInfo("arroz", 4);

    // inserirArvRB(&raiz, &info1);
    // inserirArvRB(&raiz, &info2);
    // inserirArvRB(&raiz, &info3);
    // inserirArvRB(&raiz, &info4);

    exibirArvore(raiz);
    printf("\n--------------------------------------------------------------- \n");

    removerNoArvVP(&raiz, "bicicleta");
    printf("\n--------------------------------------------------------------- \n");

    exibirArvore(raiz);

    printf("\n--------------------------------------------------------------- \n");

    BuscarPalavraIngles(&raiz, "Bus", 1);

    exibirArvore(raiz);

    // PortuguesRB *raiz = NULL;
    
    
    // printf("\n--------------------------------------------------------------- \n");
    // printf("Árvore 2-3 carregada:\n");
    // exibir_tree23(raiz);

    // printf("\n--------------------------------------------------------------- \n");
    // printf("\nPalavras da unidade 1: \n");
    // imprimirInfoUnidade(raiz, 1);

    // printf("\n--------------------------------------------------------------- \n");


    // exibir_traducao_Portugues(&raiz, "bicicleta");

    // printf("\n--------------------------------------------------------------- \n");

    // BuscarPalavraIngles(&raiz, "Coller", 1);
   
    // printf("\n--------------------------------------------------------------- \n");

    // removerElemento(&raiz, "bicicleta");

    // printf("\nPalavras apos remoção: \n\n");

    // exibir_tree23(raiz);



    // // freeTree(raiz);

    return 0;
}