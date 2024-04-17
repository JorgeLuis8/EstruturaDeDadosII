#ifndef ENTREVISTAS_H
#define ENTREVISTAS_H

typedef struct arvore_entrevistas Arvore_entrevistas;
typedef struct raiz_entrevistas Raiz_entrevistas;
Arvore_entrevistas* inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no);
Arvore_entrevistas* buscar_entrevistas(Arvore_entrevistas *raiz, char *titulo);
Raiz_entrevistas *arvore_busca(Raiz_entrevistas *raiz, char *titulo);
void imprimir_melhor(Arvore_entrevistas *raiz, int nivel);
void inserir_arvore(Raiz_entrevistas *arvore, Arvore_entrevistas *no);



#endif /* ENTREVISTAS_H */