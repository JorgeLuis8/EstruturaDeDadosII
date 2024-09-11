#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.c"   // Inclua o cabeçalho correto para a árvore de cursos
#include "alunos.c"  // Inclua o cabeçalho correto para a lista de alunos

void exibir_menu() {
    printf("Menu:\n");
    printf("1. Cadastrar novo curso\n");
    printf("2. Buscar curso por codigo\n");
    printf("3. Cadastrar novo aluno\n");
    printf("4. Buscar aluno por matricula\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Arvore_curso *raiz_cursos = NULL;
    Aluno *raiz_alunos = NULL;
    int opcao;
    int codigo, codigo_curso, matricula, max_periodos;
    char nome[100];
    Arvore_curso *curso;
    Aluno *aluno;

    while (1) {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Cadastro de curso
                printf("Digite o codigo do curso: ");
                scanf("%d", &codigo);
                if(buscar_curso(raiz_cursos, codigo) != NULL){
                    printf("Curso ja cadastrado.\n");
                    break;
                }
                printf("Digite o nome do curso: ");
                scanf(" %[^\n]", nome);
                printf("Digite o numero maximo de periodos do curso: ");
                scanf("%d", &max_periodos);

                curso = criar_curso();
                curso->codigo = codigo;
                strcpy(curso->nome, nome);
                curso->periodo = max_periodos;

                raiz_cursos = inserir_curso(raiz_cursos, curso);
                printf("Curso cadastrado com sucesso!\n");
                break;

            case 2:
                // Buscar curso
                printf("Digite o codigo do curso a buscar: ");
                scanf("%d", &codigo);

                curso = buscar_curso(raiz_cursos, codigo);
                if (curso != NULL) {
                    printf("Curso encontrado:\n");
                    printf("Codigo: %d\n", curso->codigo);
                    printf("Nome: %s\n", curso->nome);
                    printf("Numero maximo de periodos: %d\n", curso->periodo);
                } else {
                    printf("Curso nao encontrado.\n");
                }
                break;

            case 3:
                // Cadastro de aluno
                printf("Digite a matricula do aluno: ");
                if(buscar_aluno(raiz_alunos, matricula) != NULL){
                    printf("Aluno ja cadastrado.\n");
                    break;
                }
                scanf("%d", &matricula);
                printf("Digite o nome do aluno: ");
                scanf(" %[^\n]", nome);
                printf("Digite o codigo do curso do aluno: ");
                scanf("%d", &codigo_curso);

                // Verificar se o codigo do curso existe
                curso = buscar_curso(raiz_cursos, codigo_curso);
                if (curso == NULL) {
                    printf("Codigo de curso nao encontrado. Cadastro do aluno nao realizado.\n");
                    break;
                }

                aluno = criar_aluno();
                aluno->matricula = matricula;
                strcpy(aluno->nome, nome);
                aluno->codigo_curso = codigo_curso;

                raiz_alunos = inserir_aluno(raiz_alunos, aluno);
                printf("Aluno cadastrado com sucesso!\n");
                break;

            case 4:
                // Buscar aluno
                printf("Digite a matricula do aluno a buscar: ");
                scanf("%d", &matricula);

                aluno = buscar_aluno(raiz_alunos, matricula);
                if (aluno != NULL) {
                    printf("Aluno encontrado:\n");
                    printf("Matricula: %d\n", aluno->matricula);
                    printf("Nome: %s\n", aluno->nome);
                    printf("Codigo do curso: %d\n", aluno->codigo_curso);
                } else {
                    printf("Aluno nao encontrado.\n");
                }
                break;

            case 5:
                // Finalizar programa
                // Liberar memoria alocada, se necessario
                // liberar_alunos(raiz_alunos);
                // liberar_cursos(raiz_cursos);
                printf("Saindo...\n");
                exit(0);

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
