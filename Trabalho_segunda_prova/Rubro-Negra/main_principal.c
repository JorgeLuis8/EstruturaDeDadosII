#include <stdio.h>
#include <stdlib.h>
#include "Disciplina.C"
#include "Curso.C"

void menu();

int main()
{
    arv_curso *raiz_curso = NULL;
    int opcao;
    int cod1;
    int codigo_curso, bloco, carga_horaria;
    do
    {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            arv_curso *novo_curso = cria_no_curso();
            if (novo_curso == NULL)
            {
                printf("Erro ao criar novo curso.\n");
                break;
            }

            ler_dados_curso(novo_curso);

            // Verificar se o curso já existe
            arv_curso *curso_existente = buscar_disciplina_curso(raiz_curso, novo_curso->dados.codigo);
            if (curso_existente != NULL)
            {
                printf("Erro: Ja existe um curso com o codigo %d.\n", novo_curso->dados.codigo);
                break;
            }

            // Caso não exista, inserir o novo curso na árvore
            raiz_curso = inserir_curso(raiz_curso, novo_curso);
            break;
        }

        case 2:
        {
            int codigo_curso;
            printf("Informe o codigo do curso onde deseja inserir a disciplina: ");
            scanf("%d", &codigo_curso);
            arv_curso *curso = buscar_disciplina_curso(raiz_curso, codigo_curso);
            if (curso != NULL)
            {
                arv_disciplina *nova_disciplina = cria_no();
                ler_dados(nova_disciplina, curso);
                if (buscar_disciplina(curso->disciplinas, nova_disciplina->dados.codigo) != NULL)
                {
                    printf("Erro: Ja existe uma disciplina com o codigo %d.\n", nova_disciplina->dados.codigo);
                    break;
                }
                curso->disciplinas = inserir_disciplina(curso->disciplinas, nova_disciplina);
            }
            else
            {
                printf("Curso nao encontrado!\n");
            }
            break;
        }
        case 3:
            imprimir_disciplinas_curso(raiz_curso);
            break;
        case 4:
        {
            int codigo_curso;
            printf("Informe o codigo do curso que deseja buscar: ");
            scanf("%d", &codigo_curso);
            arv_curso *curso = buscar_disciplina_curso(raiz_curso, codigo_curso);
            imprimir_dados_curso(curso);
            break;
        }
        case 5:
        {
            int qtd_blocos;
            printf("Informe a quantidade de blocos: ");
            scanf("%d", &qtd_blocos);
            imprimir_cursos_por_blocos(raiz_curso, qtd_blocos);
            break;
        }
        case 6:
            printf("Informe o codigo do curso: ");
            scanf("%d", &cod1);
            arv_curso *cursoBuscar = buscar_disciplina_curso(raiz_curso, cod1);

            if (cursoBuscar != NULL)
            {
                printf("Disciplinas do curso em ordem crescente pelo codigo:\n");
                if (cursoBuscar->disciplinas != NULL)
                {
                    imprimir_disciplinas(cursoBuscar->disciplinas);
                }
                else
                {
                    printf("O curso nao possui disciplinas cadastradas.\n");
                }
            }
            else
            {
                printf("Curso inexistente\n");
            }
            break;
        case 7:
        {
            printf("Informe o codigo do curso: ");
            scanf("%d", &cod1);
            arv_curso *cursoBuscar = buscar_disciplina_curso(raiz_curso, cod1);

            if (cursoBuscar != NULL)
            {
                if (cursoBuscar->disciplinas != NULL)
                {
                    int codDisciplina;
                    printf("Informe o codigo da disciplina: ");
                    scanf("%d", &codDisciplina);
                    arv_disciplina *disciplinaBuscar = buscar_disciplina(cursoBuscar->disciplinas, codDisciplina);

                    if (disciplinaBuscar != NULL)
                    {
                        printf("Informacoes da disciplina:\n");
                        imprimir_disciplinas(disciplinaBuscar);
                    }
                    else
                    {
                        printf("Disciplina inexistente\n");
                    }
                }
                else
                {
                    printf("O curso nao possui disciplinas cadastradas.\n");
                }
            }
            else
            {
                printf("Curso inexistente\n");
            }
            break;
        }
        case 8:

            printf("Informe o codigo do curso: ");
            scanf("%d", &codigo_curso);
            arv_curso *curso = buscar_disciplina_curso(raiz_curso, codigo_curso);

            if (curso != NULL)
            {
                printf("Informe o bloco das disciplinas que deseja imprimir: ");
                scanf("%d", &bloco);
                if (curso->disciplinas != NULL)
                {
                    printf("Disciplinas do curso no bloco %d:\n", bloco);
                    imprimir_disciplinas(curso->disciplinas);
                }
                else
                {
                    printf("O curso nao possui disciplinas cadastradas.\n");
                }
            }
            else
            {
                printf("Curso inexistente\n");
            }
            break;
        case 9:

            printf("Informe o codigo do curso: ");
            scanf("%d", &codigo_curso);
            arv_curso *curso1 = buscar_disciplina_curso(raiz_curso, codigo_curso);

            if (curso1 != NULL)
            {
                printf("Informe a carga horaria das disciplinas que deseja imprimir: ");
                scanf("%d", &carga_horaria);
                if (curso1->disciplinas != NULL)
                {
                    printf("Disciplinas do curso com carga horaria %d:\n", carga_horaria);
                    imprimir_disciplinas(curso1->disciplinas);
                }
                else
                {
                    printf("O curso nao possui disciplinas cadastradas.\n");
                }
            }
            else
            {
                printf("Curso inexistente\n");
            }
            break;
        case 10:
        {
            printf("Informe o codigo do curso: ");
            scanf("%d", &codigo_curso);
            arv_curso *cursoDeletar = buscar_disciplina_curso(raiz_curso, codigo_curso);

            if (cursoDeletar != NULL)
            {
                if (cursoDeletar->disciplinas != NULL)
                {
                    int codDisciplina;
                    printf("Informe o codigo da disciplina a ser removida: ");
                    scanf("%d", &codDisciplina);

                    // Excluir a disciplina
                    if (remove_ArvLLRB(&(cursoDeletar->disciplinas), codDisciplina))
                    {
                        printf("Disciplina removida com sucesso.\n");
                    }
                    else
                    {
                        printf("Nao foi possivel remover a disciplina.\n");
                    }
                }
                else
                {
                    printf("O curso nao possui disciplinas cadastradas.\n");
                }
            }
            else
            {
                printf("Curso inexistente\n");
            }
            break;
        }
        case 11:
            printf("Informe o codigo do curso que deseja remover: ");
            scanf("%d", &codigo_curso);

            arv_curso *cursoRemover = buscar_disciplina_curso(raiz_curso, codigo_curso);

            if (cursoRemover != NULL)
            {
                if (cursoRemover->disciplinas == NULL)
                {
                    remove_ArvLLRB_curso(&raiz_curso, codigo_curso);
                    if (raiz_curso != NULL)
                    {
                        printf("Curso removido com sucesso.\n");
                    }
                }
                else
                {
                    printf("O curso possui disciplinas cadastradas. Nao e possivel remover.\n");
                }
            }
            else
            {
                printf("Curso nao encontrado.\n");
            }
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void menu()
{
    printf("\n===== Menu =====\n");
    printf("1. Inserir um novo curso\n");
    printf("2. Inserir uma nova disciplina em um curso existente\n");
    printf("3. Imprimir a arvore de cursos em ordem crescente pelo codigo do curso\n");
    printf("4. Imprimir os dados de um curso dado o codigo do mesmo\n");
    printf("5. Imprimir todos os cursos com a mesma quantidade de blocos\n");
    printf("6. Imprimir disciplinas em ordem crescente dado o codigo do curso\n");
    printf("7. Imprimir informacoes de uma disciplina dado o codigo do curso e o codigo da disciplina\n");
    printf("8. Imprmir disciplinas de um determinado bloco \n");
    printf("9. Imprimir todas as disciplinas de um determinado curso com a mesma carga horaria\n");
    printf("10. Remover uma disciplina \n");
    printf("11. Remover um curso\n");
    printf("0. Sair\n");
}
