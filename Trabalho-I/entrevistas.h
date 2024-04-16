typedef struct arvore_entrevistas Arvore_entrevistas;
typedef struct raiz_entrevistas Raiz_entrevistas;

Arvore_entrevistas* criar_arvore_entrevistas();
void Ler_dados_de_insercao_entrevistas(Arvore_entrevistas *no);
Arvore_entrevistas* inserir_entrevistas(Arvore_entrevistas *raiz, Arvore_entrevistas *no);
Arvore_entrevistas* buscar_entrevistas(Arvore_entrevistas *raiz, char *titulo);
