typedef struct arvore_temas Arvore_temas;
typedef struct raiz_temas Raiz_temas;

Arvore_temas* inserir_temas(Arvore_temas *arvore, Arvore_temas *no);
Arvore_temas *buscar_temas(Arvore_temas *raiz, char *titulo);
void inserir_arvore_temas(Raiz_temas *arvore, Arvore_temas *no);
