#include "arv_portugues-23.h"
#include "arv_ingles-binaria.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Função para verificar se o nó é uma folha (não possui filhos)
int ehFolha(Tree23Node *no) {
    return (no->left == NULL && no->middle == NULL && no->right == NULL) ? 1 : 0;
}

// Função para verificar se o nó é a raiz (não possui pai)
// Esta função está simplificada, pois na estrutura atual não há um ponteiro para o pai.
// Função que verifica se o nó é a raiz, comparando com o ponteiro da raiz
// Função para verificar se o nó é a raiz
int ehRaiz(Tree23Node *no) {
    return no->pai == NULL ? 1 : 0;
}

// Função para verificar se o nó está cheio (contém duas informações)
int estaCheio(Tree23Node *no) {
    return no->nInfos == 2 ? 1 : 0;
}

// Função para verificar se o valor está no nó (compara com as palavras em português no info1 e info2)
int estaNodo(Tree23Node *nodo, const char *valor) {
    int resp = 0;
    if (nodo) {
        if (strcmp(valor, nodo->info1.portugueseWord) == 0 ||
            (nodo->nInfos == 2 && strcmp(valor, nodo->info2.portugueseWord) == 0)) {
            resp = 1;
        }
    }
    return resp;
}

// Função para trocar dois ponteiros de nós (equivalente a trocar valores inteiros)
void trocar(Tree23Node **a, Tree23Node **b) {
    Tree23Node *temp = *a;
    *a = *b;
    *b = temp;
}

// Função para imprimir o endereço do nó
void endereco(Tree23Node *nodo) {
    if (nodo)
        printf("0x%p\n", (void*)nodo);
}

Info criarInfo(const char *palavraPortugues, int unidade) {
    Info novoInfo;
    strncpy(novoInfo.portugueseWord, palavraPortugues, 50);
    novoInfo.portugueseWord[49] = '\0';
    novoInfo.englishTreeRoot = NULL; // Inicializa a árvore de traduções em inglês
    novoInfo.unit = unidade;         // Define a unidade
    return novoInfo;
}
// Função para criar um novo nó na árvore 2-3 com as informações fornecidas
Tree23Node* criarNodo23(Info info1, Info info2, int qtdDados, Tree23Node *pai, Tree23Node *esq, Tree23Node *meio, Tree23Node *dir) {
    Tree23Node *novoNodo = (Tree23Node*) malloc(sizeof(Tree23Node));
    if (novoNodo) {
        novoNodo->info1 = info1;
        novoNodo->info2 = info2;
        novoNodo->nInfos = qtdDados;
        novoNodo->pai = pai;       // Define o ponteiro para o pai do nó
        novoNodo->left = esq;
        novoNodo->middle = meio;
        novoNodo->right = dir;
    }
    return novoNodo;
}

// Função para inserir um valor no nó Tree23Node
void inserirValorNodo(Tree23Node *nodo, Info novoInfo, Tree23Node *filho) {
    if (nodo) {
        // Comparar a palavra em português em `novoInfo` com `info1` para decidir a ordem
        if (strcmp(novoInfo.portugueseWord, nodo->info1.portugueseWord) < 0) {
            // Se `novoInfo` é menor que `info1`, desloca `info1` para `info2` e insere `novoInfo` em `info1`
            nodo->info2 = nodo->info1;
            nodo->info1 = novoInfo;
            nodo->right = nodo->middle;
            nodo->middle = filho;
        } else {
            // Caso contrário, insere `novoInfo` em `info2`
            nodo->info2 = novoInfo;
            nodo->right = filho;
        }
        // Atualiza o número de informações no nó para 2
        nodo->nInfos = 2;
    }
}

