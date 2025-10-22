#include "reproductor.h"
#include "cancion.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

Reproductor::Reproductor() : numArtistas(0) {}

void Reproductor::init_demo_catalogo() {
    numArtistas = 1;

    Artista &ar = artistas[0];
    ar.idArtista = 12031;
    ar.edad = 30;
    std::strcpy(ar.pais, "Colombia");
    ar.seguidores = 1000;
    ar.rank_tendencias = 8;

    ar.numAlbums = 1;
    Album &al = ar.albums[0];
    al.idAlbum = 1;
    al.idArtista = ar.idArtista;
    std::strcpy(al.nombre, "Lugar Secreto");
    std::strcpy(al.portada_png, "C:/tmp/portada.png"); // ruta dummy segura
    al.numCanciones = 0;

    // Cancion 1
    Cancion &c1 = al.canciones[al.numCanciones++];
    c1.id9 = 120310101; c1.idArtista = ar.idArtista; c1.idAlbum = al.idAlbum;
    c1.dur_seg = 222;
    std::strcpy(c1.nombre, "A tu lado");
    std::strcpy(c1.ruta_base, "C:/tmp/a_tu_lado");

    // Cancion 2
    Cancion &c2 = al.canciones[al.numCanciones++];
    c2.id9 = 120310102; c2.idArtista = ar.idArtista; c2.idAlbum = al.idAlbum;
    c2.dur_seg = 255;
    std::strcpy(c2.nombre, "Caminos");
    std::strcpy(c2.ruta_base, "C:/tmp/caminos");
}

void Reproductor::reproducirAleatorio(int /*tipoUsuario*/, int K, bool premium) {
    if (numArtistas <= 0) { std::printf("Sin catalogo.\n"); return; }
    Album &al = artistas[0].albums[0];
    if (al.numCanciones <= 0) { std::printf("Sin canciones.\n"); return; }

    static bool seeded = false;
    if (!seeded) { std::srand((unsigned)std::time(nullptr)); seeded = true; }

    for (int i = 0; i < K; ++i) {
        int idx = std::rand() % al.numCanciones; // seguro: >0
        Cancion &c = al.canciones[idx];
        char ruta[300]; c.rutaAudio(premium ? 320 : 128, ruta);
        std::printf("\n--- Reproduciendo ---\nAlbum: %s\nPortada: %s\nCancion: %s\nArchivo: %s\nDuracion: %d seg\n",
                    al.nombre, al.portada_png, c.nombre, ruta, c.dur_seg);
    }
}

