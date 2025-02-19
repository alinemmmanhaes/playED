//
//  playlists.h
//  Lista de Playlists
//
//  Created by Aline Manhães and Marcela Carpenter on 20/05/24.
//
#ifndef playlists_h
#define playlists_h

#include <stdio.h>
#include "musicas.h"

typedef struct listPL ListPL;

//Cria uma lista de playlists vazia
ListPL* CriaListPL();

//Insere playlist na lista de playlists
void InserePlaylist(Playlist* p, ListPL* l);

//Remove playlist da lista de playlists
void RemovePlaylist(Playlist* p, ListPL* l);

//Libera lista de playlists e suas playlists
void LiberaListPL(ListPL* l);

//Verifica se uma playlist se encontra na lista de playlists
int ExisteEmListPL(Playlist* p, ListPL* l);

//Calcula o numero de playlists na lista
int NumeroPlaylistsEmListPL(ListPL* l);

/*
Para cada playlist dentro da lista de playlists, le seu arquivo e adiciona suas músicas
*/
void InsereMusicasNasPLSDaPessoa(ListPL* l, char *diretorio);

/*
Para cada lista de playlists, analisa as suas playlists
Faz a análise para criar uma nova playlist para cada artista presente nas músicas
*/
void OrganizaListPLPorArtista(ListPL* l);

/*
Compara o nome em parâmetro com o nome das playlists na lista
Retorna a playlist que tem o mesmo nome do parâmetro
Ou NULL se não houver playlist com o nome do parâmetro
*/
Playlist* ComparaNomePLArtista(char* nome, ListPL* lista);

//Printa o número de playlists na lista e seus nomes no arquivo “played-refatorada.txt”
void PLsPlayedRefatorada(ListPL* l, FILE* arq);

//Gera um arquivo txt para cada playlist da lista de playlists, usando o diretório do parâmetro
void CriaArquivosPlaylist(ListPL* l, char* diretorio);

//Compara 2 listas de playlists e retorna a qtd de musicas similares
int ComparaPlaylists(ListPL *l1, ListPL *l2);

//Realiza o merge entre duas listas de playlists, quando existirem playlists de mesmo nome em ambas as listas
void MergePlaylists(ListPL *l1, ListPL *l2);

#endif