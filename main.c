#include <stdlib.h>
#include <string.h>
#include "playlists.h"
#include "pessoas.h"

int main(int argc, char *argv[]) {
    FILE *arqAmizades;
    char diretorio[1000];
    char amizades[1000];

    //cria diretório e abre o primeiro arquivo "amizades.txt"
	sprintf(diretorio, "%s", argv[1]);

    sprintf(amizades, "%s/amizades.txt", diretorio);
    arqAmizades = fopen(amizades, "r");

    if (arqAmizades == NULL) {
        printf("O arquivo amizades.txt do diretorio %s nao existe!\n", diretorio);
        exit(1);
    }

    //cria lista das pessoas da PlayED
    Lista *listaPessoas = CriaListPessoas();

    char nome[100], caractere;
    //le todas as pessoas e adiciona elas na lista de pessoas
    while(fscanf(amizades, "%[^;\n]%c", nome, caractere) == 2){
        Pessoa* p = CriaPessoa(nome);
        InserePessoa(listaPessoas, p);
        if(caractere == '\n'){
            break;
        }
    }

    char nome1[100], nome2[100];
    //le todas as amizades e correlaciona as pessoas envolvidas
    while(fscanf(amizades, "%s;%s%*c", nome1, nome2) == 2){
        RelacionaAmigos(nome1, nome2, listaPessoas);
    }


    LiberaListPessoas(listaPessoas, ListaGeral);

    return 0;
}