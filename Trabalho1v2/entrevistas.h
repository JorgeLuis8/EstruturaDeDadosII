#ifndef ENTREVISTAS_H
#define ENTREVISTAS_H

typedef struct arvore_entrevistas Arvore_entrevistas;
typedef struct raiz_entrevistas Raiz_entrevistas;
Raiz_entrevistas* inserir_entrevistas(Raiz_entrevistas *raiz, Arvore_entrevistas *no);
Arvore_entrevistas* buscar_entrevistas(Raiz_entrevistas *raiz, char *titulo);

#endif /* ENTREVISTAS_H */