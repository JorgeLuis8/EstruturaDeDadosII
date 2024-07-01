
#ifndef ENTREVISTAS_H
#define ENTREVISTAS_H

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

typedef struct arvore_entrevistas Arvore_entrevistas;

Arvore_entrevistas* criar_arvore_entrevistas();
void Ler_dados_de_insercao_entrevistas(Arvore_entrevistas *no);
Arvore_entrevistas* inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no);
void imprimir_dados_entrevista(Arvore_entrevistas *no);
Arvore_entrevistas* buscar_entrevistas(Arvore_entrevistas *raiz, char *titulo);
void imprimir_entrevistados(Arvore_entrevistas *entrevistas);

#endif /* ENTREVISTAS_H */
