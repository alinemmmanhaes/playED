#ifndef musicas_h
#define musicas_h

#include <stdio.h>

typedef struct musica Musica;

typedef struct playlist Playlist;

//Cria uma música com nome e artista
Musica* CriaMusica(char* nome, char* artista);

//Cria uma playlist (lista de músicas) com o nome passado por parâmetro, mas sem músicas
Playlist* CriaPlaylist(char* nome);

//Insere música na playlist
void InsereMusica(Playlist* p, Musica* m);

//Remove música da playlist
void RemoveMusica(Playlist* p, Musica* m);

//Libera uma playlist e suas músicas
void LiberaPlaylist(Playlist* p);

//Libera música
void LiberaMusica(Musica* m);

//Verifica se uma música está contida em uma playlist
int ExisteEmPlaylist(Playlist* p, Musica* m);

//Retorna o nome do artista de uma música
char* RetornaNomeArtista(Musica *m);

//Retorna o nome de uma playlist
char* RetornaNomePlaylist(Playlist *p);

/*Para cada playlist, analisa as suas músicas
Faz a análise para criar uma nova playlist para cada artista presente nas músicas
Se o artista da música já tiver uma playlist, adiciona a música na playlist
Se não, cria uma playlist, adiciona a ListPL e adiciona a música na playlist*/
void OrganizaPlaylistPorArtista(Playlist* p, void* lista);

//Imprime cada música da playlist no arquivo passado por parâmetro no formato "artista - nomedamúsica"
void ImprimePlaylistEmArquivo(Playlist* p, FILE* arq);

#endif