Tree23Node** getNodoComparacao(Tree23Node *aux, Tree23Node *nodo, Tree23Node** irmao) {
        Tree23Node **get = NULL;
        if(nodo && aux) {
                if(aux == nodo->left)
                        get = &(nodo->left);
                if(aux == nodo->middle) {
                        get = &(nodo->middle);
                        *irmao = nodo->left;
                }
                if(aux == nodo->right)
                        get = &(nodo->right);
        }
        return get;
}


// Função para dividir a raiz inserindo um novo valor
void dividirRaizInserindo(Tree23Node **nodo, Info novoInfo, Tree23Node *filho) {
    Tree23Node *filhoEsq = NULL;
    Tree23Node *filhoDir = NULL;

    if (*nodo) {
        // Criando novos nós filho esquerdo e direito após a divisão
        if (strcmp(novoInfo.portugueseWord, (*nodo)->info1.portugueseWord) < 0) {
            // Caso o novo valor seja menor que info1
            filhoEsq = criarNodo23(novoInfo, (Info){0}, 1, *nodo, (*nodo)->left, filho, NULL);
            filhoDir = criarNodo23((*nodo)->info2, (Info){0}, 1, *nodo, (*nodo)->middle, (*nodo)->right, NULL);
            (*nodo)->info1 = (*nodo)->info1;  // Atualiza info1 para manter o valor central
        } else if (strcmp(novoInfo.portugueseWord, (*nodo)->info2.portugueseWord) < 0) {
            // Caso o novo valor esteja entre info1 e info2
            filhoEsq = criarNodo23((*nodo)->info1, (Info){0}, 1, *nodo, (*nodo)->left, (*nodo)->middle, NULL);
            filhoDir = criarNodo23((*nodo)->info2, (Info){0}, 1, *nodo, filho, (*nodo)->right, NULL);
            (*nodo)->info1 = novoInfo;  // Atualiza info1 para manter o valor central
        } else {
            // Caso o novo valor seja maior que info2
            filhoEsq = criarNodo23((*nodo)->info1, (Info){0}, 1, *nodo, (*nodo)->left, (*nodo)->middle, NULL);
            filhoDir = criarNodo23(novoInfo, (Info){0}, 1, *nodo, (*nodo)->right, filho, NULL);
            (*nodo)->info1 = (*nodo)->info2;  // Atualiza info1 para manter o valor central
        }

        // Atualiza o nó raiz após a divisão
        (*nodo)->left = filhoEsq;
        (*nodo)->middle = filhoDir;
        (*nodo)->right = NULL;
        (*nodo)->nInfos = 1;  // A raiz agora possui apenas um valor após a divisão

        // Ajusta os ponteiros dos filhos, se não for folha
        if (!ehFolha(filhoEsq)) {
            filhoEsq->left->pai = filhoEsq;
            filhoEsq->middle->pai = filhoEsq;
            filhoDir->left->pai = filhoDir;
            filhoDir->middle->pai = filhoDir;
        }
    }
}


