#ifndef DISCIPLINA_H
#define DISCIPLINA_H



typedef struct
{
    int codigo;
    char nome[100];
    int bloco;
    int carga_horaria;
} dados_disciplina;

typedef struct arv_disciplina
{
    dados_disciplina *dados;
    struct arv_disciplina *esq;
    struct arv_disciplina *dir;
    int cor;
} arv_disciplina;

arv_disciplina *cria_no();
void ler_dados(arv_disciplina *no);
arv_disciplina *inserir_disciplina(arv_disciplina *raiz, arv_disciplina *no);
arv_disciplina *rotacionarDireita(arv_disciplina *no);
arv_disciplina *rotacionarEsquerda(arv_disciplina *no);
void trocaCor(arv_disciplina *no);
arv_disciplina *balancear(arv_disciplina *raiz);
int cor(arv_disciplina *no);
arv_disciplina *inserir_disciplina(arv_disciplina *raiz, arv_disciplina *no);
#endif // DISCIPLINA_H