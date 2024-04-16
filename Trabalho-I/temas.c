#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temas.h"
#include "entrevistas.h"
struct notema{
	char Tema[100];
	struct notema* Esq;
	struct notema* Dir;
	struct raizEntrevista* entrevistas;
};

struct noraiz{
	struct notema* RaizTema;
};

/* Função para criar a árvore de temas. 
 * Aloca memória para um novo nó do tipo NoTema e inicializa os ponteiros da esquerda e direita como NULL.
 * Retorna o nó recém-criado.
 */
NoTema *cria_arvore_tema(){
	NoTema *a = (NoTema*)malloc(sizeof(NoTema));
	a->Esq = NULL;
	a->Dir = NULL;
	a->entrevistas = NULL;
	return a;

}
/* Função para ler os dados do tema.
 * Recebe um nó do tipo NoTema e lê o tema do usuário através do stdin.
 * O tema é armazenado no campo Tema do nó.
 */
void ler_dados(NoTema *no){
	printf("Digite o tema: ");
	fgets(no->Tema, sizeof(no->Tema), stdin);
}

/* Função para inserir um tema na árvore de temas. 
 * Recebe a raiz da árvore de temas, o nó a ser inserido e a raiz da árvore de entrevistas.
 * Se a raiz for NULL, o nó é inserido na raiz e a raiz da árvore de entrevistas é atribuída ao nó.
 * Caso contrário, verifica se o tema do nó é menor que o tema da raiz.
 * Se for menor, chama a função recursivamente para a esquerda.
 * Se for maior, chama a função recursivamente para a direita.
 */
void Inserir_Tema(NoTema *raiz, NoTema *no,RaizEntrevista *raizEntrevista){
	if(no->Esq == NULL){
		raiz = no;
		no->entrevistas = raizEntrevista;
	}
	else{
		if(strcmp(no->Tema, raiz->Tema) < 0){
			Inserir_Tema(raiz->Esq, no, raizEntrevista);
		}
		else{
			Inserir_Tema(raiz->Dir, no, raizEntrevista);
		}
	}
}

/* Função para buscar um tema na árvore de temas.
 * Recebe a raiz da árvore de temas e o tema a ser buscado.
 * Se a raiz for NULL, retorna NULL.
 * Se o tema da raiz for igual ao tema buscado, retorna a raiz.
 * Se o tema do nó for menor que o tema buscado, chama a função recursivamente para a esquerda.
 * Se o tema do nó for maior que o tema buscado, chama a função recursivamente para a direita.
 */
NoTema *Buscar_Tema(NoTema *raiz, char *tema){
	NoTema *achou = NULL;
	if (raiz != NULL){
		if(strcmp(raiz->Tema, tema) == 0){
			achou = raiz;
		}
		else if(strcmp(raiz->Tema, tema) < 0){
			achou = Buscar_Tema(raiz->Esq, tema);
		}
		else{
			achou = Buscar_Tema(raiz->Dir, tema);
		}
		return achou;
	}