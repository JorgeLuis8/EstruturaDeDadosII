#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "entrevistas.h"

Arvore_entrevistas* criar_arvore_entrevistas() {
    Arvore_entrevistas *a = (Arvore_entrevistas*) malloc(sizeof(Arvore_entrevistas));
    if (a != NULL) {
        memset(a, 0, sizeof(Arvore_entrevistas));
    }
    return a;
}


//inserindo dados 
void Ler_dados_de_insercao_entrevistas(Arvore_entrevistas *no){
    char buffer[50];

    printf("Digite o titulo da entrevista: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%[^\n]", no->titulos);

    printf("Digite a data da entrevista: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%[^\n]", no->data);

    printf("Digite a duracao da entrevista: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &no->duracao);

    printf("Digite o nome do convidado: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%[^\n]", no->nome_convidado);

    printf("Digite a especialidade do convidado: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%[^\n]", no->especialidade_convidado);
}

 
 // Funcao para inserir entrevistas na arvore, usando a funcao de ler os dados de insercao
Arvore_entrevistas* inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no) {
    // Se a raiz for nula, o no inserido sera a raiz
    if (raiz == NULL) {
        raiz = no;
    } 
    else {
        // Se o titulo do no inserido for menor que o titulo da raiz, o no sera inserido a esquerda
        if (strcmp(no->titulos, raiz->titulos) < 0) {
            if (raiz->esq == NULL) {
                raiz->esq = no;
            } else {
                raiz->esq = inserir_entrevistas(raiz->esq, no);
            }
        // Se o titulo do no inserido for maior que o titulo da raiz, o no sera inserido a direita
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


void imprimir_dados_entrevista(Arvore_entrevistas *raiz) {
    if (raiz != NULL) {
        printf("Titulo: %s\n", raiz->titulos);
        printf("Data: %s\n", raiz->data);
        printf("Duracao: %d\n", raiz->duracao);
        printf("Nome do convidado: %s\n", raiz->nome_convidado);
        printf("Especialidade do convidado: %s\n", raiz->especialidade_convidado);
        imprimir_dados_entrevista(raiz->esq);
        imprimir_dados_entrevista(raiz->dir);
    }
}





// Funcao para buscar entrevistas na arvore
Arvore_entrevistas* buscar_entrevistas(Arvore_entrevistas *raiz, char *titulo) {
    Arvore_entrevistas *aux = NULL;
     if(raiz != NULL){ {
        if (strcmp(titulo, raiz->titulos) == 0) {
            aux = raiz;
        } else {
            if (strcmp(titulo, raiz->titulos) < 0) {
                aux = buscar_entrevistas(raiz->esq, titulo);
            } else {
                aux = buscar_entrevistas(raiz->dir, titulo);
                }
            }
        }
    }
    return aux;
}


Arvore_entrevistas* remover_entrevista (Arvore_entrevistas *raiz, char *titulo) {
    if (raiz != NULL) {
        if (strcmp(titulo, raiz->titulos) < 0) {
            raiz->esq = remover_entrevista(raiz->esq, titulo);
        } else if (strcmp(titulo, raiz->titulos) > 0) {
            raiz->dir = remover_entrevista(raiz->dir, titulo);
        } else {
            if (raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                raiz = NULL;
            } else if (raiz->esq == NULL) {
                Arvore_entrevistas *aux = raiz;
                raiz = raiz->dir;
                free(aux);
            } else if (raiz->dir == NULL) {
                Arvore_entrevistas *aux = raiz;
                raiz = raiz->esq;
                free(aux);
            } else {
                Arvore_entrevistas *aux = raiz->esq;
                while (aux->dir != NULL) {
                    aux = aux->dir;
                }
                strcpy(raiz->titulos, aux->titulos);
                raiz->esq = remover_entrevista(raiz->esq, aux->titulos);
            }
        }
    }
    return raiz;
}