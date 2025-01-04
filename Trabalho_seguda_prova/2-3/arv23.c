#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv23.h"

Portugues23 *BuscarPalavra(Portugues23 **no, const char *palavraPortugues)
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
            printf("Comparando '%s' com '%s'\n", palavraPortugues, (*no)->info2.palavraPortugues);

            if (strcmp(palavraPortugues, (*no)->info2.palavraPortugues) == 0)
            {
                resultado = *no;
            }
        }

        if (resultado == NULL)
        {
            if (strcmp(palavraPortugues, (*no)->info1.palavraPortugues) < 0)
            {
                resultado = BuscarPalavra(&(*no)->esq, palavraPortugues);
            }
            else if ((*no)->nInfos == 1 || strcmp(palavraPortugues, (*no)->info2.palavraPortugues) < 0)
            {
                resultado = BuscarPalavra(&(*no)->cent, palavraPortugues);
            }
            else
            {
                resultado = BuscarPalavra(&(*no)->dir, palavraPortugues);
            }
        }
    }

    return resultado;
}

void adicionarTraducao(Portugues23 *no, const char *palavraPortugues, const char *palavraIngles, int unidade)
{
    // Verifica se a palavra portuguesa está na primeira posição do nó
    if (strcmp(palavraPortugues, no->info1.palavraPortugues) == 0)
    {
        // Adiciona a tradução na árvore binária de palavras em inglês
        no->info1.palavraIngles = insertpalavraIngles(no->info1.palavraIngles, palavraIngles, unidade);
        printf("Unidade %d adicionada para a palavra '%s' (PT).\n", unidade, palavraPortugues);
    }
    // Verifica se a palavra portuguesa está na segunda posição do nó (se existir)
    else if (no->nInfos == 2 && strcmp(palavraPortugues, no->info2.palavraPortugues) == 0)
    {
        // Adiciona a tradução na árvore binária de palavras em inglês
        no->info2.palavraIngles = insertpalavraIngles(no->info2.palavraIngles, palavraIngles, unidade);
        printf("Unidade %d adicionada para a palavra '%s' (PT).\n", unidade, palavraPortugues);
    }
}

int inserirPalavraPortugues(Portugues23 **arvore, char *palavraPortugues, char *palavraIngles, int unidade)
{
    Info promove;
    Portugues23 *pai = NULL;

    // Busca a palavra em português na árvore
    Portugues23 *noExistente = BuscarPalavra(arvore, palavraPortugues);

    if (noExistente != NULL)
    {
        // Se a palavra em português já existe, adiciona a tradução e a unidade
        adicionarTraducao(noExistente, palavraPortugues, palavraIngles, unidade);
        return 1; // Indica que foi atualizado
    }
    else
    {
        // Cria uma nova entrada para a palavra em português
        Info novoInfo = createInfo(palavraPortugues, palavraIngles, unidade);
        inserirArv23(arvore, &novoInfo, &promove, &pai);
        printf("Nova palavra '%s' adicionada com unidade %d.\n", palavraPortugues, unidade);
        return 0; // Indica que foi inserido como novo
    }
}

Info createInfo(char *palavraPortugues, char *palavraIngles, int unidade)
{
    Info novoInfo;
    novoInfo.palavraPortugues = strdup(palavraPortugues); // Armazena a palavra em português
    novoInfo.palavraIngles = NULL;
    novoInfo.palavraIngles = insertpalavraIngles(novoInfo.palavraIngles, palavraIngles, unidade);
    return novoInfo;
}

Portugues23 *criaNo(const Info *informacao, Portugues23 *filhoesq, Portugues23 *filhocen)
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

Portugues23 *adicionaChave(Portugues23 *no,  Info *informacao, Portugues23 *filho)
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

