
#include "temas.c"
#include "entrevistas.c"
#include "podcast.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
    Arvore_temas *raiz_temas = NULL;
    Arvore_podCast *raiz_podcast = NULL;
 
    int escolha;
    char tema[50];
    char titulo_entrevista[100];
    char nome_podcast[50];
 
    do
    {
        printf("\n====== Menu ======\n");
        printf("1. Inserir tema\n");
        printf("2. Inserir entrevista\n");
        printf("3. Imprimir \n");
        printf("4. Excluir Entrevista\n");
        printf("5. Excluir Tema\n");
        printf("6. Inserir Podcast\n");
        printf("7. Imprimir Podcast\n");
        printf("8. Excluir Podcast\n");
        printf("0. Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        getchar();
 
        switch (escolha)
        {
       case 1:
            
            printf("Digite o nome do podcast onde deseja inserir o tema: ");
            fgets(nome_podcast, sizeof(nome_podcast), stdin);
            nome_podcast[strcspn(nome_podcast, "\n")] = 0;
            Arvore_podCast *podcast_encontrado = Busca_arv_podcast(raiz_podcast, nome_podcast);
            if (podcast_encontrado != NULL)
            {
                printf("Digite o tema: ");
                fgets(tema, sizeof(tema), stdin);
                tema[strcspn(tema, "\n")] = 0;
                Arvore_temas *novo_tema = criar_arvore_temas();
                strcpy(novo_tema->tema, tema);
                podcast_encontrado->raiz_temas = inserir_temas(podcast_encontrado->raiz_temas, novo_tema);
                printf("Tema '%s' inserido no podcast '%s' com sucesso.\n", tema, nome_podcast);
            }
            else
            {
                printf("Podcast '%s' não encontrado.\n", nome_podcast);
            }
            break;
        case 2:
            printf("Digite o tema relacionado a entrevista: ");
            fgets(tema, sizeof(tema), stdin);
            tema[strcspn(tema, "\n")] = 0;
            Arvore_temas *tema_encontrado = Busca_arv(raiz_temas, tema);
            if (tema_encontrado != NULL)
            {
                Arvore_entrevistas *nova_entrevista = criar_arvore_entrevistas();
                Ler_dados_de_insercao_entrevistas(nova_entrevista);
                tema_encontrado->entrevistas = inserir_entrevistas(tema_encontrado->entrevistas, nova_entrevista);
                printf("Entrevista relacionada ao tema '%s' adicionada com sucesso.\n", tema);
            }
            else
            {
                printf("Tema '%s' nao encontrado.\n", tema);
            }
            break;
        case 3:
        {
            printf("Informe o tema: ");
            fgets(tema, sizeof(tema), stdin);
            tema[strcspn(tema, "\n")] = 0;
            if (raiz_temas != NULL)
            {
                imprimir_entrevistas_tema(raiz_temas, tema);
            }
            else
            {
                printf("A arvore de temas esta vazia.\n");
            }
            break;
        }
        case 4:
        {
            printf("Digite o tema relacionado a entrevista que deseja remover: ");
            fgets(tema, sizeof(tema), stdin);
            tema[strcspn(tema, "\n")] = 0;
            Arvore_temas *tema_encontrado = Busca_arv(raiz_temas, tema);
            if (tema_encontrado != NULL)
            {
                printf("Digite o titulo da entrevista que deseja remover: ");
                fgets(titulo_entrevista, sizeof(titulo_entrevista), stdin);
                titulo_entrevista[strcspn(titulo_entrevista, "\n")] = 0;
                tema_encontrado->entrevistas = remover_entrevista(tema_encontrado->entrevistas, titulo_entrevista);
                printf("Entrevista removida com sucesso.\n");
            }
 
            else
            {
                printf("Tema '%s' não encontrado.\n", tema);
            }
            break;
        }
        case 5:
        {
            printf("Digite o tema que deseja remover: ");
            fgets(tema, sizeof(tema), stdin);
            tema[strcspn(tema, "\n")] = 0;
            //Conferir se o tema tem entrevistas associadas
            Arvore_temas *tema_encontrado = Busca_arv(raiz_temas, tema);
            if (tema_encontrado != NULL)
            {
                if (tema_encontrado->entrevistas != NULL)
                {
                    printf("O tema '%s' possui entrevistas associadas. Remova as entrevistas antes de remover o tema.\n", tema);
                }
                else
                {
                    raiz_temas = remover_tema(raiz_temas, tema);
                    printf("Tema removido com sucesso.\n");
                }
            }
            else
            {
                printf("Tema '%s' não encontrado.\n", tema);
            }
            break;
        }
        case 6:
        {
            
            Arvore_podCast *novo_podcast = criar_arvore_podCast();
            ler_dados_podcast(novo_podcast);
            raiz_podcast = inserir_podcast(raiz_podcast, novo_podcast);
            break;
            
        }
        case 7:
        {
            if (raiz_podcast != NULL)
            {
                char nome[50];
                printf("Digite o nome do podcast: ");
                scanf("%s", nome);
                //imprimir_podcast_tema(raiz_podcast, nome);
            }
            else
            {
                printf("A arvore de podcast esta vazia.\n");
            }
            break;
            
        }
        case 8:
        {
            
            printf("Digite o nome do podcast que deseja remover: ");
            fgets(titulo_entrevista, sizeof(titulo_entrevista), stdin);
            titulo_entrevista[strcspn(titulo_entrevista, "\n")] = 0;
            Arvore_podCast *podcast_encontrado = Busca_arv_podcast(raiz_podcast, titulo_entrevista);
            if (podcast_encontrado != NULL)
            {
                raiz_podcast = remover_podcast(raiz_podcast, titulo_entrevista);
                printf("Podcast removido com sucesso.\n");
            }
            else
            {
                printf("Podcast '%s' nao encontrado.\n", titulo_entrevista);
            }
            break;
            
        }

        case 0:
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Escolha invalida. Tente novamente.\n");
        }
    } while (escolha != 0);
 
    return 0;
}
