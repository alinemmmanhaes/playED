#include <stdlib.h>
#include <string.h>
#include "playlists.h"
#include "pessoas.h"

int main(int argc, char *argv[]) {
    FILE *arqAmizades, *arqPlaylist;
    char diretorio[100];
    char nomeArquivo[1000];

    //cria diretório e abre o primeiro arquivo "amizades.txt"
	sprintf(diretorio, "Entrada");

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
    while(fscanf(arqAmizades, "%[^;];%[^\n]%*c", nome, nome2) == 2){
        RelacionaAmigos(nome, nome2, listaPessoas);
    }

    sprintf(nomeArquivo, "%s/playlists.txt", diretorio);
    arqPlaylist = fopen(nomeArquivo, "r");

    if (arqPlaylist == NULL) {
        printf("O arquivo playlists.txt do diretorio %s nao existe!\n", diretorio);
        exit(1);
    }

    char nomePlaylist[100];
    int qtdPlaylist;
    //Lê as playlist de cada pessoa e adiciona à sua respectiva lista de playlists
    while(fscanf(arqPlaylist, "%[^;];%d;", nome, &qtdPlaylist) == 2){
        
        for(int i = 0; i < qtdPlaylist; i++){
            fscanf(arqPlaylist, "%[^;\n]%*c", nomePlaylist);
            
            Playlist *pl = CriaPlaylist(nomePlaylist);

            InserePLNaPessoa(nome, listaPessoas, pl);
        }
    }

    LeArquivosDePlaylist(listaPessoas, diretorio);

    OrganizaPessoaPorArtista(listaPessoas);
    GeraPlayedRefatorada(listaPessoas);

    VerificaSimilaridades(listaPessoas);

    CriaNovosArquivosPessoa(listaPessoas);

    LiberaListPessoas(listaPessoas, ListaGeral);
    fclose(arqAmizades);
    fclose(arqPlaylist);

    return 0;
}