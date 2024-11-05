#include "disciplinas.h"
#include <stdio.h>
#include <stdlib.h>

short maior_no_disc(short a, short b)
{
    // 1. Compara os dois valores fornecidos (a e b)
    // 2. Se 'a' for maior que 'b', retorna 'a'
    // 3. Caso contrário, retorna 'b'
    return (a > b) ? a : b;
}

short altura_do_no_disc(arvore_disciplinas *no)
{
    short altura; // Declara uma variável para armazenar a altura do nó.

    // 1. Verifica se o nó fornecido é nulo.
    if (no == NULL)
    {
        // 2. Se o nó for nulo, a altura é definida como -1.
        altura = -1;
    }
    else
    {
        // 3. Caso contrário, atribui a altura armazenada no nó à variável 'altura'.
        altura = no->altura;
    }

    // 4. Retorna a altura do nó.
    return altura;
}

short fator_balanceamento_disc(arvore_disciplinas *no)
{
    short fb = 0; // Declara uma variável para armazenar o fator de balanceamento.

    // 1. Verifica se o nó fornecido não é nulo.
    if (no != NULL)
    {
        // 2. Calcula o fator de balanceamento como a diferença entre as alturas da subárvore esquerda e da subárvore direita.
        fb = altura_do_no_disc(no->esq) - altura_do_no_disc(no->dir);
    }

    // 3. Retorna o fator de balanceamento.
    return fb;
}

arvore_disciplinas *rotar_esquerda_disc(arvore_disciplinas *no)
{
    arvore_disciplinas *aux, *aux1;

    // 1. O nó auxiliar 'aux' é atribuído ao nó à direita do nó atual.
    aux = no->dir;
    // 2. O nó auxiliar 'aux1' é atribuído ao nó à esquerda do nó auxiliar 'aux'.
    aux1 = aux->esq;

    // 3. Realiza a rotação para a esquerda: o nó atual (no) passa a ser filho esquerdo do nó auxiliar (aux).
    aux->esq = no;
    // 4. O filho direito do nó atual (no) é atualizado para ser o filho esquerdo do nó auxiliar (aux).
    no->dir = aux1;

    // 5. Atualiza a altura do nó atual (no) após a rotação.
    no->altura = maior_no_disc(altura_do_no_disc(no->esq), altura_do_no_disc(no->dir)) + 1;
    // 6. Atualiza a altura do nó auxiliar (aux) após a rotação.
    aux->altura = maior_no_disc(altura_do_no_disc(aux->esq), altura_do_no_disc(aux->dir)) + 1;

    // 7. Retorna o novo nó raiz da subárvore, que agora é 'aux'.
    return aux;
}

arvore_disciplinas *rotar_direita_disc(arvore_disciplinas *no)
{
    arvore_disciplinas *aux, *aux1;

    // 1. O nó auxiliar 'aux' é atribuído ao nó à esquerda do nó atual.
    aux = no->esq;
    // 2. O nó auxiliar 'aux1' é atribuído ao nó à direita do nó auxiliar 'aux'.
    aux1 = aux->dir;

    // 3. Realiza a rotação para a direita: o nó auxiliar (aux) passa a ser o pai do nó atual (no).
    aux->dir = no;
    // 4. O filho esquerdo do nó atual (no) é atualizado para ser o filho direito do nó auxiliar (aux).
    no->esq = aux1;

    // 5. Atualiza a altura do nó atual (no) após a rotação.
    no->altura = maior_no_disc(altura_do_no_disc(no->esq), altura_do_no_disc(no->dir)) + 1;
    // 6. Atualiza a altura do nó auxiliar (aux) após a rotação.
    aux->altura = maior_no_disc(altura_do_no_disc(aux->esq), altura_do_no_disc(aux->dir)) + 1;

    // 7. Retorna o novo nó raiz da subárvore, que agora é 'aux'.
    return aux;
}

arvore_disciplinas *rotar_direita_esquerda_disc(arvore_disciplinas *no)
{
    // 1. Primeiro, realiza uma rotação à direita no filho à direita do nó atual.
    no->dir = rotar_direita_disc(no->dir);
    // 2. Em seguida, realiza uma rotação à esquerda no nó atual.
    return rotar_esquerda_disc(no);
}

arvore_disciplinas *rotar_esquerda_direita_disc(arvore_disciplinas *no)
{
    // 1. Primeiro, realiza uma rotação à esquerda no filho à esquerda do nó atual.
    no->esq = rotar_esquerda_disc(no->esq);
    // 2. Em seguida, realiza uma rotação à direita no nó atual.
    return rotar_direita_disc(no);
}

