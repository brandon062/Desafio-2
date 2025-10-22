#ifndef REPRODUCTOR_H
#define REPRODUCTOR_H
#include "artista.h"

struct Reproductor {
    static const int MAX_ART = 8;
    Artista artistas[MAX_ART];
    int numArtistas;

    Reproductor();
    void init_demo_catalogo();
    void reproducirAleatorio(int tipoUsuario, int K, bool premium);
};
#endif


