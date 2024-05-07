#ifndef playlists_h
#define playlists_h

#include <stdio.h>
#include "musicas.h"

typedef struct listas Listas;

Listas* CriaLista();

void InserePlaylist(Playlist* p, Listas* l);

void RemovePlaylist(Playlist* p, Listas* l);

void LiberaLista(Listas* l);

int ExisteEmLista(Playlist* p, Listas* l);

#endif