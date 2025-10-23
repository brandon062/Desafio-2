#ifndef ARTISTA_H
#define ARTISTA_H
#include <string>
#include <iostream>
#include "estructuras.h"

class Artista {
private:
    int codigo;
    int edad;
    string pais;

public:
    Artista();
    Artista(int c, int e, const string& p);
    Artista(const Artista& otro);

    // getters/setters
    int getCodigo() const;
    int getEdad() const;
    string getPais() const;
    void setCodigo(int c);
    void setEdad(int e);
    void setPais(const string& p);

    // operadores
    bool operator==(const Artista& otro) const;
    bool operator!=(const Artista& otro) const;

    friend ostream& operator<<(ostream& os, const Artista& artista);
};

#endif






