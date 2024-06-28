#include <stdio.h>
#include <stdlib.h>
#include "Curso.c"

int main()
{
    arv_curso *raiz = NULL;
    int opcao, codigo;
    arv_curso *novo_no;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Inserir curso\n");
        printf("2. Remover curso\n");
        printf("3. Buscar curso\n");
        printf("4. Imprimir cursos\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            novo_no = cria_no_curso();
            ler_dados_curso(novo_no);
            raiz = inserir_curso(raiz, novo_no);
            break;

        case 2:
            printf("Informe o código do curso a ser removido: ");
            scanf("%d", &codigo);
            if (remove_ArvLLRB_curso(&raiz, codigo))
                printf("Curso removido com sucesso!\n");
            else
                printf("Curso não encontrado!\n");
            break;

        case 3:
            printf("Informe o código do curso a ser buscado: ");
            scanf("%d", &codigo);
            arv_curso *curso = buscar_disciplina_curso(raiz, codigo);
            if (curso != NULL)
            {
                printf("Curso encontrado:\n");
                printf("Código: %d\n", curso->dados->codigo);
                printf("Nome: %s\n", curso->dados->nome);
                printf("Quantidade de blocos: %d\n", curso->dados->qtd_blocos);
                printf("Número de semanas: %d\n", curso->dados->num_semanas);
                printf("Cor: %s\n", curso->cor == RED ? "Vermelho" : "Preto");
            }
            else
            {
                printf("Curso não encontrado!\n");
            }
            break;

        case 4:
            imprimir_disciplinas_curso(raiz);
            break;

        case 5:
            exit(0);
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    }

    return 0;
}
