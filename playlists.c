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

void InsereMusicasNasPLSDaPessoa(ListPL* l, char *diretorio){
    FILE *playlist;
    Cel* c = l->prim;
    char nomeArq[1000], artista[100], music[100];

    while(c){
        sprintf(nomeArq, "%s/%s", diretorio, RetornaNomePlaylist(c->playlist));
        playlist = fopen(nomeArq, "r");

        while(fscanf(playlist, "%s - %s\n", artista, music) == 2){//acho que tá meio errado isso aqui
            Musica *musica = CriaMusica(music, artista);
            InsereMusica(c->playlist, musica);
        }
        
        fclose(playlist);
        c = c->prox;
    }
}
