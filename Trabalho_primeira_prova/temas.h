
typedef struct arvore_temas Arvore_temas;


Arvore_temas *criar_arvore_temas();
void lerDados(Arvore_temas *no);
Arvore_temas *inserir_temas(Arvore_temas *raiz, Arvore_temas *no);
Arvore_temas *Busca_arv(Arvore_temas *raiz, char *tema);
void imprimir_temas_entrevistas(Arvore_temas *raiz);
