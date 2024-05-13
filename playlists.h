#ifndef playlists_h
#define playlists_h

#include <stdio.h>
#include "musicas.h"

typedef struct listPL ListPL;

//Cria uma lista de playlists vazia
ListPL* CriaLista();

//Insere playlist na lista de playlists
void InserePlaylist(Playlist* p, ListPL* l);

//Remove playlist da lista de playlists
void RemovePlaylist(Playlist* p, ListPL* l);

//Libera lista de playlists e suas playlists
void LiberaListPL(ListPL* l);

//Verifica se uma playlist se encontra na lista de playlists
int ExisteEmListPL(Playlist* p, ListPL* l);

/*Para cada playlist dentro da lista de playlists, le seu arquivo e adiciona suas músicas
*/
void InsereMusicasNasPLSDaPessoa(ListPL* l, char *diretorio);

#endif