// Função para dividir um nó ao inserir um novo valor
void dividirInserindo(Tree23Node **no, Info novoInfo, Tree23Node *filho) {
    Tree23Node *filhoDir = NULL;
    Info sobe;

    if (*no) {
        if ((*no)->pai == NULL) {
            // Caso especial: dividir a raiz
            dividirRaizInserindo(no, novoInfo, filho);
        } else {
            // Dividindo um nó interno
            if (strcmp(novoInfo.portugueseWord, (*no)->info1.portugueseWord) < 0) {
                // `novoInfo` é menor que `info1`, movemos `info1` para `sobe` e `info2` para `filhoDir`
                filhoDir = criarNodo23((*no)->info2, (Info){0}, 1, (*no)->pai, (*no)->middle, (*no)->right, NULL);
                sobe = (*no)->info1;
                (*no)->info1 = novoInfo;
                (*no)->middle = filho;
            } else if ((*no)->nInfos == 2 && strcmp(novoInfo.portugueseWord, (*no)->info2.portugueseWord) < 0) {
                // `novoInfo` está entre `info1` e `info2`, movemos `novoInfo` para `sobe`
                filhoDir = criarNodo23((*no)->info2, (Info){0}, 1, (*no)->pai, filho, (*no)->right, NULL);
                sobe = novoInfo;
            } else {
                // `novoInfo` é maior que `info2`, movemos `info2` para `sobe`
                filhoDir = criarNodo23(novoInfo, (Info){0}, 1, (*no)->pai, (*no)->right, filho, NULL);
                sobe = (*no)->info2;
            }

            // Ajusta o nó atual para que ele tenha apenas um valor (`info1`) após a divisão
            (*no)->right = NULL;
            (*no)->nInfos = 1;

            // Divisão recursiva no pai, se necessário
            if ((*no)->pai->nInfos == 2) {
                dividirInserindo(&((*no)->pai), sobe, filhoDir);
            } else {
                // Se o pai não está cheio, insere o valor `sobe` diretamente no pai
                inserirValorNodo((*no)->pai, sobe, filhoDir);
            }

            // Ajusta os ponteiros dos filhos, se o nó não for uma folha
            if (!ehFolha(filhoDir)) {
                filhoDir->left->pai = filhoDir;
                filhoDir->middle->pai = filhoDir;
            }
        }
    }
}

// Função para inserir um valor na árvore 2-3
void inserirValorArvore(Tree23Node **arvore, Info novoInfo) {
    Tree23Node *aux = NULL;

    if (*arvore == NULL) {
        // Árvore vazia: cria um novo nó e insere o valor.
        *arvore = criarNodo23(novoInfo, (Info){0}, 1, NULL, NULL, NULL, NULL);
    } else {
        // Encontra o nó folha onde será feita a inserção.
        aux = *arvore;
        while (aux->left != NULL) {
            if (aux->nInfos == 2 && strcmp(novoInfo.portugueseWord, aux->info2.portugueseWord) > 0) {
                aux = aux->right;
            } else {
                if (strcmp(novoInfo.portugueseWord, aux->info1.portugueseWord) < 0) {
                    aux = aux->left;
                } else {
                    aux = aux->middle;
                }
            }
        }

        // Se o nó estiver cheio, inicia uma cascata de divisões e inserções
        if (aux->nInfos == 2) {
            dividirInserindo(&aux, novoInfo, NULL);
        } else {
            // Caso contrário, insere o valor diretamente no nó
            inserirValorNodo(aux, novoInfo, NULL);
        }
    }
}

// Função para buscar um valor na árvore 2-3
Tree23Node** buscarValorArvore(Tree23Node **arvore, const char *valor, Tree23Node **irmao) {
    Tree23Node **nodo = NULL;

    if (*arvore) {
        nodo = arvore;
        
        // Loop para procurar o valor até encontrar o nó ou um nó folha
        while (*nodo && !estaNodo(*nodo, valor)) {
            *irmao = (*nodo)->middle;  // Supondo que `irmao` inicialmente seja o meio

            if ((*nodo)->nInfos == 2 && strcmp(valor, (*nodo)->info2.portugueseWord) > 0) {
                // Se `valor` é maior que `info2`, vá para o nó direito
                nodo = &((*nodo)->right);
            } else if (strcmp(valor, (*nodo)->info1.portugueseWord) < 0) {
                // Se `valor` é menor que `info1`, vá para o nó esquerdo
                nodo = &((*nodo)->left);
            } else {
                // Caso contrário, vá para o nó do meio e ajuste `irmao`
                *irmao = (*nodo)->left;
                nodo = &((*nodo)->middle);
            }
        }
    }
    return nodo;
}
void removerValorNodo(Tree23Node **nodo, const char *valor) {
    if (*nodo) {
        if ((*nodo)->nInfos == 1) {
            // Se o nó tem apenas um valor, remove e libera o nó
            free(*nodo);
            *nodo = NULL;
        } else {
            // Se o nó tem dois valores, remove o valor correto e ajusta `info1` e `info2`
            if (strcmp(valor, (*nodo)->info1.portugueseWord) == 0) {
                (*nodo)->info1 = (*nodo)->info2;  // Move `info2` para `info1`
            }
            (*nodo)->nInfos = 1;  // Reduz o número de informações no nó para 1
        }
    }
}

