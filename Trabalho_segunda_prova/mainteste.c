#include <stdio.h>
#include <stdlib.h>
#include "Curso.c"

int main()
{
    arv_curso *raiz = NULL;
    int opcao, codigo;
    arv_curso *no;

    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir curso\n");
        printf("2. Buscar curso\n");
        printf("3. Remover curso\n");
        printf("4. Imprimir cursos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            no = cria_no();
            ler_dados(no);
            raiz = inserir_disciplina(raiz, no);
            break;
        case 2:
            printf("Informe o codigo do curso que deseja buscar: ");
            scanf("%d", &codigo);
            no = buscar_disciplina(raiz, codigo);
            if (no != NULL)
            {
                printf("Curso encontrado:\n");
                printf("Codigo: %d\n", no->dados->codigo);
                printf("Nome: %s\n", no->dados->nome);
                printf("Quantidade de blocos: %d\n", no->dados->qtd_blocos);
                printf("Numero de semanas: %d\n", no->dados->num_semanas);
                printf("Cor: %d\n", no->cor);
            }
            else
            {
                printf("Curso nao encontrado.\n");
            }
            break;
        case 3:
            printf("Informe o codigo do curso que deseja remover: ");
            scanf("%d", &codigo);
            if (remove_ArvLLRB(&raiz, codigo))
                printf("Curso removido com sucesso.\n");
            else
                printf("Curso nao encontrado.\n");
            break;
        case 4:
            imprimir_disciplinas(raiz);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}