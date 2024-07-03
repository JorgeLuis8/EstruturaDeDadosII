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

        case 0:
            exit(0);

        default:
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}
