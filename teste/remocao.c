
#include "remocao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Remove_palavra_ingles_unidade(PortugueseTree **raiz, const char *palavras_ingles, const char *unidade)
{
  int confirm = 1;
  confirm = remove_palavra_ingles_unidade(*raiz, palavras_ingles, unidade, raiz);
  return confirm;
}

int remove_unidade(Inglesbin **raiz, const char *palavraIngles, const char *unidade)
{
  int confirm = 1;

  if (*raiz)
  {
    if (strcmp((*raiz)->palavraIngles, palavraIngles) == 0)
    {
      confirm = remover_lista_encadeada_unidade(&(*raiz)->unidades, unidade);
      if (!(*raiz)->unidades)
        confirm = removerPalavraIngles(raiz, palavraIngles);
    }
    else if (strcmp((*raiz)->palavraIngles, palavraIngles) > 0)
      confirm = remove_unidade(&(*raiz)->esq, palavraIngles, unidade);
    else
      confirm = remove_unidade(&(*raiz)->dir, palavraIngles, unidade);
  }

  return confirm;
}

int remove_palavra_ingles_unidade(PortugueseTree *raiz, const char *palavraIngles, const char *unidade, PortugueseTree **top)
{
  int confirm = 0;

  if (raiz)
  {
    confirm = remove_palavra_ingles_unidade((raiz)->left, palavraIngles, unidade, top);
    confirm = remove_palavra_ingles_unidade((raiz)->cent, palavraIngles, unidade, top) || confirm;

    if ((raiz)->nInfos == 2)
    {
      confirm = remove_palavra_ingles_unidade((raiz)->right, palavraIngles, unidade, top) || confirm;
      confirm = remove_unidade(&(raiz)->info2.englishWord, palavraIngles, unidade);
    }

    confirm = remove_unidade(&(raiz)->info1.englishWord, palavraIngles, unidade);


    if (!(raiz)->info1.englishWord)
      confirm = remove_node_from23_tree(top, raiz->info1.portugueseWord);

    if ((raiz)->nInfos == 2 && !(raiz)->info2.englishWord)
      confirm = remove_node_from23_tree(top, raiz->info2.portugueseWord);
  }

  return confirm;
}

//##########################################REMOVER A UNIDADE DAS PALAVRAS EM PORTUGUÊS##########################################

int _remove_palavra_portugues_unidade(Inglesbin **raiz, const char *palavraPortugues, const char *unidade)
{
  int confirm = 0;
  if (*raiz)
  {
    confirm = _remove_palavra_portugues_unidade(&(*raiz)->esq, palavraPortugues, unidade);
    confirm = _remove_palavra_portugues_unidade(&(*raiz)->dir, palavraPortugues, unidade) || confirm;
    confirm = remover_lista_encadeada_unidade(&(*raiz)->unidades, unidade);

    if (!(*raiz)->unidades)
      confirm = removerPalavraIngles(raiz, (*raiz)->palavraIngles);
  }

  return confirm;
}

int remove_palavra_portugues_unidade(PortugueseTree *raiz, char *palavraPortugues, const char *unidade, PortugueseTree **top)
{
  int confirm = 1;

  if (raiz)
  {
    if (strcmp((raiz)->info1.portugueseWord, palavraPortugues) == 0)
    {
      confirm = _remove_palavra_portugues_unidade(&(raiz)->info1.englishWord, palavraPortugues, unidade);
      if (!(raiz)->info1.englishWord)
        confirm = remove_node_from23_tree(top, palavraPortugues);
    }
    else if ((raiz)->nInfos == 2 && strcmp((raiz)->info2.portugueseWord, palavraPortugues) == 0)
    {
      confirm = _remove_palavra_portugues_unidade(&(raiz)->info2.englishWord, palavraPortugues, unidade);
      if (!(raiz)->info2.englishWord)
        confirm = remove_node_from23_tree(top, palavraPortugues);
    }
    else if (strcmp(palavraPortugues, (raiz)->info1.portugueseWord) < 0)
      confirm = remove_palavra_portugues_unidade((raiz)->left, palavraPortugues, unidade, top);
    else if ((raiz)->nInfos == 1 || strcmp(palavraPortugues, (raiz)->info2.portugueseWord) < 0)
      confirm = remove_palavra_portugues_unidade((raiz)->cent, palavraPortugues, unidade, top);
    else
      confirm = remove_palavra_portugues_unidade((raiz)->right, palavraPortugues, unidade, top);
  }

  return confirm;
}

int Remove_palavra_portugues_unidade(PortugueseTree **raiz, char *palavraPortugues, const char *unidade)
{
  int confirm = 1;
  confirm = remove_palavra_portugues_unidade(*raiz, palavraPortugues, unidade, raiz);
  return confirm;
}