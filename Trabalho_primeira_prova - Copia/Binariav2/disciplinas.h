struct  arv_disciplinas
{
    int codigo;
    char nome[50];
    int periodo;
    arv_disciplinas *esq;
    arv_disciplinas *dir;
};

typedef struct arv_disciplinas Arvore_disciplinas;