#include "musicas.h"
#include <stdlib.h>
#include <string.h>

struct musica{
    char* nome;
    char* artista;
};

typedef struct cel Cel;

struct playlist{
    Cel* prim;
    Cel* ult;
};

struct cel{
    Musica* music;
    Cel* ant;
    Cel* prox;
};

Musica* CriaMusica(char* nome, char* artista){
    Musica* m = malloc(sizeof(Musica));
    m->nome = strdup(nome);
    m->artista = strdup(artista);
    return m;
}

Playlist* CriaPlaylist(){
    Playlist* p = malloc(sizeof(Playlist));
    p->prim = p->ult = NULL;
    return p;
}

void InsereMusica(Playlist* p, Musica* m){
    Cel* c = malloc(sizeof(Cel));
    c->music = m;
    c->prox = NULL;
    c->ant = p->ult;

    if(p->prim == NULL){
        p->prim = c;
    }

    if(p->ult){
        p->ult->prox = c;
    }
    p->ult = c;
}

void RemoveMusica(Playlist* p, Musica* m){
    Cel* c = p->prim;
    while(c){
        if(c->music = m){
            break;
        }
        c = c->prox;
    }

    if(c == NULL){
        return;
    }

    if(c->ant == NULL){
        p->prim = c->prox;
    }
    if(c->prox == NULL){
        p->ult = c->ant;
    }

    if(c->ant){
        c->ant->prox = c->prox;
    }
    if(c->prox){
        c->prox->ant = c->ant;
    }

    free(c);
}

void LiberaPlaylist(Playlist* p){
    Cel* c, * aux = p->prim;
    while(aux){
        c = aux;
        aux = aux->prox;
        LiberaMusica(c->music);
        free(c);
    }
    free(p);
}

void LiberaMusica(Musica* m){
    free(m->nome);
    free(m->artista);
    free(m);
}

int ExisteEmPlaylist(Playlist* p, Musica* m){
    Cel* c = p->prim;
    while(c){
        if(c->music = m){
            return 1;
        }
        c = c->prox;
    }
    return 0;
}