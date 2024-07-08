#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Curso23.c"
#include "Disciplina23.c"

// Funções para inserir cursos e disciplinas, e imprimir a árvore de cursos
// Essas funções são assumidas como implementadas corretamente nos arquivos Curso23.c e Disciplina23.c

int main()
{
    arv_curso23 *raizCurso = NULL;
    int opcao, codigoCurso, qtd_blocos, num_semanas;
    char nomeCurso[100];
    dados_curso23 infoSobeCurso;

    int codigoDisciplina, bloco, carga_horaria;
    char nomeDisciplina[100];
    dados_disciplina infoSobeDisciplina;

    while (1)
    {
        printf("Menu:\n");
        printf("1. Inserir Curso\n");
        printf("2. Inserir Disciplina em um Curso\n");
        printf("3. Imprimir Cursos\n");
        printf("4. Imprimir Disciplinas de um Curso\n");
        printf("5. Imprimir Cursos dado o codigo\n");
        printf("6. Imprimir todos os cursos com a mesma quantidade de blocos\n");
        printf("7. Imprimir dados de uma disciplina dado o codigo da mesma e do curso\n");
        printf("8. Imprimir todas as disciplinas de um determinado bloco de um curso\n");
        printf("9. Imprimir todas as disciplinas de um curso com a mesma carga horária\n"); // Nova opção adicionada
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Inserir Curso\n");
            printf("Codigo: ");
            scanf("%d", &codigoCurso);
            printf("Nome: ");
            scanf(" %[^\n]", nomeCurso);
            printf("Quantidade de Blocos: ");
            scanf("%d", &qtd_blocos);
            printf("Numero de Semanas: ");
            scanf("%d", &num_semanas);
            inserirCurso(&raizCurso, codigoCurso, nomeCurso, qtd_blocos, num_semanas, NULL, &infoSobeCurso);
            break;

        case 2:
            printf("Inserir Disciplina em um Curso\n");
            printf("Codigo do Curso: ");
            scanf("%d", &codigoCurso);
            // Aqui você deve encontrar o curso na árvore
            arv_curso23 *curso = buscarCurso(raizCurso, codigoCurso);
            if (curso == NULL)
            {
                printf("Curso não encontrado!\n");
                break;
            }
            printf("Codigo da Disciplina: ");
            scanf("%d", &codigoDisciplina);
            printf("Nome da Disciplina: ");
            scanf(" %[^\n]", nomeDisciplina);
            printf("Bloco da Disciplina: ");
            scanf("%d", &bloco);
            printf("Carga Horaria: ");
            scanf("%d", &carga_horaria);
            inserir_Disciplina(&(curso->disciplinas), codigoDisciplina, nomeDisciplina, bloco, carga_horaria, NULL, &infoSobeDisciplina);
            break;

        case 3:
            printf("Imprimir Cursos\n");
            imprimirCurso(raizCurso);
            break;

        case 4:
            printf("Imprimir Disciplinas de um Curso\n");
            printf("Codigo do Curso: ");
            scanf("%d", &codigoCurso);
            // Aqui você deve encontrar o curso na árvore
            curso = buscarCurso(raizCurso, codigoCurso);
            if (curso == NULL)
            {
                printf("Curso não encontrado!\n");
                break;
            }
            imprimir_Disciplina(curso->disciplinas);
            break;

        case 5:
            // Imprimir cursos dado o codigo do mesmo
            printf("Imprimir Cursos dado o codigo\n");
            printf("Codigo do Curso: ");
            scanf("%d", &codigoCurso);
            // Aqui você deve encontrar o curso na árvore
            curso = buscarCurso(raizCurso, codigoCurso);
            if (curso == NULL)
            {
                printf("Curso não encontrado!\n");
                break;
            }
            printf("Codigo: %d\n", curso->info1->codigo);
            printf("Nome: %s\n", curso->info1->nome);
            printf("Quantidade de Blocos: %d\n", curso->info1->qtd_blocos);
            printf("Numero de Semanas: %d\n", curso->info1->num_semanas);
            break;

        case 6:
            // Imprimir todos os cursos com a mesma quantidade de blocos
            printf("Imprimir Cursos dado a quantidade de blocos\n");
            printf("Quantidade de Blocos: ");
            scanf("%d", &qtd_blocos);
            imprimirCursoBlocos(raizCurso, qtd_blocos);
            break;

        case 7:
            // Imprimir dados de uma disciplina dado o codigo da mesma e do curso
            printf("Imprimir Disciplina dado o codigo\n");
            printf("Codigo do Curso: ");
            scanf("%d", &codigoCurso);
            // Aqui você deve encontrar o curso na árvore
            curso = buscarCurso(raizCurso, codigoCurso);
            if (curso == NULL)
            {
                printf("Curso não encontrado!\n");
                break;
            }
            printf("Codigo da Disciplina: ");
            scanf("%d", &codigoDisciplina);
            arv_23Disciplina *disciplina = buscarDisciplina(curso->disciplinas, codigoDisciplina);
            if (disciplina == NULL)
            {
                printf("Disciplina não encontrada!\n");
                break;
            }
            printf("Codigo: %d\n", disciplina->info1->codigo);
            printf("Nome: %s\n", disciplina->info1->nome);
            printf("Bloco: %d\n", disciplina->info1->bloco);
            printf("Carga Horaria: %d\n", disciplina->info1->carga_horaria);
            break;

        case 8:
            // Imprimir todas as disciplinas de um determinado bloco de um curso
            printf("Imprimir Disciplinas dado o bloco\n");
            printf("Codigo do Curso: ");
            scanf("%d", &codigoCurso);
            // Aqui você deve encontrar o curso na árvore
            curso = buscarCurso(raizCurso, codigoCurso);
            if (curso == NULL)
            {
                printf("Curso não encontrado!\n");
                break;
            }
            printf("Bloco da Disciplina: ");
            scanf("%d", &bloco);

            imprimirDisciplinasBloco(curso->disciplinas, bloco);
            break;

        case 9:
            // Imprimir todas as disciplinas de um curso com a mesma carga horária
            printf("Imprimir Disciplinas com a mesma carga horária\n");
            printf("Codigo do Curso: ");
            scanf("%d", &codigoCurso);
            // Aqui você deve encontrar o curso na árvore
            curso = buscarCurso(raizCurso, codigoCurso);
            if (curso == NULL)
            {
                printf("Curso não encontrado!\n");
                break;
            }
            printf("Carga Horaria: ");
            scanf("%d", &carga_horaria);
            imprimirDisciplinasCargaHoraria(curso->disciplinas, carga_horaria);
            break;

        case 0:
            exit(0);

        default:
            printf("Opcao invalida!\n");
        } 
    }

    return 0;
}
