#ifndef pessoas_h
#define pessoas_h

#include <stdio.h>
#include "musicas.h"

#define Amizade 0
#define ListaGeral 1

typedef struct lista Lista;

typedef Lista Amigos;

typedef struct pessoa Pessoa;

//Cria uma pessoa, com nome, lista de amizade e lista de playlists
Pessoa* CriaPessoa(char* nome);

//Cria uma lista de pessoas vazia
Amigos* CriaListPessoas();

//Insere pessoa na lista de pessoas
void InserePessoa(Amigos* a, Pessoa* p);

//Remove pessoa da lista de pessoas
void RemovePessoa(Amigos* a, Pessoa* p);

/*Libera lista de pessoas e dependendo da situação libera as pessoas tbm.
Se for uma lista de amigos, op = 0 e não libera as pessoas
Se for uma lista de pessoas geral, op = 1 e libera as pessoas
*/
void LiberaListPessoas(Amigos* a, int op);

//Libera uma pessoa, seu nome, lista de amigos e lista de playlists
void LiberaPessoa(Pessoa* p);

//Verifica se uma pessoa está presente em uma lista de amigos/pessoas
int ExisteEmAmigos(Amigos* a, Pessoa* p);

//Retorna a pessoa caso ela seja encontrada na lista
Pessoa *EncontraPessoaNaLista(char *nome, Lista* pessoas);

/*Relaciona dois amigos
Compara seus nomes até encontrar quais pessoas eles são
Salva um na lista de amigos do outro
*/
void RelacionaAmigos(char* nome1, char* nome2, Lista* pessoas);

//Insere a playlist na lista de playlists da pessoa cujo nome foi passado como parâmetro
void InserePLNaPessoa(char *nome, Lista *pessoas, Playlist *pl);

//Lê cada arquivo de playlist e insere seu conteúdo dentro da lista de playlists de cada pessoa
void LeArquivosDePlaylist(Lista *pessoas, char *diretorio);

#endif