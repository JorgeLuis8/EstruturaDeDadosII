#ifndef ENTREVISTAS_H
#define ENTREVISTAS_H

typedef struct Arvore_entrevistas {
    char titulos[100];
    char data[100];
    int duracao;
    char nome_convidado[100];
    char especialidade_convidado[100];
    int altura;
    struct Arvore_entrevistas *esq;
    struct Arvore_entrevistas *dir;
} Arvore_entrevistas;

Arvore_entrevistas *criar_arvore_entrevistas();
short maior_no(short a, short b);
short altura_do_no(Arvore_entrevistas *no);
short fator_balanceamento(Arvore_entrevistas *no);
Arvore_entrevistas *rotar_esquerda(Arvore_entrevistas *no);
Arvore_entrevistas *rotar_direita(Arvore_entrevistas *no);
Arvore_entrevistas *rotar_direita_esquerda(Arvore_entrevistas *no);
Arvore_entrevistas *rotar_esquerda_direita(Arvore_entrevistas *no);
Arvore_entrevistas *balencar_arvore(Arvore_entrevistas *raiz);
void Ler_dados_de_insercao_entrevistas(Arvore_entrevistas *no);
Arvore_entrevistas *inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no);
void imprimir_dados(Arvore_entrevistas *raiz, int nivel);
void imprimir_dados_entrevista(Arvore_entrevistas *raiz);
void imprimir_titulos_entrevistas(Arvore_entrevistas *raiz);
Arvore_entrevistas *buscar_entrevistas(Arvore_entrevistas *raiz, char *titulo);
Arvore_entrevistas *remover_entrevista(Arvore_entrevistas *raiz, char *titulo);
void mostrar_dados_entrevista(Arvore_entrevistas *entrevista);
void imprimir_entrevistados(Arvore_entrevistas *entrevistas);

#endif // ENTREVISTAS_H