Portugues23 *quebraNo(Portugues23 **no, const Info *informacao, Info *promove, Portugues23 **filho)
{
    Portugues23 *maior;

    if (strcmp(informacao->palavraPortugues, (*no)->info2.palavraPortugues) > 0)
    {
        *promove = (*no)->info2;
        if (filho)
            maior = criaNo(informacao, (*no)->dir, *filho);
        else
            maior = criaNo(informacao, (*no)->dir, NULL);
    }
    else if (strcmp(informacao->palavraPortugues, (*no)->info1.palavraPortugues) > 0)
    {
        *promove = *informacao;
        if (filho)
            maior = criaNo(&(*no)->info2, *filho, (*no)->dir);
        else
            maior = criaNo(&(*no)->info2, NULL, (*no)->dir);
    }
    else
    {
        *promove = (*no)->info1;
        maior = criaNo(&(*no)->info2, (*no)->cent, (*no)->dir);
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
        *no = criaNo(informacao, NULL, NULL);
    }
    else
    {
        if (ehFolha(*no))
        { // Caso seja folha
            if ((*no)->nInfos == 1)
            {
                // O nó tem espaço para a nova chave
                *no = adicionaChave(*no, informacao, NULL);
            }
            else
            {
                // O nó precisa ser quebrado
                maiorNo = quebraNo(no, informacao, promove, NULL);
                if (*pai == NULL)
                { // Se não há pai, criar nova raiz
                    *no = criaNo(promove, *no, maiorNo);
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
                    *no = adicionaChave(*no, promove, maiorNo);
                    maiorNo = NULL;
                }
                else
                { // Quando não tem espaço
                    // O nó precisa ser quebrado
                    Portugues23 *novo;
                    novo = quebraNo(no, promove, &promove1, &maiorNo); // Quebra o nó e sobe a informação
                    if (*pai == NULL)
                    {
                        Portugues23 *novaRaiz;
                        novaRaiz = criaNo(&promove1, *no, novo); // Cria nova raiz se necessário
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

void exibir_tree23(const Portugues23 *raiz)
{
    if (raiz != NULL)
    {
        exibir_tree23(raiz->esq);
        printf("Palavra (PT): %s", raiz->info1.palavraPortugues);
        if (raiz->info1.palavraIngles != NULL && raiz->info1.palavraIngles->palavraIngles != NULL)
        {
            printBinaryTree(raiz->info1.palavraIngles);
            printf("\n");
        }
        exibir_tree23(raiz->cent);
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
            exibir_tree23(raiz->dir);
        }
    }
}

void imprimirPalavrasUnidade(Portugues23 *arvore, int unidade, int *unidadeImpressa)
{
    if (arvore)
    {
        // Percorre a subárvore esquerda
        imprimirPalavrasUnidade(arvore->esq, unidade, unidadeImpressa);

        // Imprime o cabeçalho da unidade uma vez
        if (!(*unidadeImpressa))
        {
            printf("%% Unidade %d\n", unidade); // Cabeçalho da unidade
            *unidadeImpressa = 1;               // Marca como já impresso
        }

        // Imprime as traduções associadas à unidade para a primeira palavra do nó
        if (arvore->info1.palavraIngles != NULL)
        {
            imprimirTraducoesNoFormato(arvore->info1.palavraIngles, unidade, arvore->info1.palavraPortugues);
        }

        // Percorre a subárvore central
        imprimirPalavrasUnidade(arvore->cent, unidade, unidadeImpressa);

        // Se houver o segundo elemento no nó, imprime também suas traduções
        if (arvore->nInfos == 2 && arvore->info2.palavraIngles != NULL)
        {
            imprimirTraducoesNoFormato(arvore->info2.palavraIngles, unidade, arvore->info2.palavraPortugues);
        }

        // Percorre a subárvore direita, se existir
        if (arvore->nInfos == 2)
        {
            imprimirPalavrasUnidade(arvore->dir, unidade, unidadeImpressa);
        }
    }
}

void imprimirTraducoesNoFormato(Inglesbin *node, int unidade, const char *palavraPortugues)
{
    if (node)
    {
        // Percorre a subárvore esquerda
        imprimirTraducoesNoFormato(node->esq, unidade, palavraPortugues);

        // Verifica se a unidade está associada à palavra em inglês
        if (buscar_unidade(node->unidades, unidade)) // Verifica se a unidade está presente na lista
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
        imprimirTraducoesNoFormato(node->dir, unidade, palavraPortugues);
    }
}

void exibirTodasTraducoes(Portugues23 *raiz, const char *palavraPortugues)
{
    if (raiz == NULL)
    {
        printf("A palavra '%s' não foi encontrada.\n", palavraPortugues);
        return;
    }

    // Verifica o nó info1
    if (strcmp(raiz->info1.palavraPortugues, palavraPortugues) == 0)
    {
        printf("Traduções para '%s':\n", palavraPortugues);
        exibirTraducoesIngles(raiz->info1.palavraIngles);
        return; // Evita loop desnecessário
    }

    // Verifica o nó info2 (se existir)
    if (raiz->nInfos == 2 && strcmp(raiz->info2.palavraPortugues, palavraPortugues) == 0)
    {
        printf("Traduções para '%s':\n", palavraPortugues);
        exibirTraducoesIngles(raiz->info2.palavraIngles);
        return; // Evita loop desnecessário
    }

    // Busca recursiva
    if (strcmp(palavraPortugues, raiz->info1.palavraPortugues) < 0)
    {
        exibirTodasTraducoes(raiz->esq, palavraPortugues);
    }
    else if (raiz->nInfos == 1 || strcmp(palavraPortugues, raiz->info2.palavraPortugues) < 0)
    {
        exibirTodasTraducoes(raiz->cent, palavraPortugues);
    }
    else
    {
        exibirTodasTraducoes(raiz->dir, palavraPortugues);
    }
}

void exibir_traducao_Portugues(Portugues23 **raiz, const char *palavraPortugues)
{
    Portugues23 *resultado = BuscarPalavra(raiz, palavraPortugues);
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

Portugues23 *arvore23_buscar_maior_filho(Portugues23 *raiz, Portugues23 **pai, Info *maior_valor)
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

Portugues23 *arvore23_buscar_menor_filho(Portugues23 *raiz, Portugues23 **pai)
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

static int calcular_altura(Portugues23 *no)
{
    int altura = -1;
    if (no != NULL)
        altura = 1 + calcular_altura(no->esq);
    return altura;
}

static int movimento_onda(Info saindo, Info *entrada, Portugues23 *pai, Portugues23 **origem, Portugues23 **raiz, Portugues23 **maior, int (*funcao_remover)(Portugues23 **, char *, Portugues23 *, Portugues23 **, Portugues23 **))
{
    int removeu = funcao_remover(raiz, saindo.palavraPortugues, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}

static Portugues23 *arvore23_buscar_pai(Portugues23 *raiz, char *info)
{
    Portugues23 *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.palavraPortugues) < 0)
                pai = arvore23_buscar_pai(raiz->esq, info);
            else if (raiz->nInfos == 1 || (strcmp(info, raiz->info2.palavraPortugues) < 0))
                pai = arvore23_buscar_pai(raiz->cent, info);
            else
                pai = arvore23_buscar_pai(raiz->dir, info);

            if (pai == NULL)
                pai = raiz;
        }
    }

    return pai;
}

static Portugues23 *arvore23_buscar_maior_pai(Portugues23 *raiz, char *info)
{
    Portugues23 *pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.palavraPortugues) < 0)
                pai = arvore23_buscar_maior_pai(raiz->esq, info);
            else if (raiz->nInfos == 1 || (strcmp(info, raiz->info2.palavraPortugues) < 0))
                pai = arvore23_buscar_maior_pai(raiz->cent, info);
            else
                pai = arvore23_buscar_maior_pai(raiz->dir, info);

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

static Portugues23 *arvore23_buscar_menor_pai_2_infos(Portugues23 *raiz, char *info)
{
    Portugues23 *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.palavraPortugues) < 0)
                pai = arvore23_buscar_menor_pai_2_infos(raiz->esq, info);
            else if (raiz->nInfos == 1 || (strcmp(info, raiz->info2.palavraPortugues) < 0))
                pai = arvore23_buscar_menor_pai_2_infos(raiz->cent, info);
            else
                pai = arvore23_buscar_menor_pai_2_infos(raiz->dir, info);

            if (pai == NULL && raiz->nInfos == 2 && strcmp(raiz->info2.palavraPortugues, info) < 0)
                pai = raiz;
        }
    }

    return pai;
}

