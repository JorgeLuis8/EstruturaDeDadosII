struct arvore_matricula
{
    int codigo_disciplina;
    arvore_matricula *esq;
    arvore_matricula *dir;
};

typedef struct arvore_matricula Arvore_matricula;