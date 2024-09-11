#include "Alunos.c"
#include <stdio.h>

void menu() {
    printf("---- Menu ----\n");
    printf("1. Inserir Aluno\n");
    printf("2. Remover Aluno\n");
    printf("3. Buscar Aluno\n");
    printf("4. Imprimir Todos os Alunos\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Aluno *lista_alunos = NULL;
    int opcao, matricula;
    

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Aluno *novo_aluno = criar_aluno();

                printf("Digite a matricula do aluno: ");
                scanf("%d", &novo_aluno->matricula);

                printf("Digite o nome do aluno: ");
                scanf(" %[^\n]", novo_aluno->nome);  // %[^\n] permite ler strings com espaços

                printf("Digite o codigo do curso: ");
                scanf("%d", &novo_aluno->codigo_curso);

                lista_alunos = inserir_aluno(lista_alunos, novo_aluno);
                printf("Aluno inserido com sucesso!\n\n");
                break;
            }

            case 2: {
                printf("Digite a matricula do aluno a ser removido: ");
                scanf("%d", &matricula);
                if(buscar_aluno(lista_alunos, matricula) == NULL){
                    printf("Aluno com matricula %d nao encontrado.\n", matricula);
                    break;
                }
                lista_alunos = remover_aluno(lista_alunos, matricula);
                printf("Aluno removido com sucesso!\n\n");
                break;
            }

            case 3: {
                printf("Digite a matricula do aluno a ser buscado: ");
                scanf("%d", &matricula);

                Aluno *aluno_encontrado = buscar_aluno(lista_alunos, matricula);
                if (aluno_encontrado != NULL) {
                    printf("Aluno encontrado:\n");
                    printf("Matricula: %d\n", aluno_encontrado->matricula);
                    printf("Nome: %s\n", aluno_encontrado->nome);
                    printf("Codigo do curso: %d\n", aluno_encontrado->codigo_curso);
                } else {
                    printf("Aluno com matricula %d nao encontrado.\n", matricula);
                }
                printf("\n");
                break;
            }

            case 4: {
                printf("Lista de todos os alunos:\n");
                imprimir_alunos(lista_alunos);
                printf("\n");
                break;
            }

            case 5: {
                printf("Saindo...\n");
                break;
            }

            default: {
                printf("Opcao invalida. Tente novamente.\n\n");
            }
        }
    } while (opcao != 5);

    return 0;
}
