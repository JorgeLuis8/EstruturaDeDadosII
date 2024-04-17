typedef struct notema NoTema;
typedef struct raiztema RaizTema;

NoTema *cria_arvore_tema();
void ler_dados(NoTema *no);
NoTema* inserir_temas(RaizTema *raiz, NoTema *no);
NoTema *Buscar_Tema(NoTema *raiz, char *tema);
