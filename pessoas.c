#include "pessoas.h"
#include "playlists.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct pessoa{
    char* nome;
    Amigos* amigos;
    ListPL* playlists;
    int jaAnalisada;
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
    p->amigos = CriaListPessoas();
    p->playlists = CriaListPL();
    p->jaAnalisada = 0;
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

    LiberaPessoa(c->pessoa);
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
    LiberaListPessoas(p->amigos, Amizade);
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

Pessoa *EncontraPessoaNaLista(char *nome, Lista* pessoas){
    Pessoa* p = NULL;
    Cel* c = pessoas->prim;
    while (c){
        if(strcmp(c->pessoa->nome, nome) == 0){
            p = c->pessoa;
            break;
        }
        c = c->prox;
    }
    return p;
}

void RelacionaAmigos(char* nome1, char* nome2, Lista* pessoas){
    Pessoa* pessoa1 = NULL, *pessoa2 = NULL;

    pessoa1 = EncontraPessoaNaLista(nome1, pessoas);
    pessoa2 = EncontraPessoaNaLista(nome2, pessoas);
    
    if(pessoa1 && pessoa2){
        InserePessoa(pessoa1->amigos, pessoa2);
        InserePessoa(pessoa2->amigos, pessoa1);
    }
}

void InserePLNaPessoa(char *nome, Lista *pessoas, Playlist *pl){
    Pessoa* pessoa = EncontraPessoaNaLista(nome, pessoas);
    InserePlaylist(pl, pessoa->playlists);
}

void LeArquivosDePlaylist(Lista *pessoas, char *diretorio){
    Cel* c = pessoas->prim;
    while (c){
        InsereMusicasNasPLSDaPessoa(c->pessoa->playlists, diretorio);
        c = c->prox;
    }
}

void OrganizaPessoaPorArtista(Lista* pessoas){
    Cel* c = pessoas->prim;
    while (c){
        OrganizaListPLPorArtista(c->pessoa->playlists);
        c = c->prox;
    }
}

void GeraPlayedRefatorada(Lista* pessoas){
    FILE* PlayedRef;
    char folder[1000], nomeArq[1100];

    sprintf(folder, "Saida"); 
    mkdir(folder, S_IRWXU);

    sprintf(nomeArq, "%s/played-refatorada.txt", folder);
    PlayedRef = fopen(nomeArq, "w");

    Cel* c = pessoas->prim;
    while(c){
        fprintf(PlayedRef, "%s;", c->pessoa->nome);
        PLsPlayedRefatorada(c->pessoa->playlists, PlayedRef);
        fprintf(PlayedRef, "\n");
        c = c->prox;
    }

    fclose(PlayedRef);
}

/*void CriaNovosArquivosPessoa(Lista* pessoas){
    Cel* c = pessoas->prim;
    while(c){
        char folder[1000];
        sprintf(folder, "Saida/%s", c->pessoa->nome);
        mkdir(folder, S_IRWXU);
        CriaArquivosPlaylist(c->pessoa->playlists, folder);
        c = c->prox;
    }
}*/

int PessoaJaFoiAnalisada(Lista *pessoas, Pessoa *p1, Pessoa *p2){
    Cel* c = pessoas->prim;
    while(c){
        if(strcmp(c->pessoa->nome, p2->nome) == 0){ 
            return 1;
        }
        else if(strcmp(c->pessoa->nome, p1->nome) == 0){
            return 0;
        }
        c = c->prox;
    }
    return 0;
}


void VerificaSimilaridades(Lista* pessoas){
    FILE* Similaridades;
    char nomeArq[1100];

    sprintf(nomeArq, "Saida/similaridades.txt");
    Similaridades = fopen(nomeArq, "w");

    Cel* c = pessoas->prim;
    Cel* p = c->pessoa->amigos->prim;
    while(c){
        p = c->pessoa->amigos->prim;
        while(p){
            //Verifica se a pessoa já foi analisada anteriormente
            if(p->pessoa->jaAnalisada == 0){
                int similar = ComparaPlaylists(c->pessoa->playlists, p->pessoa->playlists);
                fprintf(Similaridades, "%s;%s;%d\n", c->pessoa->nome, p->pessoa->nome, similar);
            }
            p = p->prox;
        }
        c->pessoa->jaAnalisada = 1;
        c = c->prox;
    }
    
    fclose(Similaridades);
}

void ZeraAnalisePessoas(Lista *pessoas){
    Cel *c = pessoas->prim;
    while(c){
        c->pessoa->jaAnalisada = 0;
    }
}
void RealizaMergePlaylists(Lista* pessoas){
    Cel *c = pessoas->prim;
    Cel *p = c->pessoa->amigos->prim;
    
    ZeraAnalisePessoas(pessoas);

    while(c){
        p = c->pessoa->amigos->prim;
        while(p){
            if(p->pessoa->jaAnalisada == 0){
                MergePlaylists(c->pessoa->playlists, p->pessoa->playlists);
            }
            p = p->prox;
        }
        c->pessoa->jaAnalisada = 1;
        c = c->prox;
    }
}

void CriaNovosArquivosPessoa(Lista* pessoas, int op){
    Cel* c = pessoas->prim;
    while(c){
        char folder[1000];
        if(op == Merge){
            sprintf(folder, "Saida/Merge/%s", c->pessoa->nome);
        }
        else {
            sprintf(folder, "Saida/%s", c->pessoa->nome);
        }
        mkdir(folder, S_IRWXU);
        CriaArquivosPlaylist(c->pessoa->playlists, folder);
        c = c->prox;
    }
}