// Função para trocar valores na árvore
Tree23Node** trocarValoresArvore(Tree23Node **nodo, const char *valor, Tree23Node **irmao) {
    Tree23Node **aux = NULL;
    Info *a, *b;

    if (*nodo) {
        aux = &((*nodo)->left);  // Inicia `aux` com o nó esquerdo
        a = &((*nodo)->info1);   // Aponta `a` para `info1`

        if ((*nodo)->nInfos == 2 && strcmp(valor, (*nodo)->info2.portugueseWord) == 0) {
            // Se o valor está em `info2`
            aux = &((*nodo)->middle);  // Vai para o nó do meio
            a = &((*nodo)->info2);     // Aponta `a` para `info2`
        }

        // Desce até encontrar um nó folha
        while (!ehFolha(*aux)) {
            if ((*aux)->nInfos == 2)
                aux = &((*aux)->right);  // Vai para o nó direito se tiver 2 valores
            else
                aux = &((*aux)->middle); // Vai para o nó do meio caso contrário
        }

        // Configura `b` para o valor a ser trocado
        b = &((*aux)->info1);
        if ((*aux)->nInfos == 2)
            b = &((*aux)->info2);

        // Troca os valores em `a` e `b`
        Info temp = *a;
        *a = *b;
        *b = temp;

        // Define `irmao` corretamente
        *irmao = (*aux)->pai->middle;
        if (*aux == (*aux)->pai->middle)
            *irmao = (*aux)->pai->left;
    }
    return aux;
}

void rotacionarEsq(Tree23Node *remover, Tree23Node *irmao) {
    Tree23Node *pai = NULL;

    if (remover && !ehRaiz(remover)) {
        pai = remover->pai;

        // Atualiza `info2` no nó `remover` com o valor `info1` do pai
        remover->info2 = pai->info1;
        remover->right = irmao->left;

        if (irmao->left) {
            irmao->left->pai = remover;
        }

        remover->nInfos = 2;  // Agora o nó `remover` tem dois valores

        // Ajusta `info1` do pai para o `info1` do irmão
        pai->info1 = irmao->info1;

        // Atualiza `irmao` deslocando `info2` para `info1`
        irmao->info1 = irmao->info2;
        irmao->left = irmao->middle;
        irmao->middle = irmao->right;
        irmao->nInfos = 1;  // O irmão agora tem apenas um valor
    }
}

// Função para rotação à direita
void rotacionarDir(Tree23Node *remover, Tree23Node *irmao) {
    Tree23Node *pai = NULL;

    if (remover && !ehRaiz(remover)) {
        pai = remover->pai;

        // Ajusta `info2` e move `info1` para `info2`
        remover->info2 = remover->info1;

        if (estaCheio(pai) && remover == pai->right) {
            remover->info1 = pai->info2;
            pai->info2 = irmao->info2;
        } else {
            remover->info1 = pai->info1;
            pai->info1 = irmao->info2;
            printf("%s\n", irmao->info2.portugueseWord);
        }

        // Ajusta ponteiros de filhos
        remover->right = remover->middle;
        remover->middle = remover->left;
        remover->left = irmao->right;

        if (irmao->right) {
            irmao->right->pai = remover;
        }

        remover->nInfos = 2;  // Agora `remover` possui dois valores
        irmao->nInfos = 1;    // `irmao` agora possui apenas um valor
    }
}
Tree23Node** unirPai(Tree23Node **remover, Tree23Node *irmao) {
    Tree23Node *pai = NULL;
    Tree23Node **novo = NULL;

    if (*remover && !ehRaiz(*remover)) {
        pai = (*remover)->pai;
        novo = remover;

        if (*remover == pai->left) {
            // Se `remover` é o filho esquerdo
            pai->info2 = irmao->info1;
            pai->right = irmao->middle;
            pai->middle = irmao->left;
        } else {
            // Se `remover` não é o filho esquerdo
            pai->info2 = pai->info1;
            pai->info1 = irmao->info1;
            pai->right = pai->middle;
            pai->middle = irmao->middle;
            pai->left = irmao->left;
            novo = &(pai->right);
        }

        if (irmao->left) {
            irmao->left->pai = pai;
            irmao->middle->pai = pai;
        }

        pai->nInfos = 2;  // Atualiza o pai para ter dois valores
        free(irmao);  // Libera o nó `irmao` pois ele foi fundido
    }
    return novo;
}

