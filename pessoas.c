#include "pessoas.h"
#include "playlists.h"
#include <stdlib.h>
#include <string.h>

struct pessoa{
    char* nome;
    Amigos* amigos;
    ListPL* playlists;
};

typedef struct cel Cel;

struct lista{
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
    p->playlists = CriaListPL();
    return p;
}

Amigos* CriaListPessoas(){
    Amigos* a = malloc(sizeof(Amigos));
    a->prim = a->ult = NULL;
    return a;
}

void InserePessoa(Amigos* a, Pessoa* p){
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

void RemovePessoa(Amigos* a, Pessoa* p){
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

void LiberaListPessoas(Amigos* a, int op){
    Cel* c, * aux = a->prim;
    while(aux){
        c = aux;
        aux = aux->prox;
        if(op == ListaGeral){
            LiberaPessoa(c->pessoa);
        }
        free(c);
    }
    free(a);
}

void LiberaPessoa(Pessoa* p){
    free(p->nome);
    LiberaAmigos(p->amigos, Amizade);
    LiberaListPL(p->playlists);
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

void RelacionaAmigos(char* nome1, char* nome2, Lista* pessoas){
    Pessoa* pessoa1 = NULL, *pessoa2 = NULL;
    Cel* c = pessoas->prim;
    while (c){
        if(strcmp(c->pessoa->nome, nome1) == 0){
            pessoa1 = c->pessoa;
            break;
        }
        c = c->prox;
    }

    c = pessoas->prim;
    while (c){
        if(strcmp(c->pessoa->nome, nome2) == 0){
            pessoa2 = c->pessoa;
            break;
        }
        c = c->prox;
    }

    if(pessoa1 && pessoa2){
        InsereAmigo(pessoa1->amigos, pessoa2);
        InsereAmigo(pessoa2->amigos, pessoa1);
    }
}