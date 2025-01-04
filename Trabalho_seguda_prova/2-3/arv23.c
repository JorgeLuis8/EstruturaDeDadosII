#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv23.h"

Portugues23 *FindWord(Portugues23 **no, const char *palavraPortugues)
{
    Portugues23 *resultado = NULL;

    if (no != NULL && *no != NULL)
    {
        if (strcmp(palavraPortugues, (*no)->info1.palavraPortugues) == 0)
        {
            resultado = *no;
        }
        else if ((*no)->nInfos == 2)
        {

            if (strcmp(palavraPortugues, (*no)->info2.palavraPortugues) == 0)
            {
                resultado = *no;
            }
        }

        if (resultado == NULL)
        {
            if (strcmp(palavraPortugues, (*no)->info1.palavraPortugues) < 0)
            {
                resultado = FindWord(&(*no)->esq, palavraPortugues);
            }
            else if ((*no)->nInfos == 1 || strcmp(palavraPortugues, (*no)->info2.palavraPortugues) < 0)
            {
                resultado = FindWord(&(*no)->cent, palavraPortugues);
            }
            else
            {
                resultado = FindWord(&(*no)->dir, palavraPortugues);
            }
        }
    }

    return resultado;
}

void insertTranslation(Portugues23 *no, const char *palavraPortugues, const char *palavraIngles, int unidade)
{
    // Verifica se a palavra portuguesa está na primeira posição do nó
    if (strcmp(palavraPortugues, no->info1.palavraPortugues) == 0)
    {
        // Adiciona a tradução na árvore binária de palavras em inglês
        no->info1.palavraIngles = insertEnglishWord(no->info1.palavraIngles, palavraIngles, unidade);

    }
    // Verifica se a palavra portuguesa está na segunda posição do nó (se existir)
    else if (no->nInfos == 2 && strcmp(palavraPortugues, no->info2.palavraPortugues) == 0)
    {
        // Adiciona a tradução na árvore binária de palavras em inglês
        no->info2.palavraIngles = insertEnglishWord(no->info2.palavraIngles, palavraIngles, unidade);
    }
}

int insertPortugueseTerm(Portugues23 **arvore, char *palavraPortugues, char *palavraIngles, int unidade) {
    Info promove;
    Portugues23 *pai = NULL;
    int resultado = 0; // Inicializa como "novo elemento inserido"

    // Busca a palavra em português na árvore
    Portugues23 *noExistente = FindWord(arvore, palavraPortugues);

    if (noExistente != NULL) {
        // Se a palavra em português já existe, adiciona a tradução e a unidade
        insertTranslation(noExistente, palavraPortugues, palavraIngles, unidade);
        resultado = 1; // Atualização realizada
    } else {
        // Cria uma nova entrada para a palavra em português
        Info novoInfo = createInfo(palavraPortugues, palavraIngles, unidade);
        inserirArv23(arvore, &novoInfo, &promove, &pai);
    }

    return resultado;
}


Info createInfo(char *palavraPortugues, char *palavraIngles, int unidade)
{
    Info novoInfo;
    novoInfo.palavraPortugues = strdup(palavraPortugues); // Armazena a palavra em português
    novoInfo.palavraIngles = NULL;
    novoInfo.palavraIngles = insertEnglishWord(novoInfo.palavraIngles, palavraIngles, unidade);
    return novoInfo;
}

Portugues23 *createNode(const Info *informacao, Portugues23 *filhoesq, Portugues23 *filhocen)
{
    Portugues23 *no = (Portugues23 *)malloc(sizeof(Portugues23));
    no->info1 = *informacao;
    no->info2.palavraIngles = NULL;
    no->info2.palavraPortugues = NULL;
    no->esq = filhoesq;
    no->cent = filhocen;
    no->dir = NULL;
    no->nInfos = 1;

    return no;
}

Portugues23 *updateNode23(Portugues23 *no,  Info *informacao, Portugues23 *filho)
{
    if (strcmp(informacao->palavraPortugues, no->info1.palavraPortugues) > 0)
    {
        no->info2 = *informacao;
        no->dir = filho;
    }
    else
    {
        no->info2 = no->info1;
        no->dir = no->cent;
        no->info1 = *informacao;
        no->cent = filho;
    }
    no->nInfos = 2;
    return no;
}

