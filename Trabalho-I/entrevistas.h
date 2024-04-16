typedef struct noentrevista NoEntrevista;
typedef struct raizentrevista RaizEntrevista;

NoEntrevista* criar_arvore_entrevistas();
void Ler_dados_de_insercao_entrevistas(NoEntrevista *no);
NoEntrevista* inserir_entrevistas(NoEntrevista *raiz, NoEntrevista *no);
NoEntrevista* buscar_entrevistas(NoEntrevista *raiz, char *titulo);
