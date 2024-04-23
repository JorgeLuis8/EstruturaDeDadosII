#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "podcast.c" // Supondo que "podcast.h" contenha as definições das estruturas e funções
#include "entrevistas.c" // Supondo que "entrevistas.h" contenha as definições das estruturas e funções
#include "temas.c" // Supondo que "temas.h" contenha as definições das estruturas e funções

int main() {
    Arvore_podCast *raiz_podcasts = NULL;
    Arvore_temas *raiz_temas = NULL;

    int escolha;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir podcast\n");
        printf("2. Adicionar tema a um podcast\n");
        printf("3. Buscar temas por podcast\n");
        printf("4. Remover podcast\n");
        printf("5. Remover tema de um podcast\n");
        printf("6. Imprimir todos os podcasts\n");
        printf("7. Adicionar entrevista a um tema de um podcast\n");
        printf("8. Buscar entrevistas por tema\n");
        printf("9. Remover tema\n");
        printf("10. Remover entrevista de um tema\n");
        printf("11. Imprimir todos os temas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch(escolha) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                printf("Inserir um novo podcast:\n");
                // Criar um novo nó de podcast
                Arvore_podCast *novo_podcast = criar_arvore_podCast();
                ler_dados_podcast(novo_podcast);

                // Inserir o podcast na árvore de podcasts
                raiz_podcasts = inserir_podcast(raiz_podcasts, novo_podcast);

                printf("Podcast '%s' inserido com sucesso.\n", novo_podcast->nome);
                break;
            case 2:
                printf("Adicionar um novo tema a um podcast:\n");
                printf("Digite o nome do podcast: ");
                char nome_podcast_tema[50];
                scanf(" %[^\n]", nome_podcast_tema); // Ler o nome do podcast

                // Buscar o podcast na árvore de podcasts
                Arvore_podCast *podcast_encontrado = Busca_arv_podcast(raiz_podcasts, nome_podcast_tema);
                if (podcast_encontrado != NULL) {
                    // Criar um novo nó de tema
                    Arvore_temas *novo_tema = criar_arvore_temas();
                    lerDados(novo_tema);

                    // Inserir o tema na árvore de temas do podcast encontrado
                    podcast_encontrado->raiz_temas = inserir_temas(podcast_encontrado->raiz_temas, novo_tema);

                    printf("Tema '%s' adicionado ao podcast '%s' com sucesso.\n", novo_tema->tema, nome_podcast_tema);
                } else {
                    printf("Podcast '%s' nao encontrado.\n", nome_podcast_tema);
                }
                break;
            case 3:
                printf("Digite o nome do podcast para buscar temas: ");
                char nome_podcast_busca[50];
                scanf(" %[^\n]", nome_podcast_busca); // Ler o nome do podcast
                printf("Temas do podcast '%s':\n", nome_podcast_busca);
                // Buscar o podcast na árvore de podcasts e imprimir seus temas
                Arvore_podCast *podcast_encontrado_busca = Busca_arv_podcast(raiz_podcasts, nome_podcast_busca);
                if (podcast_encontrado_busca != NULL) {
                    imprimir_temas(podcast_encontrado_busca->raiz_temas);
                } else {
                    printf("Podcast '%s' nao encontrado.\n", nome_podcast_busca);
                }
                break;
            case 4:
                printf("Digite o nome do podcast que deseja remover: ");
                char nome_podcast_remover[50];
                scanf(" %[^\n]", nome_podcast_remover); // Ler o nome do podcast

                // Verificar se o podcast existe na árvore de podcasts
                Arvore_podCast *podcast_encontrado_remover = Busca_arv_podcast(raiz_podcasts, nome_podcast_remover);
                if (podcast_encontrado_remover != NULL) {
                    // Verificar se o podcast possui temas associados
                    if (podcast_encontrado_remover->raiz_temas != NULL) {
                        printf("O podcast '%s' possui temas associados e nao pode ser removido.\n", nome_podcast_remover);
                    } else {
                        // Remover o podcast, pois não há temas associados a ele
                        raiz_podcasts = remover_podcast(raiz_podcasts, nome_podcast_remover);
                        printf("Podcast '%s' removido com sucesso.\n", nome_podcast_remover);
                    }
                } else {
                    printf("Podcast '%s' nao encontrado.\n", nome_podcast_remover);
                }
                break;
            case 5:
                printf("Digite o nome do podcast do qual deseja remover um tema: ");
                char nome_podcast_remover_tema[50];
                scanf(" %[^\n]", nome_podcast_remover_tema); // Ler o nome do podcast

                // Buscar o podcast na árvore de podcasts
                Arvore_podCast *podcast_encontrado_remover_tema = Busca_arv_podcast(raiz_podcasts, nome_podcast_remover_tema);
                if (podcast_encontrado_remover_tema != NULL) {
                    printf("Digite o tema que deseja remover do podcast '%s': ", nome_podcast_remover_tema);
                    char tema_remover[50];
                    scanf(" %[^\n]", tema_remover); // Ler o tema

                    // Verificar se o tema possui entrevistas associadas
                    Arvore_temas *tema_encontrado_remover_tema = Busca_arv(podcast_encontrado_remover_tema->raiz_temas, tema_remover);
                    if (tema_encontrado_remover_tema != NULL) {
                        if (tema_encontrado_remover_tema->entrevistas != NULL) {
                            printf("O tema '%s' possui entrevistas associadas e nao pode ser removido.\n", tema_remover);
                        } else {
                            // Remover o tema do podcast encontrado
                            podcast_encontrado_remover_tema->raiz_temas = remover_tema(podcast_encontrado_remover_tema->raiz_temas, tema_remover);
                            printf("Tema '%s' removido do podcast '%s' com sucesso.\n", tema_remover, nome_podcast_remover_tema);
                        }
                    } else {
                        printf("Tema '%s' nao encontrado no podcast '%s'.\n", tema_remover, nome_podcast_remover_tema);
                    }
                } else {
                    printf("Podcast '%s' nao encontrado.\n", nome_podcast_remover_tema);
                }
                break;
            case 6:
                printf("Imprimindo todos os podcasts e seus temas:\n");
                //imprimir_podcasts_e_temas(raiz_podcasts);
                break;
            case 7:
                printf("Adicionar uma nova entrevista a um tema de um podcast:\n");
                printf("Digite o nome do podcast: ");
                char nome_podcast_entrevista[50];
                scanf(" %[^\n]", nome_podcast_entrevista); // Ler o nome do podcast

                // Buscar o podcast na árvore de podcasts
                Arvore_podCast *podcast_entrevista = Busca_arv_podcast(raiz_podcasts, nome_podcast_entrevista);
                if (podcast_entrevista != NULL) {
                    printf("Digite o nome do tema: ");
                    char nome_tema_entrevista[50];
                    scanf(" %[^\n]", nome_tema_entrevista); // Ler o nome do tema

                    // Buscar o tema na árvore de temas do podcast
                    Arvore_temas *tema_entrevista = Busca_arv(podcast_entrevista->raiz_temas, nome_tema_entrevista);
                    if (tema_entrevista != NULL) {
                        // Criar uma nova entrevista
                        Arvore_entrevistas *nova_entrevista = criar_arvore_entrevistas();
                        Ler_dados_de_insercao_entrevistas(nova_entrevista);
                        // Associar a nova entrevista ao tema encontrado
                        tema_entrevista->entrevistas = inserir_entrevistas(tema_entrevista->entrevistas, nova_entrevista);
                        printf("Entrevista adicionada ao tema '%s' do podcast '%s' com sucesso.\n", nome_tema_entrevista, nome_podcast_entrevista);
                    } else {
                        printf("Tema '%s' nao encontrado no podcast '%s'.\n", nome_tema_entrevista, nome_podcast_entrevista);
                    }
                } else {
                    printf("Podcast '%s' nao encontrado.\n", nome_podcast_entrevista);
                }
                break;
            case 8:
                printf("Digite o tema para buscar entrevistas: ");
                char tema_busca[50];
                scanf(" %[^\n]", tema_busca); // Ler o tema
                imprimir_entrevistas_tema(raiz_temas, tema_busca);
                break;
            case 9:
                printf("Digite o nome do podcast do qual deseja remover um tema: ");
                
                scanf(" %[^\n]", nome_podcast_remover_tema); // Ler o nome do podcast

                // Buscar o podcast na árvore de podcasts
                Arvore_podCast *podcast_remover_tema = Busca_arv_podcast(raiz_podcasts, nome_podcast_remover_tema);
                if (podcast_remover_tema != NULL) {
                    printf("Digite o nome do tema que deseja remover: ");
                    char nome_tema_remover[50];
                    scanf(" %[^\n]", nome_tema_remover); // Ler o nome do tema

                    // Buscar o tema na árvore de temas do podcast
                    Arvore_temas *tema_remover = Busca_arv(podcast_remover_tema->raiz_temas, nome_tema_remover);
                    if (tema_remover != NULL) {
                        // Verificar se o tema possui entrevistas associadas
                        if (tema_remover->entrevistas != NULL) {
                            printf("O tema '%s' possui entrevistas associadas e nao pode ser removido.\n", nome_tema_remover);
                        } else {
                            // Remover o tema do podcast
                            podcast_remover_tema->raiz_temas = remover_tema(podcast_remover_tema->raiz_temas, nome_tema_remover);
                            printf("Tema '%s' removido do podcast '%s' com sucesso.\n", nome_tema_remover, nome_podcast_remover_tema);
                        }
                    } else {
                        printf("Tema '%s' nao encontrado no podcast '%s'.\n", nome_tema_remover, nome_podcast_remover_tema);
                    }
                } else {
                    printf("Podcast '%s' nao encontrado.\n", nome_podcast_remover_tema);
                }
                break;
            case 10:
                printf("Digite o nome do podcast do qual deseja remover uma entrevista: ");
                char nome_podcast_remover_entrevista[50];
                scanf(" %[^\n]", nome_podcast_remover_entrevista); // Ler o nome do podcast

                // Buscar o podcast na árvore de podcasts
                Arvore_podCast *podcast_remover_entrevista = Busca_arv_podcast(raiz_podcasts, nome_podcast_remover_entrevista);
                if (podcast_remover_entrevista != NULL) {
                    printf("Digite o nome do tema: ");
                    char nome_tema_remover_entrevista[50];
                    scanf(" %[^\n]", nome_tema_remover_entrevista); // Ler o nome do tema

                    // Buscar o tema na árvore de temas do podcast
                    Arvore_temas *tema_remover_entrevista = Busca_arv(podcast_remover_entrevista->raiz_temas, nome_tema_remover_entrevista);
                    if (tema_remover_entrevista != NULL) {
                        printf("Digite o titulo da entrevista que deseja remover: ");
                        char titulo_entrevista_remover[100];
                        scanf(" %[^\n]", titulo_entrevista_remover); // Ler o título da entrevista

                        // Remover a entrevista do tema encontrado
                        tema_remover_entrevista->entrevistas = remover_entrevista(tema_remover_entrevista->entrevistas, titulo_entrevista_remover);
                        printf("Entrevista '%s' removida do tema '%s' do podcast '%s' com sucesso.\n", titulo_entrevista_remover, nome_tema_remover_entrevista, nome_podcast_remover_entrevista);
                    } else {
                        printf("Tema '%s' nao encontrado no podcast '%s'.\n", nome_tema_remover_entrevista, nome_podcast_remover_entrevista);
                    }
                } else {
                    printf("Podcast '%s' nao encontrado.\n", nome_podcast_remover_entrevista);
                }
                break;
            case 11:
                printf("Imprimindo todos os temas:\n");
                imprimir_temas(raiz_temas);
                break;
            default:
                printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
                break;
        }
    } while (escolha != 0);

    return 0;
}