Portugues23 *splitNode(Portugues23 **no, const Info *informacao, Info *promove, Portugues23 **filho)
{
    Portugues23 *maior;

    if (strcmp(informacao->palavraPortugues, (*no)->info2.palavraPortugues) > 0)
    {
        *promove = (*no)->info2;
        if (filho)
            maior = createNode(informacao, (*no)->dir, *filho);
        else
            maior = createNode(informacao, (*no)->dir, NULL);
    }
    else if (strcmp(informacao->palavraPortugues, (*no)->info1.palavraPortugues) > 0)
    {
        *promove = *informacao;
        if (filho)
            maior = createNode(&(*no)->info2, *filho, (*no)->dir);
        else
            maior = createNode(&(*no)->info2, NULL, (*no)->dir);
    }
    else
    {
        *promove = (*no)->info1;
        maior = createNode(&(*no)->info2, (*no)->cent, (*no)->dir);
        (*no)->info1 = *informacao;
        if (filho)
            (*no)->cent = *filho;
        else
            (*no)->cent = NULL;
    }

    (*no)->nInfos = 1;
    return maior;
}

int ehFolha(const Portugues23 *no)
{
    return (no->esq == NULL);
}

Portugues23 *inserirArv23(Portugues23 **no, Info *informacao, Info *promove, Portugues23 **pai)
{
    Info promove1;
    Portugues23 *maiorNo = NULL;
    if (*no == NULL)
    {
        // Cria um novo nó caso seja nulo
        *no = createNode(informacao, NULL, NULL);
    }
    else
    {
        if (ehFolha(*no))
        { // Caso seja folha
            if ((*no)->nInfos == 1)
            {
                // O nó tem espaço para a nova chave
                *no = updateNode23(*no, informacao, NULL);
            }
            else
            {
                // O nó precisa ser quebrado
                maiorNo = splitNode(no, informacao, promove, NULL);
                if (*pai == NULL)
                { // Se não há pai, criar nova raiz
                    *no = createNode(promove, *no, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
        else
        { // Nó não e folha
            // Navega para o filho apropriado
            if (strcmp(informacao->palavraPortugues, (*no)->info1.palavraPortugues) < 0)
            {
                maiorNo = inserirArv23(&((*no)->esq), informacao, promove, no);
            }
            else if ((*no)->nInfos == 1 || strcmp(informacao->palavraPortugues, (*no)->info2.palavraPortugues) < 0)
            {
                maiorNo = inserirArv23(&((*no)->cent), informacao, promove, no);
            }
            else
            {
                maiorNo = inserirArv23(&((*no)->dir), informacao, promove, no);
            }

            // Após inserir, verifica se houve promoção
            if (maiorNo)
            {
                if ((*no)->nInfos == 1)
                {
                    // Adiciona chave promovida no nó atual
                    *no = updateNode23(*no, promove, maiorNo);
                    maiorNo = NULL;
                }
                else
                { // Quando não tem espaço
                    // O nó precisa ser quebrado
                    Portugues23 *novo;
                    novo = splitNode(no, promove, &promove1, &maiorNo); // Quebra o nó e sobe a informação
                    if (*pai == NULL)
                    {
                        Portugues23 *novaRaiz;
                        novaRaiz = createNode(&promove1, *no, novo); // Cria nova raiz se necessário
                        *no = novaRaiz;
                        maiorNo = NULL;
                    }
                    else
                    {
                        maiorNo = novo; // Ajusta o novo maior nó
                        *promove = promove1;
                    }
                }
            }
        }
    }

    return maiorNo;
}

// ############################################## FUNÇOES PARA EXIBIR ##############################################

void print_tree23(const Portugues23 *raiz)
{
    if (raiz != NULL)
    {
        print_tree23(raiz->esq);
        printf("Palavra (PT): %s", raiz->info1.palavraPortugues);
        if (raiz->info1.palavraIngles != NULL && raiz->info1.palavraIngles->palavraIngles != NULL)
        {
            printBinaryTree(raiz->info1.palavraIngles);
            printf("\n");
        }
        print_tree23(raiz->cent);
        // Se houver o segundo elemento (nInfos == 2), exibe o segundo filho
        if (raiz->nInfos == 2)
        {
            printf("Palavra (PT): %s", raiz->info2.palavraPortugues);

            // Exibir a tradução em inglês, se houver
            if (raiz->info2.palavraIngles != NULL && raiz->info2.palavraIngles->palavraIngles != NULL)
                printBinaryTree(raiz->info2.palavraIngles);
            printf("\n");
        }

        if (raiz->nInfos == 2)
        {
            print_tree23(raiz->dir);
        }
    }
}

void printWordsAtUnit(Portugues23 *arvore, int unidade, int *unidadeImpressa)
{
    if (arvore)
    {
        // Percorre a subárvore esquerda
        printWordsAtUnit(arvore->esq, unidade, unidadeImpressa);

        // Imprime o cabeçalho da unidade uma vez
        if (!(*unidadeImpressa))
        {
            printf("%% Unidade %d\n", unidade); // Cabeçalho da unidade
            *unidadeImpressa = 1;               // Marca como já impresso
        }

        // Imprime as traduções associadas à unidade para a primeira palavra do nó
        if (arvore->info1.palavraIngles != NULL)
        {
            printTranslationsInFormat(arvore->info1.palavraIngles, unidade, arvore->info1.palavraPortugues);
        }

        // Percorre a subárvore central
        printWordsAtUnit(arvore->cent, unidade, unidadeImpressa);

        // Se houver o segundo elemento no nó, imprime também suas traduções
        if (arvore->nInfos == 2 && arvore->info2.palavraIngles != NULL)
        {
            printTranslationsInFormat(arvore->info2.palavraIngles, unidade, arvore->info2.palavraPortugues);
        }

        // Percorre a subárvore direita, se existir
        if (arvore->nInfos == 2)
        {
            printWordsAtUnit(arvore->dir, unidade, unidadeImpressa);
        }
    }
}

void printTranslationsInFormat(Inglesbin *node, int unidade, const char *palavraPortugues)
{
    if (node)
    {
        // Percorre a subárvore esquerda
        printTranslationsInFormat(node->esq, unidade, palavraPortugues);

        // Verifica se a unidade está associada à palavra em inglês
        if (find_unit(node->unidades, unidade)) // Verifica se a unidade está presente na lista
        {
            // Remove o ';' no final de palavraPortugues, se existir
            char palavraFormatada[256];
            strcpy(palavraFormatada, palavraPortugues);
            size_t len = strlen(palavraFormatada);
            if (len > 0 && palavraFormatada[len - 1] == ';')
            {
                palavraFormatada[len - 1] = '\0';
            }

            printf("%s: %s;\n", palavraFormatada, node->palavraIngles); // Formata corretamente
        }

        // Percorre a subárvore direita
        printTranslationsInFormat(node->dir, unidade, palavraPortugues);
    }
}

void printAllTranslations(Portugues23 *raiz, const char *palavraPortugues)
{
    int encontrou = 0;

    if (raiz == NULL)
    {
        printf("A palavra '%s' nao foi encontrada.\n", palavraPortugues);
    }
    else
    {
        // Verifica o no info1
        if (strcmp(raiz->info1.palavraPortugues, palavraPortugues) == 0)
        {
            printf("Traducoes para '%s':\n", palavraPortugues);
            showEnglishTranslations(raiz->info1.palavraIngles);
            encontrou = 1;
        }

        // Verifica o no info2 (se existir e ainda nao encontrou)
        if (!encontrou && raiz->nInfos == 2 && strcmp(raiz->info2.palavraPortugues, palavraPortugues) == 0)
        {
            printf("Traducoes para '%s':\n", palavraPortugues);
            showEnglishTranslations(raiz->info2.palavraIngles);
            encontrou = 1;
        }

        // Busca recursiva se ainda nao encontrou
        if (!encontrou)
        {
            if (strcmp(palavraPortugues, raiz->info1.palavraPortugues) < 0)
            {
                printAllTranslations(raiz->esq, palavraPortugues);
            }
            else if (raiz->nInfos == 1 || strcmp(palavraPortugues, raiz->info2.palavraPortugues) < 0)
            {
                printAllTranslations(raiz->cent, palavraPortugues);
            }
            else
            {
                printAllTranslations(raiz->dir, palavraPortugues);
            }
        }
    }
}


void printPortugueseTranslation(Portugues23 **raiz, const char *palavraPortugues)
{
    Portugues23 *resultado = FindWord(raiz, palavraPortugues);
    if (resultado)
    {
        printf("Traduções em inglês para a palavra '%s':\n", palavraPortugues);

        if (strcmp(palavraPortugues, resultado->info1.palavraPortugues) == 0)
        {
            printBinaryTree(resultado->info1.palavraIngles);
        }
        else if (resultado->nInfos == 2 && strcmp(palavraPortugues, resultado->info2.palavraPortugues) == 0)
        {
            printBinaryTree(resultado->info2.palavraIngles);
        }
    }
    else
    {
        printf("A palavra '%s' não foi encontrada na árvore.\n", palavraPortugues);
    }
}

static Info no23_maior_info(Portugues23 *raiz)
{
    return raiz->nInfos == 2 ? raiz->info2 : raiz->info1;
}

static int eh_info1(Portugues23 no, char *info)
{
    return strcmp(info, no.info1.palavraPortugues) == 0;
}

static int eh_info2(Portugues23 no, char *info)
{
    return no.nInfos == 2 && strcmp(info, no.info2.palavraPortugues) == 0;
}

Portugues23 *get_maximum_child_from_tree(Portugues23 *raiz, Portugues23 **pai, Info *maior_valor)
{
    Portugues23 *filho;
    filho = raiz;

    while (!ehFolha(filho))
    {
        *pai = filho;
        if (filho->nInfos == 1)
            filho = filho->cent;
        else
            filho = filho->dir;
    }

    if (filho != NULL)
        *maior_valor = no23_maior_info(filho);

    return filho;
}

Portugues23 *findMinimumChild(Portugues23 *raiz, Portugues23 **pai)
{
    Portugues23 *filho;
    filho = raiz;

    while (!ehFolha(filho))
    {
        *pai = filho;
        filho = filho->esq;
    }

    return filho;
}

static int calculate_height(Portugues23 *no)
{
    int altura = -1;
    if (no != NULL)
        altura = 1 + calculate_height(no->esq);
    return altura;
}

static int wave_movement(Info saindo, Info *entrada, Portugues23 *pai, Portugues23 **origem, Portugues23 **raiz, Portugues23 **maior, int (*funcao_remover)(Portugues23 **, char *, Portugues23 *, Portugues23 **, Portugues23 **))
{
    int removeu = funcao_remover(raiz, saindo.palavraPortugues, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}

static Portugues23 *findParentIn23Tree(Portugues23 *raiz, char *info)
{
    Portugues23 *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.palavraPortugues) < 0)
                pai = findParentIn23Tree(raiz->esq, info);
            else if (raiz->nInfos == 1 || (strcmp(info, raiz->info2.palavraPortugues) < 0))
                pai = findParentIn23Tree(raiz->cent, info);
            else
                pai = findParentIn23Tree(raiz->dir, info);

            if (pai == NULL)
                pai = raiz;
        }
    }

    return pai;
}

static Portugues23 *findLargestParentIn23Tree(Portugues23 *raiz, char *info)
{
    Portugues23 *pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.palavraPortugues) < 0)
                pai = findLargestParentIn23Tree(raiz->esq, info);
            else if (raiz->nInfos == 1 || (strcmp(info, raiz->info2.palavraPortugues) < 0))
                pai = findLargestParentIn23Tree(raiz->cent, info);
            else
                pai = findLargestParentIn23Tree(raiz->dir, info);

            if (pai == NULL &&
                ((raiz->nInfos == 1 && (strcmp(raiz->info1.palavraPortugues, info) > 0)) ||
                 (raiz->nInfos == 2 && (strcmp(raiz->info2.palavraPortugues, info) > 0))))
            {
                pai = raiz;
            }
        }
    }

    return pai;
}