arvore_disciplinas *balencar_arvore_disc(arvore_disciplinas *raiz)
{
    // 1. Calcula o fator de balanceamento do nó raiz.
    short fb = fator_balanceamento_disc(raiz);

    // 2. Verifica se a árvore está desbalanceada para a direita.
    if (fb < -1 && fator_balanceamento_disc(raiz->dir) <= 0)
    {
        // 3. Se o fator de balanceamento do filho à direita também é negativo ou zero,
        //    realiza uma rotação à esquerda para corrigir o desbalanceamento.
        raiz = rotar_esquerda_disc(raiz);
    }
    // 4. Verifica se a árvore está desbalanceada para a esquerda.
    else if (fb > 1 && fator_balanceamento_disc(raiz->esq) >= 0)
    {
        // 5. Se o fator de balanceamento do filho à esquerda também é positivo ou zero,
        //    realiza uma rotação à direita para corrigir o desbalanceamento.
        raiz = rotar_direita_disc(raiz);
    }
    // 6. Verifica se há uma situação de desbalanceamento à esquerda do filho à direita.
    else if (fb > 1 && fator_balanceamento_disc(raiz->esq) < 0)
    {
        // 7. Realiza uma rotação à esquerda no filho à esquerda e, em seguida,
        //    uma rotação à direita no nó atual para corrigir o desbalanceamento.
        raiz = rotar_esquerda_direita_disc(raiz);
    }
    // 8. Verifica se há uma situação de desbalanceamento à direita do filho à esquerda.
    else if (fb < -1 && fator_balanceamento_disc(raiz->dir) > 0)
    {
        // 9. Realiza uma rotação à direita no filho à direita e, em seguida,
        //    uma rotação à esquerda no nó atual para corrigir o desbalanceamento.
        raiz = rotar_direita_esquerda_disc(raiz);
    }

    // 10. Retorna a nova raiz da árvore balanceada.
    return raiz;
}

arvore_disciplinas *criar_disciplina()
{
    // 1. Aloca memória para um novo nó da árvore de disciplinas.
    arvore_disciplinas *disciplina = (arvore_disciplinas *)malloc(sizeof(arvore_disciplinas));

    // 2. Verifica se a alocação de memória foi bem-sucedida.
    if (disciplina == NULL)
    {
        // 3. Se a alocação falhar, exibe uma mensagem de erro e encerra o programa.
        printf("Erro ao alocar memória para a disciplina\n");
        exit(1);
    }

    // 4. Inicializa os ponteiros para os filhos esquerdo e direito como NULL,
    //    pois é um novo nó e ainda não possui filhos.
    disciplina->esq = NULL;
    disciplina->dir = NULL;

    // 5. Define a altura do nó como 0, já que ele é uma folha.
    disciplina->altura = 0;

    // 6. Retorna o ponteiro para o novo nó da disciplina.
    return disciplina;
}

arvore_disciplinas *inserir_disciplina(arvore_disciplinas *raiz, arvore_disciplinas *no)
{
    // 1. Verifica se a árvore está vazia (raiz é NULL).
    if (raiz == NULL)
    {
        // 2. Se a árvore estiver vazia, o novo nó se torna a raiz.
        raiz = no;
    }
    else
    {
        // 3. Compara o código da nova disciplina com o código da raiz.
        if (no->codigo < raiz->codigo)
        {
            // 4. Se o código da nova disciplina for menor, insere recursivamente à esquerda.
            raiz->esq = inserir_disciplina(raiz->esq, no);
        }
        else
        {
            // 5. Se o código for maior ou igual, insere recursivamente à direita.
            raiz->dir = inserir_disciplina(raiz->dir, no);
        }
    }

    // 6. Atualiza a altura do nó raiz após a inserção.
    raiz->altura = maior_no_disc(altura_do_no_disc(raiz->esq), altura_do_no_disc(raiz->dir)) + 1;

    // 7. Balanceia a árvore após a inserção, se necessário.
    raiz = balencar_arvore_disc(raiz);

    // 8. Retorna a raiz (potencialmente nova) da árvore balanceada.
    return raiz;
}

arvore_disciplinas *buscar_disciplina(arvore_disciplinas *raiz, int codigo)
{
    arvore_disciplinas *aux = NULL;
    if (raiz != NULL)
    {
        if (codigo == raiz->codigo)
        {
            aux = raiz;
        }
        else
        {
            if (codigo < raiz->codigo)
            {
                aux = buscar_disciplina(raiz->esq, codigo);
            }
            else
            {
                aux = buscar_disciplina(raiz->dir, codigo);
            }
        }
    }
    return aux;
}

