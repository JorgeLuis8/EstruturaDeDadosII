#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.c"       // Inclua o cabeçalho correto para a árvore de cursos
#include "alunos.c"      // Inclua o cabeçalho correto para a lista de alunos
#include "disciplinas.c" // Inclua o cabeçalho correto para a árvore de disciplinas

void exibir_menu()
{
    printf("Menu:\n");
    printf("1. Cadastrar novo curso\n");
    printf("2. Cadastrar novo aluno\n");
    printf("3. Buscar curso por codigo\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Arvore_curso *raiz_cursos;
    raiz_cursos = NULL;
    Aluno *raiz_alunos;
    raiz_alunos = NULL;
    int opcao;
    int codigo, codigo_curso, matricula, carga_horaria, periodo;
    char nome[100];
    Aluno *aluno;
    Arvore_curso *curso;
    curso = NULL;
    arvore_disciplinas *disciplina;
    disciplina = NULL;
    while (opcao != 0)
    {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // Cadastro de curso
            printf("Digite o codigo do curso: ");
            scanf("%d", &codigo);
            printf("Digite o nome do curso: ");
            scanf(" %[^\n]", nome);

            curso = criar_curso();
            curso->codigo = codigo;
            strcpy(curso->nome, nome);

            raiz_cursos = inserir_curso(raiz_cursos, curso);
            printf("Curso cadastrado com sucesso!\n");
            break;

        case 2:
            // Cadastro de aluno
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula);
            printf("Digite o nome do aluno: ");
            scanf(" %[^\n]", nome);
            printf("Digite o codigo do curso do aluno: ");
            scanf("%d", &codigo_curso);

            // Verificar se o codigo do curso existe
            curso = buscar_curso(raiz_cursos, codigo_curso);
            if (curso == NULL)
            {
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

        case 3:
            // Buscar curso
            printf("Digite o codigo do curso a buscar: ");
            scanf("%d", &codigo);
            curso = buscar_curso(raiz_cursos, codigo);
            if (curso != NULL)
            {
                printf("Curso encontrado:\n");
                printf("Codigo: %d\n", curso->codigo);
                printf("Nome: %s\n", curso->nome);
            }
            else
            {
                printf("Curso nao encontrado.\n");
            }
            break;

        case 4:
            printf("Digite o codigo do curso da disciplina: ");
            scanf("%d", &codigo_curso);
            curso = buscar_curso(raiz_cursos, codigo_curso);
            if (curso == NULL)
            {
                printf("Codigo de curso nao encontrado. Cadastro da disciplina nao realizado.\n");
                break;
            }

            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo);
            printf("Digite o nome da disciplina: ");
            scanf(" %[^\n]", nome);
            printf("Digite a carga horaria da disciplina: ");
            scanf("%d", &carga_horaria);

            // Validação da carga horária
            if (carga_horaria < 30 || carga_horaria > 90 || carga_horaria % 15 != 0)
            {
                printf("Carga horaria invalida. Cadastro da disciplina nao realizado.\n");
                break;
            }

            printf("Digite o periodo da disciplina: ");
            scanf("%d", &periodo);

            // Validação do período
            if (periodo < 1 || periodo > curso->periodo)
            {
                printf("Periodo invalido. Cadastro da disciplina nao realizado.\n");
                break;
            }

            // Criar e preencher a disciplina
            disciplina = criar_disciplina();
            disciplina->codigo = codigo;
            strcpy(disciplina->nome, nome);
            disciplina->carga_horaria = carga_horaria;
            disciplina->periodo = periodo;

            // Inserir a disciplina na árvore de disciplinas do curso
            curso->raiz_disciplinas = inserir_disciplina(curso->raiz_disciplinas, disciplina);
            printf("Disciplina cadastrada com sucesso.\n");
            break;

        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
