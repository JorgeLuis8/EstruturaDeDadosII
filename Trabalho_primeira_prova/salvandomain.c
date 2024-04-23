#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "podcast.c"     // Supondo que "podcast.h" contenha as definições das estruturas e funções
#include "entrevistas.c" // Supondo que "entrevistas.h" contenha as definições das estruturas e funções
#include "temas.c"       // Supondo que "temas.h" contenha as definições das estruturas e funções
#include "plataforma.c"  // Supondo que "plataforma.h" contenha as definições das estruturas e funções
int main()
{
    Plataforma *lista_plataformas = NULL;
    int escolha;

    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir podcast\n");
        printf("2. Adicionar um tema\n");
        printf("3. Remover podcast\n");
        printf("4. Remover tema\n");
        printf("5. Adicionar entrevista\n");
        printf("6. Remover entrevista\n");
        printf("7. Inserir uma nova plataforma\n");
        printf("8. Remover uma plataforma\n");
        printf("9. Mostrar todos os nomes dos podcasts em ordem alfabetica de uma plataforma\n");
        printf("10. Mostrar todos os temas de um podcast de uma plataforma\n");
        printf("11. Mostrar todos os titulos das entrevistas de um tema de um podcast de uma plataforma\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
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
        case 2:
            printf("Adicionar um novo tema a um podcast em uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_tema[50];
            scanf(" %[^\n]", nome_plataforma_tema); // Ler o nome da plataforma

            // Buscar a plataforma na lista de plataformas
            Plataforma *plataforma_encontrada_tema = buscar_plataforma(lista_plataformas, nome_plataforma_tema);
            if (plataforma_encontrada_tema != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_tema[50];
                scanf(" %[^\n]", nome_podcast_tema); // Ler o nome do podcast

                // Buscar o podcast dentro da plataforma
                Arvore_podCast *podcast_encontrado_tema = Busca_arv_podcast(plataforma_encontrada_tema->raiz_podcast, nome_podcast_tema);
                if (podcast_encontrado_tema != NULL)
                {
                    // Criar um novo nó de tema
                    Arvore_temas *novo_tema = criar_arvore_temas();
                    lerDados(novo_tema);

                    // Inserir o tema na árvore de temas do podcast encontrado
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
        case 3:
            printf("Remover um podcast de uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_remover_podcast[50];
            scanf(" %[^\n]", nome_plataforma_remover_podcast);

            // Buscar a plataforma na lista de plataformas
            Plataforma *plataforma_remover_podcast = buscar_plataforma(lista_plataformas, nome_plataforma_remover_podcast);
            if (plataforma_remover_podcast != NULL)
            {
                printf("Digite o nome do podcast que deseja remover: ");
                char nome_podcast_remover[50];
                scanf(" %[^\n]", nome_podcast_remover);

                // Verificar se o podcast existe na plataforma
                Arvore_podCast *podcast_remover = Busca_arv_podcast(plataforma_remover_podcast->raiz_podcast, nome_podcast_remover);
                if (podcast_remover != NULL)
                {
                    // Verificar se há temas associados a este podcast
                    if (podcast_remover->raiz_temas != NULL)
                    {
                        printf("Este podcast possui temas associados e não pode ser removido.\n");
                    }
                    else
                    {
                        // Remover o podcast da plataforma
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

        case 4:
            printf("Remover um tema de um podcast em uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_remover_tema[50];
            scanf(" %[^\n]", nome_plataforma_remover_tema);

            // Buscar a plataforma na lista de plataformas
            Plataforma *plataforma_remover_tema = buscar_plataforma(lista_plataformas, nome_plataforma_remover_tema);
            if (plataforma_remover_tema != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_remover_tema[50];
                scanf(" %[^\n]", nome_podcast_remover_tema);

                // Buscar o podcast dentro da plataforma
                Arvore_podCast *podcast_remover_tema = Busca_arv_podcast(plataforma_remover_tema->raiz_podcast, nome_podcast_remover_tema);
                if (podcast_remover_tema != NULL)
                {
                    printf("Digite o nome do tema que deseja remover: ");
                    char nome_tema_remover[50];
                    scanf(" %[^\n]", nome_tema_remover);

                    // Verificar se o tema existe na árvore de temas do podcast
                    Arvore_temas *tema_remover = Busca_arv(podcast_remover_tema->raiz_temas, nome_tema_remover);
                    if (tema_remover != NULL)
                    {
                        // Verificar se o tema possui entrevistas associadas
                        if (tema_remover->entrevistas != NULL)
                        {
                            printf("O tema '%s' possui entrevistas associadas e nao pode ser removido.\n", nome_tema_remover);
                        }
                        else
                        {
                            // Remover o tema do podcast encontrado
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

        case 5:
            printf("Adicionar uma nova entrevista a um tema de um podcast em uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_entrevista[50];
            scanf(" %[^\n]", nome_plataforma_entrevista);

            // Buscar a plataforma na lista de plataformas
            Plataforma *plataforma_entrevista = buscar_plataforma(lista_plataformas, nome_plataforma_entrevista);
            if (plataforma_entrevista != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_entrevista[50];
                scanf(" %[^\n]", nome_podcast_entrevista);

                // Buscar o podcast dentro da plataforma
                Arvore_podCast *podcast_entrevista = Busca_arv_podcast(plataforma_entrevista->raiz_podcast, nome_podcast_entrevista);
                if (podcast_entrevista != NULL)
                {
                    printf("Digite o nome do tema: ");
                    char nome_tema_entrevista[50];
                    scanf(" %[^\n]", nome_tema_entrevista);

                    // Buscar o tema na árvore de temas do podcast
                    Arvore_temas *tema_entrevista = Busca_arv(podcast_entrevista->raiz_temas, nome_tema_entrevista);
                    if (tema_entrevista != NULL)
                    {
                        // Criar uma nova entrevista
                        Arvore_entrevistas *nova_entrevista = criar_arvore_entrevistas();
                        Ler_dados_de_insercao_entrevistas(nova_entrevista);

                        // Inserir a nova entrevista na árvore de entrevistas do tema encontrado
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

        case 6:
            printf("Remover uma entrevista de um tema de um podcast em uma plataforma:\n");
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_remover_entrevista[50];
            scanf(" %[^\n]", nome_plataforma_remover_entrevista);

            // Buscar a plataforma na lista de plataformas
            Plataforma *plataforma_remover_entrevista = buscar_plataforma(lista_plataformas, nome_plataforma_remover_entrevista);
            if (plataforma_remover_entrevista != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_remover_entrevista[50];
                scanf(" %[^\n]", nome_podcast_remover_entrevista);

                // Buscar o podcast dentro da plataforma
                Arvore_podCast *podcast_remover_entrevista = Busca_arv_podcast(plataforma_remover_entrevista->raiz_podcast, nome_podcast_remover_entrevista);
                if (podcast_remover_entrevista != NULL)
                {
                    printf("Digite o nome do tema: ");
                    char nome_tema_remover_entrevista[50];
                    scanf(" %[^\n]", nome_tema_remover_entrevista);

                    // Buscar o tema na árvore de temas do podcast
                    Arvore_temas *tema_remover_entrevista = Busca_arv(podcast_remover_entrevista->raiz_temas, nome_tema_remover_entrevista);
                    if (tema_remover_entrevista != NULL)
                    {
                        printf("Digite o titulo da entrevista que deseja remover: ");
                        char titulo_entrevista_remover[100];
                        scanf(" %[^\n]", titulo_entrevista_remover);

                        // Remover a entrevista do tema encontrado
                        tema_remover_entrevista->entrevistas = remover_entrevista(tema_remover_entrevista->entrevistas, titulo_entrevista_remover);
                        printf("Entrevista '%s' removida do tema '%s' do podcast '%s' na plataforma '%s' com sucesso.\n", titulo_entrevista_remover, nome_tema_remover_entrevista, nome_podcast_remover_entrevista, nome_plataforma_remover_entrevista);
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

        case 7:
            printf("Inserir uma nova plataforma:\n");
            Plataforma *nova_plataforma = criar_plataforma();
            ler_dados_plataforma(nova_plataforma);
            lista_plataformas = inserir_plataforma(lista_plataformas, nova_plataforma);
            printf("Plataforma '%s' inserida com sucesso.\n", nova_plataforma->nome);
            break;

        case 8:
            printf("Remover uma plataforma:\n");
            printf("Digite o nome da plataforma que deseja remover: ");
            char nome_plataforma_remover[50];
            scanf(" %[^\n]", nome_plataforma_remover);

            // Buscar a plataforma na lista de plataformas
            Plataforma *plataforma_remover = buscar_plataforma(lista_plataformas, nome_plataforma_remover);
            if (plataforma_remover != NULL)
            {
                // Verificar se há podcasts associados a esta plataforma
                if (plataforma_remover->raiz_podcast != NULL)
                {
                    printf("Esta plataforma possui podcasts associados e não pode ser removida.\n");
                }
                else
                {
                    // Remover a plataforma da lista de plataformas
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
            // Caso para mostrar todos os nomes dos podcasts em ordem alfabética de uma plataforma
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_podcasts_ordem[50];
            scanf(" %[^\n]", nome_plataforma_podcasts_ordem);

            // Buscar a plataforma na lista de plataformas
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
            // Caso para mostrar todos os temas de um podcast de uma plataforma
            printf("Digite o nome da plataforma: ");
            char nome_plataforma_temas[50];
            scanf(" %[^\n]", nome_plataforma_temas);

            // Buscar a plataforma na lista de plataformas
            Plataforma *plataforma_temas = buscar_plataforma(lista_plataformas, nome_plataforma_temas);
            if (plataforma_temas != NULL)
            {
                printf("Digite o nome do podcast: ");
                char nome_podcast_temas[50];
                scanf(" %[^\n]", nome_podcast_temas);

                // Buscar o podcast dentro da plataforma
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
                // Caso para mostrar todos os títulos das entrevistas de um tema de um podcast de uma plataforma
                printf("Digite o nome da plataforma: ");
                char nome_plataforma_titulos[50];
                scanf(" %[^\n]", nome_plataforma_titulos);

                // Buscar a plataforma na lista de plataformas
                Plataforma *plataforma_titulos = buscar_plataforma(lista_plataformas, nome_plataforma_titulos);
                if (plataforma_titulos != NULL) {
                    printf("Digite o nome do podcast: ");
                    char nome_podcast_titulos[50];
                    scanf(" %[^\n]", nome_podcast_titulos);

                    // Buscar o podcast dentro da plataforma
                    Arvore_podCast *podcast_titulos = Busca_arv_podcast(plataforma_titulos->raiz_podcast, nome_podcast_titulos);
                    if (podcast_titulos != NULL) {
                        printf("Digite o nome do tema: ");
                        char nome_tema_titulos[50];
                        scanf(" %[^\n]", nome_tema_titulos);

                        // Buscar o tema na árvore de temas do podcast
                        Arvore_temas *tema_titulos = Busca_arv(podcast_titulos->raiz_temas, nome_tema_titulos);
                        if (tema_titulos != NULL && tema_titulos->entrevistas != NULL) {
                            printf("Títulos das entrevistas do tema '%s' do podcast '%s' na plataforma '%s':\n", nome_tema_titulos, nome_podcast_titulos, nome_plataforma_titulos);
                            imprimir_titulos_entrevistas(tema_titulos->entrevistas);
                        } else {
                            printf("Tema '%s' nao encontrado ou sem entrevistas no podcast '%s'.\n", nome_tema_titulos, nome_podcast_titulos);
                        }
                    } else {
                        printf("Podcast '%s' nao encontrado na plataforma '%s'.\n", nome_podcast_titulos, nome_plataforma_titulos);
                    }
                } else {
                    printf("Plataforma '%s' nao encontrada.\n", nome_plataforma_titulos);
                }
                break;
                
                
                
        default:
            printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
            break;
        }
    } while (escolha != 0);

    return 0;
}
