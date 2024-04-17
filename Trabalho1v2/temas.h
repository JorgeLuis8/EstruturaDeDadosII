typedef struct arvore_temas Arvore_temas;
typedef struct raiz_temas Raiz_temas;

Arvore_temas* inserir_temas(Raiz_temas *raiz, Arvore_temas *no, Arvore_temas *novo);
Arvore_temas* buscar_temas(Raiz_temas *raiz, char *titulo);
