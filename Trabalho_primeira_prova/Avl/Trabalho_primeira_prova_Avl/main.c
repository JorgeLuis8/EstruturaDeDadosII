#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "podcast.c"
#include "entrevistas.c"
#include "temas.c"
#include "plataforma.c"

int main()
{

    Plataforma *lista_plataformas = NULL;
    int escolha;

    do
    {
        printf("\nMenu:\n");
        printf("1. Adicionar Plataforma\n");
        printf("2. Adicionar Podcast\n");
        printf("3. Adicionar Tema\n");
        printf("4. Adicionar Entrevista\n");
        printf("5. Remover Entrevista\n");
        printf("6. Remover Tema\n");
        printf("7. Remover Podcast\n");
        printf("8. Remover Plataforma\n");
        printf("9. Mostrar todos os nomes dos Podcasts em ordem alfabetica de uma plataforma\n");
        printf("10. Mostrar todos os temas de um Podcast de uma plataforma\n");
        printf("11. Mostrar todos os ttulos das entrevistas de um tema de um Podcast de uma plataforma\n");
        printf("12. Mostrar todos os dados de uma entrevista de um Podcast de uma determinada plataforma, tema e titulo da entrevista\n");
        printf("13. Mostrar todos os entrevistados de um determinado tema de um Podcast de uma plataforma\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            printf("Inserir uma nova plataforma:\n");
            Plataforma *nova_plataforma = criar_plataforma();
            ler_dados_plataforma(nova_plataforma);
            lista_plataformas = inserir_plataforma(lista_plataformas, nova_plataforma);
            printf("Plataforma '%s' inserida com sucesso.\n", nova_plataforma->nome);
            break;
        case 2:
            printf("Inserir um novo podcast em uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma[50];
            scanf(" %[^\n]", nome_plataforma);

            Plataforma *plataforma_encontrada = buscar_plataforma(lista_plataformas, nome_plataforma);
            if (plataforma_encontrada != NULL)
            {
                printf("Inserir um novo podcast:\n");
                Arvore_podCast *novo_podcast = criar_arvore_podCast();
                ler_dados_podcast(novo_podcast);

                plataforma_encontrada->raiz_podcast = inserir_podcast(plataforma_encontrada->raiz_podcast, novo_podcast);

                printf("Podcast '%s' inserido na plataforma '%s' com sucesso.\n", novo_podcast->nome, nome_plataforma);
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma);
            }
            break;
        case 3:
            printf("Adicionar um novo tema a um podcast em uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_tema[50];
            scanf(" %[^\n]", nome_plataforma_tema); // Ler o nome da plataforma

            Plataforma *plataforma_encontrada_tema = buscar_plataforma(lista_plataformas, nome_plataforma_tema);
            if (plataforma_encontrada_tema != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_tema[50];
                scanf(" %[^\n]", nome_podcast_tema);

                Arvore_podCast *podcast_encontrado_tema = Busca_arv_podcast(plataforma_encontrada_tema->raiz_podcast, nome_podcast_tema);
                if (podcast_encontrado_tema != NULL)
                {

                    Arvore_temas *novo_tema = criar_arvore_temas();
                    lerDados(novo_tema);

                    podcast_encontrado_tema->raiz_temas = inserir_temas(podcast_encontrado_tema->raiz_temas, novo_tema);

                    printf("Tema '%s' adicionado ao podcast '%s' na plataforma '%s' com sucesso.\n", novo_tema->tema, nome_podcast_tema, nome_plataforma_tema);
                }
                else
                {
                    printf("Podcast '%s' nao encontrado na plataforma '%s'.\n", nome_podcast_tema, nome_plataforma_tema);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_tema);
            }
            break;

        case 4:
            printf("Adicionar uma nova entrevista a um tema de um podcast em uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_entrevista[50];
            scanf(" %[^\n]", nome_plataforma_entrevista);

            Plataforma *plataforma_entrevista = buscar_plataforma(lista_plataformas, nome_plataforma_entrevista);
            if (plataforma_entrevista != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_entrevista[50];
                scanf(" %[^\n]", nome_podcast_entrevista);

                Arvore_podCast *podcast_entrevista = Busca_arv_podcast(plataforma_entrevista->raiz_podcast, nome_podcast_entrevista);
                if (podcast_entrevista != NULL)
                {
                    printf("Digite o nome do tema: ");
                    char nome_tema_entrevista[50];
                    scanf(" %[^\n]", nome_tema_entrevista);

                    Arvore_temas *tema_entrevista = Busca_arv(podcast_entrevista->raiz_temas, nome_tema_entrevista);
                    if (tema_entrevista != NULL)
                    {
                        Arvore_entrevistas *nova_entrevista = criar_arvore_entrevistas();
                        Ler_dados_de_insercao_entrevistas(nova_entrevista);

                        tema_entrevista->entrevistas = inserir_entrevistas(tema_entrevista->entrevistas, nova_entrevista);
                        printf("Entrevista adicionada ao tema '%s' do podcast '%s' na plataforma '%s' com sucesso.\n", nome_tema_entrevista, nome_podcast_entrevista, nome_plataforma_entrevista);
                    }
                    else
                    {
                        printf("Tema '%s' nao encontrado no podcast '%s'.\n", nome_tema_entrevista, nome_podcast_entrevista);
                    }
                }
                else
                {
                    printf("Podcast '%s' nao encontrado na plataforma '%s'.\n", nome_podcast_entrevista, nome_plataforma_entrevista);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_entrevista);
            }
            break;

        case 5:
            printf("Remover uma entrevista de um tema de um podcast em uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_remover_entrevista[50];
            scanf(" %[^\n]", nome_plataforma_remover_entrevista);

            Plataforma *plataforma_remover_entrevista = buscar_plataforma(lista_plataformas, nome_plataforma_remover_entrevista);
            if (plataforma_remover_entrevista != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_remover_entrevista[50];
                scanf(" %[^\n]", nome_podcast_remover_entrevista);

                Arvore_podCast *podcast_remover_entrevista = Busca_arv_podcast(plataforma_remover_entrevista->raiz_podcast, nome_podcast_remover_entrevista);
                if (podcast_remover_entrevista != NULL)
                {
                    printf("Digite o nome do tema: ");
                    char nome_tema_remover_entrevista[50];
                    scanf(" %[^\n]", nome_tema_remover_entrevista);

                    Arvore_temas *tema_remover_entrevista = Busca_arv(podcast_remover_entrevista->raiz_temas, nome_tema_remover_entrevista);
                    if (tema_remover_entrevista != NULL)
                    {
                        printf("Digite o titulo da entrevista que deseja remover: ");
                        char titulo_entrevista_remover[100];
                        scanf(" %[^\n]", titulo_entrevista_remover);

                        if (tema_remover_entrevista->entrevistas != NULL)
                        {
                            printf("Removendo entrevista...\n");
                            tema_remover_entrevista->entrevistas = remover_entrevista(tema_remover_entrevista->entrevistas, titulo_entrevista_remover);
                            printf("Entrevista removida.\n");
                            printf("Entrevista '%s' removida do tema '%s' do podcast '%s' na plataforma '%s' com sucesso.\n", titulo_entrevista_remover, nome_tema_remover_entrevista, nome_podcast_remover_entrevista, nome_plataforma_remover_entrevista);
                        }
                        else
                        {
                            printf("Nenhuma entrevista encontrada no tema '%s' do podcast '%s' na plataforma '%s'.\n", nome_tema_remover_entrevista, nome_podcast_remover_entrevista, nome_plataforma_remover_entrevista);
                        }
                    }
                    else
                    {
                        printf("Tema '%s' nao encontrado no podcast '%s'.\n", nome_tema_remover_entrevista, nome_podcast_remover_entrevista);
                    }
                }
                else
                {
                    printf("Podcast '%s' nao encontrado na plataforma '%s'.\n", nome_podcast_remover_entrevista, nome_plataforma_remover_entrevista);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_remover_entrevista);
            }
            break;

        case 6:
            printf("Remover um tema de um podcast em uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_remover_tema[50];
            scanf(" %[^\n]", nome_plataforma_remover_tema);

            Plataforma *plataforma_remover_tema = buscar_plataforma(lista_plataformas, nome_plataforma_remover_tema);
            if (plataforma_remover_tema != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_remover_tema[50];
                scanf(" %[^\n]", nome_podcast_remover_tema);

                Arvore_podCast *podcast_remover_tema = Busca_arv_podcast(plataforma_remover_tema->raiz_podcast, nome_podcast_remover_tema);
                if (podcast_remover_tema != NULL)
                {
                    printf("Digite o nome do tema que deseja remover: ");
                    char nome_tema_remover[50];
                    scanf(" %[^\n]", nome_tema_remover);

                    Arvore_temas *tema_remover = Busca_arv(podcast_remover_tema->raiz_temas, nome_tema_remover);
                    if (tema_remover != NULL)
                    {
                        if (tema_remover->entrevistas != NULL)
                        {
                            printf("O tema '%s' possui entrevistas associadas e nao pode ser removido.\n", nome_tema_remover);
                        }
                        else
                        {
                            podcast_remover_tema->raiz_temas = remover_tema(podcast_remover_tema->raiz_temas, nome_tema_remover);
                            printf("Tema '%s' removido do podcast '%s' na plataforma '%s' com sucesso.\n", nome_tema_remover, nome_podcast_remover_tema, nome_plataforma_remover_tema);
                        }
                    }
                    else
                    {
                        printf("Tema '%s' nao encontrado no podcast '%s'.\n", nome_tema_remover, nome_podcast_remover_tema);
                    }
                }
                else
                {
                    printf("Podcast '%s' nao encontrado na plataforma '%s'.\n", nome_podcast_remover_tema, nome_plataforma_remover_tema);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_remover_tema);
            }
            break;

        case 7:
            printf("Remover um podcast de uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_remover_podcast[50];
            scanf(" %[^\n]", nome_plataforma_remover_podcast);

            Plataforma *plataforma_remover_podcast = buscar_plataforma(lista_plataformas, nome_plataforma_remover_podcast);
            if (plataforma_remover_podcast != NULL)
            {
                printf("Digite o nome do podcast que deseja remover: ");
                char nome_podcast_remover[50];
                scanf(" %[^\n]", nome_podcast_remover);

                Arvore_podCast *podcast_remover = Busca_arv_podcast(plataforma_remover_podcast->raiz_podcast, nome_podcast_remover);
                if (podcast_remover != NULL)
                {
                    if (podcast_remover->raiz_temas != NULL)
                    {
                        printf("Este podcast possui temas associados e não pode ser removido.\n");
                    }
                    else
                    {
                        plataforma_remover_podcast->raiz_podcast = remover_podcast(plataforma_remover_podcast->raiz_podcast, nome_podcast_remover);
                        printf("Podcast '%s' removido da plataforma '%s' com sucesso.\n", nome_podcast_remover, nome_plataforma_remover_podcast);
                    }
                }
                else
                {
                    printf("Podcast '%s' nao encontrado na plataforma '%s'.\n", nome_podcast_remover, nome_plataforma_remover_podcast);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_remover_podcast);
            }
            break;
        case 8:
            printf("Remover uma plataforma:\n");
            printf("Digite o nome da plataforma que deseja remover: ");
            char nome_plataforma_remover[50];
            scanf(" %[^\n]", nome_plataforma_remover);

            Plataforma *plataforma_remover = buscar_plataforma(lista_plataformas, nome_plataforma_remover);
            if (plataforma_remover != NULL)
            {
                if (plataforma_remover->raiz_podcast != NULL)
                {
                    printf("Esta plataforma possui podcasts associados e não pode ser removida.\n");
                }
                else
                {
                    lista_plataformas = remover_plataforma(lista_plataformas, nome_plataforma_remover);
                    printf("Plataforma '%s' removida com sucesso.\n", nome_plataforma_remover);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_remover);
            }
            break;

        case 9:
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_podcasts_ordem[50];
            scanf(" %[^\n]", nome_plataforma_podcasts_ordem);

            Plataforma *plataforma_podcasts_ordem = buscar_plataforma(lista_plataformas, nome_plataforma_podcasts_ordem);
            if (plataforma_podcasts_ordem != NULL)
            {
                printf("Nomes dos podcasts em ordem alfabetica:\n");
                imprimir_nomes_podcasts_em_ordem(plataforma_podcasts_ordem->raiz_podcast);
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_podcasts_ordem);
            }
            break;
        case 10:
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_temas[50];
            scanf(" %[^\n]", nome_plataforma_temas);

            Plataforma *plataforma_temas = buscar_plataforma(lista_plataformas, nome_plataforma_temas);
            if (plataforma_temas != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_temas[50];
                scanf(" %[^\n]", nome_podcast_temas);

                Arvore_podCast *podcast_temas = Busca_arv_podcast(plataforma_temas->raiz_podcast, nome_podcast_temas);
                if (podcast_temas != NULL && podcast_temas->raiz_temas != NULL)
                {
                    printf("Temas do podcast '%s' na plataforma '%s':\n", nome_podcast_temas, nome_plataforma_temas);
                    imprimir_temas(podcast_temas->raiz_temas);
                }
                else
                {
                    printf("Podcast '%s' nao encontrado ou sem temas na plataforma '%s'.\n", nome_podcast_temas, nome_plataforma_temas);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_temas);
            }
            break;
        case 11:
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_titulos[50];
            scanf(" %[^\n]", nome_plataforma_titulos);

            Plataforma *plataforma_titulos = buscar_plataforma(lista_plataformas, nome_plataforma_titulos);
            if (plataforma_titulos != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_titulos[50];
                scanf(" %[^\n]", nome_podcast_titulos);

                Arvore_podCast *podcast_titulos = Busca_arv_podcast(plataforma_titulos->raiz_podcast, nome_podcast_titulos);
                if (podcast_titulos != NULL)
                {
                    printf("Digite o nome do tema: ");
                    char nome_tema_titulos[50];
                    scanf(" %[^\n]", nome_tema_titulos);

                    Arvore_temas *tema_titulos = Busca_arv(podcast_titulos->raiz_temas, nome_tema_titulos);
                    if (tema_titulos != NULL && tema_titulos->entrevistas != NULL)
                    {
                        printf("Titulos das entrevistas do tema '%s' do podcast '%s' na plataforma '%s':\n", nome_tema_titulos, nome_podcast_titulos, nome_plataforma_titulos);
                        imprimir_titulos_entrevistas(tema_titulos->entrevistas);
                    }
                    else
                    {
                        printf("Tema '%s' nao encontrado ou sem entrevistas no podcast '%s'.\n", nome_tema_titulos, nome_podcast_titulos);
                    }
                }
                else
                {
                    printf("Podcast '%s' nao encontrado na plataforma '%s'.\n", nome_podcast_titulos, nome_plataforma_titulos);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_titulos);
            }
            break;

        case 12:
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_entrevista_dados[50];
            scanf(" %[^\n]", nome_plataforma_entrevista_dados);

            Plataforma *plataforma_entrevista_dados = buscar_plataforma(lista_plataformas, nome_plataforma_entrevista_dados);
            if (plataforma_entrevista_dados != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_entrevista_dados[50];
                scanf(" %[^\n]", nome_podcast_entrevista_dados);

                Arvore_podCast *podcast_entrevista_dados = Busca_arv_podcast(plataforma_entrevista_dados->raiz_podcast, nome_podcast_entrevista_dados);
                if (podcast_entrevista_dados != NULL)
                {
                    printf("Digite o nome do tema: ");
                    char nome_tema_entrevista_dados[50];
                    scanf(" %[^\n]", nome_tema_entrevista_dados);

                    Arvore_temas *tema_entrevista_dados = Busca_arv(podcast_entrevista_dados->raiz_temas, nome_tema_entrevista_dados);
                    if (tema_entrevista_dados != NULL)
                    {
                        printf("Digite o titulo da entrevista: ");
                        char titulo_entrevista_dados[100];
                        scanf(" %[^\n]", titulo_entrevista_dados);

                        Arvore_entrevistas *entrevista_dados = buscar_entrevistas(tema_entrevista_dados->entrevistas, titulo_entrevista_dados);
                        if (entrevista_dados != NULL)
                        {
                            printf("Dados da entrevista:\n");
                            printf("Titulo: %s\n", entrevista_dados->titulos);
                            printf("Convidado: %s\n", entrevista_dados->nome_convidado);
                            printf("Data: %s\n", entrevista_dados->data);
                            printf("Duracao: %d minutos\n", entrevista_dados->duracao);
                            printf("Especialidade: %s\n", entrevista_dados->especialidade_convidado);
                        }
                        else
                        {
                            printf("Entrevista '%s' nao encontrada no tema '%s' do podcast '%s'.\n", titulo_entrevista_dados, nome_tema_entrevista_dados, nome_podcast_entrevista_dados);
                        }
                    }
                    else
                    {
                        printf("Tema '%s' nao encontrado no podcast '%s'.\n", nome_tema_entrevista_dados, nome_podcast_entrevista_dados);
                    }
                }
                else
                {
                    printf("Podcast '%s' nao encontrado na plataforma '%s'.\n", nome_podcast_entrevista_dados, nome_plataforma_entrevista_dados);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_entrevista_dados);
            }
            break;

        case 13:
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_entrevistados[50];
            scanf(" %[^\n]", nome_plataforma_entrevistados);

            Plataforma *plataforma_entrevistados = buscar_plataforma(lista_plataformas, nome_plataforma_entrevistados);
            if (plataforma_entrevistados != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_entrevistados[50];
                scanf(" %[^\n]", nome_podcast_entrevistados);

                Arvore_podCast *podcast_entrevistados = Busca_arv_podcast(plataforma_entrevistados->raiz_podcast, nome_podcast_entrevistados);
                if (podcast_entrevistados != NULL)
                {
                    printf("Digite o nome do tema: ");
                    char nome_tema_entrevistados[50];
                    scanf(" %[^\n]", nome_tema_entrevistados);

                    Arvore_temas *tema_entrevistados = Busca_arv(podcast_entrevistados->raiz_temas, nome_tema_entrevistados);
                    if (tema_entrevistados != NULL && tema_entrevistados->entrevistas != NULL)
                    {
                        printf("Entrevistados do tema '%s' do podcast '%s' na plataforma '%s':\n", nome_tema_entrevistados, nome_podcast_entrevistados, nome_plataforma_entrevistados);
                        imprimir_entrevistados(tema_entrevistados->entrevistas);
                    }
                    else
                    {
                        printf("Tema '%s' nao encontrado ou sem entrevistas no podcast '%s'.\n", nome_tema_entrevistados, nome_podcast_entrevistados);
                    }
                }
                else
                {
                    printf("Podcast '%s' nao encontrado na plataforma '%s'.\n", nome_podcast_entrevistados, nome_plataforma_entrevistados);
                }
            }
            else
            {
                printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_entrevistados);
            }
            break;

        default:
            printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
            break;
        }
    } while (escolha != 0);

    return 0;
}