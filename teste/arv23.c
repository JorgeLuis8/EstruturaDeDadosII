#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv23.h"
#include "arvbin.h"
#include "lista_encadeada.h"

int inserirPalavraPortugues(PortugueseTree **arvore, char *palavraPortugues, char *palavraIngles, char *unidade)
{
    NodeInfo promove;
    PortugueseTree *Pai = NULL;
    int inseriu = 0;

    NodeInfo novoInfo = criaInfo(palavraPortugues, palavraIngles, unidade);
    if (insertNode23(arvore, &novoInfo, &promove, &Pai))
        inseriu = 1;

    return inseriu;
}

NodeInfo criaInfo(char *palavra, char *palavraIngles, char *unidade)
{
    NodeInfo info;

    // Aloca e copia a palavra em portugues
    info.portugueseWord = malloc(strlen(palavra) + 1);
    strcpy(info.portugueseWord, palavra);

    // Estrutura de palavraIngles
    info.englishWord = malloc(sizeof(Inglesbin));
    info.englishWord->palavraIngles = malloc(strlen(palavraIngles) + 1);
    strcpy(info.englishWord->palavraIngles, palavraIngles);

    info.englishWord->unidades = NULL;
    inserir_lista_encadeada_unidade(&(info.englishWord->unidades), unidade);

    return info;
}

PortugueseTree *createNode(const NodeInfo *informacao, PortugueseTree *filhoesq, PortugueseTree *filhocen)
{
    PortugueseTree *no;
    no = (PortugueseTree *)malloc(sizeof(PortugueseTree)); // allocate memory

    // Preenche info1 com os dados da nova disciplina
    no->info1 = *informacao;
    no->left = filhoesq;
    no->cent = filhocen;
    no->nInfos = 1;

    // Inicializa info2 com nulo
    no->info2.englishWord = NULL;
    no->info2.portugueseWord = NULL;
    no->right = NULL;

    return no;
}

void adicionaChave(PortugueseTree *no, const NodeInfo informacao, PortugueseTree *filho)
{
    if (strcmp(informacao.portugueseWord, (no)->info1.portugueseWord) > 0)
    {
        // Adiciona a nova informação a info2
        (no)->info2 = informacao;
        (no)->right = filho; // Ajusta o ponteiro do filho dir
    }
    else
    {
        // Move info1 para info2 e coloca a nova informação em info1
        (no)->info2 = (no)->info1;
        (no)->info1 = informacao;
        (no)->right = (no)->cent;
        (no)->cent = filho;
    }
    (no)->nInfos = 2; // Atualiza o número de informações
}

PortugueseTree *quebraNo(PortugueseTree **no, const NodeInfo *informacao, NodeInfo *promove, PortugueseTree *filho)
{
    PortugueseTree *maior;

    if (strcmp(informacao->portugueseWord, (*no)->info1.portugueseWord) < 0)
    {
        // A nova informação é menor que info1, então info1 será promovida
        *promove = (*no)->info1;
        maior = createNode(&(*no)->info2, (*no)->cent, (*no)->right);

        // Atualiza info1 com a nova informação
        (*no)->info1 = *informacao;
        (*no)->cent = filho;
    }
    else if (strcmp(informacao->portugueseWord, (*no)->info2.portugueseWord) < 0)
    {
        // A nova informação é maior que info1 e menor que info2, então ela será promovida
        *promove = *informacao;
        maior = createNode(&(*no)->info2, filho, (*no)->right);
    }
    else
    {
        // A nova informação é maior que info1 e info2, então info2 será promovido
        *promove = (*no)->info2;
        maior = createNode(informacao, (*no)->right, filho);
    }

    // Limpa info2
    (*no)->info2.englishWord = NULL;
    (*no)->info2.portugueseWord = NULL;

    (*no)->nInfos = 1; // Atualizando a quantidade de informação no nó
    (*no)->right = NULL; // Ajusta o filho dir

    return maior;
}

int isNodeLeaf(const PortugueseTree *no)
{
    int achou = 0;

    if (no->left == NULL)
        achou = 1; // Se não tem filho esq, é uma folha
    return achou;
}

