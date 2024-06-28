#include <stdio.h>
#include <stdlib.h>
#include "Disciplina.c"

int main()
{
    arv_disciplina *raiz = NULL;
    int opcao;

    do
    {
        printf("1. Inserir disciplina\n");
        printf("2. Imprimir disciplinas\n");
        printf("3. Buscar disciplina\n");
        printf("4. Remover disciplina\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            arv_disciplina *no = cria_no();
            ler_dados(no);
            raiz = inserir_disciplina(raiz, no);
            break;
        }
        case 2:
            imprimir_disciplinas(raiz);
            break;
        case 3:
        {
            int codigo;
            printf("Informe o codigo da disciplina para buscar: ");
            scanf("%d", &codigo);
            arv_disciplina *disciplina = buscar_disciplina(raiz, codigo);
            if (disciplina != NULL)
            {
                printf("Disciplina encontrada!\n");
                printf("Codigo: %d\n", disciplina->dados->codigo);
                printf("Nome: %s\n", disciplina->dados->nome);
                printf("Bloco: %d\n", disciplina->dados->bloco);
                printf("Carga-Horaria: %d\n", disciplina->dados->carga_horaria);
                printf("Cor: %d\n", disciplina->cor);
            }
            else
            {
                printf("Disciplina nao encontrada.\n");
            }
            break;
        }
        case 4:
        {
            int codigo;
            printf("Informe o codigo da disciplina para remover: ");
            scanf("%d", &codigo);
            if (remove_ArvLLRB(&raiz, codigo))
            {
                printf("Disciplina removida com sucesso.\n");
            }
            else
            {
                printf("Disciplina nao encontrada.\n");
            }
            break;
        }
        case 5:
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
