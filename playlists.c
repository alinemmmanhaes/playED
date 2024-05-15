#include "playlists.h"
#include <stdlib.h>
#include <string.h>

typedef struct cel Cel;

struct listPL{
    Cel* prim;
    Cel* ult;
};

struct cel{
    Playlist* playlist;
    Cel* ant;
    Cel* prox;
};

ListPL* CriaListPL(){
    ListPL* l = malloc(sizeof(ListPL));
    l->prim = l->ult = NULL;
    return l;
}

void InserePlaylist(Playlist* p, ListPL* l){
    Cel* c = malloc(sizeof(Cel));
    c->playlist = p;
    c->prox = NULL;
    c->ant = l->ult;

    if(l->prim == NULL){
        l->prim = c;
    }
    if(l->ult){
        l->ult->prox = c;
    }
    l->ult = c;
}

void RemovePlaylist(Playlist* p, ListPL* l){
    Cel* c = l->prim;
    while(c){
        if(c->playlist == p){
            break;
        }
        c = c->prox;
    }

    if(c == NULL){
        return;
    }

    if(c->ant == NULL){
        l->prim = c->prox;
    }
    if(c->prox == NULL){
        l->ult = c->ant;
    }

    if(c->ant){
        c->ant->prox = c->prox;
    }
    if(c->prox){
        c->prox->ant = c->ant;
    }

    LiberaPlaylist(c->playlist);
    free(c);
}

void LiberaListPL(ListPL* l){
    Cel* c, * aux = l->prim;
    while(aux){
        c = aux;
        aux = aux->prox;
        LiberaPlaylist(c->playlist);
        free(c);
    }
    free(l);
}

int ExisteEmListPL(Playlist* p, ListPL* l){
    Cel* c = l->prim;
    while(c){
        if(c->playlist == p){
            return 1;
        }
        c = c->prox;
    }
    return 0;
}

int NumeroPlaylistsEmListPL(ListPL* l){
    Cel* cel = l->prim;
    int totalPL = 0;
    while(cel){
        totalPL++;
        cel = cel->prox;
    }
    return totalPL;
}

void InsereMusicasNasPLSDaPessoa(ListPL* l, char *diretorio){
    FILE *playlist;
    Cel* c = l->prim;
    char nomeArq[1000], artista[100], music[100];

    while(c){
        sprintf(nomeArq, "%s/%s", diretorio, RetornaNomePlaylist(c->playlist));
        playlist = fopen(nomeArq, "r");

        while(fscanf(playlist, "%[^-]- %[^\n]\n", artista, music) == 2){//acho que tá meio errado isso aqui
            Musica *musica = CriaMusica(music, artista);
            InsereMusica(c->playlist, musica);
        }
        
        fclose(playlist);
        c = c->prox;
    }
}

void OrganizaListPLPorArtista(ListPL* l){
    int totalPL = NumeroPlaylistsEmListPL(l);

    //Agora analisaremos apenas as playlists originais, sem acessar as novas com nome de artista
    Cel* cel = l->prim;
    for(int i=0; i < totalPL; i++){
        OrganizaPlaylistPorArtista(cel->playlist, l);
        cel = cel->prox;
    }

    //Removendo as playlist originais, depois de analisadas
    cel = l->prim;
    Cel* aux = cel;
    for(int i=0; i < totalPL; i++){
        cel = aux;
        aux = cel->prox;
        RemovePlaylist(cel->playlist, l);
    }
}

Playlist* ComparaNomePLArtista(char* nome, ListPL* lista){
    Cel* c = lista->prim;
    while(c){
        if(strcmp(nome, RetornaNomePlaylist(c->playlist)) == 0){
            return c->playlist;
        }
        c = c->prox;
    }
    return NULL;
}

void PLsPlayedRefatorada(ListPL* l, FILE* arq){
    //Contabiliza o número de playlists dentro da listPL e imprime no arquivo
    int totalPL = NumeroPlaylistsEmListPL(l);
    sprintf(arq, "%d;", totalPL);

    //imprime no arquivo o nome de cada playlist da lista
    Cel* cel = l->prim;
    while(cel){
        sprintf(arq, "%s", RetornaNomePlaylist(cel->playlist));
        cel = cel->prox;
    }
}

void CriaArquivosPlaylist(ListPL* l, char* diretorio){
    Cel* c = l->prim;
    while(c){
        char playlisttxt[1100];
        sprintf(playlisttxt, "%s/%s", diretorio, RetornaNomePlaylist(c->playlist));
        FILE* arq = fopen(playlisttxt, "w");

        ImprimePlaylistEmArquivo(c->playlist, arq);
        
        fclose(arq);
        c = c->prox;
    }
}