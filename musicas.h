#ifndef musicas_h
#define musicas_h

#include <stdio.h>

typedef struct musica Musica;

typedef struct playlist Playlist;

Musica* CriaMusica(char* nome, char* artista);

Playlist* CriaPlaylist(char* nome);

void InsereMusica(Playlist* p, Musica* m);

void RemoveMusica(Playlist* p, Musica* m);

void LiberaPlaylist(Playlist* p);

void LiberaMusica(Musica* m);

int ExisteEmPlaylist(Playlist* p, Musica* m);

char* RetornaNomeArtista(Musica *m);


#endif