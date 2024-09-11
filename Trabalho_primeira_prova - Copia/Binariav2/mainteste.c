#include <stdio.h>
#include <stdlib.h>
#include "notas.c"

// Função menu
void menu() {
    printf("\n---- Menu ----\n");
    printf("1. Inserir nota\n");
    printf("2. Remover nota\n");
    printf("3. Buscar nota\n");
    printf("4. Imprimir todas as notas\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    arvore_notas *raiz = NULL;
    int opcao;
    int codigo_disciplina;
    
    do {
        menu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: {
                // Inserir nota
                arvore_notas *novo_no = (arvore_notas *)malloc(sizeof(arvore_notas));
                if (novo_no == NULL) {
                    printf("Erro ao alocar memoria para novo nó.\n");
                    exit(1);
                }
                
                Ler_notas(novo_no);  // Função para ler os dados do nó
                
                novo_no->esq = NULL;
                novo_no->dir = NULL;

                raiz = inserir_entrevistas(raiz, novo_no);
                printf("Nota inserida com sucesso!\n");
                break;
            }

            case 2: {
                // Remover nota
                printf("Digite o codigo da disciplina para remover: ");
                scanf("%d", &codigo_disciplina);
                
                raiz = remover_nota(raiz, codigo_disciplina);
                printf("Nota removida com sucesso!\n");
                break;
            }

            case 3: {
                // Buscar nota
                printf("Digite o codigo da disciplina para buscar: ");
                scanf("%d", &codigo_disciplina);
                
                arvore_notas *nota_encontrada = buscar_notas(raiz, codigo_disciplina);
                if (nota_encontrada != NULL) {
                    printf("Nota encontrada:\n");
                    printf("Codigo da disciplina: %d\n", nota_encontrada->codigo_disciplina);
                    printf("Semestre cursado: %s\n", nota_encontrada->semestre_cursado);
                    printf("Nota Final: %d\n", nota_encontrada->nota_final);
                } else {
                    printf("Nota com o codigo da disciplina %d nao encontrada.\n", codigo_disciplina);
                }
                break;
            }

            case 4: {
                // Imprimir todas as notas
                printf("Todas as notas:\n");
                imprimir_notas(raiz);
                break;
            }

            case 5: {
                // Sair
                printf("Saindo...\n");
                break;
            }

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