// Função para unir `remover` com `irmao`, ajustando o nó pai
Tree23Node** unirFilho(Tree23Node **remover, Tree23Node *irmao) {
    Tree23Node *pai = NULL;
    Tree23Node **novo = NULL;

    if (*remover && !ehRaiz(*remover)) {
        pai = (*remover)->pai;

        if (*remover == pai->left) {
            // `remover` é o filho esquerdo do pai
            irmao->info2 = irmao->info1;
            irmao->info1 = pai->info1;
            irmao->right = irmao->middle;
            irmao->middle = irmao->left;
            irmao->left = pai->left;
            if (irmao->left) irmao->left->pai = irmao;

            pai->info1 = pai->info2;
            pai->left = pai->middle;
            pai->middle = pai->right;
            novo = &(irmao->left);

        } else if (*remover == pai->middle) {
            // `remover` é o filho do meio
            irmao->info2 = pai->info1;
            irmao->right = pai->middle;
            if (irmao->right) irmao->right->pai = irmao;

            pai->info1 = pai->info2;
            pai->middle = pai->right;
            novo = &(irmao->right);

        } else {
            // `remover` é o filho direito
            irmao->info2 = pai->info2;
            irmao->right = pai->right;
            if (irmao->right) irmao->right->pai = irmao;

            novo = &(irmao->right);
        }

        pai->nInfos = 1;  // Atualiza o pai para ter apenas um valor
        irmao->nInfos = 2;  // Atualiza `irmao` para ter dois valores
    }
    return novo;
}


// Função para reconfigurar a árvore após a remoção de um valor
// Esta funcao so e chamada se o nodo em que esta ocorrendo a remocao for folha (sem ser raiz) e nao estiver cheio
Tree23Node** reconfigArvore(Tree23Node **remover, Tree23Node *irmao) {
        Tree23Node **pai = NULL;
        Tree23Node **novo = NULL;
        Tree23Node *tio = NULL;
        Tree23Node *aux = NULL;
        if(*remover) {
                pai = &((*remover)->pai);
                if(!ehRaiz(*pai) && !estaCheio(*pai) && !estaCheio(irmao)) {
                        tio = (*pai)->pai->middle;
                        if(*pai == (*pai)->pai->middle)
                                tio = (*pai)->pai->left;
//                        printf("Nodo a remover %d: ", (*remover)->info1); endereco(*remover);
                        aux = *remover;
                        pai = reconfigArvore(pai, tio);
                        remover = getNodoComparacao(aux, *pai, &irmao);
//                        printf("Nodo a remover %d: ", (*remover)->info1); endereco(*remover);
                }
                novo = remover;
                if(estaCheio(irmao)) {
                        if(*remover == (*pai)->left)
                                rotacionarEsq(*remover, irmao);
                        else {
//                                printf("Nodo a remover %d: ", (*remover)->meio->info1); endereco((*remover)->meio);
//                                printf("Nodo irmao %d: ", irmao->info1); endereco(irmao);
                                rotacionarDir(*remover, irmao);
//                                printf("Nodo a remover %d: ", (*remover)->meio->info1); endereco((*remover)->meio);
//                                printf("Nodo irmao %d: ", irmao->info1); endereco(irmao);
                        }
                } else if(estaCheio(*pai))
//                        printf("Unir os nodo de remocao com seu irmao (%d e %d)\n", (*remover)->info1, irmao->info1);
                        novo = unirFilho(remover, irmao);
                else
                        novo = unirPai(remover, irmao);
        }
        return novo;
}