static Portugues23 *findSmallestParentWithTwoInfo(Portugues23 *raiz, char *info)
{
    Portugues23 *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.palavraPortugues) < 0)
                pai = findSmallestParentWithTwoInfo(raiz->esq, info);
            else if (raiz->nInfos == 1 || (strcmp(info, raiz->info2.palavraPortugues) < 0))
                pai = findSmallestParentWithTwoInfo(raiz->cent, info);
            else
                pai = findSmallestParentWithTwoInfo(raiz->dir, info);

            if (pai == NULL && raiz->nInfos == 2 && strcmp(raiz->info2.palavraPortugues, info) < 0)
                pai = raiz;
        }
    }

    return pai;
}

static Portugues23 *findSmallestParent23(Portugues23 *raiz, char *info)
{
    Portugues23 *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.palavraPortugues) < 0)
                pai = findSmallestParent23(raiz->esq, info);
            else if (raiz->nInfos == 1 || strcmp(info, raiz->info2.palavraPortugues) < 0)
                pai = findSmallestParent23(raiz->cent, info);
            else
                pai = findSmallestParent23(raiz->dir, info);

            if (pai == NULL && strcmp(raiz->info1.palavraPortugues, info) < 0)
                pai = raiz;
        }
    }

    return pai;
}

int removeNonLeafNodeFrom23Tree(Portugues23 **origem, Portugues23 *raiz, Info *info, Portugues23 *filho1, Portugues23 *filho2, Portugues23 **maior)
{
    int removeu;
    Portugues23 *filho, *pai;
    Info info_filho;

    pai = raiz;

    filho = get_maximum_child_from_tree(filho1, &pai, &info_filho);

    if (filho->nInfos == 2)
    {
        *info = info_filho;
        filho->nInfos = 1;
        removeu = 1;
    }
    else
    {
        filho = findMinimumChild(filho2, &pai);
        removeu = wave_movement(filho->info1, info, pai, origem, &filho, maior, deleteFrom23Tree);
    }

    return removeu;
}