static Portugues23 *arvore23_buscar_menor_pai(Portugues23 *raiz, char *info)
{
    Portugues23 *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if (strcmp(info, raiz->info1.palavraPortugues) < 0)
                pai = arvore23_buscar_menor_pai(raiz->esq, info);
            else if (raiz->nInfos == 1 || strcmp(info, raiz->info2.palavraPortugues) < 0)
                pai = arvore23_buscar_menor_pai(raiz->cent, info);
            else
                pai = arvore23_buscar_menor_pai(raiz->dir, info);

            if (pai == NULL && strcmp(raiz->info1.palavraPortugues, info) < 0)
                pai = raiz;
        }
    }

    return pai;
}

int arvore23_remover_nao_folha1(Portugues23 **origem, Portugues23 *raiz, Info *info, Portugues23 *filho1, Portugues23 *filho2, Portugues23 **maior)
{
    int removeu;
    Portugues23 *filho, *pai;
    Info info_filho;

    pai = raiz;

    filho = arvore23_buscar_maior_filho(filho1, &pai, &info_filho);

    if (filho->nInfos == 2)
    {
        *info = info_filho;
        filho->nInfos = 1;
        removeu = 1;
    }
    else
    {
        filho = arvore23_buscar_menor_filho(filho2, &pai);
        removeu = movimento_onda(filho->info1, info, pai, origem, &filho, maior, arvore23_remover1);
    }

    return removeu;
}

