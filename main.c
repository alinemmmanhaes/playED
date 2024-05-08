#include <stdlib.h>
#include <string.h>
#include "playlists.h"
#include "pessoas.h"

int main(int argc, char *argv[]) {
    FILE *arqAmizades;
    char diretorio[1000];
    char amizades[1000];

	sprintf(diretorio, "%s", argv[1]);

    sprintf(amizades, "%s/amizades.txt", diretorio);
    arqAmizades = fopen(amizades, "r");

    if (arqAmizades == NULL) {
        printf("O arquivo amizades.txt do diretorio %s nao existe!\n", diretorio);
        exit(1);
    }

    Lista *listaPessoas = CriaAmigos();

    char nome[100];
    while(fscanf(amizades, "%[^;\n]", nome) == 1){
        Pessoa* p = CriaPessoa(nome);
        InsereAmigo(listaPessoas, p);
        //como fazer pra sair do loop qnd terminar de ler a 1 linha do arquivo?
    }


    return 0;
}