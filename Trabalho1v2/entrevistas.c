#include "entrevistas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

Raiz_entrevistas* criar_raiz_entrevistas() {
    Raiz_entrevistas *r = (Raiz_entrevistas*) malloc(sizeof(Raiz_entrevistas));
    r->raiz = NULL;
    return r;
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
Raiz_entrevistas* inserir_entrevistas(Raiz_entrevistas *raiz, Arvore_entrevistas *no) {
    // Se a raiz for nula, o nó inserido será a raiz
    if (raiz == NULL) {
        raiz = criar_raiz_entrevistas();
        raiz->raiz = no;
    } 
    else {
        // Se o título do nó inserido for menor que o título da raiz, o nó será inserido à esquerda
        if (strcmp(no->titulos, raiz->raiz->titulos) < 0) {
            if (raiz->raiz->esq == NULL) {
                raiz->raiz->esq = no;
            } else {
                inserir_entrevistas(raiz->raiz->esq, no);
            }
        // Se o título do nó inserido for maior que o título da raiz, o nó será inserido à direita
        } else {
            if (raiz->raiz->dir == NULL) {
                raiz->raiz->dir = no;
            } else {
                inserir_entrevistas(raiz->raiz->dir, no);
            }
        }
    }

    return raiz;
}


// Função para buscar entrevistas na árvore
Arvore_entrevistas* buscar_entrevistas(Raiz_entrevistas *raiz, char *titulo) {
    Arvore_entrevistas* resultado = NULL;
    if(raiz != NULL) {
        if (strcmp(titulo, raiz->raiz->titulos) == 0) {
            return raiz->raiz;
        } else if (strcmp(titulo, raiz->raiz->titulos) < 0) {
            resultado = buscar_entrevistas(raiz->raiz->esq, titulo);
        } else {
            resultado = buscar_entrevistas(raiz->raiz->dir, titulo);
        }
    }
    return resultado;
}
