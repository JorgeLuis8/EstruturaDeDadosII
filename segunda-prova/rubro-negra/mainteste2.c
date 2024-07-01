#include <stdio.h>
#include <stdlib.h>
#include "Curso.c"
#include "Disciplina.c"

void menu()
{
    printf("\n--- Menu ---\n");
    printf("1. Cadastrar Curso\n");
    printf("2. Adicionar Disciplina a Curso\n");
    printf("3. Imprimir Cursos e Disciplinas\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
}

int main()
{
    arv_curso *raiz_curso = NULL;
    int opcao, codigo_curso;
    arv_curso *curso_encontrado;

    do
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            arv_curso *novo_curso = cria_no_curso();
            if (novo_curso != NULL)
            {
                ler_dados_curso(novo_curso);
                raiz_curso = inserir_curso(raiz_curso, novo_curso);
                printf("Curso cadastrado com sucesso!\n");
            }
            else
            {
                printf("Erro ao criar nó do curso.\n");
            }
            break;
        }
        case 2:
        {
            printf("Informe o código do curso para adicionar disciplinas: ");
            scanf("%d", &codigo_curso);
            curso_encontrado = buscar_disciplina_curso(raiz_curso, codigo_curso);
            if (curso_encontrado != NULL)
            {
                int continuar = 1;
                while (continuar)
                {
                    arv_disciplina *nova_disciplina = cria_no();
                    if (nova_disciplina != NULL)
                    {
                        ler_dados(nova_disciplina);
                        curso_encontrado->disciplinas = inserir_disciplina(curso_encontrado->disciplinas, nova_disciplina);
                        printf("Disciplina adicionada com sucesso!\n");
                        printf("Deseja adicionar outra disciplina? (1-Sim, 0-Não): ");
                        scanf("%d", &continuar);
                    }
                    else
                    {
                        printf("Erro ao criar nó da disciplina.\n");
                    }
                }
            }
            else
            {
                printf("Curso não encontrado.\n");
            }
            break;
        }
        case 3:
        {
            printf("\nDados dos Cursos e Disciplinas:\n");
            imprimir_disciplinas_curso(raiz_curso);
            break;
        }
        case 4:
        {
            printf("Saindo...\n");
            break;
        }
        default:
        {
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
        }
    } while (opcao != 4);

    return 0;
}
