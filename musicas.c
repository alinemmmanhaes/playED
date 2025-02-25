//
//  musicas.c
//
//  Created by Aline Manhães and Marcela Carpenter on 20/05/24.
//
#include "musicas.h"
#include "playlists.h"
#include <stdlib.h>
#include <string.h>

struct musica{
    char* nome;
    char* artista;
};

typedef struct cel Cel;

struct playlist{
    char *nome;
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

Playlist* CriaPlaylist(char* nome){
    Playlist* p = malloc(sizeof(Playlist));
    p->nome = strdup(nome);
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

    LiberaMusica(c->music);
    free(c);
}

void LiberaMusica(Musica* m){
    if(m != NULL){
        free(m->nome);
        free(m->artista);
        free(m);
    }
}

void LiberaPlaylist(Playlist* p, int op){
    Cel *prox = NULL, *atual = p->prim;
    
    while(atual){
        prox = atual->prox;
        if(op == UsoGeral){
            LiberaMusica(atual->music);
        }
        free(atual);
        atual = prox;
    }
    
    free(p->nome);
    free(p);
}

int ExisteEmPlaylist(Playlist* p, Musica* m){
    Cel* c = p->prim;
    while(c){
        if(strcmp(c->music->nome, m->nome) == 0){
            return 1;
        }
        c = c->prox;
    }
    return 0;
}

char* RetornaNomeArtista(Musica *m){
    return m->artista;
}

char* RetornaNomeMusica(Musica *m){
    return m->nome;
}

char* RetornaNomePlaylist(Playlist *p){
    return p->nome;
}

void OrganizaPlaylistPorArtista(Playlist* p, void* lista){
    Cel* c = p->prim;
    ListPL* listaPL = (ListPL*) lista;
    while(c){
        char artista[100];
        sprintf(artista, "%s.txt", c->music->artista);
        Playlist* playlist = ComparaNomePLArtista(artista, listaPL);
        if(playlist){
            if(!ExisteEmPlaylist(playlist, c->music)){
                InsereMusica(playlist, c->music);
            }
            else{
                LiberaMusica(c->music);
            }
        }
        else{
            playlist = CriaPlaylist(artista);
            InsereMusica(playlist, c->music);
            InserePlaylist(playlist, listaPL);
        }
        c = c->prox;
    }
}

void ImprimePlaylistEmArquivo(Playlist* p, FILE* arq){
    Cel* c = p->prim;
    while(c){
        fprintf(arq, "%s - %s\n", c->music->artista, c->music->nome);
        c = c->prox;
    }
}

int ComparaMusicas(Playlist *p1, Playlist *p2){
    Cel* c1 = p1->prim;
    Cel* c2= p2->prim;
    int qtd = 0;
    while(c1){
        while(c2){
            if(strcmp(c1->music->nome, c2->music->nome) == 0 && strcmp(c1->music->artista, c2->music->artista) == 0){ 
                qtd++;
                break;
            }
            c2 = c2->prox;
        }
        c1 = c1->prox;
        c2= p2->prim;
    }
    return qtd;
}

int ComparaNomePlaylists(Playlist *p1, Playlist *p2){
    if(strcmp(p1->nome, p2->nome) == 0){
        return 1;
    }
    return 0;
}

void *MergeMusicas(Playlist *p1, Playlist *p2){
    Cel* c1 = p1->prim;
    Cel* c2= p2->prim;
    
    while(c1){
        int flag = 0;
        c2 = p2->prim;
        while(c2){
            //Sinaliza caso as músicas sejam iguais, e sai do loop
            if(strcmp(c1->music->nome, c2->music->nome) == 0){
                flag = 0;
                break;
            }
            //Sinaliza que as músicas são diferentes
            else {
                flag = 1;
            }
            c2 = c2->prox;
        }
        //Se as músicas não forem iguais, adiciona a música da p1 à p2
        if(flag){
            Musica *m = CriaMusica(c1->music->nome, c1->music->artista);
            InsereMusica(p2, m);
        }
        c1 = c1->prox;
    }

}

