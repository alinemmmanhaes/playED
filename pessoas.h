#ifndef pessoas_h
#define pessoas_h

#include <stdio.h>

typedef struct amigos Amigos;

typedef struct pessoa Pessoa;

Pessoa* CriaPessoa(char* nome);

Amigos* CriaAmigos();

void InsereAmigo(Amigos* a, Pessoa* p);

void RemoveAmigo(Amigos* a, Pessoa* p);

void LiberaAmigos(Amigos* a);

void LiberaPessoa(Pessoa* p);

int ExisteEmAmigos(Amigos* a, Pessoa* p);

#endif