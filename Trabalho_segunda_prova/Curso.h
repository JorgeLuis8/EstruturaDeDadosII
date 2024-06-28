typedef Curso arv_curso;
typedef dados Dados_curso;


arv_curso *cria_no();
void ler_dados(arv_curso *no);
void trocaCor(arv_curso *raiz);
arv_curso *rotacionarEsquerda(arv_curso *A);
arv_curso *rotacionarDireita(arv_disciplina *A);
arv_curso *inserir_disciplina(arv_curso *raiz, arv_curso *no);
arv_disciplina *inserir_rec(arv_curso *raiz, arv_curso *no);
void imprimir_disciplinas(arv_curso *raiz);
arv_curso *buscar_disciplina(arv_curso *raiz, int codigo);
arv_curso *move2EsqRED(arv_curso *H);
arv_curso *move2DirRED(arv_curso *H);
arv_curso *removerMenor(arv_curso *H);
arv_curso *procuraMenor(arv_curso *atual);
arv_curso *remove_NO(arv_curso *H, int valor);
int remove_ArvLLRB(arv_curso **raiz, int codigo);