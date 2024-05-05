#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char* geradorStrings(int tam, int itr) {
	char *texto;
	int tipo[2] = {65, 97};
	int i;
	texto = (char*) malloc(sizeof(char) * tam);
	srand(time(NULL) + itr);
	for(i = 0; i < tam - 1; i++)
		texto[i] = (char) (rand() % 26 + tipo[rand() % 2]);
	texto[i] = '\0';
	return texto;
}


int main(){
    FILE *arq;
    char *str;

    arq = fopen("arquivo.txt", "w");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    for(int i = 0; i < 2000000; i++){
        str = geradorStrings(10, i);
        fprintf(arq, "%s\n", str);
        free(str);
    }
fclose(arq);

}