// Função para remover um valor da árvore 2-3
void removerValorArvore(Tree23Node **arvore, const char *valor) {
    Tree23Node **remover = NULL;
    Tree23Node *irmao = NULL;

    if (*arvore) {
        remover = buscarValorArvore(arvore, valor, &irmao);

        while (remover) {
            if (ehFolha(*remover)) {
                // Se é uma folha, remove diretamente
                if (ehRaiz(*remover) || estaCheio(*remover)) {
                    removerValorNodo(remover, valor);
                } else {
                    // Reconfigura a árvore antes de remover o valor
                    remover = reconfigArvore(remover, irmao);
                    removerValorNodo(remover, valor);
                }
                remover = NULL;
            } else {
                // Se não é folha, troca os valores para transformar o nó em folha
                remover = trocarValoresArvore(remover, valor, &irmao);
            }
        }
    }
}
void limparArvore(Tree23Node **arvore) {
    if (*arvore) {
        limparArvore(&((*arvore)->left));
        limparArvore(&((*arvore)->middle));
        
        if ((*arvore)->nInfos == 2) {
            limparArvore(&((*arvore)->right));
        }
        
        free(*arvore);
        *arvore = NULL;
    }
}

// Função para imprimir um nó individual
void imprimirNodo(Tree23Node *no, int value, int nivel) {
    int i;
    if (no) {
        // Indentação para representar o nível do nó na árvore
        for (i = 0; i < nivel; i++) {
            printf("\t");
        }

        // Exibe a palavra em português e suas traduções em inglês
        if (value == 0) {
            printf("%s\n", no->info1.portugueseWord);
            printf("Traduções em inglês:\n");
            printBinaryTree(no->info1.englishTreeRoot); // Imprime a árvore binária de traduções de `info1`
        } else {
            printf("%s\n", no->info2.portugueseWord);
            printf("Traduções em inglês:\n");
            printBinaryTree(no->info2.englishTreeRoot); // Imprime a árvore binária de traduções de `info2`
        }
    }
}

// Função para imprimir a árvore completa em ordem
void imprimirArvore(Tree23Node *arvore, int nivel) {
    if (arvore) {
        // Imprime a subárvore à esquerda
        imprimirArvore(arvore->left, nivel + 1);

        // Imprime `info1` e suas traduções
        imprimirNodo(arvore, 0, nivel);

        // Imprime a subárvore do meio
        imprimirArvore(arvore->middle, nivel + 1);

        // Se o nó possui `info2`, imprime `info2` e a subárvore à direita
        if (arvore->nInfos == 2) {
            imprimirNodo(arvore, 1, nivel);  // Imprime `info2`
            imprimirArvore(arvore->right, nivel + 1);
        }
    }
}


void imprimirInfoUnidade(Tree23Node *arvore, int unidade) {
    if (arvore) {
        // Percorre a árvore e imprime apenas as palavras da unidade especificada
        if (arvore->info1.unit == unidade) {
            int primeira = 1;
            imprimirTraducoes(arvore->info1.englishTreeRoot, arvore->info1.portugueseWord, &primeira);
        }
        if (arvore->nInfos == 2 && arvore->info2.unit == unidade) {
            int primeira = 1;
            imprimirTraducoes(arvore->info2.englishTreeRoot, arvore->info2.portugueseWord, &primeira);
        }

        // Percorre recursivamente as subárvores
        imprimirInfoUnidade(arvore->left, unidade);
        imprimirInfoUnidade(arvore->middle, unidade);
        imprimirInfoUnidade(arvore->right, unidade);
    }
}

