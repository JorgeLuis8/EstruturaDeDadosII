#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "podcast.c"     // Supondo que "podcast.h" contenha as definições das estruturas e funções
#include "temas.c"       // Supondo que "temas.h" contenha as definições das estruturas e funções
#include "entrevistas.c" // Supondo que "entrevistas.h" contenha as definições das estruturas e funções
#include "plataforma.c"  // Supondo que "plataforma.h" contenha as definições das estruturas e funções

int main()
{
    Arvore_podCast *raiz_podcasts = NULL;
    Arvore_temas *raiz_temas = NULL;
    Plataforma *lista_plataformas = NULL;
    int escolha;

    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir podcast\n");
        printf("2. Remover podcast\n");
        printf("3. Adicionar um novo tema\n");
        printf("4. Remover um tema\n");
        printf("5. Adicionar uma nova entrevista\n");
        printf("6. Remover uma entrevista\n");
        printf("7. Inserir uma nova plataforma\n");
        printf("8. Remover uma plataforma\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            printf("Inserir um novo podcast:\n");
            Arvore_podCast *novo_podcast = criar_arvore_podCast();
            ler_dados_podcast(novo_podcast);
            raiz_podcasts = inserir_podcast(raiz_podcasts, novo_podcast);
            printf("Podcast '%s' inserido com sucesso.\n", novo_podcast->nome);
            break;
        case 2:
            printf("Digite o nome do podcast que deseja remover: ");
            char nome_podcast_remover[50];
            scanf(" %[^\n]", nome_podcast_remover);
            raiz_podcasts = remover_podcast(raiz_podcasts, nome_podcast_remover);
            printf("Podcast '%s' removido com sucesso.\n", nome_podcast_remover);
            break;
        case 3:
            printf("Adicionar um novo tema:\n");
            printf("Digite o nome do podcast: ");
            char nome_podcast_tema[50];
            scanf(" %[^\n]", nome_podcast_tema);
            Arvore_podCast *podcast_encontrado = Busca_arv_podcast(raiz_podcasts, nome_podcast_tema);
            if (podcast_encontrado != NULL)
            {
                Arvore_temas *novo_tema = criar_arvore_temas();
                lerDados(novo_tema);
                podcast_encontrado->raiz_temas = inserir_temas(podcast_encontrado->raiz_temas, novo_tema);
                printf("Tema '%s' adicionado ao podcast '%s' com sucesso.\n", novo_tema->tema, nome_podcast_tema);
            }
            else
            {
                printf("Podcast '%s' nao encontrado.\n", nome_podcast_tema);
            }
            break;
        case 4:
            printf("Digite o nome do podcast do qual deseja remover um tema: ");
            char nome_podcast_remover_tema[50];
            scanf(" %[^\n]", nome_podcast_remover_tema);
            Arvore_podCast *podcast_encontrado_remover_tema = Busca_arv_podcast(raiz_podcasts, nome_podcast_remover_tema);
            if (podcast_encontrado_remover_tema != NULL)
            {
                printf("Digite o tema que deseja remover do podcast '%s': ", nome_podcast_remover_tema);
                char tema_remover[50];
                scanf(" %[^\n]", tema_remover);
                Arvore_temas *tema_encontrado_remover_tema = Busca_arv(podcast_encontrado_remover_tema->raiz_temas, tema_remover);
                if (tema_encontrado_remover_tema != NULL)
                {
                    podcast_encontrado_remover_tema->raiz_temas = remover_tema(podcast_encontrado_remover_tema->raiz_temas, tema_remover);
                    printf("Tema '%s' removido do podcast '%s' com sucesso.\n", tema_remover, nome_podcast_remover_tema);
                }
                else
                {
                    printf("Tema '%s' nao encontrado no podcast '%s'.\n", tema_remover, nome_podcast_remover_tema);
                }
            }
            else
            {
                printf("Podcast '%s' nao encontrado.\n", nome_podcast_remover_tema);
            }
            break;
        case 5:
            printf("Adicionar uma nova entrevista:\n");
            printf("Adicionar uma nova entrevista a um tema de um podcast:\n");
            printf("Digite o nome do podcast: ");
            char nome_podcast_entrevista[50];
            scanf(" %[^\n]", nome_podcast_entrevista); // Ler o nome do podcast

            // Buscar o podcast na árvore de podcasts
            Arvore_podCast *podcast_entrevista = Busca_arv_podcast(raiz_podcasts, nome_podcast_entrevista);
            if (podcast_entrevista != NULL)
            {
                printf("Digite o nome do tema: ");
                char nome_tema_entrevista[50];
                scanf(" %[^\n]", nome_tema_entrevista); // Ler o nome do tema

                // Buscar o tema na árvore de temas do podcast
                Arvore_temas *tema_entrevista = Busca_arv(podcast_entrevista->raiz_temas, nome_tema_entrevista);
                if (tema_entrevista != NULL)
                {
                    // Criar uma nova entrevista
                    Arvore_entrevistas *nova_entrevista = criar_arvore_entrevistas();
                    Ler_dados_de_insercao_entrevistas(nova_entrevista);
                    // Associar a nova entrevista ao tema encontrado
                    tema_entrevista->entrevistas = inserir_entrevistas(tema_entrevista->entrevistas, nova_entrevista);
                    printf("Entrevista adicionada ao tema '%s' do podcast '%s' com sucesso.\n", nome_tema_entrevista, nome_podcast_entrevista);
                }
                else
                {
                    printf("Tema '%s' nao encontrado no podcast '%s'.\n", nome_tema_entrevista, nome_podcast_entrevista);
                }
            }
            else
            {
                printf("Podcast '%s' nao encontrado.\n", nome_podcast_entrevista);
            }
            break;
        case 6:
            printf("Remover uma entrevista:\n");
            printf("Digite o nome do podcast do qual deseja remover uma entrevista: ");
            char nome_podcast_remover_entrevista[50];
            scanf(" %[^\n]", nome_podcast_remover_entrevista); // Ler o nome do podcast

            // Buscar o podcast na árvore de podcasts
            Arvore_podCast *podcast_remover_entrevista = Busca_arv_podcast(raiz_podcasts, nome_podcast_remover_entrevista);
            if (podcast_remover_entrevista != NULL)
            {
                printf("Digite o nome do tema: ");
                char nome_tema_remover_entrevista[50];
                scanf(" %[^\n]", nome_tema_remover_entrevista); // Ler o nome do tema

                // Buscar o tema na árvore de temas do podcast
                Arvore_temas *tema_remover_entrevista = Busca_arv(podcast_remover_entrevista->raiz_temas, nome_tema_remover_entrevista);
                if (tema_remover_entrevista != NULL)
                {
                    printf("Digite o titulo da entrevista que deseja remover: ");
                    char titulo_entrevista_remover[100];
                    scanf(" %[^\n]", titulo_entrevista_remover); // Ler o título da entrevista

                    // Remover a entrevista do tema encontrado
                    tema_remover_entrevista->entrevistas = remover_entrevista(tema_remover_entrevista->entrevistas, titulo_entrevista_remover);
                    printf("Entrevista '%s' removida do tema '%s' do podcast '%s' com sucesso.\n", titulo_entrevista_remover, nome_tema_remover_entrevista, nome_podcast_remover_entrevista);
                }
                else
                {
                    printf("Tema '%s' nao encontrado no podcast '%s'.\n", nome_tema_remover_entrevista, nome_podcast_remover_entrevista);
                }
            }
            else
            {
                printf("Podcast '%s' nao encontrado.\n", nome_podcast_remover_entrevista);
            }
            break;
        case 7:
            printf("Inserir uma nova plataforma:\n");
            // Implemente aqui a lógica para inserir uma nova plataforma
            break;
        case 8:
            printf("Remover uma plataforma:\n");
            // Implemente aqui a lógica para remover uma plataforma
            break;
        default:
            printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
            break;
        }
    } while (escolha != 0);

    return 0;
}
