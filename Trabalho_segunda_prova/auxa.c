arv_disciplina *remove_NO(arv_disciplina *no, int valor)
{
    arv_disciplina *aux = no;
    if (no == NULL)
        aux = NULL;
    if (valor < no->dados->codigo)
    {
        if (no->esq != NULL && no->esq->cor == BLACK && (no->esq->esq == NULL || no->esq->esq->cor == BLACK))
            no = move2EsqRED(no);

        if (no->esq != NULL)
            no->esq = remove_NO(no->esq, valor);
    }
    else
    {
        if (no->esq != NULL && no->esq->cor == RED)
            no = rotacionarDireita(no);

        if (valor == no->dados->codigo && (no->dir == NULL))
        {
            free(no);
            aux = NULL;
        }

        if (no->dir != NULL && no->dir->cor == BLACK && (no->dir->esq == NULL || no->dir->esq->cor == BLACK))
            no = move2DirRED(no);

        if (valor == no->dados->codigo)
        {
            arv_disciplina *x = procuraMenor(no->dir);
            no->dados->codigo = x->dados->codigo;
            no->dir = removerMenor(no->dir);
        }
        else if (no->dir != NULL)
            no->dir = remove_NO(no->dir, valor);
    }
    return balancear(aux);
}