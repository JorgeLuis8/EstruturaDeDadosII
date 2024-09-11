#include <stdio.h>
#include <stdlib.h>
#include "matricula.c"

void menu() {
    printf("\n---- Menu ----\n");
    printf("1. Inserir matrícula\n");
    printf("2. Remover matrícula\n");
    printf("3. Buscar matrícula\n");
    printf("4. Imprimir todas as matrículas\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função menu
int main() {
    arvore_matricula *raiz = NULL;
    int opcao;
    int codigo_disciplina;

    do {
        menu();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                // Inserir matrícula
                arvore_matricula *novo_no = (arvore_matricula *)malloc(sizeof(arvore_matricula));
                if (novo_no == NULL) {
                    printf("Erro ao alocar memoria para novo nó.\n");
                    exit(1);
                }

                Ler_notas(novo_no);  // Função para ler os dados do nó

                novo_no->esq = NULL;
                novo_no->dir = NULL;

                raiz = inserir_matriculas(raiz, novo_no);
                printf("Matrícula inserida com sucesso!\n");
                break;
            }

            case 2: {
                // Remover matrícula
                printf("Digite o codigo da disciplina para remover: ");
                scanf("%d", &codigo_disciplina);

                raiz = remover_nota(raiz, codigo_disciplina);
                printf("Matrícula removida com sucesso!\n");
                break;
            }

            case 3: {
                // Buscar matrícula
                printf("Digite o codigo da disciplina para buscar: ");
                scanf("%d", &codigo_disciplina);

                arvore_matricula *matricula_encontrada = buscar_notas(raiz, codigo_disciplina);
                if (matricula_encontrada != NULL) {
                    printf("Matrícula encontrada:\n");
                    printf("Codigo da disciplina: %d\n", matricula_encontrada->codigo_disciplina);
                } else {
                    printf("Matrícula com o codigo da disciplina %d nao encontrada.\n", codigo_disciplina);
                }
                break;
            }

            case 4: {
                // Imprimir todas as matrículas
                printf("Todas as matrículas:\n");
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