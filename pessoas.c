#include "pessoas.h"
#include "playlists.h"
#include <stdlib.h>
#include <string.h>

struct pessoa{
    char* nome;
    Amigos* amigos;
    Listas* playlists;
};

typedef struct cel Cel;

struct amigos{
    Cel* prim;
    Cel* ult;
};

struct cel{
    Pessoa* pessoa;
    Cel* prox;
    Cel* ant;
};

Pessoa* CriaPessoa(char* nome){
    Pessoa* p = malloc(sizeof(Pessoa));
    p->nome = strdup(nome);
    p->amigos = CriaAmigos();
    p->playlists = CriaLista();
    return p;
}

Amigos* CriaAmigos(){
    Amigos* a = malloc(sizeof(Amigos));
    a->prim = a->ult = NULL;
    return a;
}

void InsereAmigo(Amigos* a, Pessoa* p){
    Cel* c = malloc(sizeof(Cel));
    c->pessoa = p;
    c->prox = NULL;
    c->ant = a->ult;

    if(a->prim == NULL){
        a->prim = c;
    }

    if(a->ult){
        a->ult->prox = c;
    }
    a->ult = c;
}

void RemoveAmigo(Amigos* a, Pessoa* p){
    Cel* c = a->prim;
    while (c){
        if(c->pessoa == p){
            break;
        }
        c = c->prox;
    }

    if(c == NULL){
        return;
    }
    
    if(c->prox == NULL){
        a->ult = c->ant;
    }
    if(c->ant == NULL){
        a->prim = c->prox;
    }

    if(c->ant){
        c->ant->prox = c->prox;
    }
    if(c->prox){
        c->prox->ant = c->ant;
    }

    free(c);
}

void LiberaAmigos(Amigos* a){
    Cel* c, * aux = a->prim;
    while(aux){
        c = aux;
        aux = aux->prox;
        free(c);
    }
    free(a);
}

void LiberaPessoa(Pessoa* p){
    free(p->nome);
    LiberaAmigos(p->amigos);
    free(p);
}

int ExisteEmAmigos(Amigos* a, Pessoa* p){
    Cel* c = a->prim;
    while (c){
        if(c->pessoa == p){
            return 1;
        }
        c = c->prox;
    }
    return 0;
}