#include "entrevistas.h"
#include <stdlib.h>
#include <stdio.h>

struct arvore_entrevistas
{
    char titulos[50];
    char data[50];
    int duracao;
    char nome_convidado[50];
    char especialidade_convidado[50];
    struct arvore_entrevistas *esq;
    struct arvore_entrevistas *dir;
};

struct raiz_entrevistas {
    struct arvore_entrevistas *raiz;
};

Arvore_entrevistas* criar_arvore_entrevistas() {
    Arvore_entrevistas *a = (Arvore_entrevistas*) malloc(sizeof(Arvore_entrevistas));
    a->esq = NULL;
    a->dir = NULL;
    return a;
}

//inserindo dados 
void Ler_dados_de_insercao_entrevistas(Arvore_entrevistas *no){
    printf("Digite o titulo da entrevista: ");
    scanf("%s", no->titulos);
    printf("Digite a data da entrevista: ");
    scanf("%s", no->data);
    printf("Digite a duração da entrevista: ");
    scanf("%d", &no->duracao);
    printf("Digite o nome do convidado: ");
    scanf("%s", no->nome_convidado);
    printf("Digite a especialidade do convidado: ");
    scanf("%s", no->especialidade_convidado);
}
 
 // Função para inserir entrevistas na árvore, usando a função de ler os dados de inserção
Arvore_entrevistas* inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no) {
    // Se a raiz for nula, o nó inserido será a raiz
    if (raiz == NULL) {
        raiz = no;
    } 
    else {
        // Se o título do nó inserido for menor que o título da raiz, o nó será inserido à esquerda
        if (strcmp(no->titulos, raiz->titulos) < 0) {
            if (raiz->esq == NULL) {
                raiz->esq = no;
            } else {
                raiz->esq = inserir_entrevistas(raiz->esq, no);
            }
        // Se o título do nó inserido for maior que o título da raiz, o nó será inserido à direita
        } else {
            if (raiz->dir == NULL) {
                raiz->dir = no;
            } else {
                raiz->dir = inserir_entrevistas(raiz->dir, no);
            }
        }
    }

    return raiz;
}

// Função para buscar entrevistas na árvore
Arvore_entrevistas* buscar_entrevistas(Arvore_entrevistas *raiz, char *titulo) {
     if(raiz != NULL){ {
        if (strcmp(titulo, raiz->titulos) == 0) {
            return raiz;
        } else {
            if (strcmp(titulo, raiz->titulos) < 0) {
                return buscar_entrevistas(raiz->esq, titulo);
            } else {
                return buscar_entrevistas(raiz->dir, titulo);
                }
            }
        }
    }
}