arvore_disciplinas *remover_disciplina(arvore_disciplinas *raiz, int codigo)
{
    // 1. Verifica se a árvore não está vazia.
    if (raiz != NULL)
    {
        // 2. Compara o código da disciplina a ser removida com o código do nó atual.
        if (codigo < raiz->codigo)
        {
            // 3. Se o código for menor, chama a função recursivamente à esquerda.
            raiz->esq = remover_disciplina(raiz->esq, codigo);
        }
        else if (codigo > raiz->codigo)
        {
            // 4. Se o código for maior, chama a função recursivamente à direita.
            raiz->dir = remover_disciplina(raiz->dir, codigo);
        }
        else
        {
            // 5. Caso em que o código encontrado corresponde ao código da raiz (nó a ser removido).

            // 6. Se o nó a ser removido não tiver filho à esquerda, substitui pelo filho à direita.
            if (raiz->esq == NULL)
            {
                arvore_disciplinas *temp = raiz->dir; // Salva o filho à direita
                free(raiz);                           // Libera a memória do nó
                raiz = temp;                          // Substitui raiz pelo filho à direita
            }
            // 7. Se o nó a ser removido não tiver filho à direita, substitui pelo filho à esquerda.
            else if (raiz->dir == NULL)
            {
                arvore_disciplinas *temp = raiz->esq; // Salva o filho à esquerda
                free(raiz);                           // Libera a memória do nó
                raiz = temp;                          // Substitui raiz pelo filho à esquerda
            }
            else
            {
                // 8. O nó a ser removido tem dois filhos.
                // Encontra o menor nó na subárvore à direita.
                arvore_disciplinas *temp = raiz->dir;
                while (temp->esq != NULL)
                {
                    temp = temp->esq; // Vai para o filho à esquerda até encontrar o menor
                }

                // 9. Copia o código do nó encontrado para o nó a ser removido.
                raiz->codigo = temp->codigo;

                // 10. Remove o nó duplicado da subárvore à direita.
                raiz->dir = remover_disciplina(raiz->dir, temp->codigo);
            }
        }

        // 11. Atualiza a altura do nó raiz após a remoção, se a raiz ainda existir.
        if (raiz != NULL)
        {
            raiz->altura = maior_no_disc(altura_do_no_disc(raiz->esq), altura_do_no_disc(raiz->dir)) + 1;

            // 12. Balanceia a árvore após a remoção.
            raiz = balencar_arvore_disc(raiz);
        }
    }

    // 13. Retorna a raiz da árvore (que pode ter mudado).
    return raiz;
}

void imprimir_disciplinas(arvore_disciplinas *raiz)
{
    if (raiz != NULL)
    {
        imprimir_disciplinas(raiz->esq);
        printf("Codigo: %d\n", raiz->codigo);
        printf("Nome: %s\n", raiz->nome);
        printf("\n");
        imprimir_disciplinas(raiz->dir);
    }
}

void liberar_disciplinas(arvore_disciplinas *raiz)
{
    if (raiz != NULL)
    {
        liberar_disciplinas(raiz->esq);
        liberar_disciplinas(raiz->dir);
        free(raiz);
    }
}
void imprimir_disciplinas_periodo(arvore_disciplinas *raiz, int periodo)
{
    if (raiz != NULL)
    {
        imprimir_disciplinas_periodo(raiz->esq, periodo);
        if (raiz->periodo == periodo)
        {
            printf("Codigo: %d\n", raiz->codigo);
            printf("Nome: %s\n", raiz->nome);
            printf("\n");
        }
        imprimir_disciplinas_periodo(raiz->dir, periodo);
    }
}

void imprimir_historico_disciplinas(arvore_notas *raiz_notas, arvore_disciplinas *raiz_disciplinas)
{
    if (raiz_disciplinas != NULL)
    {

        arvore_notas *nota = buscar_notas(raiz_notas, raiz_disciplinas->codigo);
        if (nota != NULL)
        {
            printf("Disciplina: %s\n", raiz_disciplinas->nome);
            printf("Nota: %.2f\n", nota->nota_final);
            printf("Semestre cursado: %s\n", nota->semestre_cursado);
            printf("Carga horaria: %d\n", raiz_disciplinas->carga_horaria);
            printf("Periodo: %d\n", raiz_disciplinas->periodo);
            printf("\n");
        }

        imprimir_historico_disciplinas(raiz_notas, raiz_disciplinas->esq);

        imprimir_historico_disciplinas(raiz_notas, raiz_disciplinas->dir);
    }
}