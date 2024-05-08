#include "playlists.h"
#include <stdlib.h>
#include <string.h>

typedef struct cel Cel;

struct listas{
    Cel* prim;
    Cel* ult;
};

struct cel{
    Playlist* playlist;
    Cel* ant;
    Cel* prox;
};

Listas* CriaLista(){
    Listas* l = malloc(sizeof(Listas));
    l->prim = l->ult = NULL;
    return l;
}

void InserePlaylist(Playlist* p, Listas* l){
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

void RemovePlaylist(Playlist* p, Listas* l){
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

void LiberaLista(Listas* l){
    Cel* c, * aux = l->prim;
    while(aux){
        c = aux;
        aux = aux->prox;
        LiberaPlaylist(c->playlist);
        free(c);
    }
    free(l);
}

int ExisteEmLista(Playlist* p, Listas* l){
    Cel* c = l->prim;
    while(c){
        if(c->playlist == p){
            return 1;
        }
        c = c->prox;
    }
    return 0;
}