void imprimirArvorePorUnidade(Tree23Node *arvore) {
    int unidade = 1;
    while (1) {
        printf("%% Unidade %d\n", unidade);
        imprimirInfoUnidade(arvore, unidade);
        if (unidade++ >= 2) break; // Limite para testar as primeiras duas unidades
        printf("\n");
    }
}


// Função para adicionar uma tradução em inglês na árvore binária dentro de `Info`
void adicionarTraducao(Info *info, const char *traducaoIngles, int unit) {
    info->englishTreeRoot = insertEnglishWord(info->englishTreeRoot, traducaoIngles, unit);
}


// informar uma unidade e então imprima todas as palavras da unidade em português seguida das equivalentes em inglês
void imprimirPorDadaUnidadeTraducoes(Tree23Node *arvore, int unidade) {
    printf("%% Unidade %d\n", unidade);

    // Função auxiliar para percorrer a árvore e imprimir os dados formatados
    imprimirInfoUnidadeFormatadaLinhaPorLinha(arvore, unidade);

    printf("\n");
}

// Função auxiliar para imprimir informações formatadas (linha por linha)
void imprimirInfoUnidadeFormatadaLinhaPorLinha(Tree23Node *arvore, int unidade) {
    if (arvore != NULL) {
        // Percorre a subárvore à esquerda
        imprimirInfoUnidadeFormatadaLinhaPorLinha(arvore->left, unidade);

        // Imprime as informações do nó, se a unidade corresponder
        if (arvore->info1.unit == unidade) {
            printf("- Palavra: %s\n", arvore->info1.portugueseWord);
            printf("  Traduções:\n");
            imprimirTraducoesLinhaPorLinha(arvore->info1.englishTreeRoot);
        }
        if (arvore->nInfos == 2 && arvore->info2.unit == unidade) {
            printf("- Palavra: %s\n", arvore->info2.portugueseWord);
            printf("  Traduções:\n");
            imprimirTraducoesLinhaPorLinha(arvore->info2.englishTreeRoot);
        }

        // Percorre a subárvore do meio
        imprimirInfoUnidadeFormatadaLinhaPorLinha(arvore->middle, unidade);

        // Percorre a subárvore à direita, se o nó contiver duas informações
        if (arvore->nInfos == 2) {
            imprimirInfoUnidadeFormatadaLinhaPorLinha(arvore->right, unidade);
        }
    }
}

// Função para imprimir traduções da árvore binária (linha por linha)
void imprimirTraducoesLinhaPorLinha(TreeNode *raiz) {
    if (raiz != NULL) {
        imprimirTraducoesLinhaPorLinha(raiz->left);  // Subárvore esquerda
        printf("    - %s\n", raiz->englishWord);     // Palavra em inglês
        imprimirTraducoesLinhaPorLinha(raiz->right); // Subárvore direita
    }
}


void imprimirTraducoesEmIngles(Tree23Node *arvore, const char *palavraPortugues) {
    Tree23Node **nodo = NULL;
    Tree23Node *irmao = NULL;

    nodo = buscarValorArvore(&arvore, palavraPortugues, &irmao);
    if (*nodo) {
        printf("Traduções em inglês para a palavra '%s':\n", palavraPortugues);
        if ((*nodo)->nInfos == 2) {
            printBinaryTree((*nodo)->info1.englishTreeRoot);
            printBinaryTree((*nodo)->info2.englishTreeRoot);
        } else {
            printBinaryTree((*nodo)->info1.englishTreeRoot);
        }
    } else {
        printf("Palavra '%s' não encontrada.\n", palavraPortugues);
    }
}

