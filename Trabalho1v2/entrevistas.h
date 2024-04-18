#ifndef ENTREVISTAS_H
#define ENTREVISTAS_H

typedef struct arvore_entrevistas Arvore_entrevistas;
Arvore_entrevistas* inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no);
Arvore_entrevistas* buscar_entrevistas(Arvore_entrevistas *raiz, char *titulo);
void imprimir_melhor(Arvore_entrevistas *raiz, int nivel);




#endif /* ENTREVISTAS_H */