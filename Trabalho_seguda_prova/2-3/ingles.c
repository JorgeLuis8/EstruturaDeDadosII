#include "ingles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unidade.h"


Inglesbin *initializeNode(const char *palavraIngles, int unidade) {
    Inglesbin *novoNo = (Inglesbin *)malloc(sizeof(Inglesbin));
    if (novoNo != NULL) {
        novoNo->englishWord = (char *)malloc(strlen(palavraIngles) + 1);
        if (novoNo->englishWord != NULL) {
            strcpy(novoNo->englishWord, palavraIngles);
        }
        

        novoNo->unitList = create_unit(unidade);
        

        novoNo->leftChild = novoNo->rightChild = NULL;
    }
    return novoNo;
}


Inglesbin *insertEnglishWord(Inglesbin *root, const char *palavraIngles, int unidade) {
    Inglesbin *result;

    if (root == NULL) {

        result = initializeNode(palavraIngles, unidade);
    } else {
        
        if (strcmp(palavraIngles, root->englishWord) == 0) {
            root->unitList = insert_unit_sorted(root->unitList, create_unit(unidade));
            result = root;
        } else {
            
            if (strcmp(palavraIngles, root->englishWord) < 0) {
                root->leftChild = insertEnglishWord(root->leftChild, palavraIngles, unidade);
            } else {
                root->rightChild = insertEnglishWord(root->rightChild, palavraIngles, unidade);
            }
            result = root;
        }
    }

    return result;
}

void addEnglishTranslation(NodeInfo *info, const char *palavraIng, int unidade) {

    if (info->englishWord == NULL) {
  
        info->englishWord = initializeNode(palavraIng, unidade);
    } else {
        
        info->englishWord = insertEnglishWord(info->englishWord, palavraIng, unidade);
    }


    info->englishWord->unitList = insert_unit_sorted(info->englishWord->unitList, create_unit(unidade));
}


void printBinaryTree(Inglesbin *root)
{
    if (root != NULL)
    {
    
        printBinaryTree(root->leftChild);
        
       
        printf("\nPalavra em Inglês: %s\n", root->englishWord);
        
   
        if (root->unitList != NULL) {
            printf("Unidades associadas: ");
            print_units(root->unitList);  
        }
        else {
            printf("Nenhuma unidade associada.\n");
        }
        
  
        printBinaryTree(root->rightChild);
    }
}


int isLeafNode(Inglesbin *raiz){
    return (raiz->leftChild == NULL && raiz->rightChild == NULL);
}

Inglesbin *getSingleChild(Inglesbin *raiz){
    Inglesbin *aux;
    aux = NULL;

    if (raiz->rightChild == NULL)
    {
        aux = raiz->leftChild;
    }
    else if (raiz->leftChild == NULL)
    {
        aux = raiz->rightChild;
    }

    return aux;
}

Inglesbin *getMinimumChild(Inglesbin *raiz){
    Inglesbin *aux;
    aux = raiz;

    if (raiz)
    {
        if (raiz->leftChild)
            aux = getMinimumChild(raiz->leftChild);
    }

    return aux;
}

int removeEnglishWord(Inglesbin **raiz, const char *palavra, int unidade) {
    Inglesbin *endFilho = NULL;
    int existe = 0;

    if (*raiz) {
    
        if (strcmp(palavra, (*raiz)->englishWord) == 0) {
            Inglesbin *aux = *raiz;
            existe = 1;

          
            Unit *novaLista = remove_unit((*raiz)->unitList, unidade);

            if (novaLista != (*raiz)->unitList) {
                (*raiz)->unitList = novaLista;

            
                if (novaLista == NULL) {
                    if (isLeafNode(*raiz)) {
                        free(aux);
                        *raiz = NULL;
                    } else if ((endFilho = getSingleChild(*raiz)) != NULL) {
                        free(aux);
                        *raiz = endFilho;
                    } else {
                        endFilho = getMinimumChild((*raiz)->rightChild);
                        strcpy((*raiz)->englishWord, endFilho->englishWord);
                        (*raiz)->unitList = endFilho->unitList;

                        removeEnglishWord(&(*raiz)->rightChild, endFilho->englishWord, unidade);
                    }
                }
            }
        } else if (strcmp(palavra, (*raiz)->englishWord) < 0) {

            existe = removeEnglishWord(&(*raiz)->leftChild, palavra, unidade);
        } else {

            existe = removeEnglishWord(&(*raiz)->rightChild, palavra, unidade);
        }
    }

    return existe;
}




void clear_binary_tree(Inglesbin *raiz) {
    if (raiz != NULL) {
      
        printf("Liberando nó da árvore binária com palavra: %s\n", raiz->englishWord);

 
        clear_binary_tree(raiz->leftChild);
        clear_binary_tree(raiz->rightChild);

    
        free_list(raiz->unitList);

        free(raiz->englishWord);

   
        free(raiz);
    }
}

void printTranslations(Inglesbin *node, int unidade, const char *palavraPortugues)
{
    if (node)
    {
       
        printTranslations(node->leftChild, unidade, palavraPortugues);

   
        if (find_unit(node->unitList, unidade)) 
        {
            printf("Palavra em Português: %s\n", palavraPortugues);
            printf("Tradução em Inglês: %s\n", node->englishWord);
        }

        
        printTranslations(node->rightChild, unidade, palavraPortugues);
    }
}

Inglesbin *findEnglishWord(Inglesbin *raiz, const char *palavraIngles) {
    Inglesbin *resultado = NULL;

    if (raiz != NULL) {
        int comparacao = strcmp(palavraIngles, raiz->englishWord);

        if (comparacao == 0) {
            resultado = raiz; 
        } else if (comparacao < 0) {
            resultado = findEnglishWord(raiz->leftChild, palavraIngles);
        } else {
            resultado = findEnglishWord(raiz->rightChild, palavraIngles);
        }
    }

    return resultado;
}


void FindEnglishWord(PortugueseTree **raiz, char *palavraIngles, int unidade, PortugueseTree **pai)
{
    if (*raiz != NULL)
    {

        FindEnglishWord(&(*raiz)->left, palavraIngles, unidade, pai);

 
        if ((*raiz)->info1.englishWord != NULL)
        {
            Inglesbin *traducaoEncontrada = findEnglishWord((*raiz)->info1.englishWord, palavraIngles);
            if (traducaoEncontrada != NULL && find_unit(traducaoEncontrada->unitList, unidade))
            {
                printf("Palavra em Inglês: %s encontrada na Unidade: %d\n", palavraIngles, unidade);
            }
        }


        FindEnglishWord(&(*raiz)->cent, palavraIngles, unidade, raiz);


        if ((*raiz)->nInfos == 2 && (*raiz)->info2.englishWord != NULL)
        {
            Inglesbin *traducaoEncontrada = findEnglishWord((*raiz)->info2.englishWord, palavraIngles);
            if (traducaoEncontrada != NULL && find_unit(traducaoEncontrada->unitList, unidade))
            {
                printf("Palavra em Inglês: %s encontrada na Unidade: %d\n", palavraIngles, unidade);
            }
        }

 
        if ((*raiz)->nInfos == 2)
        {
            FindEnglishWord(&(*raiz)->right, palavraIngles, unidade, raiz);
        }
    }
}

void showEnglishTranslations(Inglesbin *raiz)
{
    if (raiz)
    {
     
        showEnglishTranslations(raiz->leftChild);


        printf("- %s\n", raiz->englishWord);

  
        showEnglishTranslations(raiz->rightChild);
    }
}