void removerPalavraIngles(Tree23Node** arvore, const char* palavraIngles, int unidade) {
    Tree23Node* node = *arvore;
    int removido = 0; // Variável para indicar se a palavra foi removida

    while (node != NULL && !removido) {
        // Verifica `info1`
        if (node->info1.englishTreeRoot != NULL) {
            TreeNode* resultado = searchEnglishWord(node->info1.englishTreeRoot, palavraIngles);
            if (resultado != NULL && resultado->unit == unidade) {
                // Remove a palavra em inglês da árvore binária
                node->info1.englishTreeRoot = removeEnglishWord(node->info1.englishTreeRoot, palavraIngles, unidade);

                // Se a árvore binária ficou vazia, remover o `info1` da árvore 2-3
                if (node->info1.englishTreeRoot == NULL) {
                    printf("Removendo palavra '%s' da árvore 2-3.\n", node->info1.portugueseWord);
                    removerValorArvore(arvore, node->info1.portugueseWord);
                }
                removido = 1; // Marca que a palavra foi removida
            }
        }

        // Verifica `info2`, se existir
        if (!removido && node->nInfos == 2 && node->info2.englishTreeRoot != NULL) {
            TreeNode* resultado = searchEnglishWord(node->info2.englishTreeRoot, palavraIngles);
            if (resultado != NULL && resultado->unit == unidade) {
                // Remove a palavra em inglês da árvore binária
                node->info2.englishTreeRoot = removeEnglishWord(node->info2.englishTreeRoot, palavraIngles, unidade);

                // Se a árvore binária ficou vazia, remover o `info2` da árvore 2-3
                if (node->info2.englishTreeRoot == NULL) {
                    printf("Removendo palavra '%s' da árvore 2-3.\n", node->info2.portugueseWord);
                    removerValorArvore(arvore, node->info2.portugueseWord);
                }
                removido = 1; // Marca que a palavra foi removida
            }
        }

        // Decidir qual subárvore percorrer
        if (!removido) {
            if (strcmp(palavraIngles, node->info1.portugueseWord) < 0) {
                node = node->left;
            } else if (node->nInfos == 1 || strcmp(palavraIngles, node->info2.portugueseWord) < 0) {
                node = node->middle;
            } else {
                node = node->right;
            }
        }
    }

    if (!removido) {
        printf("Palavra '%s' não encontrada na unidade %d.\n", palavraIngles, unidade);
    }
}

void removerPalavraPortugues(Tree23Node **arvore, const char *palavraPortugues, int unidade) {
    Tree23Node **remover = NULL;
    Tree23Node *irmao = NULL;

    if (*arvore) {
        remover = buscarValorArvore(arvore, palavraPortugues, &irmao);

        while (remover && *remover) {
            if (ehFolha(*remover)) {
                // Verifica se a palavra pertence à unidade especificada
                if (strcmp((*remover)->info1.portugueseWord, palavraPortugues) == 0 && (*remover)->info1.unit == unidade) {
                    // Limpa a árvore binária associada ao `info1`
                    limparArvoreBinaria(&((*remover)->info1.englishTreeRoot));
                    removerValorNodo(remover, palavraPortugues);
                } else if ((*remover)->nInfos == 2 &&
                           strcmp((*remover)->info2.portugueseWord, palavraPortugues) == 0 &&
                           (*remover)->info2.unit == unidade) {
                    // Limpa a árvore binária associada ao `info2`
                    limparArvoreBinaria(&((*remover)->info2.englishTreeRoot));
                    removerValorNodo(remover, palavraPortugues);
                } else {
                    printf("Palavra '%s' não encontrada na unidade %d.\n", palavraPortugues, unidade);
                }
                remover = NULL;
            } else {
                // Caso não seja folha, troca os valores para transformar o nó em folha
                remover = trocarValoresArvore(remover, palavraPortugues, &irmao);
            }
        }
    } else {
        printf("A árvore está vazia.\n");
    }
}
