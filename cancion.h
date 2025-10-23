#ifndef CANCION_H
#define CANCION_H
#include <string>
#include <iostream>
#include "estructuras.h"

class Cancion {
private:
    int identificador;
    string nombre;
    int duracion;
    string rutaAudio128;
    string rutaAudio320;
    int reproducciones;

public:
    Cancion();
    Cancion(int id, const string& n, int d, const string& r128, const string& r320);
    Cancion(const Cancion& otro);

    // getters/setters
    int getIdentificador() const;
    string getNombre() const;
    int getDuracion() const;
    string getRutaAudio128() const;
    string getRutaAudio320() const;
    int getReproducciones() const;

    void setIdentificador(int id);
    void setNombre(const string& n);
    void setDuracion(int d);
    void setRutaAudio128(const string& r);
    void setRutaAudio320(const string& r);

    // específicos
    void incrementarReproducciones();
    int getCodigoArtista() const;
    int getCodigoAlbum() const;
    int getCodigoCancion() const;

    // operadores
    bool operator==(const Cancion& otro) const;
    bool operator!=(const Cancion& otro) const;
    friend ostream& operator<<(ostream& os, const Cancion& cancion);
};

#endif