int nonLeafNodeDeletion(Portugues23 **origem, Portugues23 *raiz, Info *info, Portugues23 *filho1, Portugues23 *filho2, Portugues23 **maior)
{
    int removeu = 0;
    Portugues23 *filho, *pai;
    Info info_filho;

    pai = raiz;

    filho = findMinimumChild(filho1, &pai);

    if (filho->nInfos == 2)
    {
        *info = filho->info1;
        filho->info1 = filho->info2;
        filho->nInfos = 1;
        removeu = 1;
    }
    else
    {
        filho = get_maximum_child_from_tree(filho2, &pai, &info_filho);
        removeu = wave_movement(info_filho, info, pai, origem, &filho, maior, removeNodeFrom23Tree);
    }

    return removeu;
}

int deleteFrom23Tree(Portugues23 **raiz, char *info, Portugues23 *pai, Portugues23 **origem, Portugues23 **maior)
{
    int removeu = 0;

    if (*raiz != NULL)
    {
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if (info1 || info2)
        {
            removeu = 1;
            if (ehFolha(*raiz))
            {
                if ((*raiz)->nInfos == 2)
                {
                    if (info1)
                    {
                        (*raiz)->info1 = (*raiz)->info2;
                        (*raiz)->nInfos = 1; // Agora está claro que esta linha pertence ao bloco do if
                    }
                }
                else
                {
                    if (pai == NULL)
                        deallocateTree(raiz);
                    else
                    {
                        Portugues23 *pai_aux;
                        Info info_pai;
                        if (*raiz == pai->esq || (pai->nInfos == 2 && *raiz == pai->cent))
                        {
                            pai_aux = findParentIn23Tree(*origem, pai->info1.palavraPortugues);

                            if (*raiz == pai->esq)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = wave_movement(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, deleteFrom23Tree);
                        }
                        else
                        {
                            pai_aux = findLargestParentIn23Tree(*origem, (*raiz)->info1.palavraPortugues);

                            Portugues23 *menor_pai;
                            menor_pai = findSmallestParentWithTwoInfo(*origem, (*raiz)->info1.palavraPortugues);

                            if (pai_aux != NULL)
                            {
                                if (strcmp(pai_aux->info1.palavraPortugues, (*raiz)->info1.palavraPortugues) > 0)
                                    info_pai = pai_aux->info1;
                                else
                                    info_pai = pai_aux->info2;
                            }

                            int altura_menor_pai = calculate_height(menor_pai);
                            int altura_pai_aux = calculate_height(pai_aux);

                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL &&
                                                    altura_menor_pai <= altura_pai_aux && strcmp(info_pai.palavraPortugues, menor_pai->info2.palavraPortugues) > 0))
                            {
                                *maior = pai;
                                (*raiz)->nInfos = 0;
                                removeu = -1;
                            }
                            else
                            {
                                Portugues23 *avo;
                                avo = findParentIn23Tree(*origem, info_pai.palavraPortugues);
                                removeu = wave_movement(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, deleteFrom23Tree);
                            }
                        }
                    }
                }
            }
            else if (info2)
                removeu = removeNonLeafNodeFrom23Tree(origem, *raiz, &((*raiz)->info2), (*raiz)->cent, (*raiz)->dir, maior);
            else if (info1)
                removeu = removeNonLeafNodeFrom23Tree(origem, *raiz, &((*raiz)->info1), (*raiz)->esq, (*raiz)->cent, maior);
        }
        else
        {
            if (strcmp(info, (*raiz)->info1.palavraPortugues) < 0)
                removeu = deleteFrom23Tree(&(*raiz)->esq, info, *raiz, origem, maior);
            else if ((*raiz)->nInfos == 1 || (strcmp(info, (*raiz)->info2.palavraPortugues) < 0))
                removeu = deleteFrom23Tree(&(*raiz)->cent, info, *raiz, origem, maior);
            else
                removeu = deleteFrom23Tree(&(*raiz)->dir, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int removeNodeFrom23Tree(Portugues23 **raiz, char *info, Portugues23 *pai, Portugues23 **origem, Portugues23 **maior)
{
    int removeu = 0;

    if (*raiz != NULL)
    {
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if (info1 || info2)
        {
            removeu = 1;
            if (ehFolha(*raiz))
            {
                if ((*raiz)->nInfos == 2)
                {
                    if (info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->nInfos = 1;
                }
                else
                {
                    if (pai == NULL)
                        deallocateTree(raiz);
                    else
                    {
                        Portugues23 *pai_aux;
                        Info info_pai;
                        if (*raiz == pai->cent || (pai->nInfos == 2 && *raiz == pai->dir))
                        {
                            pai_aux = findParentIn23Tree(*origem, pai->info1.palavraPortugues);

                            if (*raiz == pai->cent)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = wave_movement(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, removeNodeFrom23Tree);
                        }
                        else
                        {
                            pai_aux = findSmallestParent23(*origem, (*raiz)->info1.palavraPortugues);

                            Portugues23 *menor_pai;
                            menor_pai = findSmallestParentWithTwoInfo(*origem, (*raiz)->info1.palavraPortugues);

                            Portugues23 *avo;
                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {
                                removeu = -1;
                                *maior = pai;
                            }
                            else
                            {
                                if (pai_aux->nInfos == 2 && pai_aux->info2.palavraPortugues < (*raiz)->info1.palavraPortugues)
                                    info_pai = pai_aux->info2;
                                else
                                    info_pai = pai_aux->info1;

                                avo = findParentIn23Tree(*origem, info_pai.palavraPortugues);
                                removeu = wave_movement(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, removeNodeFrom23Tree);
                            }
                        }
                    }
                }
            }
            else if (info2)
                removeu = nonLeafNodeDeletion(origem, *raiz, &((*raiz)->info2), (*raiz)->dir, (*raiz)->cent, maior);
            else if (info1)
                removeu = nonLeafNodeDeletion(origem, *raiz, &((*raiz)->info1), (*raiz)->cent, (*raiz)->esq, maior);
        }
        else
        {
            if (strcmp(info, (*raiz)->info1.palavraPortugues) < 0)
                removeu = removeNodeFrom23Tree(&(*raiz)->esq, info, *raiz, origem, maior);
            else if ((*raiz)->nInfos == 1 || (strcmp(info, (*raiz)->info2.palavraPortugues) < 0))
                removeu = removeNodeFrom23Tree(&(*raiz)->cent, info, *raiz, origem, maior);
            else
                removeu = removeNodeFrom23Tree(&(*raiz)->dir, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int can_remove_node(Portugues23 *raiz)
{
    int possivel = 0;

    if (raiz != NULL)
    {
        possivel = raiz->nInfos == 2;

        if (!possivel)
        {
            possivel = can_remove_node(raiz->cent);

            if (!possivel)
                possivel = can_remove_node(raiz->esq);
        }
    }

    return possivel;
}

Portugues23 *mergeNode23(Portugues23 *filho1, Info *info, Portugues23 *maior, Portugues23 **raiz)
{
    updateNode23(filho1, info, maior);

    (*raiz)->nInfos--;

    if ((*raiz)->nInfos == 0)
        deallocateTree(raiz);

    return filho1;
}

static void balanceTreeNodes(Portugues23 **raiz, Portugues23 *filho1, Portugues23 **filho2, Info info, Portugues23 **maior)
{
    if (*filho2 == NULL || (*filho2)->nInfos == 0)
    {
        if (*filho2 != NULL)
            deallocateTree(filho2);
        *maior = mergeNode23(filho1, &info, *maior, raiz);
    }
}

int rebalanceTree23(Portugues23 **raiz, char *info, Portugues23 **maior)
{
    int balanceou = 0;
    if (*raiz != NULL)
    {
        if (!ehFolha(*raiz))
        {
            if (strcmp(info, (*raiz)->info1.palavraPortugues) < 0)
                balanceou = rebalanceTree23(&((*raiz)->esq), info, maior);
            else if ((*raiz)->nInfos == 1 || (strcmp(info, (*raiz)->info2.palavraPortugues) < 0))
            {
                if ((*raiz)->esq->nInfos == 2 && !can_remove_node((*raiz)->cent))
                    balanceou = -1;
                else
                    balanceou = rebalanceTree23(&((*raiz)->cent), info, maior);
            }
            else
            {
                if ((*raiz)->cent->nInfos == 2 && !can_remove_node((*raiz)->dir))
                    balanceou = -1;
                else
                    balanceou = rebalanceTree23(&((*raiz)->dir), info, maior);
            }

            if (balanceou != -1)
            {
                if ((*raiz)->nInfos == 1)
                    balanceTreeNodes(raiz, (*raiz)->esq, &((*raiz)->cent), (*raiz)->info1, maior);
                else if ((*raiz)->nInfos == 2)
                    balanceTreeNodes(raiz, (*raiz)->cent, &((*raiz)->dir), (*raiz)->info2, maior);
                balanceou = 1;
            }
        }
    }

    return balanceou;
}

int remove_node_from23_tree(Portugues23 **raiz, char *info)
{
    Portugues23 *maior, *posicao_juncao;
    int removeu = deleteFrom23Tree(raiz, info, NULL, raiz, &posicao_juncao);

    if (removeu == -1)
    {
        Info valor_juncao = no23_maior_info(posicao_juncao);
        maior = NULL;
        removeu = rebalanceTree23(raiz, valor_juncao.palavraPortugues, &maior);

        if (removeu == -1)
        {
            Portugues23 *pai, *posicao_juncao2;
            Info *entrada;
            pai = findParentIn23Tree(*raiz, valor_juncao.palavraPortugues);

            if (eh_info1(*posicao_juncao, valor_juncao.palavraPortugues))
                entrada = &(posicao_juncao->cent->info1);
            else
                entrada = &(posicao_juncao->dir->info1);

            removeu = wave_movement(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2, removeNodeFrom23Tree);

            if (removeu == -1)
            {
                valor_juncao = posicao_juncao2->info1;
                pai = findParentIn23Tree(*raiz, valor_juncao.palavraPortugues);
                removeu = wave_movement(valor_juncao, &(posicao_juncao2->esq->info1), pai, raiz, &posicao_juncao2, &posicao_juncao, deleteFrom23Tree);

                valor_juncao = no23_maior_info(posicao_juncao);
                maior = NULL;
                removeu = rebalanceTree23(raiz, valor_juncao.palavraPortugues, &maior);
            }
        }

        if (*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}

/*#########################################FREE#######################################################*/

void deleteInfo2_3(Info *info)
{
    if (info != NULL)
    {
        clear_binary_tree(info->palavraIngles);
        free(info->palavraPortugues);
    }
}

void deallocateTree(Portugues23 **no)
{
    if (*no != NULL)
    {
        deallocateTree(&((*no)->esq));
        deallocateTree(&((*no)->cent));
        if ((*no)->nInfos == 2)
        {
            deleteInfo2_3(&((*no)->info2));
            deallocateTree(&((*no)->dir));
        }
        deleteInfo2_3(&((*no)->info1));
        free(*no);
        *no = NULL;
    }
}


void removeEnglishTranslation(Portugues23 **raiz, char *palavraIngles, int unidade, Portugues23 **pai) {
    if (*raiz != NULL) {
        // Percorre a subárvore esquerda
        removeEnglishTranslation(&(*raiz)->esq, palavraIngles, unidade, pai);

        // Verifica no primeiro elemento do nó
        if ((*raiz)->info1.palavraIngles != NULL) {
            removeEnglishWord(&(*raiz)->info1.palavraIngles, palavraIngles, unidade);
        }

        // Percorre a subárvore central
        removeEnglishTranslation(&(*raiz)->cent, palavraIngles, unidade, pai);

        // Verifica no segundo elemento do nó, se existir
        if ((*raiz)->nInfos == 2 && (*raiz)->info2.palavraIngles != NULL) {
            removeEnglishWord(&(*raiz)->info2.palavraIngles, palavraIngles, unidade);
        }

        // Percorre a subárvore direita, se existir
        if ((*raiz)->nInfos == 2) {
            removeEnglishTranslation(&(*raiz)->dir, palavraIngles, unidade, pai);
        }
    }
}

void printFormattedWordsByUnit(Portugues23 *arvore, int unidade, int *unidadeImpressa) {
    if (arvore) {
        // Percorre a subárvore esquerda
        printFormattedWordsByUnit(arvore->esq, unidade, unidadeImpressa);

        // Verifica as palavras associadas ao `info1` do nó
        if (arvore->info1.palavraIngles != NULL) {
            Inglesbin *ingles = arvore->info1.palavraIngles;
            while (ingles) {
                if (find_unit(ingles->unidades, unidade)) {
                    if (!(*unidadeImpressa)) {
                        printf("%% Unidade %d\n", unidade);
                        *unidadeImpressa = 1;
                    }
                    printf("%s: %s;\n", arvore->info1.palavraPortugues, ingles->palavraIngles);
                }
                ingles = ingles->esq ? ingles->esq : ingles->dir;
            }
        }

        // Percorre a subárvore central
        printFormattedWordsByUnit(arvore->cent, unidade, unidadeImpressa);

        // Verifica as palavras associadas ao `info2` do nó, se existir
        if (arvore->nInfos == 2 && arvore->info2.palavraIngles != NULL) {
            Inglesbin *ingles = arvore->info2.palavraIngles;
            while (ingles) {
                if (find_unit(ingles->unidades, unidade)) {
                    if (!(*unidadeImpressa)) {
                        printf("%% Unidade %d\n", unidade);
                        *unidadeImpressa = 1;
                    }
                    printf("%s: %s;\n", arvore->info2.palavraPortugues, ingles->palavraIngles);
                }
                ingles = ingles->esq ? ingles->esq : ingles->dir;
            }
        }

        // Percorre a subárvore direita, se existir
        if (arvore->nInfos == 2) {
            printFormattedWordsByUnit(arvore->dir, unidade, unidadeImpressa);
        }
    }
}



void removePortugueseWordByUnit(Portugues23 **raiz, const char *palavraPortugues, int unidade) {
    Portugues23 *noPortugues = FindWord(raiz, palavraPortugues);
    int encontrado = 0;

    if (noPortugues != NULL) {
        // Verificar info1
        if (strcmp(noPortugues->info1.palavraPortugues, palavraPortugues) == 0) {
            Inglesbin *ingles = noPortugues->info1.palavraIngles;
            while (ingles) {
                if (find_unit(ingles->unidades, unidade)) {
                    encontrado = 1;
                    removeEnglishWord(&(noPortugues->info1.palavraIngles), ingles->palavraIngles, unidade);

                    if (noPortugues->info1.palavraIngles == NULL) {
                        deleteInfo2_3(&(noPortugues->info1));
                        noPortugues->info1.palavraPortugues = NULL; // Marca como vazio
                    }
                }
                ingles = ingles->esq ? ingles->esq : ingles->dir;
            }
        }

        // Verificar info2
        if (!encontrado && noPortugues->nInfos == 2 && strcmp(noPortugues->info2.palavraPortugues, palavraPortugues) == 0) {
            Inglesbin *ingles = noPortugues->info2.palavraIngles;
            while (ingles) {
                if (find_unit(ingles->unidades, unidade)) {
                    encontrado = 1;
                    removeEnglishWord(&(noPortugues->info2.palavraIngles), ingles->palavraIngles, unidade);

                    if (noPortugues->info2.palavraIngles == NULL) {
                        deleteInfo2_3(&(noPortugues->info2));
                        noPortugues->info2.palavraPortugues = NULL; // Marca como vazio
                    }
                }
                ingles = ingles->esq ? ingles->esq : ingles->dir;
            }
        }
    }

    // A lógica de retorno único
  
}


int Delete_portuguese_word_unit(Inglesbin **raiz, const char *palavraPortugues, int unidade) {
    int confirm = 0;

    if (*raiz) {
        // Remoção recursiva nos filhos
        confirm = Delete_portuguese_word_unit(&(*raiz)->esq, palavraPortugues, unidade);
        confirm = Delete_portuguese_word_unit(&(*raiz)->dir, palavraPortugues, unidade) || confirm;

        // Atualiza a lista de unidades associadas
        Unit *novaLista = remove_unit((*raiz)->unidades, unidade);
        if (novaLista != (*raiz)->unidades) {
            confirm = 1; // Indica que a unidade foi removida
        }
        (*raiz)->unidades = novaLista;

        // Se a lista de unidades ficar vazia, remove o nó da árvore binária
        if (!(*raiz)->unidades) {
            confirm = removeEnglishWord(raiz, (*raiz)->palavraIngles, unidade);
        }
    }

    return confirm;
}


int delete_portuguese_word_in_unit(Portugues23 *raiz, char *palavraPortugues, int unidade, Portugues23 **top) {
    int confirm = 0;

    if (raiz) {
        if (strcmp(raiz->info1.palavraPortugues, palavraPortugues) == 0) {
            confirm = Delete_portuguese_word_unit(&raiz->info1.palavraIngles, palavraPortugues, unidade);

            if (!raiz->info1.palavraIngles) {
                confirm = remove_node_from23_tree(top, palavraPortugues);
            }
        } else if (raiz->nInfos == 2 && strcmp(raiz->info2.palavraPortugues, palavraPortugues) == 0) {
            confirm = Delete_portuguese_word_unit(&raiz->info2.palavraIngles, palavraPortugues, unidade);

            if (!raiz->info2.palavraIngles) {
                confirm = remove_node_from23_tree(top, palavraPortugues);
            }
        } else if (strcmp(palavraPortugues, raiz->info1.palavraPortugues) < 0) {
            confirm = delete_portuguese_word_in_unit(raiz->esq, palavraPortugues, unidade, top);
        } else if (raiz->nInfos == 1 || strcmp(palavraPortugues, raiz->info2.palavraPortugues) < 0) {
            confirm = delete_portuguese_word_in_unit(raiz->cent, palavraPortugues, unidade, top);
        } else {
            confirm = delete_portuguese_word_in_unit(raiz->dir, palavraPortugues, unidade, top);
        }
    }

    return confirm;
}

int Remove_word_from_portuguese_unit(Portugues23 **raiz, char *palavraPortugues, int unidade) {
    int confirm = 0;
    confirm = delete_portuguese_word_in_unit(*raiz, palavraPortugues, unidade, raiz);
    return confirm;
}