PortugueseTree *insertNode23(PortugueseTree **no, NodeInfo *informacao, NodeInfo *promove, PortugueseTree **Pai)
{
    NodeInfo promove1;
    PortugueseTree *maiorNo = NULL;

    if (*no == NULL)
        *no = createNode(informacao, NULL, NULL); // Cria um novo nó caso seja nulo
    if (strcmp(informacao->portugueseWord, (*no)->info1.portugueseWord) == 0)
        insertpalavraIngles(&(*no)->info1.englishWord, informacao);
    else if ((*no)->nInfos == 2 && strcmp(informacao->portugueseWord, (*no)->info2.portugueseWord) == 0)
        insertpalavraIngles(&(*no)->info2.englishWord, informacao);
    else
    {
        if (isNodeLeaf(*no))
        { // Verifica se é folha
            if ((*no)->nInfos == 1)
                adicionaChave(*no, *informacao, NULL); // O nó tem espaço para a nova chave
            else
            {
                // O nó precisa ser quebrado
                PortugueseTree *novo;
                novo = quebraNo(no, informacao, promove, NULL); // quebra no e sobe a informação
                if (*Pai == NULL)
                {
                    PortugueseTree *novaRaiz;
                    novaRaiz = createNode(promove, *no, novo); // Cria nova raiz se o pai for nulo e o novo no se torna filho do cent
                    *no = novaRaiz;
                }
                else
                    maiorNo = novo; // Ajusta o novo maior nó
            }
        }
        else
        { // Nó não é folha
            // Navega para o filho apropriado
            if (strcmp(informacao->portugueseWord, (*no)->info1.portugueseWord) < 0)
                maiorNo = insertNode23(&((*no)->left), informacao, promove, no); // Insere na subárvore à esq
            else if ((*no)->nInfos == 1 || strcmp(informacao->portugueseWord, (*no)->info2.portugueseWord) < 0)
                maiorNo = insertNode23(&((*no)->cent), informacao, promove, no); // Insere na subárvore do cent
            else
                maiorNo = insertNode23(&((*no)->right), informacao, promove, no); // Insere na subárvore à dir

            // Após inserir, verifica se houve promoção
            if (maiorNo != NULL)
            {
                if ((*no)->nInfos == 1)
                {
                    adicionaChave(*no, *promove, maiorNo);
                    maiorNo = NULL;
                }
                else
                { // Quando não tem espaço
                    // O nó precisa ser quebrado
                    PortugueseTree *novo;
                    novo = quebraNo(no, promove, &promove1, maiorNo); // Quebra o nó e sobe a informação
                    if (*Pai == NULL)
                    {
                        PortugueseTree *novaRaiz;
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

void print_tree23(const PortugueseTree *Raiz)
{
    if (Raiz != NULL)
    {
        print_tree23(Raiz->left);
        printf("Palavra (PT): %s\n", Raiz->info1.portugueseWord);
        printBinaryTree(Raiz->info1.englishWord);
        printf("\n");
        print_tree23(Raiz->cent);
        // Se houver o segundo elemento (nInfos == 2), exibe o segundo filho
        if (Raiz->nInfos == 2)
        {
            printf("Palavra (PT): %s\n", Raiz->info2.portugueseWord);
            printBinaryTree(Raiz->info2.englishWord);
            printf("\n");
            print_tree23(Raiz->right);
        }
    }
}

void imprimirPalavrasUnidade(PortugueseTree *arvore, char *unidade)
{
    if (arvore)
    {
        imprimirPalavrasUnidade(arvore->left, unidade);
        imprimirTraducoes(arvore->info1.englishWord, unidade, arvore->info1.portugueseWord);

        imprimirPalavrasUnidade(arvore->cent, unidade);
        if (arvore->nInfos == 2)
        {
            imprimirTraducoes(arvore->info2.englishWord, unidade, arvore->info2.portugueseWord);
        }
        imprimirPalavrasUnidade(arvore->right, unidade);
    }
}

void imprimirTraducoes(Inglesbin *node, char *unidade, const char *palavraPortugues)
{
    if (node)
    {
        if (buscar_lista_encadeada_unidade(node->unidades, unidade))
        {
            printf("Palavra em Portugues: %s\n", palavraPortugues);
            printf("Palavra em ingles: %s\n", node->palavraIngles);
        }
        imprimirTraducoes(node->esq, unidade, palavraPortugues);
        imprimirTraducoes(node->dir, unidade, palavraPortugues);
    }
}

PortugueseTree *FindWord(PortugueseTree **no, const char *palavraPortugues)
{
    PortugueseTree *inserida = NULL; // Inicializa o retorno como NULL

    if (no != NULL && *no != NULL)
    {
        if (strcmp(palavraPortugues, (*no)->info1.portugueseWord) == 0)
            inserida = (*no); // Palavra encontrada, retorna o nó
        else if ((*no)->nInfos == 2 && strcmp(palavraPortugues, (*no)->info2.portugueseWord) == 0)
            inserida = (*no);
        else
        {
            // Continua a busca nos filhos
            if (strcmp(palavraPortugues, (*no)->info1.portugueseWord) < 0)
                inserida = FindWord(&(*no)->left, palavraPortugues);
            else if ((*no)->nInfos == 1 || strcmp(palavraPortugues, (*no)->info2.portugueseWord) < 0)
                inserida = FindWord(&(*no)->cent, palavraPortugues);
            else
                inserida = FindWord(&(*no)->right, palavraPortugues);
        }
    }

    return inserida;
}

void printPortugueseTranslation(PortugueseTree **Raiz, const char *palavraPortugues)
{
    PortugueseTree *resultado = NULL;
    if (Raiz != NULL)
    {
        resultado = FindWord(Raiz, palavraPortugues);
        if (resultado)
        {
            printf("Traducoes em ingles para a palavra '%s':\n", palavraPortugues);

            if (strcmp(palavraPortugues, resultado->info1.portugueseWord) == 0)
                printBinaryTree(resultado->info1.englishWord);
            else
                printBinaryTree(resultado->info2.englishWord);
        }
        else
            printf("A palavra '%s' nao foi encontrada na arvore.\n", palavraPortugues);
    }
}

void arvore23_exibir_pre(PortugueseTree *raiz)
{
    if (raiz != NULL)
    {
        printf("[1º] %s -> ", raiz->info1.portugueseWord);
        if (raiz->nInfos == 2)
            printf("[2º] %s -> ", raiz->info2.portugueseWord);

        arvore23_exibir_pre(raiz->left);
        arvore23_exibir_pre(raiz->cent);
        if (raiz->nInfos == 2)
            arvore23_exibir_pre(raiz->right);
    }
}

void arvore23_exibir_ordem(PortugueseTree *raiz)
{
    if (raiz != NULL)
    {
        arvore23_exibir_ordem(raiz->left);
        printf("[1º] %s -> ", raiz->info1.portugueseWord);
        arvore23_exibir_ordem(raiz->cent);

        if (raiz->nInfos == 2)
        {
            printf("[2º] %s -> ", raiz->info2.portugueseWord);
            arvore23_exibir_ordem(raiz->right);
        }
    }
}

void arvore23_exibir_pos(PortugueseTree *raiz)
{
    if (raiz != NULL)
    {
        arvore23_exibir_pos(raiz->left);
        arvore23_exibir_pos(raiz->cent);
        if (raiz->nInfos == 2)
            arvore23_exibir_pos(raiz->right);

        printf("[1º] %s -> ", raiz->info1.portugueseWord);
        if (raiz->nInfos == 2)
            printf("[2º] %s -> ", raiz->info2.portugueseWord);
    }
}

// ############################################# REMOÇÃO ############################################

static NodeInfo no23_maior_info(PortugueseTree *raiz)
{
    return raiz->nInfos == 2 ? raiz->info2 : raiz->info1;
}

static int eh_info1(PortugueseTree no, char *info)
{
    return strcmp(info, no.info1.portugueseWord) == 0;
}

static int eh_info2(PortugueseTree no, char *info)
{
    return no.nInfos == 2 && strcmp(info, no.info2.portugueseWord) == 0;
}

PortugueseTree *get_maximum_child_from_tree(PortugueseTree *raiz, PortugueseTree **pai, NodeInfo *maior_valor)
{
    PortugueseTree *filho;
    filho = raiz;

    while (!isNodeLeaf(filho))
    {
        *pai = filho;
        if (filho->nInfos == 1)
            filho = filho->cent;
        else
            filho = filho->right;
    }

    if (filho != NULL)
        *maior_valor = no23_maior_info(filho);

    return filho;
}

PortugueseTree *findMinimumChild(PortugueseTree *raiz, PortugueseTree **pai)
{
    PortugueseTree *filho;
    filho = raiz;

    while (!isNodeLeaf(filho))
    {
        *pai = filho;
        filho = filho->left;
    }

    return filho;
}

static int calculate_height(PortugueseTree *no)
{
    int altura = -1;
    if (no != NULL)
        altura = 1 + calculate_height(no->left);
    return altura;
}

static int wave_movement(NodeInfo saindo, NodeInfo *entrada, PortugueseTree *pai, PortugueseTree **origem, PortugueseTree **raiz, PortugueseTree **maior, int (*funcao_remover)(PortugueseTree **, char *, PortugueseTree *, PortugueseTree **, PortugueseTree **))
{
    int removeu = funcao_remover(raiz, saindo.portugueseWord, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}

static PortugueseTree *findParentIn23Tree(PortugueseTree *raiz, char *info)
{
    PortugueseTree *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.portugueseWord) < 0)
                pai = findParentIn23Tree(raiz->left, info);
            else if (raiz->nInfos == 1 || (strcmp(info, raiz->info2.portugueseWord) < 0))
                pai = findParentIn23Tree(raiz->cent, info);
            else
                pai = findParentIn23Tree(raiz->right, info);

            if (pai == NULL)
                pai = raiz;
        }
    }

    return pai;
}

static PortugueseTree *findLargestParentIn23Tree(PortugueseTree *raiz, char *info)
{
    PortugueseTree *pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.portugueseWord) < 0)
                pai = findLargestParentIn23Tree(raiz->left, info);
            else if (raiz->nInfos == 1 || (strcmp(info, raiz->info2.portugueseWord) < 0))
                pai = findLargestParentIn23Tree(raiz->cent, info);
            else
                pai = findLargestParentIn23Tree(raiz->right, info);

            if (pai == NULL &&
                ((raiz->nInfos == 1 && (strcmp(raiz->info1.portugueseWord, info) > 0)) ||
                 (raiz->nInfos == 2 && (strcmp(raiz->info2.portugueseWord, info) > 0))))
            {
                pai = raiz;
            }
        }
    }

    return pai;
}