int arvore23_remover_nao_folha2(Portugues23 **origem, Portugues23 *raiz, Info *info, Portugues23 *filho1, Portugues23 *filho2, Portugues23 **maior)
{
    int removeu = 0;
    Portugues23 *filho, *pai;
    Info info_filho;

    pai = raiz;

    filho = arvore23_buscar_menor_filho(filho1, &pai);

    if (filho->nInfos == 2)
    {
        *info = filho->info1;
        filho->info1 = filho->info2;
        filho->nInfos = 1;
        removeu = 1;
    }
    else
    {
        filho = arvore23_buscar_maior_filho(filho2, &pai, &info_filho);
        removeu = movimento_onda(info_filho, info, pai, origem, &filho, maior, arvore23_remover2);
    }

    return removeu;
}

int arvore23_remover1(Portugues23 **raiz, char *info, Portugues23 *pai, Portugues23 **origem, Portugues23 **maior)
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
                        freeTree(raiz);
                    else
                    {
                        Portugues23 *pai_aux;
                        Info info_pai;
                        if (*raiz == pai->esq || (pai->nInfos == 2 && *raiz == pai->cent))
                        {
                            pai_aux = arvore23_buscar_pai(*origem, pai->info1.palavraPortugues);

                            if (*raiz == pai->esq)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = movimento_onda(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, arvore23_remover1);
                        }
                        else
                        {
                            pai_aux = arvore23_buscar_maior_pai(*origem, (*raiz)->info1.palavraPortugues);

                            Portugues23 *menor_pai;
                            menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.palavraPortugues);

                            if (pai_aux != NULL)
                            {
                                if (strcmp(pai_aux->info1.palavraPortugues, (*raiz)->info1.palavraPortugues) > 0)
                                    info_pai = pai_aux->info1;
                                else
                                    info_pai = pai_aux->info2;
                            }

                            int altura_menor_pai = calcular_altura(menor_pai);
                            int altura_pai_aux = calcular_altura(pai_aux);

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
                                avo = arvore23_buscar_pai(*origem, info_pai.palavraPortugues);
                                removeu = movimento_onda(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, arvore23_remover1);
                            }
                        }
                    }
                }
            }
            else if (info2)
                removeu = arvore23_remover_nao_folha1(origem, *raiz, &((*raiz)->info2), (*raiz)->cent, (*raiz)->dir, maior);
            else if (info1)
                removeu = arvore23_remover_nao_folha1(origem, *raiz, &((*raiz)->info1), (*raiz)->esq, (*raiz)->cent, maior);
        }
        else
        {
            if (strcmp(info, (*raiz)->info1.palavraPortugues) < 0)
                removeu = arvore23_remover1(&(*raiz)->esq, info, *raiz, origem, maior);
            else if ((*raiz)->nInfos == 1 || (strcmp(info, (*raiz)->info2.palavraPortugues) < 0))
                removeu = arvore23_remover1(&(*raiz)->cent, info, *raiz, origem, maior);
            else
                removeu = arvore23_remover1(&(*raiz)->dir, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int arvore23_remover2(Portugues23 **raiz, char *info, Portugues23 *pai, Portugues23 **origem, Portugues23 **maior)
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
                        freeTree(raiz);
                    else
                    {
                        Portugues23 *pai_aux;
                        Info info_pai;
                        if (*raiz == pai->cent || (pai->nInfos == 2 && *raiz == pai->dir))
                        {
                            pai_aux = arvore23_buscar_pai(*origem, pai->info1.palavraPortugues);

                            if (*raiz == pai->cent)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = movimento_onda(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, arvore23_remover2);
                        }
                        else
                        {
                            pai_aux = arvore23_buscar_menor_pai(*origem, (*raiz)->info1.palavraPortugues);

                            Portugues23 *menor_pai;
                            menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.palavraPortugues);

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

                                avo = arvore23_buscar_pai(*origem, info_pai.palavraPortugues);
                                removeu = movimento_onda(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, arvore23_remover2);
                            }
                        }
                    }
                }
            }
            else if (info2)
                removeu = arvore23_remover_nao_folha2(origem, *raiz, &((*raiz)->info2), (*raiz)->dir, (*raiz)->cent, maior);
            else if (info1)
                removeu = arvore23_remover_nao_folha2(origem, *raiz, &((*raiz)->info1), (*raiz)->cent, (*raiz)->esq, maior);
        }
        else
        {
            if (strcmp(info, (*raiz)->info1.palavraPortugues) < 0)
                removeu = arvore23_remover2(&(*raiz)->esq, info, *raiz, origem, maior);
            else if ((*raiz)->nInfos == 1 || (strcmp(info, (*raiz)->info2.palavraPortugues) < 0))
                removeu = arvore23_remover2(&(*raiz)->cent, info, *raiz, origem, maior);
            else
                removeu = arvore23_remover2(&(*raiz)->dir, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int possivel_remover(Portugues23 *raiz)
{
    int possivel = 0;

    if (raiz != NULL)
    {
        possivel = raiz->nInfos == 2;

        if (!possivel)
        {
            possivel = possivel_remover(raiz->cent);

            if (!possivel)
                possivel = possivel_remover(raiz->esq);
        }
    }

    return possivel;
}

Portugues23 *no23_juntar(Portugues23 *filho1, Info *info, Portugues23 *maior, Portugues23 **raiz)
{
    adicionaChave(filho1, info, maior);

    (*raiz)->nInfos--;

    if ((*raiz)->nInfos == 0)
        freeTree(raiz);

    return filho1;
}

static void balanceamento(Portugues23 **raiz, Portugues23 *filho1, Portugues23 **filho2, Info info, Portugues23 **maior)
{
    if (*filho2 == NULL || (*filho2)->nInfos == 0)
    {
        if (*filho2 != NULL)
            freeTree(filho2);
        *maior = no23_juntar(filho1, &info, *maior, raiz);
    }
}

int arvore23_rebalancear(Portugues23 **raiz, char *info, Portugues23 **maior)
{
    int balanceou = 0;
    if (*raiz != NULL)
    {
        if (!ehFolha(*raiz))
        {
            if (strcmp(info, (*raiz)->info1.palavraPortugues) < 0)
                balanceou = arvore23_rebalancear(&((*raiz)->esq), info, maior);
            else if ((*raiz)->nInfos == 1 || (strcmp(info, (*raiz)->info2.palavraPortugues) < 0))
            {
                if ((*raiz)->esq->nInfos == 2 && !possivel_remover((*raiz)->cent))
                    balanceou = -1;
                else
                    balanceou = arvore23_rebalancear(&((*raiz)->cent), info, maior);
            }
            else
            {
                if ((*raiz)->cent->nInfos == 2 && !possivel_remover((*raiz)->dir))
                    balanceou = -1;
                else
                    balanceou = arvore23_rebalancear(&((*raiz)->dir), info, maior);
            }

            if (balanceou != -1)
            {
                if ((*raiz)->nInfos == 1)
                    balanceamento(raiz, (*raiz)->esq, &((*raiz)->cent), (*raiz)->info1, maior);
                else if ((*raiz)->nInfos == 2)
                    balanceamento(raiz, (*raiz)->cent, &((*raiz)->dir), (*raiz)->info2, maior);
                balanceou = 1;
            }
        }
    }

    return balanceou;
}

int arvore_2_3_remover(Portugues23 **raiz, char *info)
{
    Portugues23 *maior, *posicao_juncao;
    int removeu = arvore23_remover1(raiz, info, NULL, raiz, &posicao_juncao);

    if (removeu == -1)
    {
        Info valor_juncao = no23_maior_info(posicao_juncao);
        maior = NULL;
        removeu = arvore23_rebalancear(raiz, valor_juncao.palavraPortugues, &maior);

        if (removeu == -1)
        {
            Portugues23 *pai, *posicao_juncao2;
            Info *entrada;
            pai = arvore23_buscar_pai(*raiz, valor_juncao.palavraPortugues);

            if (eh_info1(*posicao_juncao, valor_juncao.palavraPortugues))
                entrada = &(posicao_juncao->cent->info1);
            else
                entrada = &(posicao_juncao->dir->info1);

            removeu = movimento_onda(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2, arvore23_remover2);

            if (removeu == -1)
            {
                valor_juncao = posicao_juncao2->info1;
                pai = arvore23_buscar_pai(*raiz, valor_juncao.palavraPortugues);
                removeu = movimento_onda(valor_juncao, &(posicao_juncao2->esq->info1), pai, raiz, &posicao_juncao2, &posicao_juncao, arvore23_remover1);

                valor_juncao = no23_maior_info(posicao_juncao);
                maior = NULL;
                removeu = arvore23_rebalancear(raiz, valor_juncao.palavraPortugues, &maior);
            }
        }

        if (*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}

/*#########################################FREE#######################################################*/

void freeInfo2_3(Info *info)
{
    if (info != NULL)
    {
        free_arvore_binaria(info->palavraIngles);
        free(info->palavraPortugues);
    }
}

void freeTree(Portugues23 **no)
{
    if (*no != NULL)
    {
        freeTree(&((*no)->esq));
        freeTree(&((*no)->cent));
        if ((*no)->nInfos == 2)
        {
            freeInfo2_3(&((*no)->info2));
            freeTree(&((*no)->dir));
        }
        freeInfo2_3(&((*no)->info1));
        free(*no);
        *no = NULL;
    }
}


void removerTraducaoIngles(Portugues23 **raiz, char *palavraIngles, int unidade, Portugues23 **pai) {
    if (*raiz == NULL) {
        printf("A árvore está vazia.\n");
        return;
    }

    // Percorre a subárvore esquerda
    removerTraducaoIngles(&(*raiz)->esq, palavraIngles, unidade, pai);

    // Verifica no primeiro elemento do nó
    if ((*raiz)->info1.palavraIngles != NULL) {
        if (removerPalavraIngles(&(*raiz)->info1.palavraIngles, palavraIngles, unidade)) {
            printf("Palavra '%s' removida da unidade %d (info1).\n", palavraIngles, unidade);
        }
    }

    // Percorre a subárvore central
    removerTraducaoIngles(&(*raiz)->cent, palavraIngles, unidade, pai);

    // Verifica no segundo elemento do nó, se existir
    if ((*raiz)->nInfos == 2 && (*raiz)->info2.palavraIngles != NULL) {
        if (removerPalavraIngles(&(*raiz)->info2.palavraIngles, palavraIngles, unidade)) {
            printf("Palavra '%s' removida da unidade %d (info2).\n", palavraIngles, unidade);
        }
    }

    // Percorre a subárvore direita, se existir
    if ((*raiz)->nInfos == 2) {
        removerTraducaoIngles(&(*raiz)->dir, palavraIngles, unidade, pai);
    }
}
void imprimirPalavrasFormatadasPorUnidade(Portugues23 *arvore, int unidade, int *unidadeImpressa) {
    if (arvore) {
        // Percorre a subárvore esquerda
        imprimirPalavrasFormatadasPorUnidade(arvore->esq, unidade, unidadeImpressa);

        // Verifica as palavras associadas ao `info1` do nó
        if (arvore->info1.palavraIngles != NULL) {
            Inglesbin *ingles = arvore->info1.palavraIngles;
            while (ingles) {
                if (buscar_unidade(ingles->unidades, unidade)) {
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
        imprimirPalavrasFormatadasPorUnidade(arvore->cent, unidade, unidadeImpressa);

        // Verifica as palavras associadas ao `info2` do nó, se existir
        if (arvore->nInfos == 2 && arvore->info2.palavraIngles != NULL) {
            Inglesbin *ingles = arvore->info2.palavraIngles;
            while (ingles) {
                if (buscar_unidade(ingles->unidades, unidade)) {
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
            imprimirPalavrasFormatadasPorUnidade(arvore->dir, unidade, unidadeImpressa);
        }
    }
}



void removerPalavraPortuguesUnidade(Portugues23 **raiz, const char *palavraPortugues, int unidade) {
    // Buscar a palavra em português na árvore 2-3
    Portugues23 *noPortugues = BuscarPalavra(raiz, palavraPortugues);

    if (noPortugues == NULL) {
        printf("Palavra em português '%s' não encontrada na árvore 2-3.\n", palavraPortugues);
        return;
    }

    int encontrado = 0;

    // Verificar info1
    if (strcmp(noPortugues->info1.palavraPortugues, palavraPortugues) == 0) {
        Inglesbin *ingles = noPortugues->info1.palavraIngles;
        while (ingles) {
            // Verificar se a palavra em inglês está associada à unidade
            if (buscar_unidade(ingles->unidades, unidade)) {
                encontrado = 1;

                // Remover a palavra em inglês da árvore binária
                if (removerPalavraIngles(&(noPortugues->info1.palavraIngles), ingles->palavraIngles, unidade)) {
                    printf("Palavra '%s' removida da unidade %d na árvore binária.\n", ingles->palavraIngles, unidade);
                }

                // Verificar se a árvore binária está vazia e remover info1 da árvore 2-3
                if (noPortugues->info1.palavraIngles == NULL) {
                    printf("Palavra '%s' removida completamente da árvore 2-3 (info1).\n", palavraPortugues);
                    freeInfo2_3(&(noPortugues->info1));
                    noPortugues->info1.palavraPortugues = NULL; // Marca como vazio
                }
                break; // Já encontrou e removeu
            }
            ingles = ingles->esq ? ingles->esq : ingles->dir;
        }
    }

    // Verificar info2
    if (!encontrado && noPortugues->nInfos == 2 && strcmp(noPortugues->info2.palavraPortugues, palavraPortugues) == 0) {
        Inglesbin *ingles = noPortugues->info2.palavraIngles;
        while (ingles) {
            // Verificar se a palavra em inglês está associada à unidade
            if (buscar_unidade(ingles->unidades, unidade)) {
                encontrado = 1;

                // Remover a palavra em inglês da árvore binária
                if (removerPalavraIngles(&(noPortugues->info2.palavraIngles), ingles->palavraIngles, unidade)) {
                    printf("Palavra '%s' removida da unidade %d na árvore binária.\n", ingles->palavraIngles, unidade);
                }

                // Verificar se a árvore binária está vazia e remover info2 da árvore 2-3
                if (noPortugues->info2.palavraIngles == NULL) {
                    printf("Palavra '%s' removida completamente da árvore 2-3 (info2).\n", palavraPortugues);
                    freeInfo2_3(&(noPortugues->info2));
                    noPortugues->info2.palavraPortugues = NULL; // Marca como vazio
                }
                break; // Já encontrou e removeu
            }
            ingles = ingles->esq ? ingles->esq : ingles->dir;
        }
    }

    if (!encontrado) {
        printf("Unidade %d não encontrada para a palavra '%s'.\n", unidade, palavraPortugues);
    }
}

int _remove_palavra_portugues_unidade(Inglesbin **raiz, const char *palavraPortugues, int unidade) {
    int confirm = 0;

    if (*raiz) {
        // Remoção recursiva nos filhos
        confirm = _remove_palavra_portugues_unidade(&(*raiz)->esq, palavraPortugues, unidade);
        confirm = _remove_palavra_portugues_unidade(&(*raiz)->dir, palavraPortugues, unidade) || confirm;

        // Atualiza a lista de unidades associadas
        Unidade *novaLista = remover_unidade((*raiz)->unidades, unidade);
        if (novaLista != (*raiz)->unidades) {
            confirm = 1; // Indica que a unidade foi removida
        }
        (*raiz)->unidades = novaLista;

        // Se a lista de unidades ficar vazia, remove o nó da árvore binária
        if (!(*raiz)->unidades) {
            confirm = removerPalavraIngles(raiz, (*raiz)->palavraIngles, unidade);
        }
    }

    return confirm;
}


int remove_palavra_portugues_unidade(Portugues23 *raiz, char *palavraPortugues, int unidade, Portugues23 **top) {
    int confirm = 0;

    if (raiz) {
        if (strcmp(raiz->info1.palavraPortugues, palavraPortugues) == 0) {
            confirm = _remove_palavra_portugues_unidade(&raiz->info1.palavraIngles, palavraPortugues, unidade);

            if (!raiz->info1.palavraIngles) {
                confirm = arvore_2_3_remover(top, palavraPortugues);
            }
        } else if (raiz->nInfos == 2 && strcmp(raiz->info2.palavraPortugues, palavraPortugues) == 0) {
            confirm = _remove_palavra_portugues_unidade(&raiz->info2.palavraIngles, palavraPortugues, unidade);

            if (!raiz->info2.palavraIngles) {
                confirm = arvore_2_3_remover(top, palavraPortugues);
            }
        } else if (strcmp(palavraPortugues, raiz->info1.palavraPortugues) < 0) {
            confirm = remove_palavra_portugues_unidade(raiz->esq, palavraPortugues, unidade, top);
        } else if (raiz->nInfos == 1 || strcmp(palavraPortugues, raiz->info2.palavraPortugues) < 0) {
            confirm = remove_palavra_portugues_unidade(raiz->cent, palavraPortugues, unidade, top);
        } else {
            confirm = remove_palavra_portugues_unidade(raiz->dir, palavraPortugues, unidade, top);
        }
    }

    return confirm;
}

int Remove_palavra_portugues_unidade(Portugues23 **raiz, char *palavraPortugues, int unidade) {
    int confirm = 0;
    confirm = remove_palavra_portugues_unidade(*raiz, palavraPortugues, unidade, raiz);
    return confirm;
}