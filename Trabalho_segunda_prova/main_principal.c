#include <stdio.h>
#include <stdlib.h>
#include "Curso.c"
#include "Disciplina.c"

#define BLACK 0
#define RED 1

void menu();

int main() {
    arv_curso *raiz_curso = NULL;
    int opcao;

    do {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                imprimir_disciplinas_curso(raiz_curso);
                break;
            case 2: {
                arv_curso *novo_curso = cria_no_curso();
                if (novo_curso == NULL) {
                    printf("Erro ao criar novo curso.\n");
                    break;
                }
                ler_dados_curso(novo_curso);
                raiz_curso = inserir_curso(raiz_curso, novo_curso);
                break;
            }
            case 3: {
                int codigo_curso;
                printf("Informe o codigo do curso onde deseja inserir a disciplina: ");
                scanf("%d", &codigo_curso);
                arv_curso *curso = buscar_disciplina_curso(raiz_curso, codigo_curso);
                if (curso != NULL) {
                    arv_disciplina *nova_disciplina = cria_no();
                    if (nova_disciplina == NULL) {
                        printf("Erro ao criar nova disciplina.\n");
                        break;
                    }
                    ler_dados(nova_disciplina);
                    curso->disciplinas = inserir_disciplina(curso->disciplinas, nova_disciplina);
                } else {
                    printf("Curso nao encontrado!\n");
                }
                break;
            }
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}

void menu() {
    printf("\n===== Menu =====\n");
    printf("1. Imprimir a árvore de cursos em ordem crescente pelo código do curso\n");
    printf("2. Inserir um novo curso\n");
    printf("3. Inserir uma nova disciplina em um curso existente\n");
    printf("4. Sair\n");
}