static PortugueseTree *findSmallestParentWithTwoInfo(PortugueseTree *raiz, char *info)
{
    PortugueseTree *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.portugueseWord) < 0)
                pai = findSmallestParentWithTwoInfo(raiz->left, info);
            else if (raiz->nInfos == 1 || (strcmp(info, raiz->info2.portugueseWord) < 0))
                pai = findSmallestParentWithTwoInfo(raiz->cent, info);
            else
                pai = findSmallestParentWithTwoInfo(raiz->right, info);

            if (pai == NULL && raiz->nInfos == 2 && strcmp(raiz->info2.portugueseWord, info) < 0)
                pai = raiz;
        }
    }

    return pai;
}

static PortugueseTree *findSmallestParent23(PortugueseTree *raiz, char *info)
{
    PortugueseTree *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.portugueseWord) < 0)
                pai = findSmallestParent23(raiz->left, info);
            else if (raiz->nInfos == 1 || strcmp(info, raiz->info2.portugueseWord) < 0)
                pai = findSmallestParent23(raiz->cent, info);
            else
                pai = findSmallestParent23(raiz->right, info);

            if (pai == NULL && strcmp(raiz->info1.portugueseWord, info) < 0)
                pai = raiz;
        }
    }

    return pai;
}

int removeNonLeafNodeFrom23Tree(PortugueseTree **origem, PortugueseTree *raiz, NodeInfo *info, PortugueseTree *filho1, PortugueseTree *filho2, PortugueseTree **maior)
{
    int removeu;
    PortugueseTree *filho, *pai;
    NodeInfo info_filho;

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

int nonLeafNodeDeletion(PortugueseTree **origem, PortugueseTree *raiz, NodeInfo *info, PortugueseTree *filho1, PortugueseTree *filho2, PortugueseTree **maior)
{
    int removeu = 0;
    PortugueseTree *filho, *pai;
    NodeInfo info_filho;

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

int deleteFrom23Tree(PortugueseTree **raiz, char *info, PortugueseTree *pai, PortugueseTree **origem, PortugueseTree **maior)
{
    int removeu = 0;

    if (*raiz != NULL)
    {
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if (info1 || info2)
        {
            removeu = 1;
            if (isNodeLeaf(*raiz))
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
                        PortugueseTree *pai_aux;
                        NodeInfo info_pai;
                        if (*raiz == pai->left || (pai->nInfos == 2 && *raiz == pai->cent))
                        {
                            pai_aux = findParentIn23Tree(*origem, pai->info1.portugueseWord);

                            if (*raiz == pai->left)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = wave_movement(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, deleteFrom23Tree);
                        }
                        else
                        {
                            pai_aux = findLargestParentIn23Tree(*origem, (*raiz)->info1.portugueseWord);

                            PortugueseTree *menor_pai;
                            menor_pai = findSmallestParentWithTwoInfo(*origem, (*raiz)->info1.portugueseWord);

                            if (pai_aux != NULL)
                            {
                                if (strcmp(pai_aux->info1.portugueseWord, (*raiz)->info1.portugueseWord) > 0)
                                    info_pai = pai_aux->info1;
                                else
                                    info_pai = pai_aux->info2;
                            }

                            int altura_menor_pai = calculate_height(menor_pai);
                            int altura_pai_aux = calculate_height(pai_aux);

                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL &&
                                                    altura_menor_pai <= altura_pai_aux && strcmp(info_pai.portugueseWord, menor_pai->info2.portugueseWord) > 0))
                            {
                                *maior = pai;
                                (*raiz)->nInfos = 0;
                                removeu = -1;
                            }
                            else
                            {
                                PortugueseTree *avo;
                                avo = findParentIn23Tree(*origem, info_pai.portugueseWord);
                                removeu = wave_movement(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, deleteFrom23Tree);
                            }
                        }
                    }
                }
            }
            else if (info2)
                removeu = removeNonLeafNodeFrom23Tree(origem, *raiz, &((*raiz)->info2), (*raiz)->cent, (*raiz)->right, maior);
            else if (info1)
                removeu = removeNonLeafNodeFrom23Tree(origem, *raiz, &((*raiz)->info1), (*raiz)->left, (*raiz)->cent, maior);
        }
        else
        {
            if (strcmp(info, (*raiz)->info1.portugueseWord) < 0)
                removeu = deleteFrom23Tree(&(*raiz)->left, info, *raiz, origem, maior);
            else if ((*raiz)->nInfos == 1 || (strcmp(info, (*raiz)->info2.portugueseWord) < 0))
                removeu = deleteFrom23Tree(&(*raiz)->cent, info, *raiz, origem, maior);
            else
                removeu = deleteFrom23Tree(&(*raiz)->right, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int removeNodeFrom23Tree(PortugueseTree **raiz, char *info, PortugueseTree *pai, PortugueseTree **origem, PortugueseTree **maior)
{
    int removeu = 0;

    if (*raiz != NULL)
    {
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if (info1 || info2)
        {
            removeu = 1;
            if (isNodeLeaf(*raiz))
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
                        PortugueseTree *pai_aux;
                        NodeInfo info_pai;
                        if (*raiz == pai->cent || (pai->nInfos == 2 && *raiz == pai->right))
                        {
                            pai_aux = findParentIn23Tree(*origem, pai->info1.portugueseWord);

                            if (*raiz == pai->cent)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = wave_movement(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, removeNodeFrom23Tree);
                        }
                        else
                        {
                            pai_aux = findSmallestParent23(*origem, (*raiz)->info1.portugueseWord);

                            PortugueseTree *menor_pai;
                            menor_pai = findSmallestParentWithTwoInfo(*origem, (*raiz)->info1.portugueseWord);

                            PortugueseTree *avo;
                            if (pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {
                                removeu = -1;
                                *maior = pai;
                            }
                            else
                            {
                                if (pai_aux->nInfos == 2 && pai_aux->info2.portugueseWord < (*raiz)->info1.portugueseWord)
                                    info_pai = pai_aux->info2;
                                else
                                    info_pai = pai_aux->info1;

                                avo = findParentIn23Tree(*origem, info_pai.portugueseWord);
                                removeu = wave_movement(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, removeNodeFrom23Tree);
                            }
                        }
                    }
                }
            }
            else if (info2)
                removeu = nonLeafNodeDeletion(origem, *raiz, &((*raiz)->info2), (*raiz)->right, (*raiz)->cent, maior);
            else if (info1)
                removeu = nonLeafNodeDeletion(origem, *raiz, &((*raiz)->info1), (*raiz)->cent, (*raiz)->left, maior);
        }
        else
        {
            if (strcmp(info, (*raiz)->info1.portugueseWord) < 0)
                removeu = removeNodeFrom23Tree(&(*raiz)->left, info, *raiz, origem, maior);
            else if ((*raiz)->nInfos == 1 || (strcmp(info, (*raiz)->info2.portugueseWord) < 0))
                removeu = removeNodeFrom23Tree(&(*raiz)->cent, info, *raiz, origem, maior);
            else
                removeu = removeNodeFrom23Tree(&(*raiz)->right, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int can_remove_node(PortugueseTree *raiz)
{
    int possivel = 0;

    if (raiz != NULL)
    {
        possivel = raiz->nInfos == 2;

        if (!possivel)
        {
            possivel = can_remove_node(raiz->cent);

            if (!possivel)
                possivel = can_remove_node(raiz->left);
        }
    }

    return possivel;
}

PortugueseTree *no23_juntar(PortugueseTree *filho1, NodeInfo info, PortugueseTree *maior, PortugueseTree **raiz)
{
    adicionaChave(filho1, info, maior);

    (*raiz)->nInfos--;

    if ((*raiz)->nInfos == 0)
        deallocateTree(raiz);

    return filho1;
}

static void balanceTreeNodes(PortugueseTree **raiz, PortugueseTree *filho1, PortugueseTree **filho2, NodeInfo info, PortugueseTree **maior)
{
    if (*filho2 == NULL || (*filho2)->nInfos == 0)
    {
        if (*filho2 != NULL)
            deallocateTree(filho2);
        *maior = no23_juntar(filho1, info, *maior, raiz);
    }
}

int rebalanceTree23(PortugueseTree **raiz, char *info, PortugueseTree **maior)
{
    int balanceou = 0;
    if (*raiz != NULL)
    {
        if (!isNodeLeaf(*raiz))
        {
            if (strcmp(info, (*raiz)->info1.portugueseWord) < 0)
                balanceou = rebalanceTree23(&((*raiz)->left), info, maior);
            else if ((*raiz)->nInfos == 1 || (strcmp(info, (*raiz)->info2.portugueseWord) < 0))
            {
                if ((*raiz)->left->nInfos == 2 && !can_remove_node((*raiz)->cent))
                    balanceou = -1;
                else
                    balanceou = rebalanceTree23(&((*raiz)->cent), info, maior);
            }
            else
            {
                if ((*raiz)->cent->nInfos == 2 && !can_remove_node((*raiz)->right))
                    balanceou = -1;
                else
                    balanceou = rebalanceTree23(&((*raiz)->right), info, maior);
            }

            if (balanceou != -1)
            {
                if ((*raiz)->nInfos == 1)
                    balanceTreeNodes(raiz, (*raiz)->left, &((*raiz)->cent), (*raiz)->info1, maior);
                else if ((*raiz)->nInfos == 2)
                    balanceTreeNodes(raiz, (*raiz)->cent, &((*raiz)->right), (*raiz)->info2, maior);
                balanceou = 1;
            }
        }
    }

    return balanceou;
}

int remove_node_from23_tree(PortugueseTree **raiz, char *info)
{
    PortugueseTree *maior, *posicao_juncao;
    int removeu = deleteFrom23Tree(raiz, info, NULL, raiz, &posicao_juncao);

    if (removeu == -1)
    {
        NodeInfo valor_juncao = no23_maior_info(posicao_juncao);
        maior = NULL;
        removeu = rebalanceTree23(raiz, valor_juncao.portugueseWord, &maior);

        if (removeu == -1)
        {
            PortugueseTree *pai, *posicao_juncao2;
            NodeInfo *entrada;
            pai = findParentIn23Tree(*raiz, valor_juncao.portugueseWord);

            if (eh_info1(*posicao_juncao, valor_juncao.portugueseWord))
                entrada = &(posicao_juncao->cent->info1);
            else
                entrada = &(posicao_juncao->right->info1);

            removeu = wave_movement(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2, removeNodeFrom23Tree);

            if (removeu == -1)
            {
                valor_juncao = posicao_juncao2->info1;
                pai = findParentIn23Tree(*raiz, valor_juncao.portugueseWord);
                removeu = wave_movement(valor_juncao, &(posicao_juncao2->left->info1), pai, raiz, &posicao_juncao2, &posicao_juncao, deleteFrom23Tree);

                valor_juncao = no23_maior_info(posicao_juncao);
                maior = NULL;
                removeu = rebalanceTree23(raiz, valor_juncao.portugueseWord, &maior);
            }
        }

        if (*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}

/*#########################################FREE#######################################################*/

void deleteInfo2_3(NodeInfo *info)
{
    if (info != NULL)
    {
        clear_binary_tree(info->englishWord);
        free(info->portugueseWord);
    }
}

void deallocateTree(PortugueseTree **no)
{
    if (*no != NULL)
    {
        deallocateTree(&((*no)->left));
        deallocateTree(&((*no)->cent));
        if ((*no)->nInfos == 2)
        {
            deleteInfo2_3(&((*no)->info2));
            deallocateTree(&((*no)->right));
        }
        deleteInfo2_3(&((*no)->info1));
        free(*no);
        *no = NULL;
    }
}