#include <stdlib.h>
#include <string.h>
#include "playlists.h"
#include "pessoas.h"

int main(int argc, char *argv[]) {
    FILE *arqAmizades, *arqPlaylist;
    char diretorio[1000];
    char nomeArquivo[1100];

    //cria diretório e abre o primeiro arquivo "amizades.txt"
	sprintf(diretorio, "%s", argv[1]);

    sprintf(nomeArquivo, "%s/amizades.txt", diretorio);
    arqAmizades = fopen(nomeArquivo, "r");

    if (arqAmizades == NULL) {
        printf("O arquivo amizades.txt do diretorio %s nao existe!\n", diretorio);
        exit(1);
    }

    //cria lista das pessoas da PlayED
    Lista *listaPessoas = CriaListPessoas();

    char nome[100], nome2[100], caractere;
    //le todas as pessoas e adiciona elas na lista de pessoas
    while(fscanf(arqAmizades, "%[^;\n]%c", nome, &caractere) == 2){
        Pessoa* p = CriaPessoa(nome);
        InserePessoa(listaPessoas, p);
        if(caractere == '\n'){
            break;
        }
    }

    //le todas as amizades e correlaciona as pessoas envolvidas
    while(fscanf(arqAmizades, "%s;%s%*c", nome, nome2) == 2){
        RelacionaAmigos(nome, nome2, listaPessoas);
    }

    sprintf(nomeArquivo, "%s/playlists.txt", diretorio);
    arqPlaylist = fopen(nomeArquivo, "r");

    char nomePlaylist[100];
    int qtdPlaylist;
    //Lê as playlist de cada pessoa e adiciona à sua respectiva lista de playlists
    while(fscanf(arqPlaylist, "%s;%d;", nome, &qtdPlaylist) == 2){
        
        for(int i = 0; i < qtdPlaylist; i++){
            fscanf(arqPlaylist, "%[^;\n]%*c", nomePlaylist);
            
            Playlist *pl = CriaPlaylist(nomePlaylist);

            InserePLNaPessoa(nome, listaPessoas, pl);
        }
    }

    LeArquivosDePlaylist(listaPessoas, diretorio);

    LiberaListPessoas(listaPessoas, ListaGeral);
    fclose(arqAmizades);
    fclose(arqPlaylist);

    return 0;
}